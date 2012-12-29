#include <iostream>
#include <boost/algorithm/string.hpp>
#include "SearchStats.hpp" 
#include "TopKHeap.hpp"
#include "Utils.hpp"
using namespace boost;
using namespace std;

#define COUNTER_SIZE 10000
#define TOP_MAX_ITEMS 100
SearchStats::SearchStats()
{
}
SearchStats::~SearchStats(){
}
void SearchStats::reset(){
    counter.clear();
    v_reserved_term.clear();
}

void SearchStats::inc_multi(const string &keys){
    for(size_t i=0;i<keys.size()/sizeof(term_t);i++){
        term_t *term = (term_t *)(keys.data()+sizeof(term_t)*i);
        inc(*term);
    }
}
void SearchStats::inc(const term_t &key){
    if(counter.find(key)==counter.end()){
        counter[key] = 1;
    }else{
        counter[key] += 1;
    }
}

void SearchStats::reserve_term(const term_t &key){
    v_reserved_term.push_back(key);
}

int SearchStats::topk(std::vector<pair_t> &topv,unsigned k){
    topv.clear();
    TopKHeap<pair_t,Compare> topk(k+v_reserved_term.size());
    for(hash_counter_t::iterator it=counter.begin();it!=counter.end();it++){
        topk.push(*it);
    }
    while(topk.size() > k){
        topk.pop();
    }
    for(size_t i=0;i<v_reserved_term.size();i++){
        term_t &termid = v_reserved_term[i];
        bool skip = false;
        for(size_t i=0;i<topk.size();i++){
            if(topk[i].first == termid){
                skip = true;
                break;
            }
        }
        if(skip){
            continue;
        }
        uint64_t count = 0;
        if(counter.find(termid) != counter.end()){
            count = counter[termid];
        }
        topk.push(make_pair(termid,count));
    }
    while(topk.size()){
        topv.insert(topv.begin(),topk.pop());
    }
    return topv.size();
}


