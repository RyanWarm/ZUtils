#include<iostream>
#include<xapian.h>
#include<stdint.h>
#include<map>
#include<vector>
#include "UserSearchSorter.hpp"
#include "Def.hpp"


std::string UserSearchSorter::operator()(const Xapian::Document &doc) const
{
    return doc.get_value(0);
} 



