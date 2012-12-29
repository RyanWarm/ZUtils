#include "JobSearchSession.hpp"
#include "JobSearchWeight.hpp"
#include "JobSearchResult.pb.h"

void 
JobSearchSession::reset()
{
    m_stats.reset();
    m_mid_data_recorder.clear();
}
Xapian::Weight *
JobSearchSession::weighter(Xapian::Database *db) {
    if(m_weight){
        return m_weight;
    }else{
        m_weight = new JobSearchWeight(db,this);
        return dynamic_cast<Xapian::Weight *>(m_weight);
    }
}
    
bool 
JobSearchSession::serialize_result(Xapian::MSet &matches, string &resp)
{
    JobSearchResult pb_result;
    //numbers
    pb_result.set_offset(m_query.offset());
    pb_result.set_total_estimated(m_qualified_matches);
    TB_INFO("matches count:"<<matches.get_matches_estimated());
    TB_INFO("matches qualified:"<<m_qualified_matches);
    //matches
    for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
        if(i.get_weight() == 0){
            break;
        }
        string data = i.get_document().get_data();
        JobSearchResult pb_;
        pb_.ParseFromString(data);
        
        JobSearchResult_ResultItem &item = *(pb_result.add_result_item());
        item.set_jid(pb_.result_item(0).jid());
        item.set_title(pb_.result_item(0).title());
        item.set_location(pb_.result_item(0).location());
        item.set_company_id(pb_.result_item(0).company_id());
        item.set_company_name(pb_.result_item(0).company_name());
        item.set_company_image(pb_.result_item(0).company_image());
        item.set_department(pb_.result_item(0).department());
        item.set_post_date(pb_.result_item(0).post_date());
        item.set_score(i.get_weight()); 
        if(m_query.pb_query.has_debug() && m_query.pb_query.debug()){
            item.set_debug_data(m_mid_data_recorder[item.jid()]);
        }
        TB_DEBUG("jid :"<<item.jid());
    }
    pb_result.set_count(pb_result.result_item_size());
    TB_INFO("matches in range:"<<pb_result.result_item_size());

    //stats
    std::vector<SearchStats::pair_t> top_v;
    m_stats.topk(top_v,MAX_STATS_ITEMS);
    for(unsigned i=0;i<top_v.size();i++){
        const SearchStats::term_t &key = top_v[i].first;
        uint32_t value = top_v[i].second;
        JobSearchResult_StatsItem *stats = pb_result.add_stats_item();
        stats->set_stats_type(JOB_STATS_NAME[m_query.task_type]);
        stats->set_stats_key(key);
        stats->set_stats_value(value);
    }
    
    //serialize
    if(false == pb_result.SerializeToString(&resp)){
        TB_INFO("serialize response failed");
        return false;
    }
    return true;
}

