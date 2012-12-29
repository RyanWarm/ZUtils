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
my $cid = 0;
my $retweet_text = Encode::encode('UTF8','的勋章');
my $ruzhu_text = Encode::encode('UTF8','他的新动态');
$p->parse_file($ARGV[0]);

sub start
{
        my ($tagname, $attr) = @_;
        if($tagname eq "input" and $attr->{class} eq "hujian") {
            print "\n$attr->{id}";
        }elsif($tagname eq "img" and $attr->{id} eq "userAvatar"){
            print "\t$attr->{src}";
        }elsif($tagname eq "h3") {
            $find_info = 1;
            $find_num = 0;
        }elsif($tagname eq "ul" and $attr->{class} eq "u_info_list") {
            $find_num = 1;
        }elsif(($find_num == 1 or $attr->{class} eq "first bor6") and $tagname eq "li") {
            print "\t";
        }elsif($tagname eq "span" and ($attr->{class} eq "text_atr" or $attr->{class} eq "text_val") ) {
            $find_data = 1;
        }elsif($tagname eq "a" and $attr->{class} eq "text_count") {
            print ":";
            $find_data = 1;
            $find_extra = 1;
        }elsif($tagname eq "div" and $attr->{class} eq "side") {
            $find_info = 0;
            $find_num = 0;
        }elsif($tagname eq "h4" and $attr->{class} eq "SC_vdata_tit") {
            $find_valid = 1;
        }elsif($tagname eq "p" and $attr->{class} eq "desc" and $find_valid == 1) {
            $find_valid_info = 1;
        }
}

sub text
{
        my $dtext = shift;
        if ($find_info eq 1) {
          $dtext =~ s/\s+//g;
          $dtext =~ s/\n//g;
          $dtext =~ s/\t//g;
          if($dtext =~ /$retweet_text/) {
            $find_num = 0;
            $find_info = 0;
            return;
          }
          if(length($dtext) > 0) {
            print "\t$dtext\t";
          }
          $find_info = 0;
        }   
        if ($find_data eq 1) {
          $dtext =~ s/\s+//g;
          $dtext =~ s/\t//g;
            $dtext =~ s/\n//g;
          if(length($dtext) > 0) {
            print $dtext;
           }
           if ($find_extra eq 1) {
             print "\t";
             $find_extra = 0;
           }
           $find_data = 0;
           return;
        }

        if ($find_num eq 1) {                                                            
          $dtext =~ s/\s+//g;                                                             
            $dtext =~ s/\n//g;                                                             
          $dtext =~ s/\t//g;
          if(length($dtext) > 0) {                                                        
            print "$dtext";                                                            
           }                                                                              
        }

        if ($find_valid_info eq 1) {                                                            
          $dtext =~ s/\s+//g;                                                             
            $dtext =~ s/\n//;                                                             
          if(length($dtext) > 0) {                                                        
            print "Validation_Info:$dtext\t";                                                            
           }                                                                              
           $find_valid_info = 0;
           $find_valid = 0;
        }

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
