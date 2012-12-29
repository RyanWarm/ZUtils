#pragma once
#include "UserSearchQuery.hpp"
#include "Session.hpp"

class ComContactsKeeper;
class UserSearchWeight;
class UserSearchSession : public Session
{
    friend class UserSearchWeight;
public:
    typedef google::sparse_hash_map<uint64_t, std::string> mid_data_recorder_t;
public:
    UserSearchSession(boost::asio::io_service& ioservice, Server* server)
        :Session(ioservice, server),
        m_com_contacts(server->m_com_contacts),
        m_query(m_stats,m_com_contacts),
        m_weight(0),
        name_score(0)
    {
    }
    ~UserSearchSession();
    virtual void reset();
    virtual Xapian::Weight *weighter(Xapian::Database *db);
    virtual SearchQuery *search_query() {
        return dynamic_cast<SearchQuery *>(&m_query);
    }
    virtual bool serialize_result(Xapian::MSet &matches, string &resp);

public: 
    mid_data_recorder_t m_mid_data_recorder;
    SearchStats m_stats;
    CompanyContactsKeeper *m_com_contacts;
private:
    UserSearchQuery m_query;
    UserSearchWeight *m_weight;
     
    mutable double name_score;
};

