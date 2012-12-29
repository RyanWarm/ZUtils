#include <iostream>
#include <vector>
#include <map>
#include "JobSearchQuery.hpp"
#include "Utils.hpp"
#include "Def.hpp"
using namespace std;

bool 
JobSearchQuery::loads(const char *buffer,unsigned len){
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
        TB_INFO("query term "<<*(uint64_t *)term.data()<<": "<<weight);
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
    TB_INFO("pb_query.debug = "<<pb_query.debug());
    return true;
}


