#pragma once
#include <iostream>
#include <stdint.h>
#include <google/sparse_hash_map>
#include <set>

#include <tr1/functional>
using std::tr1::hash;

//using google::sparse_hash_map;      // namespace where class lives by default

class UserDistance
{
public:
    //typedef sparse_hash_map<uint32_t, uint32_t, hash<uint32_t> > hash_counter_t;
    typedef std::set<uint64_t> user_set_t;
private:
    user_set_t *d1_set;
    user_set_t *d2_set;
public:
    UserDistance();
    virtual ~UserDistance();
    void reset();
    void set_d1(uint64_t uid);
    void set_d2(uint64_t uid);
    bool find_d1(uint64_t uid);
    bool find_d2(uint64_t uid);
};

