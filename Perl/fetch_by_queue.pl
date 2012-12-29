#!/usr/bin/perl -w
use JSON;
use DBI;
use Net::Stomp;
use Data::Dumper;
use Date::Format; 
use Date::Parse; 
use Time::Local;
use Getopt::Long;
use YAML::Syck;
use Encode;

my $config_file;
my $debug = 0;
GetOptions(
    "config=s" => \$config_file,
    "debug=i" => \$debug,
);
if(!$config_file){
    print STDERR "Usage: -config xx\n";
    exit -1;
}
my $config = LoadFile($config_file);
my $input_queue = $config->{ActiveMQ}->{fetch_input_queue};
my $out_page_queue = $config->{ActiveMQ}->{fetch_out_queue};
my $queue_host = $config->{ActiveMQ}->{hostname};
my $queue_port = $config->{ActiveMQ}->{port}; 

my $stomp = Net::Stomp->new( { hostname => $queue_host, port => $queue_port } );
$stomp->connect( { login => '', passcode => '' } );

my $file="tt_users";
open FILE, "<$file" or die "ERROR:can't open $file";
my @keywords;

my $line_id = 0;
while(<FILE>)
{
    chomp;
    $line_id += 1;
    next if ($line_id < 3800001);
    #last if ($line_id == 3800000);
    my $w = $_;
    push @keywords,$w;
}

my $i = 0;
while($i < (scalar(@keywords)))
{
    my @fields = split /\t/,$keywords[$i];
    my $name = $fields[1];
    my $link = "http://p.t.qq.com/m/home_userinfo.php?u=$name";
    print STDERR "Send user id $link\n";
    my $req = {
        id  => 1,
        link => $link,
        seq => time,
        page_queue => $out_page_queue,
        headers => {
            'User-Agent' => 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.7; rv:11.0) Gecko/20100101 Firefox/11.0',
            'Cookie' => 'qqmusic_uin=12345678; qqmusic_key=12345678; qqmusic_fromtag=30; verifysession=h000ed4920f448afcaaa9a6a96c0d66c41257224b106a7ddef8f9c2ec8f5a6035e25abfcafbdba6793efb802faf29db9922; mb_reg_from=8; ptisp=cnc; pgv_pvi=7690862592; pgv_si=s3514812416; FTN5K=3cfbcca5; suid=7744538464; qm_authimgs_id=0; qm_verifyimagesession=h00154cb147686d465a75cc6ed8629a075a3c1a42f2f51071afb91f771a0b07ed3ccf30995c4a33df69; qm_sid=c75301b8cdb1138ca7237f7922aa2f08,c-zqbkfVGKlg.; qm_username=2610073010; qm_domain=http://exmail.qq.com; qm_qz_key=1_b8a6b20214b871f2fc1dadf0124bdb47010a0d050f0100000204; dm_login_weixin_scan=; wbilang_1487866256=zh_CN; wbilang_10000=zh_CN; home_silentUserJump=1; qm_sk=-1684894286&zXDT6vN8; qm_ssum=-1684894286&81103affd534326c79613c10cc6b7959; wb_regf=%3B0%3B%3Bmessage.t.qq.com%3B0; pt2gguin=o1945841107; uin=o1945841107; skey=@yFjYk5rb6; RK=z9hm0jbmvX; luin=o1945841107; lskey=00010000455b612c82369d754ad24235d30eaf1d58ccab459eaf51b3cf936f74de2ec4712428e4e1ad054eec; ptui_loginuin=hewei2021; wbilang_1945841107=zh_CN; pgv_pvid=6473165951; pgv_info=ssid=s6854965406&pgvReferrer=http://dict.qq.com/; o_cookie=1945841107',
            'Host'   => "p.t.qq.com",
        },
        'max_redirects' => 5,
        'max_retry' => 5,
        'task_id' => 'tencent',
    };
    $stomp->send({
        destination => $input_queue,
        body => to_json $req,
    });
    $i = $i + 1;
}

