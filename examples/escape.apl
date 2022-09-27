#
# ESCAPE FROM PIRATE'S ISLE -- A sample adventure by Bjorn Gustavsson.
#

# ----------------------------------------------------------------------
# General notes
# ~~~~~~~~~~~~~
# The declarations in this file (of room, items, actions etc) can be
# placed in any order, with a few exceptions.
#
# 1) 	You can only refer to things that has been defined previously
#	in the following (i.e. forward references are not allowed).
#	For instance, an action can only refer to rooms or items which
#	have been previously defined, and an item which should
#	iniatially reside in a specific room must be defined after
#	the room has been defined.
#
# 	This rule has one exception.  When you define the room exits
#	for a room, references to rooms not yet defined are allowed.
#	(Of course.)
#
# 2)	The three special verbs GO, GET and DROP must be defined
#	before any other verb is defined.
#
# 3)	The six special nouns for the directions NORTH, SOUTH, EAST,
#	WEST, UP, and DOWN, must be defined before any other noun.
#
# All names are case-sensitive.  Therefore, get is not the same
# as Get or GET.
# ----------------------------------------------------------------------

#
# The title screen is for the TI-99 format only.  It will be shown
# as soon as the Adventure cartridge has loaded the story file.
# 23 lines by 40 characters can be defined here; the last line
# is reserved for the compiler's version number.
#
title_screen =
#         1         2         3
# 123456789012345678901234567890123456789
"       ESCAPE FROM PIRATE'S ISLE",
"",
"A sample adventure for ScottCom",
"by Bjorn Gustavsson.",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"Press ENTER to start playing.";

#
# Declare the direction nouns.  They must be declared before any other noun.
#
noun(north) north;
noun(south) south;
noun(east)  east;
noun(west)  west;
noun(up)    up;
noun(down)  down;

#
# Declare verbs.  Most verbs don't have to be declared before using
# them in an action, but in the following three circumstances it is
# necessary:
#
# 1. The verbs for GO, DROP, and GET are specially handled by the
#    driver and they must be declared before any other verb.
#
# 2. If you want to give any of your verbs synonyms, the verb must
#    be declared (before being used in an action).
#
# 3. If you want to put the verb in the dictionary, but you don't
#    intend to handle in an action.  This is useful if you don't
#    want the player to see the message "I don't know how to XXX".
#    If a word is in the dictionary but has no action, the message
#    will instead be "I don't understand your command".
#
# Each verb will be truncated to the word length give by 'abbreviate'
# and capitalised before being put in the dictionary.
#
verb(go) go;
verb(drop) drop, throw;
verb(get) get, take;

flag intro;		# Set if intro written.
flag(night) night;	# Turn this on for darkness.
flag(runout) runout;	# Set when light has just run out.

act auto 100 {
	!set(intro);
	on intro;
	"Welcome to 'ESCAPE FROM PIRATE'S ISLE', by Bjorn Gustavsson. "
	"That damned pirate left me here on Pirates's isle, because I "
	"couldn't give him any more rum!";
}

room Dock "I'm on a dock.", n_to Beach;
initial = Dock;

room Beach "I'm in a beach by a small hill.", s_to Dock, e_to RockyBeach;

room Hill "I'm on top of a small hill.", d_to Sorry;
item Crack "Narrow crack in rock";

act climb hill {
	in(Beach);
	goto Hill;
}

room Cavern "I'm in a cavern.", n_to Hill;

item Hermit "Angry-looking hermit";
noun hermit;

item ToolShed "Tool shed";
item(light) Torch(torch) "Unlit torch" void;
light_time = 120;

act go crack {
	in(Hill);
	goto Cavern;
}

alias hermit_stop_me = "The Hermit won't let me.";
alias complain = "'Get out of here', yells the Hermit.";

noun shed, tool;
act go shed {
	here(ToolShed);
	!moved(Torch);
	hermit_stop_me;
	"The Hermit throws something at me. It hits my head and bounces away "
	"and falls to the floor somewhere near the crack.";
	same Torch, Hermit;
}

act go shed {
	here(ToolShed);
	moved(Torch);
	hermit_stop_me;
}

act get torch {
	here(Torch);
	here(Hermit);
	hermit_stop_me;
}

act get torch {
	here(Torch);
	get Torch;
}

act get torch {
	!here(Torch);
	"I don't see it here.";
}

act kick torch {
	"The torch rolls out through the crack, and the Hermit doesn't seem "
	"to notice.";
	move Hill, Torch;
}

room Sorry "Sorry, to explore the rest of Pirate's Isle you need Scott Adams' "
	"Pirate Adventure.", u_to Hill;
item Sign1 "Sign";

act read sign {
	avail(Sign1);
	"Keep out! Location shooting for 'Pirate Adventure - The Movie'.";
}

room RockyBeach "I'm on a rocky beach by the sea.", w_to Beach;

room NeverNever "Welcome to Never-Never land!";

act climb any { "I see nothing suitable to climb."; }

verb look, examine;

act look any { "I see nothing special."; }

act quit any { quit; }

