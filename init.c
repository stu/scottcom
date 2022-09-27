/*
 *	  ScottCom -- Compiles adventures into the Scott Adams format.
 *	  Copyright (C) 1985-1996  Bjorn Gustavsson
 *
 *	  This program is free software; you can redistribute it and/or modify
 *	  it under the terms of the GNU General Public License as published by
 *	  the Free Software Foundation; either version 2 of the License, or
 *	  (at your option) any later version.
 *
 *	  This program is distributed in the hope that it will be useful,
 *	  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 *	  GNU General Public License for more details.
 *
 *	  You should have received a copy of the GNU General Public License
 *	  along with this program; if not, write to the Free Software
 *	  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: init.c,v 1.2 1996/10/17 04:04:05 bjorn Exp bjorn $
 *
 */

#include "scottcom.h"
#include "parser.h"

extern Symbol* main_table;
extern Symbol* verb_table;
extern Symbol* noun_table;
extern Symbol* label_table;

static Keyword actions[] = {
	/*
	 * Conditions.	The value is code for the TI-99 format, and it will
	 * be translated before being inserted into the symbol table.
	*/
	{"has",		 TESTOBJ,		(OP_BASE+0xb7)},
	{"here",	 TESTOBJ,		(OP_BASE+0xb8)},
	{"avail",	 TESTOBJ,		(OP_BASE+0xb9)},
	{"!here",	 TESTOBJ,		(OP_BASE+0xba)},
	{"!has",	 TESTOBJ,		(OP_BASE+0xbb)},
	{"!avail",	 TESTOBJ,		(OP_BASE+0xbc)},
	{"exists",	 TESTOBJ,		(OP_BASE+0xbd)},
	{"!exists",	 TESTOBJ,		(OP_BASE+0xbe)},
	{"in",		 TESTROOM,		(OP_BASE+0xbf)},
	{"!in",		 TESTROOM,		(OP_BASE+0xc0)},
	{"set",		 TESTFLAG,		(OP_BASE+0xc1)},
	{"!set",	 TESTFLAG,		(OP_BASE+0xc2)},
	{"something",PARAMLESS,		(OP_BASE+0xc3)},
	{"nothing",	 PARAMLESS,		(OP_BASE+0xc4)},
	{"le",		 TESTNUM,		(OP_BASE+0xc5)},
	{"gt",		 TESTNUM,		(OP_BASE+0xc6)},
	{"eq",		 TESTNUM,		(OP_BASE+0xc7)},
	{"!moved",	 TESTOBJ,		(OP_BASE+0xc8)},
	{"moved",	 TESTOBJ,		(OP_BASE+0xc9)},

	/*
	 * Operations, with values for the TI-99 format.
	 */
	{"cls",		 PARAMLESS,		OP_CLS},
	{"pic",		 ACTNUM,		OP_SHOW_PIC},
	{"inv",		 PARAMLESS,		(OP_BASE+0xd6)},
	{"!inv",	 PARAMLESS,		(OP_BASE+0xd7)},
	{"ignore",	 PARAMLESS,		(OP_BASE+0xd8)},
	{"success",	 PARAMLESS,		(OP_BASE+0xd9)},
	{"try",		 IF,			(OP_BASE+0xda)},
	{"get",		 ACTOBJ,		(OP_BASE+0xdb)},
	{"drop",	 ACTOBJ,		(OP_BASE+0xdc)},
	{"goto",	 ACTROOM,		(OP_BASE+0xdd)},
	{"zap",		 ACTOBJ,		(OP_BASE+0xde)},
	{"die",		 PARAMLESS,		(OP_BASE+0xe5)},
	{"move",	 ACTROOMOBJ,	(OP_BASE+0xe6)},
	{"quit",	 PARAMLESS,		(OP_BASE+0xe7)},
	{".score",	 PARAMLESS,		(OP_BASE+0xe8)},
	{".inv",	 PARAMLESS,		(OP_BASE+0xe9)},
	{"refill",	 PARAMLESS,		(OP_BASE+0xea)},
	{"save",	 PARAMLESS,		(OP_BASE+0xeb)},
	{"steal",	 ACTOBJ,		(OP_BASE+0xed)},
	{"same",	 ACTOBJOBJ,		(OP_BASE+0xee)},
	{"nop",		 PARAMLESS,		(OP_BASE+0xef)},
	{".room",	 PARAMLESS,		(OP_BASE+0xf0)},
	{".timer",	 PARAMLESS,		(OP_BASE+0xf4)},
	{"timer",	 ACTNUM,		(OP_BASE+0xf5)},
	{".noun",	 PARAMLESS,		(OP_BASE+0xfb)},
	{".noun_nl", PARAMLESS,		(OP_BASE+0xfc)},
	{".nl",		 PARAMLESS,		(OP_BASE+0xfd)},
	{"delay",	 PARAMLESS,		(OP_BASE+0xfe)},
	{"end",		PARAMLESS,		(OP_BASE+0xFF)},
};

/*
 * This table contains keywords which are format-independent.
 */
static Keyword keywords[] = {
	{"on",		 ACTFLAG,		 0},
	{"off",		 ACTFLAG,		 1},
	{"add",		 TIMER,			 0},
	{"sub",		 TIMER,			 1},

	/*
	 * Keywords for generic operations.	 The value is not used.
	 */
	 {"swap",	  SWAP,			  0},


	/*
	 * Keywords.  The value is not used.
	 */
	{"noun",	 KW_NOUN,		 0},
	{"verb",	 KW_VERB,		 0},
	{"item",	 KW_OBJECT,		 0},
	{"room",	 KW_ROOM,		 0},
	{"act",		 KW_ACTION,		 0},
	{"alias",	 KW_MESSAGE,	 0},
	{"flag",	 KW_FLAG,		 0},
	{"timreg",	 KW_TIMREG,		 0},
	{"roomreg",	 KW_ROOMREG,	 0},

	/*
	 * All directions.	The value is used to index into the room
	 * index table.
	 */
	{"n_to",	 DIRECT,		 0},
	{"s_to",	 DIRECT,		 1},
	{"e_to",	 DIRECT,		 2},
	{"w_to",	 DIRECT,		 3},
	{"u_to",	 DIRECT,		 4},
	{"d_to",	 DIRECT,		 5},

	/* player, void and any */
	{"void",	 VOID,			 0},
	{"limbo",	 VOID,			 0},
	{"player",	 PLAYER,		 0},

	/* parameters */
	{"initial",	 PARSTART,		 0},
	{"treasure", PARTREASURE,	 0},
	{"light_time", PARLIGHT,	 0},
	{"max_load", PARCARRY,		 0},
	{"word_length", PARABBREV,	 0},
	{"title_screen", PARTITLE,	 0},

	{"rm_ZERO", ROOM,			0}
};

/*
 * All labels for verbs, nouns, flags, and items which must have
 * a special number.
 */
static Keyword labels[] = {
	/* Verbs. */
	{"go",		 VLABEL,		 VERB_GO},
	{"get",		 VLABEL,		 VERB_GET},
	{"drop",	 VLABEL,		 VERB_DROP},

	/* Direction nouns. */
	{"north",	 NLABEL,		 1},
	{"south",	 NLABEL,		 2},
	{"east",	 NLABEL,		 3},
	{"west",	 NLABEL,		 4},
	{"up",		 NLABEL,		 5},
	{"down",	 NLABEL,		 6},

	/* The light-source item. */
	{"light",	 OLABEL,		 9},

	/* The special flags. */
	{"night",	 FLABEL,		 15},
	{"runout",	 FLABEL,		 16}

};

void init(void)					/* install constants and built-ins in table */
{
	Symbol *s;
	int i;

	/*
	 * Install all words used in actions.  Since their actual value
	 * depends on the output format, the format-specific translate()
	 * function will be called.
	 */
	for (i = 0; i < ARRAYSIZE(actions); i++) {
		s = install(&main_table, actions[i].name, actions[i].token);
		s->value = translate(actions[i].value);
	}

	/*
	 * Install the keywords for the main table.
	 */
	install_keywords(&main_table, keywords, ARRAYSIZE(keywords));

	/*
	 * Install the keywords for the label table.
	 */
	install_keywords(&label_table, labels, ARRAYSIZE(labels));

	/* installs rm_ZERO */
	MakeRoom(NULL, NULL);

	/*
	 * Install the first verb ("auto") into the verb table.
	 */
	s = install(&verb_table, "auto", VERB);
	s->value = 0;
	NumberVerb(VERB_AUTO);
	SetVerb(s, PRIMARY);

	/*
	 * Install the first noun ("any") into the noun table.
	 */
	s = install(&noun_table, "any", NOUN);
	s->value = 0;
	NounNo(0);
	SetNoun(s, PRIMARY);
}

/*
 *----------------------------------------------------------------------
 *
 * install_keywords --
 *
 *		This procedure install keywords into a symbol table.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void
install_keywords(
  Symbol** table,				/* Symbol table to install keywords in. */
  Keyword* keywords,			/* Pointer to keyword table. */
  int size)						/* Size of keyword table. */
{
	Symbol* s;
	int i;

	for (i = 0; i < size; i++)
	{
		s = install(table, keywords[i].name, keywords[i].token);
		s->value = keywords[i].value;

		if(verbose)
			printf("installing : %s\n", keywords[i].name);
	}
}

void printtok(int t, YYSTYPE val) /* print token symbolically */
{
	int		   i;

	switch(t) {
	case TESTOBJ:
	case TESTROOM:
	case TESTFLAG:
	case PARAMLESS:
	case TESTNUM:
	case IF:
	case ACTOBJ:
	case ACTROOM:
	case ACTROOMOBJ:
	case ACTOBJOBJ:
	case ACTNUM:
		for (i = 0; keywords[i].value != yylval.n; i++)
			;
		printf("action '%s'", keywords[i].name);
		break;
	case TIMER:
	case ACTFLAG:
		printf("action");
		break;
	case UNDEF:
		printf("identifier '%s'", yylval.sym->name);
		break;
	case STRING:
		fprintf(stderr, "\"...\"");
		break;
	case NUMBER:
		printf("'%d'", yylval.n);
		break;
	case ROOM:
		printf("room '%s'", yylval.sym->name);
		break;
	case VERB:
		printf("verb #%d", yylval.n);
		break;
	case NOUN:
		printf("noun #%d", yylval.n);
		break;
	case OBJECT:
		printf("object #%d", yylval.n);
		break;
	case MESSAGE:
		printf("message #%d", yylval.n);
		break;
	case FLAG:
		printf("flag #%d", yylval.n);
		break;
	default:
		printf("token %d", t);
		break;
	}
}
