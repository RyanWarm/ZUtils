#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <pthread.h>
#include "Def.hpp"

using boost::asio::ip::tcp;
using namespace std;

class Session;
class CompanyContactsKeeper;
class CompanyScoreKeeper;

class Server
{
public:
    typedef enum{
        SERVER_TYPE_USER = 0,
        SERVER_TYPE_JOB
    } server_type_t;
    Server(boost::asio::io_service& io_service,
            short port,
            const char * index_dir,
            server_type_t server_type,
            const string &mongodb_addr,
            const string &company_list_filename,
            const string &company_score_filename);
    ~Server();
    bool init();
    Session *create_session();
    int run();
    int stop();

    void handle_accept(Session* new_session,
            const boost::system::error_code& error);
    Xapian::Database *fetch_db();
    void release_db(Xapian::Database *db);
private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;

    string   m_index_dir; 
    vector<Xapian::Database *> m_dbs;
    vector<bool> m_dbs_busy;
public: 
    CompanyContactsKeeper *m_com_contacts;
    CompanyScoreKeeper *m_com_score;
    string m_mongodb_addr;
    string m_company_list_filename;
    string m_company_score_filename;
private:
    size_t thread_num;
    size_t db_pool_size;
    pthread_mutex_t m_db_lock;
    pthread_cond_t  m_db_cond;
    
    server_type_t m_server_type; 
};

