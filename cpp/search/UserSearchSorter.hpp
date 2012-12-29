#include<iostream>
#include<xapian.h>
#include<stdint.h>
#include<map>
#include<vector>

class UserSearchSorter : public Xapian::KeyMaker
{
private:
    Xapian::Enquire *m_enquire;
public:
    UserSearchSorter() {}
    void set_enquire(Xapian::Enquire &enquire){
        m_enquire = &enquire;
    }
    virtual std::string operator()(const Xapian::Document &doc) const;
};

