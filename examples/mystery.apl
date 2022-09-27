#
# Port of Mysterious Island (Mountain Valley Software)
# to ScottCom TI99/4A format
#

title_screen =
#	 123456789-123456789-123456789-123456789-
	"",
	"",
	"",
	"",
	"",
	"",
	"    Welcome to Mystery Island v0.4",
	"             by Stu George",
	"",
	"    Based on the C64 version created",
	"      by Mountain Valley Software",
	"    circa somewhere in the mid 80's",
	"",
	"                 Enjoy!",
	"",
	"",
	"",
	"",
	"        Press a key to continue.";


alias version_string = "Port Version 0.4 by Stu George";

word_length = 8;
light_time = 15;
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

verb read, see, glance, peruse;
verb inventory, inv, i;
verb panic;
verb quit, q;
verb climb, shinny;
verb throw, chuck, pitch, lob, toss;
verb look, l, examine, ex, x;
verb break, kick, smash, bash;
verb unlock;
verb pump, inflate;
verb say, shout, yell;
verb cut, saw;
verb move, push, pull;
verb rub, polish, shine;
verb spray, squirt;
verb fix, repair, mend, build;
verb shoot;
verb version, ver, credits, author;

verb one;
verb two;
verb three;
verb four;
verb five;
verb six;
verb seven;
verb eight;
verb nine;
verb zero, nought;

timreg tr_Zero;
timreg tr_Moves;
timreg tr_Pistol;

timreg tr_Safe;
timreg tr_Safe1;
timreg tr_Safe2;
timreg tr_Safe3;


flag fl_Intro;				# Set if intro written.
flag(night) fl_Night;			# Turn this on for darkness.
flag(runout) fl_RunOut;			# Set when light has just run out.

flag fl_Temp;				# temp flag
flag fl_InflatedRaft;		# inflated raft
flag fl_Stairs;				# stairs fixed
flag fl_Safe;				# rusted dial

flag fl_Safe1;
flag fl_Safe2;
flag fl_Safe3;
flag fl_SafeCrack;


room rm_Shore
	"I am on the shore.",
	s_to rm_PeninsulaFake,
	w_to rm_Rocks,
	n_to rm_PlainPath;

room rm_Peninsula
	"I am on a sandy beach.",
	n_to rm_Shore;

room rm_PeninsulaFake
	"FAKE I am on a sandy beach.",
	n_to rm_Shore;

room rm_Rocks
	"I am by a cliff.",
	e_to rm_Shore;

room rm_Shipwreck
	"I am on the deck of a ship.",
	n_to rm_Rocks;

room rm_Cabin
	"I am in the captains cabin.",
	e_to rm_Shipwreck;

room rm_Bed
	"I am in a warm bed.",
	s_to rm_Cabin;

room rm_PlainPath
	"I am on a path leading inland.",
	n_to rm_FootOfCliff,
	w_to rm_NextToHut,
	s_to rm_Shore;

room rm_NextToHut
	"I am on the banks of a river.",
	e_to rm_PlainPath;

room rm_FootOfCliff
	"I am at the foot of a sheer cliff.",
	s_to rm_PlainPath;

room rm_Plateau
	"I am on a plateau";

room rm_Waterfall
	"I am in a secret cave.",
	w_to rm_Plateau;

room rm_Lighthouse
	"I am in the lighthouse.",
	e_to rm_Plateau;


room rm_Hut
	"I am inside a wooden hut.",
	e_to rm_NextToHut;

room rm_River1
	"I am in a shallow river.",
	s_to rm_Plateau;

room rm_River2
	"I am on raft on a turbulent river";

room rm_Jungle
	"I am in a jungle clearing.";

room rm_Celler
	"I am in a small damp cellar.",
	u_to rm_Lighthouse;

room rm_TopLighthouse
	"I am at the top of the lighthouse",
	d_to rm_Lighthouse;

# death room........
room rm_RedRoom "Death!";


noun planks, wood, plank;
item itm_Planks (planks) "Planks" limbo;

noun tiger;
item itm_Tiger (tiger) "Hungry Tiger" rm_Hut;

noun cupboard;
item itm_Cupboard (cupboard) "Cupboard" rm_Hut;
item itm_CupboardOpen (cupboard) "Cupboard (Open)" void;

noun waterfall;
item itm_Waterfall (waterfall) "Waterfall" rm_Plateau;

noun lighthouse;
item itm_Lighthouse (lighthouse) "Lighthouse" rm_Plateau;

noun pistol, gun;
item itm_Pistol(pistol) "Pistol" rm_Waterfall;

noun ring;
item itm_IronRing (ring) "Iron Ring" rm_Lighthouse;
item itm_IronRing2 (ring) "Iron Ring" void;

noun trapdoor, trap;
item itm_TrapDoor (trapdoor) "Trapdoor" void;

noun chest;
item itm_Chest (chest) "Chest" rm_Celler;
item itm_ChestUnlocked (chest) "Chest" void;

noun stairs;
item itm_Stairs (stairs) "Stairs" rm_Lighthouse;

noun crab;
item itm_CrabDead (crab) "Dead Crab" void;
item itm_Crab (crab) "Giant Crab" rm_Shore;

noun meat, crabmeat;
item itm_CrabMeat (meat) "Crab Meat" limbo;

noun tree;
item itm_RottenTree (tree) "Tree" rm_Shore;

noun ocean, sea;
item itm_Ocean (ocean) "Ocean" rm_Peninsula;

noun sand;
item itm_Sand (sand) "Sand" rm_Peninsula;

noun boulder;
item itm_Boulder1 (boulder) "Boulder" rm_Peninsula;
item itm_Boulder (boulder) "Boulder" rm_FootOfCliff;

noun raft;
item itm_Raft (raft) "Raft" void;

noun rocks;
item itm_Rocks (rocks) "Rocks" rm_Rocks;

noun ship;
item itm_Ship (ship) "Wrecked Ship" rm_Rocks;

noun cabin;
item itm_Cabin (cabin) "Cabin" rm_Shipwreck;

noun door;
item itm_ClosedCabinDoor (door) "Closed Door" rm_Shipwreck;

noun cutlass, sword;
item itm_Cutlass (cutlass) "Cutlass" rm_Shipwreck;

noun rope;
item itm_Rope (rope) "Rope" rm_Shipwreck;

noun bed;
item itm_Bed (bed) "Bed" rm_Cabin;

noun table;
item itm_Table (table) "Table" rm_Cabin;

noun dish;
item itm_SilverDish (dish) "*Silver Dish*" void;

noun key;
item itm_Key (key) "Key" void;

noun bowl;
item itm_IvoryBowl (bowl) "*Ivory Bowl*" void;

noun mattress;
item itm_Mattress (mattress) "Mattress" rm_Bed;

noun emerald;
item itm_Emerald (emerald) "*Emerald*" void;

noun paper;
item itm_Paper (paper) "Paper" void;

noun sign;
item itm_Sign (sign) "Sign" rm_PlainPath;
item itm_Sign2 (sign) "Sign" rm_Waterfall;

noun shovel;
item itm_Shovel(shovel) "Shovel" rm_River1;

noun ruby;
item itm_Ruby(ruby) "*Ruby*" rm_River1;

noun river;
item itm_River (river) "River" rm_NextToHut;
item itm_River1 (river) "River" rm_Plateau;

noun hut;
item itm_WoodenHut (hut) "Wooden Hut" rm_NextToHut;

noun tunnel;
item itm_Tunnel (tunnel) "Tunnel" void;

noun nails;
item itm_Nails (nails) "Nails" void;

noun pump;
item itm_Pump (pump) "Pump" void;

noun pearl;
item itm_Pearl (pearl) "*Pearl*" void;

noun diamond;
item itm_Diamond (diamond) "*Diamond*" void;

noun rapids;
item itm_Rapids (rapids) "Rapids" rm_River2;

noun clearing;
item itm_Clearing (clearing) "Clearing" rm_River2;

noun crocodile;
item itm_Croc (crocodile) "Crocodile" rm_Jungle;

noun rock;
item itm_Rock (rock) "Rock" rm_Jungle;

noun lamp;
item itm_Lamp (lamp) "*Gold Lamp*" void;

noun spraycan, spray, can;
item itm_Spraycan (spraycan) "Spray Can" void;

noun hammer;
item itm_Hammer (hammer) "Hammer" void;

noun safe;
item itm_Safe (safe) "Safe" rm_TopLighthouse;
item itm_SafeOpen (safe) "Safe" void;

noun necklace;
item itm_Necklace (necklace) "*Necklace*" void;

noun sapphire;
item itm_Sapphire (sapphire) "*Sapphire*" void;

noun gold, bar, goldbar;
item itm_GoldBar (gold) "*Gold Bar*" void;

noun sesame;

act auto 100
{
	!set(fl_Intro);
	on fl_Intro;

	# init moves counter to 0, to avoid -1 bug
	timer 0;
	swap tr_Moves;

	timer 0;
	swap tr_Safe;
	timer 0;
	swap tr_Safe1;
	timer 0;
	swap tr_Safe2;
	timer 0;
	swap tr_Safe3;

	# set pistol to 3 bullets
	timer 3;
	swap tr_Pistol;

	"Welcome to the Mysterious Island!  The goal is to "
	"find and store all ten treasures hidden on the island "
	"by the nasty long dead pirate Barnabous Redbeard!";
	.nl;
	.nl;
	"Good luck!";
	.nl;
	.nl;
	version_string;
	.nl;

	!inv;
}

# MOVE COUNT
act auto 100
{
	swap tr_Moves;
	add 1;
	swap tr_Moves;
}

act auto 100
{
	in(rm_PeninsulaFake);
	try
	{
		exists(itm_Crab);
		"The crab doesnt let me.";
		goto rm_Shore;
		end;
	}

	try
	{
		goto rm_Peninsula;
	}
}

act auto 100
{
	try
	{
		in(rm_River1);
		move rm_River1, itm_Waterfall;
		end;
	}

	try
	{
		in(rm_Plateau);
		move rm_Plateau, itm_Waterfall;
		end;
	}
}

alias not_yet = "I can't do that... Yet.";
alias msg_sorry = "Sorry, I can't do that.";
alias i_found = "I found : ";
alias msg_spraycan = "SSSSSSSSSS.";

###############################################################################
# rm_Shore, crab + tree
#

act climb tree
{
	here(itm_RottenTree);
	"My weight is too much for the rotten tree and it snaps.";
	die;
	quit;
}

act get tree
{
	here(itm_RottenTree);
	msg_sorry;
}

act look tree
{
	here(itm_RottenTree);
	"Its old and rotten.";
	.nl;
	"There is writing on the trunk.";
}

act read writing
{
	here(itm_RottenTree);
	"It says...";
	.nl;
	"'2 - 1 = 3'";
}


act look crab
{
	here(itm_Crab);
	"Its green and mean";
	.nl;
	"And its waving its big claws about.";
}

act get crab
{
	here(itm_Crab);
	"I grab the giant crab, which grabs me!";
	.nl;
	"Its pincers crush the life out of me.";
	die;
	quit;
}

act kill crab
{
	here(itm_Crab);
	!has(itm_Pistol);
	has(itm_Cutlass);

	"I swing at the crab with the cutlass, but I am too close!";
	.nl;
	"Its pincers crush the life out of me.";
}


act kill crab
{
	in(rm_Shore);
	here(itm_Crab);
	has(itm_Pistol);

	# test for bullets
	swap tr_Pistol;

	try
	{
		eq(0);
		"Click! The pistol is empty.";
		swap tr_Pistol;
		end;
	}

	gt(0);
	# sub 1 bullet
	sub 1;
	swap tr_Pistol;

	"Bang!";
	.nl;
	"I got him right between the eyes.";
	swap itm_CrabDead, itm_Crab;
}

act shoot crab
{
	in(rm_Shore);
	here(itm_Crab);
	has(itm_Pistol);

	# test for bullets
	swap tr_Pistol;

	try
	{
		eq(0);
		"Click! The pistol is empty.";
		swap tr_Pistol;
		end;
	}

	gt(0);
	# sub 1 bullet
	sub 1;
	swap tr_Pistol;

	"Bang!";
	.nl;
	"I got him right between the eyes.";
	swap itm_CrabDead, itm_Crab;
}

act get crab
{
	here(itm_CrabDead);
	msg_sorry;
}

act cut crab
{
	here(itm_CrabDead);
	has(itm_Cutlass);
	swap itm_CrabDead, itm_CrabMeat;
	"The crab is hacked to pieces.";
}



###############################################################################
# beach
#

act move boulder
{
	in(rm_Peninsula);
	try
	{
		!exists(itm_Raft);
		drop itm_Raft;
		i_found;
		"rubber raft.";
		end;
	}
	"I found nothing.";
}

act look sand
{
	in(rm_Peninsula);
	"There's writing in the sand.";
	.nl;
	"It says...";
	.nl;
	"'4 = 1'";
}

act get sand
{
	here(itm_Sand);
	msg_sorry;
}

act get ocean
{
	here(itm_Ocean);
	msg_sorry;
}

act get boulder
{
	here(itm_Boulder1);
	msg_sorry;
}

act look ocean
{
	here(itm_Ocean);
	"I see sharks.";
}

act dig any
{
	in(rm_Peninsula);
	try
	{
		!exists(itm_Pearl);
		drop itm_Pearl;
		i_found;
		"*Pearl*";
		end;
	}
	"I found nothing.";
}

act go ocean
{
	here(itm_Ocean);
	"Sharks in the ocean tear me to pieces";
	die;
	quit;
}

###############################################################################
# By Cliff
#

act get rocks
{
	here(itm_Rocks);
	msg_sorry;
}

act get ship
{
	here(itm_Ship);
	msg_sorry;
}

act look ship
{
	here(itm_Ship);
	"It's an old sailing ship.";
	.nl;
	"It's stranded high and dry.";
}

act move rocks
{
	in(rm_Rocks);

	try
	{
		!exists(itm_Planks);
		drop itm_Planks;
		i_found;
		"some wooden planks.";
		end;
	}

	"I found nothing.";
}

act go ship
{
	in(rm_Rocks);
	goto rm_Shipwreck;
	"OK.";
}

###############################################################################
# on Ship
#

act get cabin
{
	here(itm_Cabin);
	msg_sorry;
}

act get door
{
	here(itm_ClosedCabinDoor);
	msg_sorry;
}

act break door
{
	in(rm_Shipwreck);

	try
	{
		here(itm_ClosedCabinDoor);
		zap itm_ClosedCabinDoor;

		"I give the door a swift kick!";
		.nl;
		"I hurt my foot, but the door is open.";
		end;
	}

	"The door is already open.";
}

act look door
{
	in(rm_Shipwreck);

	try
	{
		here(itm_ClosedCabinDoor);
		"Its wooden.. and locked.";
		end;
	}

	"There is no door anymore.";
}

act go cabin
{
	in(rm_Shipwreck);
	goto rm_Cabin;
	"OK.";
}

###############################################################################
# in cabin
#

act get bed
{
	here(itm_Bed);
	msg_sorry;
}

act get table
{
	here(itm_Table);
	msg_sorry;
}

act look table
{
	in(rm_Cabin);

	try
	{
		!exists(itm_SilverDish);
		drop itm_SilverDish;
		i_found;
		"*Silver Dish*";
		end;
	}

	try
	{
		!exists(itm_Key);
		drop itm_Key;
		i_found;
		"Key.";
		end;
	}

	"I found nothing.";
}


act look bed
{
	in(rm_Cabin);
	"It looks like a warm place to sleep.";
}

act move bed
{
	in(rm_Cabin);
	try
	{
		!exists(itm_IvoryBowl);
		drop itm_IvoryBowl;
		i_found;
		"*Ivory Bowl*";
		end;
	}
	"I found nothing.";
}


act get bed
{
	here(itm_Bed);
	msg_sorry;
}

act go bed
{
	in(rm_Cabin);
	goto rm_Bed;
}

###############################################################################
# in bed
#

act look mattress
{
	here(itm_Mattress);
	try
	{
		!exists(itm_Paper);
		"It looks a little lumpy.";
		end;
	}

	"It has a cut in it..";
}

act get mattress
{
	here(itm_Mattress);
	msg_sorry;
}

act sleep any
{
	in(rm_Bed);
	"Goodnight!";
	.nl;
	delay;
	delay;
	"Good Morning!";
	.nl;
	"During the night I had a dream. A voice said";
	.nl;
	"'I am sleeping on magic...'";
}

act cut mattress
{
	in(rm_Bed);

	try
	{
		has(itm_Cutlass);
		!exists(itm_Paper);
		drop itm_Paper;
		i_found;
		"some paper";
		end;
	}

	try
	{
		exists(itm_Paper);
		"I already have.";
		end;
	}

	!exists(itm_Paper);
	!has(itm_Cutlass);
	not_yet;
}

act move mattress
{
	in(rm_Bed);
	try
	{
		!exists(itm_Emerald);
		drop itm_Emerald;
		i_found;
		"*Emerald*";
		end;
	}
	"I found nothing.";
}

act read paper
{
	avail(itm_Paper);
	"It says...";
	.nl;
	"The magic word is 'sesame'";
}

act look paper
{
	avail(itm_Paper);
	"There is writing on it.";
}


###############################################################################
# on path
#

act look sign
{
	avail(itm_Sign);
	"There is writing on it.";
}

act read sign
{
	in(rm_PlainPath);
	avail(itm_Sign);
	"It says...";
	.nl;
	"'Beware of the CAT.'";
}

act get sign
{
	here(itm_Sign);
	msg_sorry;
}


###############################################################################
# next to hut
#

act go hut
{
	in(rm_NextToHut);
	goto rm_Hut;
}

act look river
{
	in(rm_NextToHut);
	"It's very deep and turbulent.";
}

act get river
{
	here(itm_River);
	msg_sorry;
}

act get hut
{
	here(itm_WoodenHut);
	msg_sorry;
}

act dig any
{
	in(rm_NextToHut);
	try
	{
		!exists(itm_Diamond);
		drop itm_Diamond;
		i_found;
		"*Diamond*";
		end;
	}
	"I found nothing.";
}

act go river
{
	in(rm_NextToHut);

	try
	{
		has(itm_Raft);
		set(fl_InflatedRaft);
		goto rm_River2;
		end;
	}

	try
	{
		has(itm_Raft);
		!set(fl_InflatedRaft);
		"The raft is not inflated.";
		.nl;
	}

	"The river is swift and deep. I sink to the bottom and drown.";
	die;
	quit;
}

###############################################################################
# foot of sheer cliff
#

act get boulder
{
	here(itm_Boulder);
	msg_sorry;
}

act get tunnel
{
	here(itm_Tunnel);
	msg_sorry;
}

act look cliff
{
	in(rm_FootOfCliff);
	"There is some writing on the cliff.";
}

act read writing
{
	in(rm_FootOfCliff);
	"It says...";
	.nl;
	"'Say the Magic Word'.";
}

act say sesame
{
	in(rm_FootOfCliff);
	!exists(itm_Tunnel);
	"'SESAME'";
	.nl;
	"Part of the cliff moves aside revealing a tunnel.";
	move rm_FootOfCliff, itm_Tunnel;
}

act open sesame
{
	in(rm_FootOfCliff);
	!exists(itm_Tunnel);
	"'SESAME'";
	.nl;
	"Part of the cliff moves aside revealing a tunnel.";
	move rm_FootOfCliff, itm_Tunnel;
}

###############################################################################
# in river near plateau
#

act get waterfall
{
	here(itm_Waterfall);
	msg_sorry;
}

act go waterfall
{
	in(rm_River1);
	goto rm_Waterfall;
}

###############################################################################
# on plateau
#

act go waterfall
{
	in(rm_Plateau);
	goto rm_Waterfall;
}

act go river
{
	in(rm_Plateau);
	goto rm_River1;
}

act look river
{
	in(rm_Plateau);
	"Its very shallow.";
}

act get lighthouse
{
	here(itm_Lighthouse);
	msg_sorry;
}

act go lighthouse
{
	in(rm_Plateau);
	goto rm_Lighthouse;
}

act go tunnel
{
	here(itm_Tunnel);

	try
	{
		in(rm_FootOfCliff);
		goto rm_Plateau;
		drop itm_Tunnel;
		end;
	}

	in(rm_Plateau);
	goto rm_FootOfCliff;
	drop itm_Tunnel;
}

###############################################################################
# in waterfall
#

act read sign
{
	in(rm_Waterfall);
	here(itm_Sign2);
	"It says...";
	.nl;
	"'Drop Treasures Here' and say score.";
}

act get sign
{
	here(itm_Sign2);
	msg_sorry;
}

###############################################################################
# in lighthouse
#

act get ring
{
	here(itm_IronRing);
	msg_sorry;
}

act get stairs
{
	here(itm_Stairs);
	msg_sorry;
}

act look stairs
{
	here(itm_Stairs);
	try
	{
		!set(fl_Stairs);
		"They are made of wooden planks which are completely rotten.";
		end;
	}

	"The stairs are repaired and look safe.";
}


act turn ring
{
	in(rm_Lighthouse);
	try
	{
		here(itm_IronRing);
		"It's rusted solid.";
		end;
	}

	here(itm_IronRing2);
	try
	{
		!exists(itm_TrapDoor);
		"A trapdoor opens in the floor....";
		drop itm_TrapDoor;
		end;
	}

	"I already have.";
}

act go trapdoor
{
	here(itm_TrapDoor);
	goto rm_Celler;
}

act fix stairs
{
	in(rm_Lighthouse);

	try
	{
		set(fl_Stairs);
		"They are already fixed.";
		end;
	}

	try
	{
		has(itm_Hammer);
		has(itm_Nails);
		has(itm_Planks);

		move rm_PeninsulaFake, itm_Planks;
		move rm_PeninsulaFake, itm_Nails;

		on fl_Stairs;

		"The stairs are repaired.";
		end;
	}

	not_yet;
}

act go stairs
{
	in(rm_Lighthouse);

	try
	{
		set(fl_Stairs);
		goto rm_TopLighthouse;
		end;
	}

	"The planks in the stairs are rotten. I fall through and break my neck!";
	die;
	quit;
}

act spray ring
{
	has(itm_Spraycan);
	in(rm_Lighthouse);

	msg_spraycan;

	try
	{
		here(itm_IronRing);
		swap itm_IronRing, itm_IronRing2;
	}

	"The ring is soaked.";
}

###############################################################################
# celler
#

act get chest
{
	here(itm_Chest);
	msg_sorry;
}

act get chest
{
	here(itm_ChestUnlocked);
	msg_sorry;
}

act unlock chest
{
	here(itm_ChestUnlocked);
	"It is already unlocked.";
}

act unlock chest
{
	here(itm_Chest);

	try
	{
		has(itm_Key);
		swap itm_Chest, itm_ChestUnlocked;

		"The chest is open.";
		end;
	}

	not_yet;
}

act look chest
{
	in(rm_Celler);
	here(itm_Chest);
	"Its made of solid oak.";
	.nl;
	"Its locked.";
}

act look chest
{
	in(rm_Celler);
	here(itm_ChestUnlocked);

	try
	{
		!exists(itm_Necklace);
		drop itm_Necklace;
		i_found;
		"*Necklace*";
		end;
	}
	"I found nothing.";
}

act move chest
{
	in(rm_Celler);
	try
	{
		!exists(itm_Hammer);
		drop itm_Hammer;
		i_found;
		"Hammer";
		end;
	}
	"I found nothing.";
}

###############################################################################
# top of lighthouse
#

act get safe
{
	here(itm_Safe);
	msg_sorry;
}

act get safe
{
	here(itm_SafeOpen);
	msg_sorry;
}

act look safe
{
	here(itm_Safe);
	"It's got a combination dial.";
}

act look safe
{
	here(itm_SafeOpen);

	try
	{
		!exists(itm_GoldBar);
		drop itm_GoldBar;
		i_found;
		"*Gold Bar*";
		end;
	}
	"I found nothing.";
}

act move safe
{
	off fl_Temp;

	try
	{
		here(itm_Safe);
		on fl_Temp;
	}

	try
	{
		here(itm_SafeOpen);
		on fl_Temp;
	}

	try
	{
		!set(fl_Temp);
		"I can't see it here.";
		end;
	}

	try
	{
		!exists(itm_Sapphire);
		drop itm_Sapphire;
		i_found;
		"*Sapphire*";
		end;
	}

	"I found nothing.";
}

act spray safe
{
	in(rm_TopLighthouse);
	has(itm_Spraycan);

	msg_spraycan;

	on fl_Safe;
	"The dial is soaked.";
}

act one any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 1;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 1;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 1;
		swap tr_Safe3;
		end;
	}
}

act two any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 2;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 2;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 2;
		swap tr_Safe3;
		end;
	}
}

act three any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 3;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 3;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 3;
		swap tr_Safe3;
		end;
	}
}

act four any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 4;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 4;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 4;
		swap tr_Safe3;
		end;
	}
}

act five any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 5;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 5;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 5;
		swap tr_Safe3;
		end;
	}
}

act six any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 6;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 6;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 6;
		swap tr_Safe3;
		end;
	}
}

act seven any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 7;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 7;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 7;
		swap tr_Safe3;
		end;
	}
}

act eight any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 8;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 8;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 8;
		swap tr_Safe3;
		end;
	}
}

act nine any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 9;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 9;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 9;
		swap tr_Safe3;
		end;
	}
}

act zero any
{
	set(fl_SafeCrack);

	swap tr_Safe;
	add 1;
	swap tr_Safe;

	try
	{
		!set(fl_Safe1);
		on fl_Safe1;

		swap tr_Safe1;
		timer 0;
		swap tr_Safe1;
		end;
	}

	try
	{
		!set(fl_Safe2);
		on fl_Safe2;

		swap tr_Safe2;
		timer 0;
		swap tr_Safe2;
		end;
	}

	try
	{
		!set(fl_Safe3);
		on fl_Safe3;

		swap tr_Safe3;
		timer 0;
		swap tr_Safe3;
		end;
	}
}

# aks for safe input..
act auto 100
{
	set(fl_SafeCrack);

	swap tr_Safe;

	try
	{
		eq(3);
		"Enter third number";
		swap tr_Safe;
		end;
	}

	try
	{
		eq(2);
		"Enter second Number";
		swap tr_Safe;
		end;
	}

	try
	{
		eq(4);
		# off crack routine
		off fl_SafeCrack;

		try
		{
			swap tr_Safe1;
			eq(4);
			swap tr_Safe2;
			eq(9);
			swap tr_Safe3;
			eq(5);

			# only gets to here if combo is correct
			try
			{
				set(fl_Safe);
				"The safe opens....";
				swap itm_Safe, itm_SafeOpen;
				end;
			}

			# only gets to here if safe is not set... so automatically rusted.
			"I try and turn the dial but it is rusted.";
			end;
		}

		# gets here if combo is wrong.
		"I try the combination but it does not work.";

		# reset all vars
		timer 0;
		swap tr_Safe1;
		timer 0;
		swap tr_Safe2;
		timer 0;
		swap tr_Safe3;
		timer 0;
		swap tr_Safe;
		end;
	}

	swap tr_Safe;
}

act open safe
{
	try
	{
		here(itm_SafeOpen);
		"It is already open.";
		end;
	}

	here(itm_Safe);
	swap tr_Safe;
	timer 1;
	swap tr_Safe;

	off fl_Safe1;
	off fl_Safe2;
	off fl_Safe3;

	on fl_SafeCrack;

	"Enter the Combination as words (one, two, etc), not numbers (1,2,3)";
	.nl;
	"Enter first number";
}


###############################################################################
# in hut
#

act get cupboard
{
	here(itm_Cupboard);
	msg_sorry;
}

act get tiger
{
	here(itm_Tiger);
	msg_sorry;
}

act open cupboard
{
	here(itm_Tiger);
	here(itm_Cupboard);
	not_yet;
}

act look cupboard
{
	here(itm_Cupboard);
	"Its locked.";
}

act look tiger
{
	here(itm_Tiger);
	"Cute little fellow.";
}

act drop meat
{
	here(itm_Tiger);
	has(itm_CrabMeat);

	zap itm_CrabMeat;
	zap itm_Tiger;

	"The tiger grabs the crab meat and bounds out of the hut.";
}

act feed tiger
{
	here(itm_Tiger);
	has(itm_CrabMeat);

	zap itm_CrabMeat;
	zap itm_Tiger;

	"The tiger grabs the crab meat and bounds out of the hut.";
}


act unlock cupboard
{
	here(itm_Cupboard);
	has(itm_Key);

	swap itm_Cupboard, itm_CupboardOpen;
	"The cupboard is now open...";
}

act unlock cupboard
{
	here(itm_CupboardOpen);
	"It is already unlocked.";
}

act look cupboard
{
	here(itm_CupboardOpen);

	try
	{
		!exists(itm_Nails);
		drop itm_Nails;
		i_found;
		"Nails.";
		end;
	}

	try
	{
		!exists(itm_Pump);
		drop itm_Pump;
		i_found;
		"Pump.";
		end;
	}

	"I found nothing.";
}

###############################################################################
# on river
#

act get rapids
{
	here(itm_Rapids);
	msg_sorry;
}

act get clearing
{
	here(itm_Clearing);
	msg_sorry;
}

act go rapids
{
	here(itm_Rapids);
	"The raft is smashed to pieces in the rapids.";
	die;
	quit;
}

act look rapids
{
	here(itm_Rapids);
	"UH OH!";
}

act look clearing
{
	here(itm_Clearing);
	"Looks like a safe place to go.";
}

act go clearing
{
	here(itm_Clearing);
	# move to hidden room so it still exists
	move rm_PeninsulaFake, itm_Raft;
	"The raft is carried away by the river. I am stranded.";
	goto rm_Jungle;
}

###############################################################################
# clearing
#

act get rock
{
	here(itm_Rock);
	msg_sorry;
}

act get crocodile
{
	here(itm_Croc);
	msg_sorry;
}

act shoot crocodile
{
	here(itm_Croc);

	try
	{
		has(itm_Pistol);

		swap tr_Pistol;

		try
		{
			le(0);
			"Click! The pistol is empty.";
		}

		try
		{
			gt(0);
			"Bang!";
		}

		.nl;
		"The crocodile wakes up and attacks.";
		die;
		quit;
	}

	"What with?";
}


act dig any
{
	in(rm_Jungle);
	!exists(itm_Lamp);
	drop itm_Lamp;
	i_found;
	"*Gold Lamp*";
}

act move rock
{
	in(rm_Jungle);
	try
	{
		!exists(itm_Spraycan);
		drop itm_Spraycan;
		i_found;
		"Spray Can";
		end;
	}
	"I found nothing.";
}

act look crocodile
{
	in(rm_Jungle);
	"The crocodile is asleep.";
}

act look rock
{
	in(rm_Jungle);
	here(itm_Rock);
	"There is writing on the rock.";
}

act read writing
{
	in(rm_Jungle);
	"It says...";
	.nl;
	"'5 + 1 = 2'";
}

act look spraycan
{
	avail(itm_Spraycan);
	"It's full.";
	.nl;
	"There is a label on the side.";
}

act read label
{
	avail(itm_Spraycan);
	"It says...";
	.nl;
	"'Rust Remover'.";
}

act spray spraycan
{
	has(itm_Spraycan);
	msg_spraycan;
}


###############################################################################
# raft
#

act pump raft
{
	has(itm_Pump);
	has(itm_Raft);

	try
	{
		set(fl_InflatedRaft);
		"The raft is already inflated.";
		end;
	}

	try
	{
		!set(fl_InflatedRaft);
		on fl_InflatedRaft;
		"The raft is inflated.";
		end;
	}
}

act look raft
{
	has(itm_Raft);
	try
	{
		!set(fl_InflatedRaft);
		"The raft is not inflated.";
		end;
	}

	"The raft is inflated.";
}

###############################################################################
# lamp
#

act rub lamp
{
	has(itm_Lamp);
	"Everything spins.....";
	delay;

	try
	{
		in(rm_Jungle);
		goto rm_NextToHut;
		end;
	}

	goto rm_Jungle;
}


###############################################################################
# gun commands
#
act shoot any
{
	try
	{
		has(itm_Pistol);
		swap tr_Pistol;

		try
		{
			le(0);
			"Click! The pistol is empty.";
		}

		try
		{
			gt(0);
			sub 1;
			"Bang!";
		}

		.nl;

		swap tr_Pistol;
		end;
	}

	"Shoot what?";
}

act look pistol
{
	has(itm_Pistol);
	swap tr_Pistol;

	"It's loaded with";
	.timer;
	try
	{
		eq(1);
		"bullet.";
	}

	try
	{
		gt(1);
		"bullets.";
	}
	try
	{
		le(0);
		"bullets.";
	}

	swap tr_Pistol;
}


###############################################################################
# generics
#

act dig any
{
	try
	{
		!has(itm_Shovel);
		"I dont have anything to dig with.";
		end;
	}

	# gets here if we have the shovel
	"Digging here is useless.";
}


act look any
{
	#.room;
	"I see nothing special.";
}

act quit any
{
	quit;
}

act inventory any
{
	# issuing inv does not count as a move
	swap tr_Moves;
	sub 1;
	swap tr_Moves;

	.inv;
}

act score any
{
	# issuing score does not count as a move
	swap tr_Moves;
	sub 1;
	swap tr_Moves;

	.score;

	.nl;
	"I have made";
	swap tr_Moves;
	.timer;
	swap tr_Moves;
	"moves.";
}

act move any
{
	"I found nothing.";
}

act climb any
{
	"I can't climb that.";
}


act sleep any
{
	!in(rm_Bed);
	"The nights are cold on Mystery Island.";
	.nl;
	"I freeze to death.";
	die;
	quit;
}

act save any
{
	save;
}

act say any
{
	"'";
	.noun;
	"'";

	.nl;
	"Nothing happens...";
}

act open any
{
	"open what?";
}

act auto 100
{
	in(rm_Waterfall);

	here(itm_SilverDish);
	here(itm_IvoryBowl);
	here(itm_Emerald);
	here(itm_Ruby);
	here(itm_Pearl);
	here(itm_Diamond);
	here(itm_Lamp);
	here(itm_Necklace);
	here(itm_Sapphire);
	here(itm_GoldBar);

	success;
	.nl;
	.nl;
#    123456789-123456789-123456789-123456789-
	"\\\\\\*\*\* CONGRATULATIONS *\*\*";
	.nl;
	.nl;
	"I've been here in";

	swap tr_Moves;
	.timer;
	swap tr_Moves;

	"moves.";
	.nl;

	"And stored all ten treasures.";
	.nl;
	.nl;
	"I've solved it all!";

	.score;
}

act version any
{
	.nl;
	version_string;
	.nl;
}

initial=rm_Shore;
treasure=rm_Waterfall;
