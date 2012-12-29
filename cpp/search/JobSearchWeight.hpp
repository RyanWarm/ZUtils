#pragma once
#include<map>
#include<iostream>
#include<xapian.h>
#include "SearchStats.hpp"
#include "JobSearchQuery.hpp"
#include "JobSearchSession.hpp"
#include "UserDistance.hpp"
#include "Def.hpp"
#include "Types.hpp"

using namespace std;

class JobSearchWeight : public Xapian::Weight {
    
    JobSearchSession *session;
public:
    JobSearchWeight(Xapian::Database *db,JobSearchSession *ss)
    :Xapian::Weight(),
    session(ss)
    {
        database(db);
    }
    JobSearchWeight * clone() const { 
        JobSearchWeight * c = new JobSearchWeight(const_cast<JobSearchWeight *>(this)->database(),session); 
        return c;
    }
    JobSearchWeight() { }
    ~JobSearchWeight() { }
    void init(double factor) {}
    std::string name() const { return "JobSearchWeight"; }
    std::string serialise() const { return ""; }
    JobSearchWeight * unserialise(const std::string &s) const {
        return new JobSearchWeight;
    }
    std::vector<Xapian::termpos> wdpos(const std::string &term);

    Xapian::weight get_sumpart(Xapian::termcount term_count, Xapian::termcount doc_length) const;
    Xapian::weight get_maxpart() const { return 1e+10; }

    Xapian::weight get_sumextra(Xapian::termcount doc_length) const ; 
    Xapian::weight get_maxextra() const { return 1e+10; }

    bool get_sumpart_needs_doclength() const { return false; }
    
    void set_session(JobSearchSession *d){ this->session = d; }
   
    double advanced_score(
        JobSearchSession::mid_data_recorder_t &md_recorder,
        uint64_t jobid,
        uint64_t create_time,
        JobSearchQuery &query_obj, 
        double company_score) const;
};

