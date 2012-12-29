#pragma once
#include <iostream>
#include <stdint.h>

#define TERM_COM 1
#define TERM_JOB 2
#define TERM_TAG 2

inline uint32_t term_type(uint64_t term){
    return term>>60;
}
inline uint32_t term_type(const std::string &s){
    return term_type(*(uint64_t *)s.data());
}


inline bool is_com_term(uint64_t term){
    return (term>>60) == 0x1;
}
inline bool is_com_term(const std::string &s){
    return is_com_term(*(uint64_t *)s.data());
}

inline bool is_pos_term(uint64_t term){
    return (term>>60) == 0x2;
}
inline bool is_pos_term(const std::string &s){
    return is_pos_term(*(uint64_t *)s.data());
}
inline bool is_tag_term(uint64_t term){
    return (term>>60) == 0x3; 
}
inline bool is_tag_term(const std::string &s){
    return is_tag_term(*(uint64_t *)s.data());
}

inline bool is_loc_term(uint64_t term){
    return (term>>60) == 0x4;
}
inline bool is_loc_term(const std::string &s){
    return is_loc_term(*(uint64_t *)s.data());
}

inline bool is_year_term(uint64_t term){
    return (term>>60) == 0x5;
}
inline bool is_year_term(const std::string &s){
    return is_year_term(*(uint64_t *)s.data());
}

//job stuff
inline bool is_job_com_term(uint64_t term){
    return (term>>56) == 0x1;
}
inline bool is_job_com_term(const std::string &s){
    return is_job_com_term(*(uint64_t *)s.data());
}

inline bool is_job_pos_term(uint64_t term){
    return (term>>56) == 0x2;
}
inline bool is_job_pos_term(const std::string &s){
    return is_job_pos_term(*(uint64_t *)s.data());
}

inline bool is_job_tag_term(uint64_t term){
    return (term>>56) == 0x3; 
}
inline bool is_job_tag_term(const std::string &s){
    return is_job_tag_term(*(uint64_t *)s.data());
}

