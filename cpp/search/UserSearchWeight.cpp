#include <stdint.h>
#include <math.h>
#include "UserSearchWeight.hpp"
#include "Utils.hpp"
#include "Def.hpp"
#include "Types.hpp"
#include "UserSearchSession.hpp"

using namespace std;

Xapian::weight
UserSearchWeight::get_sumpart(Xapian::termcount payload, Xapian::termcount doc_length) const {
    UserSearchQuery &query_obj = dynamic_cast<UserSearchQuery &>(*session->search_query());
    string *term = const_cast<UserSearchWeight*>(this)->current_term();
    query_obj.m_matchings[*term] = payload;
    if(*(uint64_t *)term->data() >> 60 == 12){ //name match
        double in_doc_weight = (double)payload/1000000.0;
        double in_query_weight = query_obj.m_query_weight[*term];
        TB_DEBUG("term="<<*(uint64_t *)term->data()<<",in_doc_weight="<<in_doc_weight<<",in_query_weight="<<in_query_weight);
        session->name_score += in_doc_weight * in_query_weight;
    }
    return 0;
}

Xapian::weight 
UserSearchWeight::get_sumextra(Xapian::termcount doc_length) const { 
    UserSearchQuery &query_obj = dynamic_cast<UserSearchQuery &>(*session->search_query());
    double name_score = session->name_score;
    session->name_score = 0;
    
    uint64_t uid = *(uint64_t *)get_value(0).data();
    TB_DEBUG("uid "<<uid<<" name score original "<<name_score/50<<", amplified "<<name_score);
    
    SearchStats::term_t distance = 0;
    if(query_obj.m_distance.find_d1(uid)){
        distance = 1;
    }else if(query_obj.m_distance.find_d2(uid)){
        distance = 2;
    }else{
        distance = 3;
    }
    SearchStats::term_t com_distance = 0;
    if(query_obj.check_com_contacts(uid)){
        com_distance = 101;
    }else{
        com_distance = 102;
    }
        
    double weight = 0;
    //scoring
    { 
        string v1 = get_value(1);
        size_t offset = 0;
        uint32_t fans_num = *(uint32_t *)(v1.data()+offset); offset += sizeof(uint32_t);
        uint32_t user_score = *(uint32_t *)(v1.data()+offset); offset += sizeof(uint32_t);
        if(uid == 1951466251){
            user_score = 95;
        }
        uint32_t wyear = *(uint32_t *)(v1.data()+offset); offset += sizeof(uint32_t);
        assert(offset == v1.size());
       
        switch(query_obj.search_type){
            case 0: //normal search
                weight = advanced_score(session->m_mid_data_recorder,query_obj,fans_num,user_score,wyear,name_score,uid);
                break;
            case 1: //loose patch
                weight = loose_match_score(query_obj,fans_num,user_score,wyear,name_score,uid);
                break;
            default:
                assert(false);
        }
        if(query_obj.link_distance_filter(distance) == false){
            weight = 0; 
        }
        if(query_obj.company_contacts_filter(uid) == false){
            weight = 0;
        }
    }
    //stats
    if(query_obj.task_type != TASK_SEARCH && weight > 0)
    { 
        if(query_obj.task_type == TASK_STATS_DIS){
            session->m_stats.inc(distance);
        }else if(query_obj.task_type == TASK_STATS_COM_CONTACTS){
            TB_DEBUG("increase for TASK_STATS_COM_CONTACTS");
            session->m_stats.inc(com_distance);
        }else{
            uint32_t slot_idx = query_obj.task_type;
            session->m_stats.inc_multi(get_value(slot_idx+2));
        }
        weight = 0;
    }
    if(weight>0){
        session->m_qualified_matches += 1;
    }
    return weight;
} 

double 
UserSearchWeight::advanced_score(UserSearchSession::mid_data_recorder_t &md_recorder,UserSearchQuery &query_obj,unsigned fans_num,double user_score,unsigned wyear,double name_score,uint64_t uid) const
{
    matchings_t &matchings = query_obj.m_matchings;
    query_weight_t &query_weight = query_obj.m_query_weight;
    query_expansion_t &query_expansion = query_obj.m_query_expansion;
    unsigned tag_num_in_query = query_obj.m_tag_num_in_query;
    unsigned pos_num_in_query = query_obj.m_pos_num_in_query;
    TB_DEBUG("score input: tag_num_in_query="<<tag_num_in_query<<" pos_num="<<pos_num_in_query);
    TB_DEBUG("score input: uid="<<uid);
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
    double comp_pos_match_wt= 0.0;
    std::map<Xapian::termpos,int> pos_match;

    for(matchings_t::iterator it=matchings.begin();it!=matchings.end();it++){
        if (is_tag_term(it->first)) {    
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
        } else if (is_pos_term(it->first)) {
            pos_sum += 1.0;
            std::string term = it->first;
            std::vector<Xapian::termpos> pos_list = const_cast<UserSearchWeight*>(this)->wdpos(term);
            for (size_t i = 0; i < pos_list.size(); i++) {
                if (pos_match.find(pos_list[i]) != pos_match.end()) {
                    if (pos_match[pos_list[i]] == 1) {
                        comp_pos_match_wt = 1.0;
                        break;
                    }
                }
                pos_match.insert(std::pair<Xapian::termpos,int>(pos_list[i],0));
            }
        } else if (is_com_term(it->first)) {
            com_sum += 1.0;
            std::string term = it->first;
            std::vector<Xapian::termpos> pos_list = const_cast<UserSearchWeight*>(this)->wdpos(term);
            for (size_t i = 0; i < pos_list.size(); i++) {
                if (pos_match.find(pos_list[i]) != pos_match.end()) {
                    if (pos_match[pos_list[i]] == 0) {
                        comp_pos_match_wt = 1.0;
                        break;
                    }
                }
                pos_match.insert(std::pair<Xapian::termpos,int>(pos_list[i],1));
            }
        }
    }
    matchings.clear();

    if (wdf_sum == 0.0 && pos_sum == 0.0 && com_sum == 0.0 && name_score < 0.6) {
        return 0;
    }

    if (name_score == 1) {
        name_score = 100;
    }else if (name_score > 0.9) {
        name_score = pow(name_score,2) * 80;
    } else {
        name_score = pow(name_score,2) * 60;
    }


    /*double query_weight_sum = 0;
    for(query_weight_t::iterator it=query_weight.begin();it!=query_weight.end();it++){
        query_weight_sum += it->second;
    }

    if (query_weight_sum >= 1) {    
        tag_num_in_query = (unsigned)query_weight_sum;
    }

    TB_DEBUG("query weight sum = "<< query_weight_sum);
    */

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
        pos_match_score = pos_sum * 100 / pos_num_in_query;
    }

    double tag_value = 0; 
    if(max_tag_value > 0){
        tag_value = wdf_sum/max_tag_value;
    }
    tag_value = (tag_value<1)?tag_value:1; 
    double tag_score = tag_value * 300; 
   
    double fans_score = (double)fans_num; 
    if(fans_score > 10000){ 
        fans_score = 10000; 
    }
    fans_score = pow(fans_score/10000,0.4) * 50; //80

    double work_score = 0; 
    if(wyear > 10){ 
        work_score = 15;
    }else if(wyear > 5){
        work_score = 10;
    }else if(wyear > 0){
        work_score = 5;
    } 
    user_score *= 1.3; 
    double comp_pos_match_score = comp_pos_match_wt*50;
    
    double final_score = tag_score + fans_score + user_score + work_score + pos_match_score + comp_pos_match_score + name_score;
    ostringstream os;
    os<<"total_score:"<<final_score<<",tag_score:"<<tag_score << ",fans_score:"<<fans_score<<",user_score:"<<user_score<<",work_score:"<<work_score<<",pos_match_score:"<<pos_match_score<<",com_pos_match_score:"<<comp_pos_match_score<<",name_score:"<<name_score; 
    TB_DEBUG(os.str());
    if (query_obj.pb_query.has_debug() && query_obj.pb_query.debug()){
        md_recorder[uid] = os.str();
    }
    return final_score;
}

double 
UserSearchWeight::loose_match_score(UserSearchQuery &query_obj,unsigned fans_num,double user_score,unsigned wyear,double name_score,uint64_t uid) const
{
    matchings_t &matchings = query_obj.m_matchings;
    query_weight_t &query_weight = query_obj.m_query_weight;
    query_expansion_t &query_expansion = query_obj.m_query_expansion;
    unsigned tag_num_in_query = query_obj.m_tag_num_in_query;
    unsigned pos_num_in_query = query_obj.m_pos_num_in_query;
    TB_DEBUG("score input: uid="<<uid);
    query_weight_t query_expansion_wt;
    query_weight_t pos_expansion_wt;
    //get orignal query term num
    tag_num_in_query = tag_num_in_query - query_expansion.size();
    if (tag_num_in_query <= 0) {
        tag_num_in_query = 1;
    }

    double wdf_sum = 0;
    double pos_sum = 0;
    double year_matched = 0;
    double loc_matched = 0; 

    for(matchings_t::iterator it=matchings.begin();it!=matchings.end();it++){
        if (is_tag_term(it->first)) {
            double wdf_wt = 1.0;
            if (query_weight.find(it->first) != query_weight.end()) {
                wdf_wt = query_weight[it->first];
            }
            wdf_wt = wdf_wt * it->second;

            string query_expanded = it->first;
            if (query_expansion.find(it->first) != query_expansion.end()) {
                query_expanded = query_expansion[it->first];
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
        } else if (is_pos_term(it->first)) {
            double wdf_wt = 1.0;
            string pos_expanded = it->first;
            if (query_expansion.find(it->first) != query_expansion.end()) {
                pos_expanded = query_expansion[it->first];
            }

            if (pos_expansion_wt.find(pos_expanded) == pos_expansion_wt.end()) {
                pos_expansion_wt.insert(query_weight_t::value_type(pos_expanded,wdf_wt));
                pos_sum += wdf_wt;
            } else {
                double wt_ex = pos_expansion_wt[pos_expanded];
                if (wt_ex < wdf_wt) {
                    pos_expansion_wt[pos_expanded] = wdf_wt;
                    pos_sum += (wdf_wt - wt_ex);
                }
            }
            TB_DEBUG("score input: matching position="<<*(uint64_t *)it->first.data()<<",wdf="<<it->second<<",wt="<<wdf_wt);
        }else if (is_loc_term(it->first)) {
            loc_matched = 1.0;
        }else if (is_year_term(it->first)) {
            year_matched = 1.0;
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
        pos_match_score = pos_sum * 100 / pos_num_in_query;
    }

    double tag_value = 0;
    if(max_tag_value > 0){
        tag_value = wdf_sum/max_tag_value;
    }
    tag_value = (tag_value<1)?tag_value:1;
    double tag_score = tag_value * 200;
    if (tag_score < 50){
        TB_DEBUG("tag score "<<tag_score<<" under threshold,cut it");
        return 0;
    }
    double fans_score = (double)fans_num;
    if(fans_score > 10000){
        fans_score = 10000;
    }
    fans_score = pow(fans_score/10000,0.4) * 30;

    double final_score = tag_score + fans_score + user_score * 0.7 + pos_match_score +loc_matched*50 + year_matched*50;
    if (final_score < 80){
        TB_DEBUG("final score "<<final_score<<" under threshold,cut it");
        return 0;
    }
    TB_DEBUG("final score:"<<final_score<<",tag_score:"<<tag_score
            <<",fans_num:"<<fans_num<<",user_score:"<<user_score<<",wyear:"<<wyear<<",pos_match:"<<pos_match_score);
    return final_score; 
}

double 
UserSearchWeight::user_similarity_score(UserSearchQuery &query_obj,unsigned fans_num,double user_score,unsigned wyear,uint64_t uid) const
{
    return 0;
}

std::vector<Xapian::termpos>
UserSearchWeight::wdpos(const std::string &term) {
    if(false == this->database()->has_positions()){
        throw "Index has no positional information";
    }
    std::vector<Xapian::termpos> vec;
    Xapian::PositionIterator it = this->database()->positionlist_begin(this->current_docid(),term);
    Xapian::PositionIterator itend = this->database()->positionlist_end(this->current_docid(),term);
    while(it!=itend){
        vec.push_back(*it);
        it++;
    }
    return vec;
}
