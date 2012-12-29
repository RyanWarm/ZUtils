#include "UserDistance.hpp"


UserDistance::UserDistance()
{
    d1_set = new user_set_t();
    d2_set = new user_set_t();
}

UserDistance::~UserDistance()
{
    delete d1_set;
    delete d2_set;
}

void
UserDistance::reset()
{
    d1_set->clear();
    d2_set->clear();
}

void 
UserDistance::set_d1(uint64_t uid)
{
    d1_set->insert(uid); 
}

void 
UserDistance::set_d2(uint64_t uid)
{
    d2_set->insert(uid);
}

bool 
UserDistance::find_d1(uint64_t uid)
{
    return d1_set->find(uid)!=d1_set->end();
}

bool 
UserDistance::find_d2(uint64_t uid)
{
    return d2_set->find(uid)!=d2_set->end();
}


