#!/usr/bin/python
#encoding=utf8
import lxml
from lxml.html import fromstring as eparse
import sys,json,re,codecs
    
def parse_profile(t):
    item = {}

    #user name
    name_div = t.cssselect('div[class="mod-userinfo"]')
    if name_div:
        name_link = name_div[0].cssselect('a')
        if name_link:
            item['name'] = name_link[0].text_content().strip().replace('\n',' ')

    #space name
    space_section = t.xpath('//section[contains("mod-topspaceinfo",@class)]')
    if space_section:
        space_link = space_section[0].cssselect('a')
        if space_link:
            item['space_name'] = space_link[0].text_content().strip().replace('\n',' ')

    #keywords and descs
    keywords = t.cssselect('meta[name="keywords"]')
    if keywords:
        item['keywords'] = keywords[0].get("content").strip().replace('\n',' ')
    desc = t.cssselect('meta[name="description"]')
    if desc:
        item['description'] = desc[0].get("content").strip().replace('\n',' ')

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
                    user_id = profile_id[20:]
                    info['baidu_id'] = user_id
                    output = json.dumps(info)
                    fn_profile.write('%s\n' % (output))
                    print profile_id
                else:
                    info = parse_dir(page)
                    fn_dir.write('%s\n' % ('\n'.join(info)))

            if line.find('www.baidu') != -1:
                #skip www.baidu.com
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
            user_id = profile_id[20:]
            info['baidu_id'] = user_id
            output = json.dumps(info)
            fn_profile.write('%s\n' % (output))
        else:
            info = parse_dir(page)
            fn_dir.write('%s\n' % ('\n'.join(info)))
    fn_profile.close()
    fn_dir.close()

