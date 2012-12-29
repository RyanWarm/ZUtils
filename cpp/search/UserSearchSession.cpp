#include "UserSearchSession.hpp"
#include "UserSearchWeight.hpp"

UserSearchSession::~UserSearchSession(){
        if(m_weight){
            delete m_weight;
            m_weight = 0;
        }
    }
    
Xapian::Weight *
UserSearchSession::weighter(Xapian::Database *db) {
        if(m_weight){
            return m_weight;
        }else{
            m_weight = new UserSearchWeight(db,this);
            return dynamic_cast<Xapian::Weight *>(m_weight);
        }
    }
    
void
UserSearchSession::reset()
{
    m_stats.reset();
    m_mid_data_recorder.clear();
}
bool 
UserSearchSession::serialize_result(Xapian::MSet &matches, string &resp)
{
    UserSearchResult pb_result;
    //numbers
    pb_result.set_offset(m_query.offset());
    pb_result.set_total_estimated(m_qualified_matches);
    TB_DEBUG("matches count:"<<matches.get_matches_estimated());
    TB_DEBUG("matches qualified:"<<m_qualified_matches);
    //matches
    for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
        if(i.get_weight() == 0){
            break;
        }
        string data = i.get_document().get_data();
        UserSearchResult_ResultItem *item = pb_result.add_result_item();
        item->set_uid(*(uint64_t*)data.data()); 
        item->set_score(i.get_weight()); 
        item->set_link_distance(1); 
        if(m_query.pb_query.has_debug() && m_query.pb_query.debug()){
            item->set_debug_data(m_mid_data_recorder[item->uid()]);
        }
        TB_DEBUG("uid :"<<item->uid());
    }
    pb_result.set_count(pb_result.result_item_size());
    TB_DEBUG("matches in range:"<<pb_result.result_item_size());

    //stats
    std::vector<SearchStats::pair_t> top_v;
    m_stats.topk(top_v,MAX_STATS_ITEMS);
    for(unsigned i=0;i<top_v.size();i++){
        const SearchStats::term_t &key = top_v[i].first;
        uint32_t value = top_v[i].second;
        UserSearchResult_StatsItem *stats = pb_result.add_stats_item();
        stats->set_stats_type(USER_STATS_NAME[m_query.task_type]);
        stats->set_stats_key(key);
        stats->set_stats_value(value);
    }
    //serialize
    if(false == pb_result.SerializeToString(&resp)){
        TB_DEBUG("serialize response failed");
        return false;
    }
    return true;
}

