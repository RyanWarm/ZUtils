#pragma once
#include<map>
#include<iostream>
#include<xapian.h>
#include "SearchStats.hpp"
#include "UserSearchQuery.hpp"
#include "UserSearchSession.hpp"
#include "UserDistance.hpp"
#include "Def.hpp"
#include "Types.hpp"

using namespace std;

class UserSearchWeight : public Xapian::Weight {
        
    UserSearchSession *session;
public:
    UserSearchWeight(Xapian::Database *db,UserSearchSession *ss)
    :Xapian::Weight(),
    session(ss)
    {
        database(db);
    }
    UserSearchWeight * clone() const { 
        UserSearchWeight * c = new UserSearchWeight(const_cast<UserSearchWeight *>(this)->database(),session); 
        return c;
    }
    UserSearchWeight() { }
    ~UserSearchWeight() { }
    void init(double factor) {}
    std::string name() const { return "UserSearchWeight"; }
    std::string serialise() const { return ""; }
    UserSearchWeight * unserialise(const std::string &s) const {
        return new UserSearchWeight;
    }

    std::vector<Xapian::termpos> wdpos(const std::string &term);

    Xapian::weight get_sumpart(Xapian::termcount term_count, Xapian::termcount doc_length) const;
    Xapian::weight get_maxpart() const { return 1e+10; }

    Xapian::weight get_sumextra(Xapian::termcount doc_length) const ; 
    Xapian::weight get_maxextra() const { return 1e+10; }

    bool get_sumpart_needs_doclength() const { return false; }
    
    double advanced_score(UserSearchSession::mid_data_recorder_t &md_recorder,UserSearchQuery &query_obj,unsigned fans_num,double user_score,unsigned wyear,double name_score, uint64_t uid) const;
    double loose_match_score(UserSearchQuery &query_obj,unsigned fans_num,double user_score,unsigned wyear,double name_score, uint64_t uid) const;
    double user_similarity_score(UserSearchQuery &query_obj,unsigned fans_num,double user_score,unsigned wyear,uint64_t uid) const;
    
    
};

