#!/usr/bin/perl -w

use strict;
use warnings;

use LWP::UserAgent;
use Getopt::Long;
use URI::Escape;
use Encode;
use DB_File;
use Data::Dumper;
use HTTP::Request;
use HTTP::Async;
use Storable qw(nstore retrieve);
use JSON;
use DBI;
use YAML::Syck;
binmode(STDOUT, ':encoding(utf8)');
my $PARALLEL = 1;
my $INTERVAL= 30*60;


my %headers = (
    "Host"              => "p.t.qq.com",
    "User-Agent"        => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:8.0.1) Gecko/20100101 Firefox/8.0.1",
    "Accept"            => "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "Accept-Charset"   => "GBK,utf-8;q=0.7,*;q=0.3",
    "Accept-Encoding"   => "gzip, deflate,sdch",
    "Accept-Language"    => "zh-CN,zh;q=0.8",
    "Connection"        => "keep-alive",
);

my %cookie_map;

$SIG{INT}  = $SIG{HUP}  = $SIG{TERM} =
    sub {print STDOUT "gracefully exited\n";};

my $async = HTTP::Async->new;
my $json = new JSON;
$json->allow_blessed([1]);
$json->convert_blessed([1]);
$json->utf8([1]);
my $cookie = 'qqmusic_uin=12345678; qqmusic_key=12345678; qqmusic_fromtag=30; verifysession=h000ed4920f448afcaaa9a6a96c0d66c41257224b106a7ddef8f9c2ec8f5a6035e25abfcafbdba6793efb802faf29db9922; mb_reg_from=8; ptisp=cnc; pgv_pvi=7690862592; pgv_si=s3514812416; FTN5K=3cfbcca5; suid=7744538464; qm_authimgs_id=0; qm_verifyimagesession=h00154cb147686d465a75cc6ed8629a075a3c1a42f2f51071afb91f771a0b07ed3ccf30995c4a33df69; qm_sid=c75301b8cdb1138ca7237f7922aa2f08,c-zqbkfVGKlg.; qm_username=2610073010; qm_domain=http://exmail.qq.com; qm_qz_key=1_b8a6b20214b871f2fc1dadf0124bdb47010a0d050f0100000204; dm_login_weixin_scan=; wbilang_1487866256=zh_CN; wbilang_10000=zh_CN; home_silentUserJump=1; qm_sk=-1684894286&zXDT6vN8; qm_ssum=-1684894286&81103affd534326c79613c10cc6b7959; wb_regf=%3B0%3B%3Bmessage.t.qq.com%3B0; pt2gguin=o1945841107; uin=o1945841107; skey=@yFjYk5rb6; RK=z9hm0jbmvX; luin=o1945841107; lskey=00010000455b612c82369d754ad24235d30eaf1d58ccab459eaf51b3cf936f74de2ec4712428e4e1ad054eec; ptui_loginuin=hewei2021; wbilang_1945841107=zh_CN; pgv_pvid=6473165951; pgv_info=ssid=s6854965406&pgvReferrer=http://dict.qq.com/; o_cookie=1945841107';
my $file="tt_users";
open FILE, "<$file" or die "ERROR:can't open $file";
my $line_id = 0;
my @keywords;
while(<FILE>)
{
    chomp;
    $line_id += 1;
    next if ($line_id < 7922);
    my $w = $_;
    push @keywords,$w;
}

my $i = 0;
while($i <= scalar(@keywords))
{
    my @fields = split /\t/,$keywords[$i];
    my $name = $fields[1];
    if($async->total_count < $PARALLEL){
        my $link = "http://p.t.qq.com/m/home_userinfo.php?u=";
       
        add_request($link,  $name);
        $i += 1;
        next;
    }
    if($async->total_count == 0){
        print STDOUT "idle.\n";
        sleep 3;
        next;
    }
    my ($resp,$id) = $async->wait_for_next_response();
    my $age_id = delete $cookie_map{$id};
    if($resp->code == 302 ){
        my $loc = $resp->header('Location');
        if ($loc =~ /^\/([\w\/]*)$/){
            add_request($i);
        }
        elsif ($loc =~ /login\.zhihu\.com/) {
            print STDOUT "Need login\n";
        }
        else{
            print STDOUT "ERROR on URL:",$resp->request->uri->as_string,
                ", redirected to ",$resp->header('Location'),"\n";
            sleep 1000;
            last;
        }
        next;
    }
    else {
        print "<input class=hujian id=$age_id>\n";
        print $resp->decoded_content."\n";
        #if ($i % 100 == 0) {
        #  sleep 5;
        #}
    }
}



#--------------------------
sub add_request
{
    my $url = shift;
    my $offset = shift;
    die "ERROR: failed to retrieve weibo cookies\n" if (!defined($cookie));
    $url = "$url$offset";
    print STDERR "add request: $url\n";
    my $request = HTTP::Request->new(GET => $url);
   
    #[params => $params, method => "next", _xsrf => "9a5c037616c74ac6bff59b7848f1de1b"]);
    foreach my $key (keys %headers){
        $request->header($key => $headers{$key});
    }
    $request->header(Cookie => $cookie);
    my $id = $async->add_with_opts($request,{max_redirects => 2,timeout => 20});
    $cookie_map{$id} = $offset;
}

sub get_appengine_host
{
    #my $gapp_idx = int(rand(5))+1;
    #return "tb-fetch.appspot.com";
    return "localhost:8080";
}
