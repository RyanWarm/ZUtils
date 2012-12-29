#pragma once
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "Def.hpp" 
#include "Types.hpp" 
#include "Server.hpp" 
#include "SearchQuery.hpp" 

using boost::asio::ip::tcp;

class Server;
class Session
{
public:
    Session(boost::asio::io_service& io_service, Server * server);
    virtual ~Session();
    int init(){
        return 0;
    }
    tcp::socket& socket()
    {
        return m_incoming_socket;
    }
    virtual void reset() {}; 
    void start();
    void recv_expect_len(const boost::system::error_code& error,size_t bytes_transferred);
    void handle_query(const boost::system::error_code& error, size_t bytes_transferred); 
    uint64_t bigending(uint64_t u);
    void handle_end(const boost::system::error_code& error);
    void handle_error(const boost::system::error_code& error);
    void handle_close();

    uint32_t m_qualified_matches;
    virtual Xapian::Weight *weighter(Xapian::Database *db) = 0;
    virtual SearchQuery *search_query() = 0;
    virtual bool serialize_result(Xapian::MSet &matches, string &resp) = 0;
    inline Server * server(){ return m_server; }
private:
    const static uint32_t BUFFER_SIZE = 10*1024*1024;
     
    tcp::socket m_incoming_socket;
    tcp::socket m_svr_socket;
    Server * m_server;
    boost::asio::io_service& m_io_service;
    Xapian::Enquire *m_enquire;
    Xapian::Database *m_db;

    char m_buffer[BUFFER_SIZE];
    int m_recv_len;
    int m_expect_len;
    unsigned m_response_length;
    string m_response;

    timeval m_tv_start;
    timeval m_tv_end;
    
    uint32_t session_id;
};

