#pragma once
#include<iostream>
#include<iomanip>
#include<string>
#include<stdio.h>
#include<time.h>
#include <xapian.h>
using namespace std;

/*
 * color code: http://www.cplusplus.com/forum/unices/36461/
 */
#define COLOR_BOLD      "\033[1m"
#define COLOR_BLUE      "\033[0,34m"
#define COLOR_RED       "\033[0,31m"
#define COLOR_NORMAL    "\033[0m"

#define TB_ERROR(a) cerr<<__FILE__<<" : "<<__func__<<" : "<<__LINE__<<" : "<<a<<endl
#define TB_INFO(a) cerr<<__FILE__<<" : "<<__func__<<" : "<<__LINE__<<" : "<<a<<endl
#ifdef DEBUG
#define TB_DEBUG(a) cerr<<__FILE__<<" : "<<__func__<<" : "<<__LINE__<<" : "<<a<<endl
#else
#define TB_DEBUG(a) 
#endif


#define MAX_STATS_ITEMS 100
#define JOB_DECAY_FACTOR 0.9
