#pragma once
#include <iostream>
#include <stdint.h>
#include <google/sparse_hash_map>
#include <vector>
#include <map>
#include <tr1/functional>
#include "UserSearchResult.pb.h"

using std::tr1::hash;
//using google::sparse_hash_map;      // namespace where class lives by default
using namespace std;

class SearchStats
{
public:
    typedef uint64_t term_t;
    typedef google::sparse_hash_map<term_t, uint64_t> hash_counter_t;
    typedef pair<term_t,uint64_t> pair_t;

    struct Compare
    {
        bool operator()(const pair_t &a,const pair_t &b){
            return a.second>b.second;
        }
    };

private:
    hash_counter_t counter;
    vector<term_t> v_reserved_term;
    
public:
    SearchStats();
    virtual ~SearchStats();
    void reset();
    void inc_multi(const string &keys);
    void inc(const term_t &key);
    void reserve_term(const term_t &key);
    int topk(vector<pair_t> &topv,unsigned k);
};

