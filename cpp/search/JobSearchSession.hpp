#pragma once
#include "JobSearchQuery.hpp"
#include "Session.hpp"

class JobSearchWeight;
class JobSearchSession : public Session
{
public:
    typedef google::sparse_hash_map<uint64_t, std::string> mid_data_recorder_t;
public:
    JobSearchSession(boost::asio::io_service& ioservice, Server* server)
        :Session(ioservice, server),
        m_query(m_stats)
    {
    }
    virtual void reset();
    virtual Xapian::Weight *weighter(Xapian::Database *db);
    virtual SearchQuery *search_query() {
        return dynamic_cast<SearchQuery *>(&m_query);
    }
    virtual bool serialize_result(Xapian::MSet &matches, string &resp);

public:
    mid_data_recorder_t m_mid_data_recorder;
    SearchStats m_stats;
private:
    JobSearchQuery m_query;
    JobSearchWeight *m_weight;
};

