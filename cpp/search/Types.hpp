#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>

typedef std::map<std::string,Xapian::termcount> matchings_t;
typedef std::map<std::string,double> query_weight_t;
typedef std::vector<std::string> expansion_list_t;
typedef std::map<std::string,std::string> query_expansion_t;

typedef enum{
    QUERY_USER = 0,
    QUERY_JOB,
} query_type_t;

typedef enum{
    TASK_SEARCH = 0,
    TASK_STATS_COM = 1,
    TASK_STATS_JOB,
    TASK_STATS_TAG,
    TASK_STATS_LOC,
    TASK_STATS_EXP,
    TASK_STATS_RLL,
    TASK_STATS_COMTYPE,
    TASK_STATS_COMSIZE,
    TASK_STATS_JOBTYPE,
    TASK_STATS_CURCOM,
    TASK_STATS_SCH,
    TASK_STATS_NAM, //V
    TASK_STATS_DIS = 13,
    TASK_STATS_NETWORK = 14,
    TASK_STATS_COM_CONTACTS = 15,
} task_type_t;

static std::string USER_STATS_NAME[] = {
    "null",
    "com",
    "job",
    "tag",
    "loc",
    "exp",
    "rll",
    "comtype",
    "comsize",
    "jobtype",
    "curcom",
    "sch",
    "nam",
    "link_distance",
    "network",
    "com_contacts",
};
static std::string JOB_STATS_NAME[] = {
    "null",
    "com",
    "job",
    "tag",
    "loc",
    "exp",
    "rll",
    "comtype",
    "comsize",
    "jobtype",
    "curcom",
    "sch",
    "des",
    "edulvl",
    "worktype",
    "mgrexp",
    "stale"
};


