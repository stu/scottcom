#
# Note, This port uses a special 'flag' so that the Bunyon interpreter
# will not auto-interpreter n/s/e/w commands before running any code
# (standard scott adams behaviour is to auto run the n/s/e/w code
# before it runs any user written code!)
#

title_screen =
    #1234567890123456789012345678901234567890
    "",
    "",
    "",
    "          Lost Dutchman's Mine",
    "                   By",
    "",
    "          Cleveland M. Blakemore",
    "   Written in 1988 for Ahoy! magazine",
    "",
    "",
    "     Port Version 0.4 - Stu George",
    "",
    "",
    "         Press a key to continue.",
    "";

alias version_string = "Port Version 0.4 by Stu George";

word_length = 31;
light_time = 1000;
max_load = 6;

noun(north) north;
noun(south) south;
noun(east)  east;
noun(west)  west;
noun(up)    up;
noun(down)  down;

verb(go)    go;
verb(drop)  drop, putdown, put, place, leave;
verb(get)   get, take, pickup, grab, steal, grift, lift, snatch;

verb call;
verb dig;
verb shoot;
verb kill;
verb say;
verb turn, rotate, twist;
verb whistle, blow;

verb read, see, glance, peruse;
verb inventory, inv, i;
verb quit, q;
verb climb, shinny;
verb throw, chuck, pitch, lob, toss;
verb look, l, examine, ex, x;

verb light, ignite;

verb versions, vers, ver;

noun gozer;
noun shelf;

room rm_GasStation
	"You are in a deserted last chance gas station."
	;

initial = rm_GasStation;
treasure = rm_GasStation;

room rm_AdobeHouse
	"You are in a dusty adobe house with a sunbeam coming through an east window.",
	n_to rm_MineEnterance
	;

room rm_EW_MineShaft
	"You are in a long e-w mineshaft",
	u_to rm_GraniteTunnel,
	w_to rm_StoneStaircase,
	e_to rm_CoolCavern
	;

room rm_GraniteTunnel
	"You are in a sloping granite tunnel.",
	d_to rm_EW_MineShaft,
	u_to rm_MineEnterance
	;

room rm_MineEnterance
	"You are in front of an old boarded up mineshaft entrance",
	n_to rm_GraniteTunnel,
	s_to rm_AdobeHouse,
	w_to rm_Ravine
	;

room rm_CoolCavern
	"You are inside a cool cavern with a small crack leading down to the north.",
	n_to rm_RiverBed,
	d_to rm_RiverBed,
	w_to rm_EW_MineShaft
	;


room rm_StoneStaircase
	"You are on a spiral stone staircase.",
	e_to rm_EW_MineShaft,
	e_to rm_EW_MineShaft,
	d_to rm_BurialGround
	;

room rm_RiverBed
	"You are in a subterranean river bed running east & west.",
	s_to rm_CoolCavern,
	u_to rm_CoolCavern
	;


room rm_BurialGround
	"You are in an ancient indian burial ground.",
	u_to rm_StoneStaircase
	;

room rm_Ravine
	"You are in a deep ravine.",
	e_to rm_MineEnterance
	;

noun plaque;
item itm_Plaque (plaque) "a metal plaque above a glass shelf" rm_GasStation;

noun skull;
item itm_Skull (skull) "a skull mounted on a spear" rm_AdobeHouse;

noun skeleton;
item itm_Skeleton (skeleton) "a skeleton draped with cobwebs" rm_EW_MineShaft;

noun spirit;
item itm_Spirit (spirit) "a whistling evil spirit" rm_MineEnterance;

noun calendar;
item itm_Calendar (calendar) "a colossal stone sun calendar" rm_CoolCavern;

noun wolf, timber;
item itm_Wolf (wolf) "a ravenous snarling timber wolf!" rm_StoneStaircase;
item itm_DeadWolf (wolf) "a dead timber wolf" void;

noun wheel;
item itm_Wheel (wheel) "a circular wheel set in the middle of an iron door to the east" rm_RiverBed;

noun mound;
item itm_Mound (mound) "a large burial mound" rm_BurialGround;

noun matchbook, book;
item itm_Matchbook (matchbook) "a matchbook" rm_GasStation;

noun torch;
item itm_UnlightTorch (torch) "a wooden torch" rm_AdobeHouse;
item (light) itm_Torch (torch) "a lit torch" void;

noun revolver, gun, pistol;
item itm_Revolver (revolver) "a perl handled revolver" rm_GasStation;

noun bottle;
item itm_Bottle (bottle) "an empty 7-Up bottle" rm_GasStation ;

noun ruby;
item itm_Ruby (ruby) "a lustrous red ruby." void;

noun bullets;
item itm_Bullets (bullets) "a handfull of rusty bullets." rm_EW_MineShaft;

noun shovel;
item itm_Shovel (shovel) "a rusty shovel" rm_Ravine;

noun diamond;
item itm_Diamond (diamond) "a glowing diamond" rm_RiverBed;

noun nugget;
item itm_Nugget (nugget) "the dutchman's nugget" void;

flag (night) f_Darkness;
flag f_Intro;
flag f_Temp;

flag f_GoCrack;
flag f_ReleasedWater;

timreg t_Zero;
timreg t_WolfCount;
timreg t_GhostCount;
timreg t_River;

roomreg rSwap;

act auto 100
{
	!set(f_Intro);
	on f_Intro;

	# set some variables, so our interp sees a special sign.....
	timer 115;	# s
	timer 103;	# g
	timer 101;	# e
	timer 111;	# o
	timer 114;	# r
	timer 103;	# g
	timer 101;	# e
	try
	{
		gt(0);
		"This game was designed to run on Bunyon.";
		ignore;
		die;
		quit;
	}

	"Welcome to the Lost Ducthman's Mine by Cleveland M. Blakemore, written in 1988 for Ahoy! magazine. Ported to Scott Adams Format as a test.";
	.nl;
	.nl;
	version_string;
	.nl;

	# set wolf attack to 0.
	timer 0;
	swap t_WolfCount;

	# set ghost attack to 0
	timer 0;
	swap t_GhostCount;

	timer 0;
	swap t_Zero;

	timer 3;
	swap t_River;

	goto rm_AdobeHouse;
	swap rSwap;
	goto rm_GasStation;

	!inv;
}

act auto 100
{
	!avail(itm_Torch);

	try
	{
		in(rm_GasStation);
		off f_Darkness;
		end;
	}

	try
	{
		in(rm_AdobeHouse);
		off f_Darkness;
		end;
	}

	try
	{
		in(rm_MineEnterance);
		off f_Darkness;
		end;
	}

	try
	{
		in(rm_Ravine);
		off f_Darkness;
		end;
	}

	try
	{
		in(rm_EW_MineShaft);
		off f_Darkness;
		end;
	}

	on f_Darkness;
}

act go down
{
	in(rm_CoolCavern);
	on f_GoCrack;
}

act go north
{
	in(rm_CoolCavern);
	on f_GoCrack;
}

act go crack
{
	in(rm_CoolCavern);
	on f_GoCrack;
}

act auto 100
{
	in(rm_CoolCavern);
	set(f_GoCrack);
	off f_GoCrack;
	timer 0;

	try
	{
		has(itm_Matchbook);
		add 1;
	}

	try
	{
		has(itm_Revolver);
		add 1;
	}

	try
	{
		has(itm_Bottle);
		add 1;
	}

	try
	{
		has(itm_Ruby);
		add 1;
	}

	try
	{
		has(itm_Bullets);
		add 1;
	}

	try
	{
		has(itm_Shovel);
		add 1;
	}

	try
	{
		has(itm_Diamond);
		add 1;
	}

	try
	{
		has(itm_Nugget);
		add 1;
	}

	try
	{
		has(itm_Torch);
		add 1;
	}

	try
	{
		gt(1);
		"You are carrying too much to fit throughthe crack.";
		end;
	}

	try
	{
		eq(1);			# has torch?
		has(itm_Torch);
		"OK.";
		goto rm_RiverBed;
	}
}

act auto 100
{
	in(rm_GraniteTunnel);
	has(itm_Torch);
	!exists(itm_Ruby);
	move rm_GraniteTunnel, itm_Ruby;
}

act auto 100
{
	in(rm_EW_MineShaft);

	# reset wolf attack count
	timer 0;
	swap t_WolfCount;
}

act read matchbook
{
	has(itm_Matchbook);
	"Gozer Travel inc. 'Need to travel?? Call Gozer!!'";
}

act read plaque
{
	here(itm_Plaque);
	"Put all the treasure on this shelf.";
}

act help any
{
	try
	{
		in(rm_AdobeHouse);
		"Try reading the matchbook.";
		end;
	}
	
	"Try to find the gold and escape!";
}

act call gozer
{
	off f_Temp;

	try
	{
		in(rm_AdobeHouse);
		on f_Temp;
	}

	try
	{
		in(rm_GasStation);
		on f_Temp;
	}

	set(f_Temp);
	swap rSwap;
}

act call gozer
{
	"Not from here.";
}

act whistle bottle
{
	has(itm_Bottle);
	here(itm_Spirit);

	.nl;
	"The spirit writhes and vanishes in a cloud of smoke.";

	zap itm_Spirit;
}

act whistle any
{
 	"Tweet Tweet Tweet...";

 	# load ghost count
 	swap t_GhostCount;

 	try
 	{
		here(itm_Spirit);

 		.nl;
		"The spirit trembles and wavers a little.";

		add 1;
		.nl;
	}

	try
	{
		here(itm_Spirit);

		gt(2);
		.nl;
		.nl;
		"The spirit looks real angry!";
	}

	try
	{
		here(itm_Spirit);

		eq(5);
		.nl;
		.nl;
		"The evil spirit sucked the breath out of you!";
		die;
		quit;
	}

	# save it back
	swap t_GhostCount;
}

act auto 100
{
	try
	{
		in(rm_EW_MineShaft);
		off f_Darkness;
	}

	try
	{
		in(rm_GraniteTunnel);
		on f_Darkness;
	}
}


act auto 100
{
	in(rm_StoneStaircase);
	here(itm_Wolf);

	# load wolfcount
	swap t_WolfCount;
	add 1;

	try
	{
		eq(2);
		.nl;
		"The timber wolf tears you to shreds.";
		die;
		quit;
	}

	# save wlfcount
	swap t_WolfCount;
}

act go north
{
	in(rm_MineEnterance);
	here(itm_Spirit);
	"The spirit scares you back.";
}

act light torch
{
	try
	{
		has(itm_Torch);
		"It's already burning.";
		end;
	}

	try
	{
		!has(itm_UnlightTorch);
		"I dont have it.";
		end;
	}

	try
	{
		has(itm_UnlightTorch);
		!has(itm_Matchbook);
		"What with?";
		end;
	}

	has(itm_UnlightTorch);
	has(itm_Matchbook);
	swap itm_UnlightTorch, itm_Torch;
	"It's burning.";
}

act look skeleton
{
	here(itm_Skeleton);
	"His bony claw points to the east.";
}


act shoot wolf
{
	here(itm_Wolf);
	has(itm_Revolver);

	try
	{
		!has(itm_Bullets);
		"I have no bullets!";
		end;
	}

	try
	{
		has(itm_Bullets);
		"The revolver thunders fire and the wolf falls over dead in mid-leap.";
		swap itm_DeadWolf, itm_Wolf;
	}
}

act turn wheel
{
	in(rm_RiverBed);
	!set(f_ReleasedWater);
	on f_ReleasedWater;

	"The door blasts open with a tidal wave of water!!!";
	.nl;
	"The river bed quickly fills up and you are drenched.";
	.nl;
	"You'd better leave. It's almost neck deep in here!";

	swap t_River;
	timer 3;
	swap t_River;
}

act auto 100
{
	in(rm_RiverBed);
	set(f_ReleasedWater);
	swap t_River;

	try
	{
		gt(0);
		sub 1;
	}

	try
	{
		eq(1);
		"Bubbles are coming out of your clenched lips under water.";
	}

	try
	{
		eq(0);
		"You drowned in the river.";
		die;
		quit;
	}

	swap t_River;
}

act go down
{
	in(rm_StoneStaircase);

	try
	{
		here(itm_Wolf);
		"The wolf wont let me....";
		end;
	}

	try
	{
		!set(f_ReleasedWater);
		!here(itm_Wolf);
		goto rm_BurialGround;
		.room;
		goto rm_StoneStaircase;

		"You quickly come back up, its flooded down there.";
		end;
	}

	try
	{
		set(f_ReleasedWater);
		!here(itm_Wolf);
		goto rm_BurialGround;
	}
}

act dig any
{
	in(rm_BurialGround);

	try
	{
		moved(itm_Nugget);
		"The mound has already been excavated.";
		end;
	}

	try
	{
		!moved(itm_Nugget);
		"okay, you have dug a deep hole...";
		move rm_BurialGround, itm_Nugget;
	}
}

act inventory any
{
	.inv;
}

act look any
{
	.room;
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


act auto 100
{
	in(rm_GasStation);
	here(itm_Ruby);
	here(itm_Diamond);
	here(itm_Nugget);

	"Congratulations! you've won the game!";
	quit;
}

act version any
{
	version_string;
	.nl;
}
