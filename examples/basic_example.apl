# Small sample game, using treasure, torches, etc.

title_screen =
#         1         2         3
# 123456789012345678901234567890123456789
 "          SAMPLE ADVENTURE #1",
 "",
 "    A sample adventure for ScottCom",
 "            by Stu George.",
 "",
 "",
 "",
 "",
 "    Press ENTER to start playing.";

word_length = 16;
light_time = 10;
max_load = 6;


#
# Declare the direction nouns.  They must be declared before any other noun.
#
noun(north) north;
noun(south) south;
noun(east)  east;
noun(west)  west;
noun(up)    up;
noun(down)  down;

# important game verbs
verb(go) 	go;
verb(drop) 	drop, putdown, put, place, leave;
verb(get) 	get, take, pickup, grab, steal, snatch;

flag f_Intro;		# Set if intro written.
flag(night) f_Night;	# Turn this on for darkness.
flag(runout) f_Runout;	# Set when light has just run out.

# some game versbs

verb inventory, inv, i;
verb quit, q;
verb look, l, examine, ex, x;
verb light, ignite;
verb unlight;


# declare some rooms

room rm_Outside "Outside a cave.",
	n_to rm_Cave1;

room rm_Cave1 "Cave enterance.",
	n_to rm_Cave2,
	s_to rm_Outside;

room rm_Cave2 "I'm in a Cold cavern.",
	e_to rm_Cave3,
	s_to rm_Cave1;

room rm_Cave3 "I'm in a Cold cavern.",
	n_to rm_Cave4,
	w_to rm_Cave2;

room rm_Cave4 "I'm in a Cold cavern.",
	s_to rm_Cave3;

room rm_DeadRoom "This is the dead room, where dead players go when they die.";

# mark the treasure room
treasure = rm_Outside;

# mark the start room
initial = rm_Outside;

noun torch;

item(light) itm_LitTorch (torch) "Torch (on)" void;
item itm_UnlitTorch (torch) "Torch (off)" player;

# This is our treasure item.
noun diamond;
item itm_Diamond (diamond) "*Diamond" rm_Cave4;


#
# ======================================

act auto 100
{
	!set(f_Intro);
	on f_Intro;

	"This is a small example adventure. You are required to enter "
	"the cave and retrieve the diamond, drop it here, and say score!";
}

#
# =======================================
# darkness!

# if player in cave1, turn on the darkness flag
act auto 100
{
	in(rm_Cave1);
	on f_Night;
}

act auto 100
{
	in(rm_Outside);
	off f_Night;
}


#
# =======================================
# code to turn on / off the torch

act light torch
{
	try
	{
		has(itm_LitTorch);
		"The torch is already on.";
		end;
	}

	try
	{
		!has(itm_LitTorch);
		!has(itm_UnlitTorch);
		"You dont have it.";
		end;
	}

	try
	{
		has(itm_UnlitTorch);
		swap itm_UnlitTorch, itm_LitTorch;
		"You turn the torch on.";
		end;
	}
}

act unlight torch
{
	try
	{
		has(itm_UnlitTorch);
		"The torch is already off.";
		end;
	}

	try
	{
		!has(itm_UnlitTorch);
		!has(itm_LitTorch);
		"You dont have it.";
		end;
	}

	try
	{
		has(itm_LitTorch);
		swap itm_UnlitTorch, itm_LitTorch;
		"You turn the torch off.";
		end;
	}
}

# if our torch has ranout... enable darkness IF we are in a dark area...
act auto 100
{
	set(f_Runout);
	off f_Runout;

	swap itm_UnlitTorch, itm_LitTorch;

	try
	{
		!in(rm_Outside);
		on f_Night;
	}
}

# ======================================
# declare standard routines.

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

act score any
{
	.score;
}

