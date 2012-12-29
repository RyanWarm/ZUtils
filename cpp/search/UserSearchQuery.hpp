#pragma once
#include <iostream>
#include <xapian.h>
#include "Types.hpp"
#include "UserDistance.hpp"
#include "SearchStats.hpp"
#include "SearchQuery.hpp"
#include "UserSearchQuery.pb.h"
using namespace user_search;

class CompanyContactsKeeper;

class UserSearchQuery : public SearchQuery
{
public:
    UserSearchQuery(SearchStats &stats,CompanyContactsKeeper *keeper)
        :SearchQuery(stats),
        m_cc_keeper(keeper),
        m_searcher_company_hash(0)
    {}
    bool loads(const char *buffer,unsigned len);
    void reset(){
        pb_query = PbUserSearchQuery();
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
        m_searcher_company_hash = 0;
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
    bool link_distance_filter(int distance);
    bool check_com_contacts(uint64_t uid);
    bool company_contacts_filter(uint64_t uid);
    PbUserSearchQuery pb_query;
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
    CompanyContactsKeeper *m_cc_keeper;
    uint64_t m_searcher_company_hash;
};

