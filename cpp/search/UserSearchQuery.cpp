#include <iostream>
#include <vector>
#include <map>
#include "UserSearchQuery.hpp"
#include "Utils.hpp"
#include "Def.hpp"
#include "CompanyContactsKeeper.hpp"
using namespace std;

bool 
UserSearchQuery::loads(const char *buffer,unsigned len){
    if(false == pb_query.ParseFromString(string(buffer,len))){
        TB_INFO("parse query failed");
        return false; 
    }
    
    if(pb_query.has_search_type()){
        search_type = pb_query.search_type();
    }else{
        search_type = 0;
    }
    if(pb_query.has_task_type()){
        task_type = (task_type_t)pb_query.task_type();
    }else{
        task_type = TASK_SEARCH;
    }
    TB_INFO("task type:"<<task_type);    
    m_offset = pb_query.offset();
    m_count = pb_query.count();
    searcher_uid = pb_query.searcher_uid();
    
    //query 
    search_query = Xapian::Query::unserialise(pb_query.xapian_query_blob());
    if(search_query.empty()){
        TB_INFO("empty xapian query");
        return false;
    }
    TB_DEBUG("xapian_query: "<<search_query.get_description());
    map<string,Xapian::termcount> terms_wdf = search_query.get_terms_with_wdf();
    for(map<string,Xapian::termcount>::iterator it=terms_wdf.begin(); it!=terms_wdf.end(); it++){
        string term = it->first;
        double weight = (double)it->second / 1000000;
        if(is_tag_term(term)){
            ++m_tag_num_in_query;
        } else if(is_pos_term(term)){
            ++m_pos_num_in_query;
        }
        TB_DEBUG("query term "<<*(uint64_t *)term.data()<<": "<<weight);
        try{
            m_query_weight[term] = weight;
        }catch(Xapian::InvalidOperationError &e){
            m_query_weight[term] = 1;
        }

    }
    //reserved stats        
    switch(int(task_type)){
        case TASK_STATS_COM:
            for(int i=0;i<pb_query.stats_com_term_size();i++){
                m_stats.reserve_term(pb_query.stats_com_term(i));
            }
            break;
        case TASK_STATS_JOB:
            for(int i=0;i<pb_query.stats_job_term_size();i++){
                m_stats.reserve_term(pb_query.stats_job_term(i));
            }    
        case TASK_STATS_TAG:
            for(int i=0;i<pb_query.stats_tag_term_size();i++){
                m_stats.reserve_term(pb_query.stats_tag_term(i));
            }
            break;
        case TASK_STATS_SCH:
            for(int i=0;i<pb_query.stats_sch_term_size();i++){
                m_stats.reserve_term(pb_query.stats_sch_term(i));
            }
            break;
    }
    //query expansion map
    if(pb_query.te_size()>0){
        std::map<std::string,int> eterm_originals;
        for(int i=0;i<pb_query.te_size();i++){
            const std::string &term = pb_query.te(i).term();
            eterm_originals[term] = 1;
        }
        for(int i=0;i<pb_query.te_size();i++){
            const std::string &term = pb_query.te(i).term();
            TB_INFO("query expansion : termid="<<*(uint64_t*)(term.data())<<",expansion_list:");
            for(int j=0;j<pb_query.te(i).eterm_size();j++){
                const std::string &eterm = pb_query.te(i).eterm(j);
                TB_INFO("expansion_termid="<<*(uint64_t*)(eterm.data()));
                if(eterm_originals.find(eterm)==eterm_originals.end()){
                    m_query_expansion[eterm] = term;
                }
            }
        }
    }
    //friends
    for(int i=0;i<pb_query.d1_uid_size();i++){
        m_distance.set_d1(pb_query.d1_uid(i));
    }
    for(int i=0;i<pb_query.d2_uid_size();i++){
        m_distance.set_d2(pb_query.d2_uid(i));
    }

    return true;
}
bool 
UserSearchQuery::link_distance_filter(int distance)
{
    if(pb_query.has_link_distance_filter() == false){
        return true;
    }else{
        if(distance == 1 && pb_query.link_distance_filter().has_link_1du() && pb_query.link_distance_filter().link_1du()){
            return true;
        }else if(distance == 2 && pb_query.link_distance_filter().has_link_2du() && pb_query.link_distance_filter().link_2du()){
            return true; 
        }else if(distance > 2 && pb_query.link_distance_filter().has_link_xdu() && pb_query.link_distance_filter().link_xdu()){
            return true;
        }else{
            return false;
        }
    }
}
bool
UserSearchQuery::company_contacts_filter(uint64_t uid)
{
    if(m_searcher_company_hash==0){
        if(false == pb_query.has_searcher_company_name()){
            return true;
        }else{
            m_searcher_company_hash = CompanyContactsKeeper::company_name_hash(pb_query.searcher_company_name());
        }
    }
    if(pb_query.has_filter_company_1du_contacts() && pb_query.has_filter_non_company_1du_contacts()){
        return true;
    }else if(pb_query.has_filter_company_1du_contacts()){
        return m_cc_keeper->check(m_searcher_company_hash,uid);
    }else if(pb_query.has_filter_non_company_1du_contacts()){
        return !m_cc_keeper->check(m_searcher_company_hash,uid);
    }else{
        return true;
    }
}

bool
UserSearchQuery::check_com_contacts(uint64_t uid)
{
    if(m_searcher_company_hash==0){
        if(false == pb_query.has_searcher_company_name()){
            TB_DEBUG("no searcher_company_name set in query");
            return false;
        }else{
            m_searcher_company_hash = CompanyContactsKeeper::company_name_hash(pb_query.searcher_company_name());
            TB_DEBUG("searcher_company_name set query: "<<pb_query.searcher_company_name());
        }
    }
    bool hit = m_cc_keeper->check(m_searcher_company_hash,uid);
    if(hit){
        TB_DEBUG("com contacts hit for uid "<<uid);
    }else{
        TB_DEBUG("com contacts miss for uid "<<uid);
    }
    return hit;
}
