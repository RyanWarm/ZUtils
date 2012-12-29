#ifndef __CompanyContactsKeeper_hpp_
#define __CompanyContactsKeeper_hpp_

#include <iostream>
#include <string>
#include <vector>
#include <google/sparse_hash_set>
#include <google/sparse_hash_map>

using std::string;
using std::vector;

class CompanyContactsKeeper
{
    typedef google::sparse_hash_set<uint64_t> uid_set_t;
    typedef google::sparse_hash_map<uint64_t,uid_set_t *> com_contacts_t;
public:
    CompanyContactsKeeper(const string &mongodb_addr,const string &company_name_file);
    ~CompanyContactsKeeper();
    bool init();
    void set_company(const string &company_name);
    bool check(uint64_t uid);
    bool check(uint64_t company_hash,uint64_t uid);
    static uint64_t company_name_hash(const string &str);
private:
    bool load_company_names(const string &filename);
private:
    string m_company_name_file;
    string m_mongodb_addr;
    vector<string> m_company_list;

    uint64_t m_company_name_hash;
    uid_set_t *m_uid_set;
    com_contacts_t m_com_contacts; 
};

#endif //__CompanyContactsKeeper_hpp_

