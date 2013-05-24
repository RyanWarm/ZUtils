#!/usr/bin/python
import struct,sys,json,binascii,urllib,hashlib,time,threading,traceback,signal,os,re
from optparse import OptionParser
import tornado
from tornado import template 
import mysql
import cgi
import binascii,json,urllib
from proto import WeiboProfile_pb2
from proto import Linkedin_pb2
from proto import Resume_pb2
from proto import SimpleResume_pb2

def get_user_info(api_addr,uid):
    r = {}
    zid_list = []
    nid_list = []
    uid_list = [uid,]
    for uid in uid_list:
        if uid>>56 == 127:
            zid_list.append(uid & (~(0xff<<56)))
        else:
            nid_list.append(uid)
    if nid_list:
        s = urllib.urlopen("http://%s/?cmd=info_pb&uid=%s" % (api_addr,",".join(map(lambda x:str(x),nid_list))))
        resp = s.read()
        xx = json.loads(resp)
        for uid in xx:
            if not xx[uid]:
                continue
            if int(uid)>>56 == 0:
                pb = WeiboProfile_pb2.WeiboProfile()
                pb.ParseFromString(binascii.unhexlify(xx[uid]))
                r[uid] = {
                        'name':pb.personal_info.name,
                        'image':pb.personal_info.img,
                        }
                if pb.his_data and pb.his_data.com:
                    r[uid]['position'] = pb.his_data.com[0].position
                else:
                    r[uid]['position'] = ''
            else:
                pb = Linkedin_pb2.LinkedinProfile()
                pb.ParseFromString(binascii.unhexlify(xx[uid]))
                r[uid] = {
                        'name':pb.personal_info.name,
                        'image':pb.personal_info.img,
                        }
                if pb.his_data and pb.his_data.com:
                    r[uid]['position'] = pb.his_data.com[0].position 
                else:
                    r[uid]['position'] = ''
            r[uid]['url'] = "http://www.ztelic.com/recruit/user/n/" + str(uid_encode(uid))
    if zid_list:
        s = urllib.urlopen("http://%s/?cmd=fetch_resume&zid=%s" % (api_addr,",".join(map(lambda x:str(x),zid_list))))
        resp = s.read()
        xx = json.loads(resp)
        for uid in xx:
            if not xx[uid]:
                continue
            pb = Resume_pb2.Resume()
            pb.ParseFromString(binascii.unhexlify(xx[uid]))
            r[str(int(uid)|(127<<56))] = {'name':pb.basic_info.name,'image':pb.basic_info.image,'position':""}
    if str(uid) in r:
        return r[str(uid)]

def uid_encode(uid):
    if int(uid)>>56!=0:
        return int(uid)
    m = {'0':'4','1':'8', '2':'3', '3':'7', '4' : '2', '5' : '9', '6' : '5', '7' : '6', '8' : '1', '9' : '0'}
    s = str(int(uid)+54088)
    e = ""
    for c in s:
        e += m[c]
    return int(e)

def dump(offset,limit):
    db = mysql.Mysql("mysql:uc05,root,z64577580,zhaopin")
    sql = "select id,uid_list,expected_result,experiment_result from alignment_training_set"
    sql += " limit %d,%d" % (int(offset),int(limit))
    db.execute(sql)
    array = []
    for (case_id,uid_list,expected,experiment) in db.fetchall():
        uid_list = uid_list.strip(" ,")
        info_map = {}
        uid_list_int = []
        for uid in uid_list.split(","):
            if not uid: continue
            uid_list_int.append(int(uid))
            info = get_user_info("uc06:8080",int(uid))
            if info:
                info_map[uid] = info
        array.append((case_id,info_map,",".join(map(lambda x:str(x),uid_list_int)),expected))
    return array

def resp(records,offset,count):
    print "Content-Type: text/html\r\n\r\n"
    loader = template.Loader("./")
    print loader.load("alignment_training_set.tpl").generate(offset=int(offset),count=int(count),records=records)

def main():
    form = cgi.FieldStorage()
    params = {} 
    db = mysql.Mysql("mysql:uc05,root,z64577580,zhaopin")
    for key in form:
        params[key] = form[key].value
    ptn_case_id_list = re.compile("^case_(\d+)_list$")
    for key in params:
        m = ptn_case_id_list.match(key)
        if m:
            case_id = int(m.group(1))
            uid_list = params[key]
            expected = 'Y'
            if "case_%d_expected"%case_id in params:
                expected = params["case_%d_expected"%case_id]
            if case_id<=0:
                db.execute("insert into alignment_training_set (uid_list,expected_result) values ('%s','%s')" % (uid_list,expected))
            else:
                db.execute("replace into alignment_training_set (id,uid_list,expected_result,experiment_result) values (%d,'%s','%s',NULL)" % (case_id,uid_list,expected))

    if 'offset' not in params:
        params['offset'] = 0
    if 'count' not in params:
        params['count'] = 1000 
    resp(
        dump(params['offset'],params['count']),
        params['offset'],
        params['count'],
        )
    
if __name__=='__main__':
    main()
