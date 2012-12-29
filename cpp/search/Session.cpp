#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>
#include <time.h>
#include "Session.hpp"
#include "Def.hpp"
#include "Utils.hpp"

using boost::asio::ip::tcp;
using namespace boost;
using namespace std;

static uint32_t uuid = 0;

Session::Session(boost::asio::io_service& io_service, Server * server)
    :m_incoming_socket(io_service),
    m_svr_socket(io_service),
    m_server(server),
    m_io_service(io_service),
    m_enquire(0),
    session_id(uuid++)
{
}
Session::~Session()
{
}
void Session::start()
{
    TB_INFO("session"<<session_id<<",waiting data from client...");
    search_query()->reset();
    m_qualified_matches = 0;
    m_recv_len = 0;
    m_expect_len = 0;
    reset();
    m_incoming_socket.async_read_some(boost::asio::buffer(&m_expect_len, sizeof(int)),
            boost::bind(&Session::recv_expect_len, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void Session::recv_expect_len(const boost::system::error_code& error,size_t bytes_transferred)
{
    if (error){
        return handle_error(error);
    }
    if(bytes_transferred != sizeof(int) || m_expect_len <= 0){
        return handle_close();
    }
    TB_DEBUG("recved "<<bytes_transferred<<" bytes");
    m_incoming_socket.async_read_some(boost::asio::buffer(m_buffer, BUFFER_SIZE),
            boost::bind(&Session::handle_query, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

}
uint64_t Session::bigending(uint64_t u)
{
    uint64_t b=0;
    char * bc = (char *)&b;
    for(int i=0;i<8;i++){
        bc[7-i] = (char)(u | 0xFF);
        u >>= 8;
    }
    return b;
}
void Session::handle_query(const boost::system::error_code& error,size_t bytes_transferred) 
{
    if (error){
        return handle_error(error);
    }
    if(bytes_transferred==0){
        return handle_close();
    }
    if((m_recv_len+=bytes_transferred) < m_expect_len && (size_t)m_recv_len<BUFFER_SIZE){
        return m_incoming_socket.async_read_some(boost::asio::buffer(m_buffer+m_recv_len, BUFFER_SIZE-m_recv_len),
                boost::bind(&Session::handle_query, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }
    gettimeofday(&m_tv_start,0); 

    //query
    if(search_query()->loads(m_buffer,m_recv_len)==false){
        return handle_close();
    }
    uint64_t offset = search_query()->offset();
    uint64_t count = search_query()->count();
    
    TB_DEBUG("start enquire,offset="<<offset<<",count="<<count);
    //enquire
    m_db = m_server->fetch_db();
    m_enquire = new Xapian::Enquire(*m_db);
    m_enquire->set_weighting_scheme(*this->weighter(m_db));
    m_enquire->set_query(search_query()->xapian_query());
    Xapian::MSet matches; 
    while(1){
        try{
            matches = m_enquire->get_mset(offset,count,100000);
            if(serialize_result(matches,m_response) == false){
                delete m_enquire;
                return handle_close(); 
            }
            break;
        }catch(Xapian::DatabaseModifiedError &e){
            TB_INFO("databas modified error, reopen it");
            m_db->reopen();
            continue;
        }/*catch(Xapian::DatabaseError &e){
            TB_INFO("databas error:"<<e.get_msg()<<", retry");
            continue;
        }*/
    }
    delete m_enquire;
    m_server->release_db(m_db);
    
    std::vector<boost::asio::const_buffer> rbuffer;
    m_response_length = m_response.size();
    rbuffer.push_back(boost::asio::const_buffer(&m_response_length,sizeof(m_response_length)));
    rbuffer.push_back(boost::asio::const_buffer(m_response.data(),m_response.size()));
    TB_DEBUG("resp serialize to string: pb length = "<<m_response_length);

    gettimeofday(&m_tv_end,0);
    timeval tv_cost;
    timersub(&m_tv_end,&m_tv_start,&tv_cost);
    TB_INFO("session"<<session_id<<" search timing: "<<tv_cost.tv_sec<<"."<<tv_cost.tv_usec<<" seconds");
    return  boost::asio::async_write(m_incoming_socket, 
            rbuffer,
            boost::bind(&Session::handle_end, this, boost::asio::placeholders::error));
}

void Session::handle_end(const boost::system::error_code& error)
{
    if(error){
        return handle_error(error);
    }else{
        TB_INFO("session"<<session_id<<" finished");
        return start();
    }
}

void Session::handle_error(const boost::system::error_code& error)
{
    if(error==boost::asio::error::eof){
        TB_ERROR("session"<<session_id<<" closed by remote peer");
    }else{
        TB_ERROR("session"<<session_id<<" rrror occur:"<<error.message());
    }
    m_incoming_socket.close();
    delete this;
}

void Session::handle_close()
{
    m_incoming_socket.close();
    TB_INFO("session"<<session_id<<" connection closed");
    delete this;
}
