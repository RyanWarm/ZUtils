#include <config.h>
#include <typeinfo>
#include <iostream>
#include "extraweightpostlist.h"
#include "valuestreamdocument.h"
Xapian::weight
ExtraWeightPostList::get_weight() const {
    wt->current_docid(pl->get_docid());
    wt->vsdoc(const_cast<ExtraWeightPostList*>(this)->vsdoc());
    return pl->get_weight() + wt->get_sumextra(pl->get_doclength());
}

