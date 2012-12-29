#include <stdint.h>
#include <math.h>
#include "JobSearchWeight.hpp"
#include "Utils.hpp"
#include "Def.hpp"
#include "Types.hpp"
#include "time.h"
#include "JobSearchSession.hpp"
#include "CompanyScoreKeeper.hpp"

using namespace std;

Xapian::weight
JobSearchWeight::get_sumpart(Xapian::termcount payload, Xapian::termcount doc_length) const {
    string *term = const_cast<JobSearchWeight*>(this)->current_term();
    JobSearchQuery &query_obj = dynamic_cast<JobSearchQuery &>(*session->search_query());
    query_obj.m_matchings[*term] = payload;
    TB_DEBUG("current term:"<<*(uint64_t *)term->data()<<",wdf:"<<payload);
    return 0;
}



Xapian::weight 
JobSearchWeight::get_sumextra(Xapian::termcount doc_length) const {
    JobSearchQuery &query_obj = dynamic_cast<JobSearchQuery &>(*session->search_query());
   
    uint64_t jobid = *(uint64_t *)get_value(100).data();
    uint64_t create_time = *(uint64_t *)get_value(101).data();
    uint64_t company_name_hash = *(uint64_t *)get_value(102).data();
    
    double company_score = session->server()->m_com_score->score(company_name_hash);
    double weight = advanced_score(
            session->m_mid_data_recorder,
            jobid,
            create_time,
            query_obj,
            company_score);
    if(query_obj.task_type != TASK_SEARCH && weight > 0)
    { //stats
        uint32_t slot_idx = query_obj.task_type;
        session->m_stats.inc_multi(get_value(slot_idx));
        weight = 0;
    }
    if(weight>0){
        session->m_qualified_matches += 1;
    }
    return weight;
} 


double 
JobSearchWeight::advanced_score(
        JobSearchSession::mid_data_recorder_t &md_recorder,
        uint64_t jobid,
        uint64_t create_time,
        JobSearchQuery &query_obj, 
        double company_score) const
{
    matchings_t &matchings = query_obj.m_matchings;
    query_weight_t &query_weight = query_obj.m_query_weight;
    query_expansion_t &query_expansion = query_obj.m_query_expansion;
    unsigned tag_num_in_query = query_obj.m_tag_num_in_query;
    unsigned pos_num_in_query = query_obj.m_pos_num_in_query;
    uint64_t current_time = time(NULL);
	double decay_factor = pow(JOB_DECAY_FACTOR,(current_time-create_time)/86400.0);

    TB_DEBUG("score input: tag_num_in_query="<<tag_num_in_query<<" pos_num="<<pos_num_in_query);
    query_weight_t query_expansion_wt;
    //get orignal query term num
    tag_num_in_query = tag_num_in_query - query_expansion.size();
    if (tag_num_in_query <= 0) {
        tag_num_in_query = 1;
    }
    TB_DEBUG("original tag input: tag_num_in_query="<<tag_num_in_query << "\tmap size:" <<query_expansion.size());

    double wdf_sum = 0;
    double pos_sum = 0;
    double com_sum = 0;
    std::map<Xapian::termpos,int> pos_match;

    for(matchings_t::iterator it=matchings.begin();it!=matchings.end();it++){
        if (is_job_tag_term(it->first)) {    
            double wdf_wt = 1.0;
            if (query_weight.find(it->first) != query_weight.end()) {
                wdf_wt = query_weight[it->first];
            }
            wdf_wt = wdf_wt * it->second;

            string query_expanded = it->first;
            if (query_expansion.find(it->first) != query_expansion.end()) {
                query_expanded = query_expansion[it->first];
                TB_DEBUG("HIT EXPANSION: matching term");
            }

            if (query_expansion_wt.find(query_expanded) == query_expansion_wt.end()) {
                query_expansion_wt.insert(query_weight_t::value_type(query_expanded,wdf_wt));
                wdf_sum += wdf_wt;
            } else {
                double wt_ex = query_expansion_wt[query_expanded];
                if (wt_ex < wdf_wt) {
                    query_expansion_wt[query_expanded] = wdf_wt;
                    wdf_sum += (wdf_wt - wt_ex);
                }
            }
            TB_DEBUG("score input: matching term="<<*(uint64_t *)it->first.data()<<",wdf="<<it->second<<",wt="<<wdf_wt);
        } else if (is_job_pos_term(it->first)) {
            pos_sum += 1.0;
        } else if(is_job_com_term(it->first)) {
			com_sum += 1.0;
		}
    }
    matchings.clear();

    double max_tag_value = 0.0;
    if(tag_num_in_query< 3){
        max_tag_value = tag_num_in_query* 3;
    }else if(tag_num_in_query< 8){
        max_tag_value = tag_num_in_query* 2;
    }else{
        max_tag_value = tag_num_in_query* 1.5;
    }

    double pos_match_score = 0;
    if(pos_sum > 0) {
        pos_match_score = pos_sum * 200 / pos_num_in_query;
    }

    double tag_value = 0; 
    if(max_tag_value > 0){
        tag_value = wdf_sum/max_tag_value;
    }
    tag_value = (tag_value<1)?tag_value:1; 
    double tag_score = tag_value * 300; 
  
    /*if (tag_score < 50){
        TB_DEBUG("tag score "<<tag_score<<" under threshold,cut it");
        return 0;
    }*/

    double final_score = tag_score + pos_match_score + company_score;
    final_score = final_score * decay_factor;
    ostringstream os;
    os<<"total_score:"<<final_score<<",tag_score:"<<tag_score << ",pos_match_score:"<<pos_match_score<<",company_score:"<<company_score<<",decay:"<<decay_factor;
    TB_DEBUG(os.str());
    if (query_obj.pb_query.has_debug() && query_obj.pb_query.debug()){
        md_recorder[jobid] = os.str();
    }
    return final_score;
}
