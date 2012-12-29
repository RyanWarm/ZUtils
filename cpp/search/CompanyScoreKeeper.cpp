#include "CompanyScoreKeeper.hpp"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <openssl/md5.h> 
#include "Def.hpp"

CompanyScoreKeeper::CompanyScoreKeeper(const string &company_score_file)
    :m_company_score_file(company_score_file)
{
}
CompanyScoreKeeper::~CompanyScoreKeeper()
{
}
bool 
CompanyScoreKeeper::init()
{
    std::ifstream ifs(m_company_score_file.data());
    if(ifs.is_open() == false){
        return false;
    }
    string line;
    while(getline( ifs, line)){
        size_t pos = line.find("\t");
        if(pos == string::npos){
            continue;
        }
        string name = line.substr(0,pos);
        pos += 1;
        if(pos >= line.size()){
            continue;
        }
        double score = atof(line.data()+pos);
        m_com_score[company_name_hash(name)] = score;
    }
    return true;
}

uint64_t 
CompanyScoreKeeper::company_name_hash(const string &str)
{
    string str_ = str;
    std::transform(str_.begin(), str_.end(), str_.begin(), ::tolower);
    MD5_CTX ctx;
    unsigned char md[16];
    MD5_Init(&ctx);
    MD5_Update(&ctx,str_.data(),str_.size());
    MD5_Final(md,&ctx);
    return *(uint64_t*)md&(~((uint64_t)1<<63));
}

double
CompanyScoreKeeper::score(uint64_t name_hash)
{
    com_score_t::iterator it = m_com_score.find(name_hash);
    if(it == m_com_score.end()){
        return 0;
    }else{
        return it->second;
    }
}


