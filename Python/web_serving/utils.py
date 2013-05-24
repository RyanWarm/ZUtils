#!/usr/bin/python
import sqlite3,bson,MySQLdb,time

def mysql_connection(host,user,passwd,dbname):
    db = MySQLdb.connect(host=host,user=user,passwd=passwd,db=dbname)
    db.set_character_set('utf8')
    return db

def sqlite_connection(filename):
    return sqlite3.connect(filename)
def sql_db_connection(addr):
    pos = addr.find(":")
    if pos < 0:
        db_type = 'sqlite'
        db_addr = addr
    else:
        db_type = addr[0:pos]
        db_addr = addr[pos+1:]
    if db_type == 'mysql':
        (host,user,passwd,dbname) = db_addr.split(",")
        return mysql_connection(host,user,passwd,dbname)
    elif db_type == 'sqlite':
        return sqlite_connection(db_addr)
    else:
        raise Exception("invalid db addr")

def print_json(json,depth=0,indent=1):
    ss = ''
    if type(json) in (str,bson.binary.Binary): 
        ss += "\t"*depth*indent+json.strip()+"\n"
    elif type(json) == unicode:
        ss += "\t"*depth*indent+json.strip().encode('utf8')+"\n"
    elif type(json) in (int,long,float): 
        ss += "\t"*depth*indent+str(json)+"\n"
    elif type(json) == dict:
        ss += "\t"*depth*indent+"{\n"
        for key in json:
            raw_key = key
            if hasattr(key,'encode'):
                key = key.encode('utf8').strip()
            ss += "\t"*(depth+1)+"*"+str(key)+":  "
            ss += print_json(json[raw_key],depth+1,0)
        ss += "\t"*depth+"}\n"
    elif type(json) in (list,tuple):
        ss += "\t"*depth*indent+"[\n"
        for i in range(0,len(json)):
            ss += print_json(json[i],depth+1)
        ss += "\t"*depth+"]\n"
    else:
        ss += "\t"*depth*indent+"invalid type:"+str(type(json))+"\n"
    return ss

def map_to_obj(m):
    class X(object):
        def __init__(self,m):
            self.m = m
        def __getattr__(self,key):
            return self.m[key]
    x = X(m)
    return x

def timing(f,show_result=True):
    start = time.time() 
    r = f()
    end = time.time() 
    t = end-start
    if not show_result:
        r = "-"
    return (r,t*1000)

def uid2partid(uid,part_num):
    prime = 5381;  
    for c in str(uid):
        prime = (((prime << 5) & 0xffffffff) + prime) + ord(c)
    return prime % part_num
