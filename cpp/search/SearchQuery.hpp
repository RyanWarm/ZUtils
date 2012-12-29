#pragma once
#include <iostream>
#include <xapian.h>
#include "Types.hpp"
#include "SearchStats.hpp"

class SearchQuery
{
public:
    SearchQuery(SearchStats &stats)
        :m_stats(stats)
    {}
    virtual bool loads(const char *buffer,unsigned len) = 0;
    virtual void reset() = 0;
    virtual Xapian::Query &xapian_query() = 0;
    virtual unsigned offset() = 0;
    virtual unsigned count() = 0;

public:
    SearchStats &m_stats;
};

