import lxml
from lxml.html import fromstring as eparse
import sys,json,re,codecs

def parse(page):
    try:
       t=eparse(page)
    except lxml.etree.ParserError:
       print sys.stderr, "page content error"
       return info

    info = {}
    
def parse_csdn(page):
    try:
        t=eparse(page)
    except lxml.etree.ParserError:
       print sys.stderr, "page content error"
       return info
    r = []
    sel = []
    find = t.cssselect('div[class="per_dynamic"]')
    if find:
        titles = find[0].xpath('//a[contains(@href,"http:")]')
        for li in titles:
            r.append(li.text_content().strip().replace('\n',' '))
    print "======",r
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
               info = parse_csdn(page)
               #info['uid'] = profile_id
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
        info = parse_csdn(page)
        #info['uid'] = profile_id
        output = json.dumps(info)
        fn_profile.write('%s\n' % (output))
    else:
        info = parse_dir(page)
        fn_dir.write('%s\n' % ('\n'.join(info)))
    fn_profile.close()
    fn_dir.close()
