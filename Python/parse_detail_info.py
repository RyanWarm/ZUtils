#!/usr/bin/python
#encoding=utf8
import lxml
from lxml.html import fromstring as eparse
import sys,json,re,codecs

def parse_work(t):
    r = []
    sel = []
    sel1 = t.cssselect('div[class="position  first experience vevent vcard summary-current"]')
    for li in sel1:
        sel.append(li)

    sel2 = t.cssselect('div[class="position   experience vevent vcard summary-past"]')
    for li in sel2:
        sel.append(li)

    for li in sel:
        item = {}
        item['company'] = {}
        find = li.cssselect('span[class="title"]')
        if find:
            item['title'] = find[0].text_content().strip().replace('\n',' ')
        find = li.cssselect('span[class="org summary"]')
        if find:
            item['company']['name'] = find[0].text_content().strip().replace('\n',' ')
        find = li.cssselect('a[class="company-profile-public"]')
        if find:
            item['company']['profile_link'] = find[0].attrib['href']
        find = li.cssselect('p[class="orgstats organization-details current-position"]')
        if find:
            item['company']['orgstats'] = find[0].text_content().strip().replace('\n',' ')
            item['current'] = 1
        find = li.cssselect('p[class="orgstats organization-details past-position"]')
        if find:
            item['company']['orgstats'] = find[0].text_content().strip().replace('\n',' ')
            item['current'] = 0
        find = li.cssselect('p[class=" description current-position"]')
        if find:
            item['desc'] = find[0].text_content().strip().replace('\n',' ')
            item['current'] = 1
        find = li.cssselect('p[class=" description past-position"]')
        if find:
            item['desc'] = find[0].text_content().strip().replace('\n',' ')
            item['current'] = 0
        find = li.cssselect('abbr[class="dtstart"]')
        if find:
            item['dtstart'] = find[0].text_content().strip().replace('\n',' ')
        find = li.cssselect('abbr[class="dtstamp"]')
        if find:
            item['dtend'] = find[0].text_content().strip().replace('\n',' ')
   
        find = li.cssselect('abbr[class="dtend"]')
        if find:
            item['dtend'] = find[0].text_content().strip().replace('\n',' ')

        find = li.cssselect('span[class="duration"]')
        if find:
            item['duration'] = find[0].text_content().strip().replace('\n',' ')

        find = li.cssselect('p[class="period"] span[class="location"]')
        if find:
            item['location'] = find[0].text_content().strip().replace('\n',' ')

        r.append(item)

    return r

def parse_edu(t):
    r = []
    sel = []
    sel1 = t.cssselect('div[class="position  first education vevent vcard"]')
    for li in sel1:
        sel.append(li)
    
    sel2 = t.cssselect('div[class="position  education vevent vcard"]')
    for li in sel2:
        sel.append(li)
    
    for li in sel:
        item = {}
        find = li.cssselect('h3[class="summary fn org"]')
        if find:
            item['school'] = find[0].text_content().strip().replace('\n',' ')
            
        find = li.cssselect('span[class="degree"]')
        if find:
            item['degree'] = find[0].text_content().strip().replace('\n',' ')
            
        find = li.cssselect('span[class="major"]')
        if find:
            item['major'] = find[0].text_content().strip().replace('\n',' ')
            
        find = li.cssselect('abbr[class="dtstart"]')
        if find:
            item['dtstart'] = find[0].text_content().strip().replace('\n',' ')
        find = li.cssselect('abbr[class="dtstamp"]')
        if find:
            item['dtend'] = find[0].text_content().strip().replace('\n',' ')
            
        find = li.cssselect('abbr[class="dtend"]')
        if find:
            item['dtend'] = find[0].text_content().strip().replace('\n',' ')
        
        find = li.cssselect('p[class=" desc details-education"]')
        if find:
            item['desc'] = find[0].text_content().strip().replace('\n',' ')

        find = li.cssselect('p[class="desc details-education"]')
        if find:
            item['activities'] = find[0].text_content().strip().replace('\n',' ')
        
        r.append(item)
    return r
    
def parse_addition(t):
    item = {}
    sel = t.cssselect('a[class="jellybean"]')
    item['skills'] = []
    item['groups'] = []
    
    for li in sel:
        item['skills'].append(li.text_content().strip().replace('\n',' '))
        
    sel = t.cssselect('a[tracking="fulpro_grplogo"]')
    for li in sel:
        if li.attrib.has_key('class') == True: continue
        link = li.attrib['href']
        group_name = li.text_content().strip().replace('\n',' ')
        item['groups'].append((link,group_name))
 
    sel = t.cssselect('dd[class="overview-connections"]')
    if sel:
        item['connections'] = sel[0].text_content().strip().replace('\n',' ')

    sel = t.cssselect('p[class=" description summary"]')
    if sel:
        item['summary'] = sel[0].text_content().strip().replace('\n',' ')

    sel = t.cssselect('div[id="profile-specialties"]')
    if sel:
        item['specialties'] = sel[0].text_content().strip().replace('\n',' ')

    sel = t.cssselect('p[class="headline-title title"]')
    if sel:
        item['headline-title'] = sel[0].text_content().strip().replace('\n',' ')

    sel = t.cssselect('dd span[class="locality"]')
    if sel:
        item['location'] = sel[0].text_content().strip().replace('\n',' ')

    sel = t.cssselect('dd[class="industry"]')
    if sel:
        item['industry'] = sel[0].text_content().strip().replace('\n',' ')

    sel = t.cssselect('div[id="profile-picture"] img')
    if sel:
        item['profile-pic'] = sel[0].attrib['src'].strip().replace('\n','')

    sel = t.cssselect('title')
    if sel:
        item['name'] = sel[0].text_content().strip().replace('  - China | LinkedIn','').replace(' | LinkedIn','')
        item['name'] = item['name'].replace(' - China','').rstrip()
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
    info = parse_addition(t)
    work = parse_work(t)
    info['work'] = work
    edu = parse_edu(t)
    info['edu'] = edu
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
