#!/usr/bin/python
#encoding=utf8
import lxml
from lxml.html import fromstring as eparse
import sys,json,re,codecs

def parse_dynamic(t):
    r = []

    find = t.cssselect('div[class="per_dynamic"]')
    if find:
        titles = find[0].xpath('//a[contains(@href,"http:")]')
        for li in titles:
            r.append(li.text_content().strip().replace('\n',' '))

    return r

def parse_profile(t):
    item = {}

    per_info = t.cssselect('div[class="per_info"]')
    if per_info:
        name = per_info[0].cssselect('dt')
        if name:
            item['name'] = name[0].text_content().strip().replace('\n',' ')

        infos = per_info[0].cssselect('dd')
	    print "len===",len(infos)
	    if infos:
            comma = '：'
	    for info in infos:
		value = info.text_content()
	        if value.find('性别') > -1:
		    item['gender'] = value[value.find(comma)+1:]
	        if value.find('简介') > -1:
		    item['intro'] = value[value.find(comma)+1:]
	        if value.find('日期') > -1:
		    item['date'] = value[value.find(comma)+1:]

    self_img = t.cssselect('img[alt="spritenet"]')
    if self_img:
        item['img'] = self_img[0].attrib['src'].strip().replace('\n','')

    status = t.cssselect('div[class="result"]')
    if status:
        sta_lines = status[0].cssselect('dd')
        if sta_lines and len(sta_lines) == 3:
            spans = sta_lines[0].cssselect('span')
            if spans and len(spans) == 2:
                item['score_pro'] = spans[1].text_content().strip().replace('\n',' ')

            spans = sta_lines[1].cssselect('span')
            if spans and len(spans) == 3:
                item['score_blog'] = spans[0].text_content().strip().replace('\n',' ')
                item['rank_blog'] = spans[1].text_content().strip().replace('\n',' ')
                item['visit_blog'] = spans[2].text_content().strip().replace('\n',' ')
            
    return item

def parse_dir(t):
    r = []
    try:
        t=eparse(page)
    except lxml.etree.ParserError:
       print sys.stderr, "page content error"
       return r
    sel = t.cssselect('h2 strong a')
    for li in sel:
       r.append(li.attrib['href'])
    return r

def parse(page):
    info = {}
    try:
        t=eparse(page)
    except lxml.etree.ParserError:
       print sys.stderr, "page content error"
       return info
    info = parse_profile(t)
    dynamic = parse_dynamic(t)
    info['dynamic'] = dynamic
    return info

if __name__=='__main__':
    reload(sys)
    sys.setdefaultencoding('utf8')
    fd = open(sys.argv[1])
    fn_profile = open(sys.argv[2],'w')
    fn_dir = open(sys.argv[3],'w')
    #fd = codecs.open(sys.argv[1],'r','utf8')
    content = []
    profile_id = ''
    #import pdb
    #pdb.set_trace()
    profile_num = 0

    for line in fd:
       if line.find('<input class=hujian') != -1:
         if len(content) > 5:
           profile_num = profile_num + 1
           page = '\n'.join(content)
           if profile_id.find('pub/dir/') == -1:
               info = parse(page)
               info['uid'] = profile_id
               output = json.dumps(info)
               fn_profile.write('%s\n' % (output))
           else:
               info = parse_dir(page)
               fn_dir.write('%s\n' % ('\n'.join(info)))
         else:
           print profile_id 
         profile_id = line[24:-3]
         content = []
       content.append(line.rstrip())

    page = '\n'.join(content)
    if profile_id.find('pub/dir/') == -1:
        info = parse(page)
        info['uid'] = profile_id
        output = json.dumps(info)
        fn_profile.write('%s\n' % (output))
    else:
        info = parse_dir(page)
        fn_dir.write('%s\n' % ('\n'.join(info)))
    fn_profile.close()
    fn_dir.close()

