#pragma once
#include <iostream>
#include <xapian.h>
#include "Types.hpp"
#include "UserDistance.hpp"
#include "SearchStats.hpp"
#include "SearchQuery.hpp"
#include "JobSearchQuery.pb.h"
using namespace job_search;

class JobSearchQuery : public SearchQuery
{
public:
    JobSearchQuery(SearchStats &stats)
        :SearchQuery(stats)
    {}
    bool loads(const char *buffer,unsigned len);
    void reset(){
        pb_query = PbJobSearchQuery();
        search_query = Xapian::Query();
        m_distance.reset();
        m_matchings.clear();
        m_query_weight.clear();
        m_query_expansion.clear();
        m_tag_num_in_query = 0;
        searcher_uid = 0;
        search_type = 0;
        task_type = TASK_SEARCH;
        m_offset = 0;
        m_count = 0;
    }
    virtual Xapian::Query &xapian_query(){
        return search_query;
    }
    virtual unsigned offset(){
        return m_offset;
    }
    virtual unsigned count(){
        return m_count;
    }
public:
    PbJobSearchQuery pb_query;
    Xapian::Query search_query;
    matchings_t m_matchings;
    query_weight_t m_query_weight;
    query_expansion_t m_query_expansion;
    unsigned m_tag_num_in_query;
    unsigned m_pos_num_in_query;
    uint64_t searcher_uid;    
    uint32_t search_type;
    task_type_t task_type;

    unsigned m_offset;
    unsigned m_count;
    
    UserDistance m_distance;
};

