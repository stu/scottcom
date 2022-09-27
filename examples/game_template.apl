###############################################################################
#
# ScottCom Game Template v0.1 - 20051031 - Stu George
#



###############################################################################
# Our TI99 Title Screen
#          1         2         3
# 123456789012345678901234567890123456789

title_screen =
 "          SAMPLE ADVENTURE #1",
 "",
 "    A sample adventure for ScottCom",
 "            by Stu George.",
 "",
 "",
 "",
 "",
 "    Press ENTER to start playing.";

###############################################################################
#
# define word length, light time and how much you can carry
#

word_length = 4;
light_time = 16;
max_load = 6;


###############################################################################
#
# Declare the direction nouns.  They must be declared before any other noun.
#
noun(north) north;
noun(south) south;
noun(east)  east;
noun(west)  west;
noun(up)    up;
noun(down)  down;

###############################################################################
#
# Declare some important game verbs
#
verb(go) 	go;
verb(drop) 	drop, putdown, put, place, leave;
verb(get) 	get, take, pickup, grab, steal, snatch;

###############################################################################
#
# declare some important flags
#
flag f_Intro;		# Set if intro written.
flag(night) f_Night;	# Turn this on for darkness.
flag(runout) f_Runout;	# Set when light has just run out.


###############################################################################
#
# Declare your game verbs and nouns here.....
#
verb inventory, inv, i;
verb look, l, examine, ex, x;
verb light, ignite;
verb unlight, putout;
verb quit, q;
verb save;
verb score;


###############################################################################
#
# declare game rooms here
#


###############################################################################
#
# declare game items here...
#


###############################################################################
#
# Implicit code routines here.....
#

act auto 100
{
	!set(f_Intro);
	on f_Intro;

	"This is a small example adventure. You are required to enter "
	"the cave and retrieve the diamond, drop it here, and say score!";
}

###############################################################################
#
# Explicit routines here......
#

###############################################################################
#
# declare standard routines.
#

act inventory any
{
	.inv;
}

act look any
{
	#.room;
	"I don't see anything special.";
}

act quit any
{
	.nl;
	.nl;
	"Game is over. Press any key to quit.";
	quit;
}

act save any
{
	save;
}

act score any
{
	.score;
}

###############################################################################
#
# mark the treasure room and start location
#

treasure = ROOM_NAME;
initial = ROOM_NAME;
