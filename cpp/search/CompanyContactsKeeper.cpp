#include "CompanyContactsKeeper.hpp"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <mongo.h>
#include <openssl/md5.h> 
#include "Def.hpp"

CompanyContactsKeeper::CompanyContactsKeeper(const string &mongodb_addr,const string &company_name_file)
    :m_company_name_file(company_name_file),
    m_mongodb_addr(mongodb_addr),
    m_company_name_hash(0),
    m_uid_set(0)
{
}
CompanyContactsKeeper::~CompanyContactsKeeper()
{
    for(com_contacts_t::iterator it=m_com_contacts.begin();it!=m_com_contacts.end();it++){
        if(it->second != NULL){
            delete it->second;
            it->second = NULL;
        }
    }
}
bool 
CompanyContactsKeeper::init()
{
    if(false == load_company_names(m_company_name_file)){
        return false;
    }
    mongo conn;
    mongo_init( &conn );
    mongo_set_op_timeout( &conn, 1000 );
    size_t pos = m_mongodb_addr.find(':');
    if(pos == string::npos){
        return false;
    }
    const string host = m_mongodb_addr.substr(0,pos);
    int port = strtoul(m_mongodb_addr.substr(pos+1).data(),0,0);
    int status = mongo_client( &conn, host.data(),port);
    if(status != MONGO_OK){
        switch ( conn.err ) {
            case MONGO_CONN_NO_SOCKET:  printf( "mongodb: no socket\n" ); return false;
            case MONGO_CONN_FAIL:       printf( "mongodb: connection failed\n" ); return false;
            case MONGO_CONN_NOT_MASTER: printf( "mongodb: not master\n" ); return false;
            default: printf("mongodb: unkown error\n"); return false;
        } 
    }
    for(size_t i=0;i<m_company_list.size();i++){
        uint64_t company_hash = company_name_hash(m_company_list[i]);
        std::cout<<m_company_list[i]<<": "<<company_hash<<std::endl;
        uid_set_t *uid_set = new uid_set_t;
        m_com_contacts[company_hash] = uid_set;

        bson query[1];
        mongo_cursor cursor[1];
        bson_init( query );
        bson_append_long( query, "_id", company_hash);
        bson_finish( query );
        mongo_cursor_init( cursor, &conn, "company.company_1du_contacts_full" );
        mongo_cursor_set_query( cursor, query );
        if( mongo_cursor_next( cursor ) == MONGO_OK ) {
            bson_iterator iterator[1];
            if ( bson_find( iterator, mongo_cursor_bson( cursor ), "contacts" )) {
                string contacts_str = bson_iterator_string( iterator );
                vector<string> tokens;
                boost::split(tokens, contacts_str, boost::is_any_of(","));
                for(size_t j=0;j<tokens.size();j++){
                    uid_set->insert(strtoul(tokens[j].data(),NULL,0)); 
                }
            }
            std::cout<<uid_set->size()<<" contacts"<<std::endl;
        }else{
            std::cout<<"contacts of company "<<m_company_list[i]<<" not found in mongodb"<<std::endl;
        }
        bson_destroy( query );
        mongo_cursor_destroy( cursor );
    }
    mongo_destroy( &conn );
    return true;
}
void
CompanyContactsKeeper::set_company(const string &company_name)
{
    m_company_name_hash = company_name_hash(company_name);
    com_contacts_t::iterator it = m_com_contacts.find(m_company_name_hash);
    if(it==m_com_contacts.end()){
        m_uid_set = NULL;
    }else{
        m_uid_set = it->second;
    }
}
bool 
CompanyContactsKeeper::check(uint64_t uid)
{
    if(m_uid_set==NULL){
        return false;
    }
    return (m_uid_set->find(uid) != m_uid_set->end());
}
bool 
CompanyContactsKeeper::check(uint64_t company_hash,uint64_t uid)
{
    com_contacts_t::iterator it = m_com_contacts.find(company_hash);
    if(it==m_com_contacts.end()){
        TB_DEBUG("company contacts group not found in CompanyContactsKeeper for company_hash="<<company_hash);
        return false;
    }else{
        return (it->second->find(uid) != it->second->end());
    }
}

uint64_t 
CompanyContactsKeeper::company_name_hash(const string &str)
{
    string str_ = str;
    std::transform(str_.begin(), str_.end(), str_.begin(), ::tolower);
    MD5_CTX ctx;
    unsigned char md[16];
    MD5_Init(&ctx);
    MD5_Update(&ctx,str_.data(),str_.size());
    MD5_Final(md,&ctx);
    return *(uint64_t*)md&(~((uint64_t)1<<63));
}

bool 
CompanyContactsKeeper::load_company_names(const string &filename)
{
    std::ifstream ifs(filename.data());
    if(ifs.is_open() == false){
        return false;
    }
    string line;
    while(getline( ifs, line)){
        m_company_list.push_back(line);
    }
    return true;
}

