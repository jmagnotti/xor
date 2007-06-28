#! /usr/bin/perl

use Switch;

%nodes = ();

$nodes{'22'} = '7';
$nodes{'23'} = '14';
$nodes{'24'} = '21';
$nodes{'25'} = '1';
$nodes{'26'} = '8';
$nodes{'27'} = '15';
$nodes{'28'} = '22';
$nodes{'29'} = '29';
$nodes{'30'} = '2';
$nodes{'31'} = '9';
$nodes{'32'} = '16';
$nodes{'33'} = '23';
$nodes{'34'} = '30';
$nodes{'35'} = '3';
$nodes{'36'} = '10';
$nodes{'37'} = '17';
$nodes{'38'} = '24';
$nodes{'39'} = '31';
$nodes{'40'} = '4';
$nodes{'41'} = '11';
$nodes{'42'} = '18';
$nodes{'43'} = '25';
$nodes{'44'} = '32';
$nodes{'45'} = '5';
$nodes{'46'} = '12';
$nodes{'47'} = '19';
$nodes{'48'} = '26';
$nodes{'49'} = '33';
$nodes{'50'} = '13';
$nodes{'51'} = '20';
$nodes{'52'} = '27';

switch($ARGV[0])
{
	case "vlc"
	{
		while(my($key,$value) = each(%nodes))
		{
			vlc($key,$value);
		}
	}
	case "killallvlc"
	{
		while(my($key,$value) = each(%nodes))
		{
			killallvlc($key);
		}
	}

	case "cars"
	{
		while(my($key,$value) = each(%nodes))
		{
			cars($key);
		}
	}
	case "killallcars"
	{
		while(my($key,$value) = each(%nodes))
        {
			killallcars($key);
        }
    }

	case "photoalbum"
	{
		while(my($key,$value) = each(%nodes))
        {
			photoalbum($key);
		}
    }

	case "killallphotoalbum"
	{
		while(my($key,$value) = each(%nodes))
        {
			killallphotoalbum($key);
		}
    }

	case "restartgdm"
	{
		while(my($key,$value) = each(%nodes))
        {
			restartgdm($key);
        }
    }

}

sub vlc
{
	($node, $wallactive) = @_;

	@args = ("ssh", "-f", "-i", "id_rsa", "display\@wall-node$node", "export DISPLAY=:0 && vlc -f --vout-filter wall --wall-rows 5 --wall-cols 7 --wall-active $wallactive udp:\@239.239.239.239:2007");

	system(@args);
}

sub killallvlc
{
	($node) = @_;

	@args = ("ssh", "-i", "id_rsa", "display\@wall-node$node", "killall vlc");

	system(@args);
}

sub photoalbum
{
	($node) = @_;
	@args = ("ssh", "-f", "-i", "id_rsa", "display\@wall-node$node",
		"export DISPLAY=:0 && cd ~/master2/xor/src/demo/photoalbum/ && ~/master2/xor/src/demo/photoalbum/PhotoAlbum");
	system(@args);

}

sub killallphotoalbum
{
	($node) = @_;
    @args = ("ssh", "-i", "id_rsa", "display\@wall-node$node", "killall
		PhotoAlbum");
	system(@args);

}

sub cars
{
	($node) = @_;
	@args = ("ssh", "-f", "-i", "id_rsa", "display\@wall-node$node",
		"export DISPLAY=:0 && cd ~/master2/xor/src/demo/cars/ &&
		~/master2/xor/src/demo/cars/Cars");
	system(@args);

}
sub killallcars
{
        ($node) = @_;
        @args = ("ssh", "-i", "id_rsa", "display\@wall-node$node", "killall Cars");
        system(@args);
}


sub restartgdm
{
        ($node) = @_;
        @args = ("ssh", "-i", "id_rsa", "root\@wall-node$node", "/etc/init.d/gdm restart");
        system(@args);
}
