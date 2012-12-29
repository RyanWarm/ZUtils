#!/usr/bin/env python
#encoding=utf8
import pymongo
import defs,utils
from proto import WeiboProfile_pb2
import json
import sys,re
import codecs

def read_mongo(max_doc):
    mconnection = pymongo.Connection('10.200.189.26', 27017)
    mdb = mconnection.weibo_info_pb_20120927

    #output = codecs.open('user_birth','w','utf-8') 
    output_tag = codecs.open('user_tags','w','utf-8')
    doc_num = 0
    find_num = 0
    for i in range(0,8):
        mcollection = mdb['info_%d' % i]
        mcursor = mcollection.find()
        while 1:
            try:
              info=mcursor.next()
            except StopIteration:
                print "stop iteration"
                break
            if info is None:
                print "info is none"
                break

            import pdb
            pdb.set_trace()
            if 'pb' in info:
              pb = WeiboProfile_pb2.WeiboProfile()
              pb.ParseFromString(info['pb'])
              if len(pb['tag']) > 0:
               output_tag.write(info['uid']+'\t'+' '.join(pb['tag'])+'\n')

            doc_num += 1
            if doc_num % 10000 == 0:
                print "loaded %s docs" % doc_num
    print "%d\t%d" % (doc_num, find_num)
    print "load finished"
    output.close()
    #output_tag.close()

if __name__ == "__main__":
    read_mongo(max_doc = int(sys.argv[1]))
