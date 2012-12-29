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

# connect to tweets cluster update queue
my $stomp = Net::Stomp->new( { hostname => $queue_host, port => $queue_port } );
$stomp->connect( { login => '', passcode => ''});
$stomp->subscribe({
    destination             => $out_page_queue,
    'ack'                   => 'client',
    'activemq.prefetchSize' => 1
});

while(1)
{
    my $frame = $stomp->receive_frame;
    if ($frame->body)
    {
        Add2Buffer($frame->body);
    }
    $stomp->ack( { frame => $frame } );
    $cnt ++;
    last if ($debug ==2 );
}
$stomp->disconnect;

# ------------- methods ---------------
sub Add2Buffer
{
    my $buffer_item = {};
    my $obj_str = shift @_;
    my $obj;
    eval{
        $obj  = from_json $obj_str ;
        #$obj  = $json->decode ( $obj_str ) ;
    };
    if ( !defined($obj) ){
        print STDERR "ERROR: Cannot decode json string\t$obj_str\n";
        return;
    }

    my $link = $obj->{resp}->{'link'};
    my $body = $obj->{resp}->{'body'};
  
    print '<input class=hujian id="'."$link".'">'."\n";
    print "$body\n";
}
