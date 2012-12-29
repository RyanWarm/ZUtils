#include <sys/dir.h>
#include <sys/types.h>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include "Server.hpp"
#include "Session.hpp"
#include "UserSearchSession.hpp"
#include "JobSearchSession.hpp"
#include "CompanyContactsKeeper.hpp"
#include "CompanyScoreKeeper.hpp"

Server::Server(boost::asio::io_service& io_service,
			short port,
            const char * index_dir,
            server_type_t server_type,
            const string &mongodb_addr,
            const string &company_list_filename,
            const string &company_score_filename)
: io_service_(io_service),
	acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
    m_index_dir(index_dir),
    m_com_contacts(0),
    m_com_score(0),
    m_mongodb_addr(mongodb_addr),
    m_company_list_filename(company_list_filename),
    m_company_score_filename(company_score_filename),
    thread_num(4),
    db_pool_size(1),
    m_server_type(server_type)
{
}
Server::~Server()
{
}
bool
Server::init()
{
    if(m_server_type == SERVER_TYPE_USER){
        m_com_contacts = new CompanyContactsKeeper(m_mongodb_addr,m_company_list_filename);
        if(m_com_contacts->init()==false){
            return false;
        }
    }
    if(m_server_type == SERVER_TYPE_JOB){
        m_com_score = new CompanyScoreKeeper(m_company_score_filename);
        if(m_com_score->init()==false){
            return false;
        }
    }
    pthread_mutex_init(&m_db_lock,0);
    pthread_cond_init(&m_db_cond,0);
    for(size_t i=0;i<db_pool_size;i++){
        m_dbs.push_back(new Xapian::Database(m_index_dir));
        m_dbs_busy.push_back(false);
    }
    Session* new_session = create_session();
    new_session->init();
    acceptor_.async_accept(new_session->socket(),
		boost::bind(&Server::handle_accept, this, new_session,
		boost::asio::placeholders::error));
   return true; 
}

Session *
Server::create_session(){
    if(m_server_type == SERVER_TYPE_USER){
        return dynamic_cast<Session *>(new UserSearchSession(io_service_,this));
    }else if(m_server_type == SERVER_TYPE_JOB){
        return dynamic_cast<Session *>(new JobSearchSession(io_service_,this));
    }else{
        assert(0);
        return NULL;
    }
}

Xapian::Database * 
Server::fetch_db()
{
    pthread_mutex_lock(&m_db_lock);
    Xapian::Database *db = 0;
    while(db == NULL){
        for(size_t i=0;i<db_pool_size;i++){
            if(m_dbs_busy[i] == false){
                m_dbs_busy[i] = true;
                db = m_dbs[i];
                break;
            }
        }
        if(db == NULL){
            pthread_cond_wait(&m_db_cond, &m_db_lock);
        }    
    } 
    pthread_mutex_unlock(&m_db_lock);
    TB_DEBUG("fetch db "<<db);
    return db;
}
void 
Server::release_db(Xapian::Database *db)
{
    TB_DEBUG("release db "<<db);
    pthread_mutex_lock(&m_db_lock);
    for(size_t i=0;i<db_pool_size;i++){
        if(m_dbs[i] == db){
            m_dbs_busy[i] = false;
            break;
        }
    }
    pthread_mutex_unlock(&m_db_lock);
    pthread_cond_signal(&m_db_cond);
}

int Server::run()
{
    // Create a pool of threads to run all of the io_services.
    size_t thread_pool_size_ = thread_num;
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < thread_pool_size_; ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
                    boost::bind(&boost::asio::io_service::run, &io_service_)));
        threads.push_back(thread);
    }

    // Wait for all threads in the pool to exit.
    for (std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join(); 
    return 0; 
}

int Server::stop()
{
    io_service_.stop();
    return 0;
}

void Server::handle_accept(Session* new_session,
        const boost::system::error_code& error)
{
    if (!error)
    {
        new_session->start();
        new_session = create_session();
        new_session->init();
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&Server::handle_accept, this, new_session,
                    boost::asio::placeholders::error));
    }
    else
    {
        delete new_session;
    }
}

