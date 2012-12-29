#ifndef __CompanyScoreKeeper_hpp_
#define __CompanyScoreKeeper_hpp_

#include <iostream>
#include <string>
#include <vector>
#include <google/sparse_hash_set>
#include <google/sparse_hash_map>

using std::string;
using std::vector;

class CompanyScoreKeeper
{
    typedef google::sparse_hash_map<uint64_t,double> com_score_t;
public:
    CompanyScoreKeeper(const string &company_score_file);
    ~CompanyScoreKeeper();
    bool init();
    double score(uint64_t name_hash);
    static uint64_t company_name_hash(const string &str);
private:
    string m_company_score_file;
    com_score_t m_com_score; 
};

#endif //__CompanyScoreKeeper_hpp_

