#!/usr/bin/python
#encoding=utf8
import lxml
from lxml.html import fromstring as eparse
import sys,json,re,codecs
    
def parse_profile(t):
    item = {}

    infos = t.cssselect('span[class="profile-attr"]')
    if infos:
        for info in infos:
            key = info.text_content()
            if key.find("性别") != -1:
                item['gender'] = info.getnext().text_content().strip().replace('\n',' ')
                #print item['gender']
	
            if key.find("生日") != -1:
                item['birthday'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("居住地") != -1:
                item['resident'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("简介") != -1:
                item['intro'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("教育程度") != -1:
                item['edu'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("职业") != -1:
                item['career'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("联系方式") != -1:
                item['contact'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("大学") != -1:
                item['college'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("高中") != -1:
                item['highschool'] = info.getnext().text_content().strip().replace('\n',' ')
    
            if key.find("初中") != -1:
                item['juniorschool'] = info.getnext().text_content().strip().replace('\n',' ')
    
    portrait = t.cssselect('div[class="portrait"]')
    if portrait:
        img = portrait[0].cssselect('img')
        if img:
            item['img'] = img[0].get("src").strip().replace('\n',' ')

    jobs_name = t.cssselect('span[class="profile-corp-name"]')
    jobs_exp = t.cssselect('span[class="profile-corp-exp"]')
    if jobs_name and jobs_exp:
        jobs = []
        for index in range(len(jobs_name)):
            job = {}
            job['company'] = jobs_name[index].text_content()[2:].strip().replace('\n', ' ')
            job['exp'] = jobs_exp[index].text_content().strip().replace('\n', ' ')
            jobs.append(job)
        item['jobs'] = jobs

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
    user_id = ''
    #import pdb
    #pdb.set_trace()

    skip = 0
    for line in fd:
        if line.find('<input class=hujian') != -1:
            if len(content) > 5 and skip == 0:
                page = '\n'.join(content)
                if profile_id.find('pub/dir/') == -1:
                    info = parse(page)
                    info['uid'] = profile_id
                    user_id = profile_id[23:-7]
                    info['name'] = user_id
                    output = json.dumps(info)
                    fn_profile.write('%s\n' % (output))
                    print profile_id
                else:
                    info = parse_dir(page)
                    fn_dir.write('%s\n' % ('\n'.join(info)))

            if line.find('hi.baidu') != -1:
                #skip hi.baidu.com
                skip = 1
            else:
                skip = 0
            profile_id = line[24:-3]
            content = []

        if skip == 0:
            content.append(line.rstrip())

    if skip == 0:
        page = '\n'.join(content)
        if profile_id.find('pub/dir/') == -1:
            info = parse(page)
            info['uid'] = profile_id
            user_id = profile_id[23:-7]
            info['name'] = user_id
            output = json.dumps(info)
            fn_profile.write('%s\n' % (output))
        else:
            info = parse_dir(page)
            fn_dir.write('%s\n' % ('\n'.join(info)))
    fn_profile.close()
    fn_dir.close()

