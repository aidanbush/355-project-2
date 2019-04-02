#! /usr/bin/perl
use FileHandle;
use IPC::Open2;

if($#ARGV!=1)
{
  print "USAGE: driver.pl blackplayer whiteplayer\n";
}
else
{


    $pid1 = open2( \*Reader1,\*Writer1, "stdbuf -i0 -o0 -e0 ./$ARGV[0] newgame.txt B" );
    Writer1->autoflush();
    $ll=<Reader1>;
    print "B:";
    print $ll;
    $ll=substr($ll,0,-1);
    $ll.=".txt";
    $pid2 = open2( \*Reader2,\*Writer2, "stdbuf -i0 -o0 -e0 ./$ARGV[1] $ll W" );
    Writer2->autoflush();
    for($i=0;$i<=33;$i++)
    {
       $ll=<Reader2>;
       print "W:";
       print $ll;
       print Writer1 $ll;
       $ll=<Reader1>;
       print "B:";
       print $ll;
       print Writer2 $ll;
    }
 }
