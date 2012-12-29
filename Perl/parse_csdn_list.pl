#!/home/y/bin/perl
use Data::Dumper;
use HTML::Parser ();
use Encode;

use utf8;

$p = HTML::Parser->new( api_version => 3,
                        start_h => [\&start, "tagname, attr"],
                        text_h => [\&text, "dtext"],
                        marked_sections => 1,
                      );



my $find_data= 0,$find_name = 0,$find_extra = 0, $find_num = 0,$find_info = 0, $find_valid = 0,$find_valid_info = 0;
my $href = "";
my $tlink = "";
my $text = "";
my $cid = "";
my $retweet_text = Encode::encode('UTF8','的勋章');
my $ruzhu_text = Encode::encode('UTF8','他的新动态');
$p->parse_file($ARGV[0]);

sub start
{
        my ($tagname, $attr) = @_;
        if($tagname eq "input" and $attr->{class} eq "hujian") {
            $cid = $attr->{id};
            my $pos = index($cid,"forum_id=");
            $cid = substr($cid,$pos);
        }elsif($tagname eq "a"){
            if($attr->{href} =~ /my.csdn.net/) {
                print "$cid\t$attr->{href}\n";
            }
        }
}

sub text
{
        my $dtext = shift;

=pod
        if($dtext =~ m/组　号/) {
          print "ok\t";
          $find_num = 1;
        }
=cut
        #if($dtext =~ m/粉丝/){
        #  print "$dtext\n";
        #}
}
