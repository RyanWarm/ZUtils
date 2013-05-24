#!/usr/bin/python
import struct,sys,json,binascii,urllib,hashlib,time,threading,traceback,signal,os,re
import tornado
from tornado import template 
import mysql
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

def dump(alignment_result):
    db = mysql.Mysql("mysql:uc05,root,z64577580,zhaopin")
    sql = "select id,uid_list,expected_result from alignment_training_set"
    db.execute(sql)
    array = []
    correct = 0
    exp_match = 0
    all_match = 0
    for (case_id,uid_list,expected) in db.fetchall():
        uid_list = uid_list.strip(" ,")
        experiment_result = 'N' 
        info_map = {}
        uid_list_int = [] 
        for uid in uid_list.split(","):
            if not uid: continue
            uid_list_int.append(int(uid))
            info = get_user_info("uc06:8080",int(uid))
            if info:
                info_map[uid] = info
        group = alignment_result[str(uid_list_int[0])]
        if group:
            flag = True
            for uid in uid_list_int[1:]:
                if uid not in group:
                    flag = False
            if flag == True:
                experiment_result = 'Y'
        array.append((case_id,info_map,",".join(map(lambda x:str(x),uid_list_int)),expected,experiment_result))
        if expected == experiment_result:
            correct += 1
        if expected == 'Y':
            all_match += 1
            if experiment_result == expected:
                exp_match += 1
    precision = float(correct)/len(array)
    recall = float(exp_match)/all_match
    return (array,precision,recall)

def main():
    print "Content-Type: text/html\r\n\r\n"
    db = mysql.Mysql("mysql:uc05,root,z64577580,zhaopin")
    sql = "select uid_list from alignment_training_set"
    db.execute(sql)
    uid_list = []
    for (uid_list_s,) in db.fetchall():
        for uid in uid_list_s.split(','):
            if uid: uid_list.append(uid)
    url = "http://uc06:8081/?cmd=align_by_group&uids=[%s]" % ",".join(uid_list)
    sys.stderr.write(url+"\n")
    s = urllib.urlopen(url) 
    resp = s.read()
    sys.stderr.write("alignment resp:"+resp+"\n")
    if not resp:
        print "Alignment error occured. "
        return
    alignment_result = json.loads(resp)
    (array,precision,recall) = dump(alignment_result)

    loader = template.Loader("./")
    print loader.load("alignment_run.tpl").generate(records=array,precision=precision,recall=recall)

if __name__=='__main__':
    main()
