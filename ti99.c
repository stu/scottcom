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
 * $Id: ti99.c,v 1.2 1996/10/17 04:16:44 bjorn Exp $
 *
 */

#include "scottcom.h"
#include "adams.h"
#define BLOCK_SIZE 256			/* Maximum block size. */


/*
 * The following variables are used for the current block being assembled.
 */
static byte* code_buf;			/* Scratch space for the last action. */
static byte* code_p;			/* Pointer into code_buf. */
static byte* catch_p;			/* Pointer to beginning of catch. */
static int current_verb;		/* The verb we are collecting actions for. */
static int current_noun;		/* The noun we are collecting actions for. */

/*
 * The following variable keeps tracks of where the next line for the
 * title screen is.
 */
static int title_line = 0;		/* Line number. */
extern char acknowledge[];		/* Acknowledge string to put on last line. */

/*
 * Local functions.
 */
static unsigned ti99_translate(unsigned code);
static void ti99_titlestr(char* str);
static void ti99_begaction(int verb, int noun);
static void ti99_endaction(void);
static void ti99_begcatch(void);
static void ti99_endcatch(void);
static void ti99_action0(unsigned code);
static void ti99_action1(unsigned code, unsigned arg);
static void ti99_action2(unsigned code, unsigned arg1, unsigned arg2);
static void ti99_dump(void);
static void storeByte(unsigned value);
static void dump_actions(void);


/*----------------------------------------------------------------------
 *
 * ti99_init --
 *
 *		This procedure initializes the TI-99/4 output format.
 *		It setups the pointers to the format-dependent functions
 *		and allocates the needed memory.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
*/
void ti99_init(void)
{
	int i;

	translate = ti99_translate;
	titlestr = ti99_titlestr;
	begaction = ti99_begaction;
	endaction = ti99_endaction;
	begcatch = ti99_begcatch;
	endcatch = ti99_endcatch;
	action0 = ti99_action0;
	action1 = ti99_action1;
	action2 = ti99_action2;
	dump = ti99_dump;

	action = (Action **) emalloc(sizeof(Action*) * MAX_VERBS);
	code_buf = (byte *) emalloc(256);
	for (i = 0; i < MAX_VERBS; i++) {
		action[i] = (Action *) 0;
	}
}


/*----------------------------------------------------------------------
 *
 * ti99_translate --
 *
 *		This procedure translates from the generic format to the current
 *		format.	 (Since the generic format is based on the TI-99 format,
 *		with only OP_BASE added to the code, the translation is trivial.)
 *
 * Results:
 *		The translated opcode.
 *
 *----------------------------------------------------------------------
 */
static unsigned
ti99_translate(
  unsigned code)				/* The code to be translated. */
{
	if (code < OP_BASE) {
		return code;			/* No need to translate. */
	}
	if (code == OP_CLS || code == OP_SHOW_PIC) {
		return OP_IGNORE;		/* Not supported -- ignore. */
	}
	return code-OP_BASE;		/* Return the real code to use. */
}


/*----------------------------------------------------------------------
 *
 * ti99_titlestr --
 *
 *		This procedure stores the string for one line of
 *		title screen.  The first time this procedure is called,
 *		the first line on the title screen screen is stored,
 *		the second time the second line and so on.	23 lines
 *		can be stored by call ti99_titlestr (the last line is
 *		reserved for the compiler's version string).
 *
 *		If a string contains more than 40 characters, it will
 *		be truncated and stored, and a warning message will be
 *		shown.	If ti99_titlestr is called more than 23 times,
 *		a warning message will be shown for the first string
 *		superfluous line.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void ti99_titlestr(
  char* str)					/* One title-screen line. */
{
	if (title_line == 24) {
		warn("too many title lines");
	} else if (title_line < 23) {
		unsigned length = strlen(str);
		if (length > 40) {
			length = 40;
			warn("title line is longer than 40 characters (was truncated)");
		}
		Org(0x400+40*title_line);
		outbuf((byte*)str, length);
	}
	title_line++;
}


/*----------------------------------------------------------------------
 *
 * ti99_begaction --
 *
 *		This procedure begins a new action.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_begaction(
  int verb,						/* The verb the action should be done for. */
  int noun						/* The noun the action should be done for. */
)
{
	int i;

	for(i=0; i<MAX_TRY_DEPTH; i+=1)
		try_level[i] = 0;

	ASSERT(verb < 256 && verb>=0);
	ASSERT(noun < 256 && noun>=0);
	code_p = code_buf;
	catch_p = 0;
	current_verb = verb;
	current_noun = noun;

}

/*----------------------------------------------------------------------
 *
 * ti99_endaction --
 *
 *		This procedure ends an action.	It will allocate an Action
 *		structure, copy the collected code block into it and link
 *		the Action block into the chain for this verb.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_endaction(void)
{
	unsigned length = code_p - code_buf;
	Action *actp = (Action *) emalloc(sizeof(Action)+length-1);
	actp->verb = current_verb;
	actp->noun = current_noun;
	actp->length = length;
	memcpy(actp->code, code_buf, length);
	if (action[current_verb] == (Action *) 0) {
		actp->next = actp;
		action[current_verb] = actp;
	} else {
		actp->next = action[current_verb]->next;
		action[current_verb]->next = actp;
		action[current_verb] = actp;
	}

	if(verbose)
	{
		if(current_verb == 0)
			printf("action (size:%3i): %s %i\n",  length, Verbs[current_verb]->name, current_noun);
		else
			printf("action (size:%3i): %s %s\n",  length, Verbs[current_verb]->name, NounNames[current_noun]->name);
	}
}

/*----------------------------------------------------------------------
 *
 * ti99_begcatch --
 *
 *		This procedure marks the beginning of a catch.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_begcatch(void)
{
	action0(0xDA);				/* Continue op-code. */

	ASSERT(try_index < MAX_TRY_DEPTH);
	try_level[try_index++] = code_p;
	//catch_p = code_p;

	action0(0);					/* Place-holder for jump offset. */
}

/*----------------------------------------------------------------------
 *
 * ti99_endcatch --
 *
 *		This procedure ends a catch block.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_endcatch(void)
{
	ASSERT(try_index > 0);
	try_index -= 1;

	catch_p = try_level[try_index];
	try_level[try_index] = 0;

	ASSERT(catch_p);
	*catch_p = code_p - catch_p;
	catch_p = 0;
}


/*----------------------------------------------------------------------
 *
 * ti99_action0 --
 *
 *		This procedure stores an action with no arguments in
 *		the current action block.  If the code block becomes full,
 *		an diagnostic is issued.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_action0(
  unsigned code					/* The op-code for the action. */
)
{
	/*
	 * Translate the code if it is generic (format-independent).
	 */
	if (code >= OP_BASE) {
		code -= OP_BASE;
	}

	/*
	 * Store the code in the current action block.
	 */
	storeByte(code);
}


/*----------------------------------------------------------------------
 *
 * ti99_action1 --
 *
 *		This procedure stores an action with one argument in
 *		the current action block.  See ti99_action0 for further details.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_action1(
  unsigned code,				/* The op-code for the action. */
  unsigned arg					/* The argument for the action. */
)
{
	action0(code);
	storeByte(arg);
}


/*----------------------------------------------------------------------
 *
 * ti99_action2 --
 *
 *		This procedure stores an action with two arguments in
 *		the current action block.	 See ti99_action0 for further details.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_action2(
  unsigned code,				/* The op-code for the action. */
  unsigned arg1,				/* The first argument for the action. */
  unsigned arg2					/* The second argument for the action. */
)
{
	action0(code);
	storeByte(arg1);
	storeByte(arg2);
}


/*----------------------------------------------------------------------
 *
 * ti99_dump --
 *
 *		This procedure dumps everything collected to the output file
 *		in the TI-99 format.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
ti99_dump(void)
{
	ASSERT(strlen(acknowledge) <= 40); /* Otherwise won't fit. */
	Org(0x400+40*23);
	outbuf((byte*)acknowledge, strlen(acknowledge));

	/*
	 * Dump the setable header parameters.
	 */
	Org(BEGROOM);
	OutByte(info.current_room);
	if(verbose)
		printf("Header : Start Room - %i\n", info.current_room);
	Org(TREASURE);
	OutByte(info.treasure_room);
	if(verbose)
		printf("Header : Treasure Room - %i\n", info.treasure_room);
	Org(LIGHT);
	OutWord(info.light_time);
	if(verbose)
		printf("Header : Light Time - %i\n", info.light_time);
	Org(MAXITEM);
	OutByte(info.max_load);
	if(verbose)
		printf("Header : Max Carry - %i\n", info.max_load);
	Org(ABBREV);
	OutByte(info.word_length);
	if(verbose)
		printf("Header : Word Length - %i\n", info.word_length);

	/*
	 * Dump the rest of the data structures.
	 */
	ti99_DumpRooms();
	ti99_DumpItems();
	DumpMessages();
	DumpVerbs();
	DumpNouns();
	dump_actions();
}


/*----------------------------------------------------------------------
 *
 * storeByte --
 *
 *		This procedure stores a byte into the current code block,
 *		if there is room for it.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
storeByte(
  unsigned value)				/* The value to store. */
{
	ASSERT(value < 256);
	if (code_p >= code_buf+BLOCK_SIZE) {
		error("too big action block");
		return;
	}
	*code_p++ = value;
}


/*----------------------------------------------------------------------
 *
 * dump_actions --
 *
 *		This procedure dumps the action tables to the output file.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void
dump_actions(void)
{
	int i;
	int numverbs = GetNoVerbs();
	int ptrs[257];
	Action* actp;

	Org(Here());
	for (i = 0; i < numverbs; i++) {
		ptrs[i] = 0;
		actp = action[i];
		if (actp == 0)
			continue;
		ptrs[i] = OutAddress();
		ASSERT(actp->verb == i);
		do {
			actp = actp->next;
			OutByte(actp->noun);
			if (actp == action[i]) { /* The last block. */
				OutByte(0);
			} else {
				OutByte(actp->length+2);
			}
			outbuf(actp->code, actp->length);
			OutByte(0xFF);
		} while (actp != action[i]);
	}
	SetHere(ptrs[i] = OutAddress());

	/*
	 * Write into header.
	 */
	if (ptrs[0] == 0) {
		error("no implicit actions defined");
		return;
	}
	Org(IMPLICIT);
	OutWord(ptrs[0]);
	ptrs[0] = 0;
	Org(EXPLICIT);
	OutWord(Here());
	Org(Here());
	for (i = 0; i < numverbs; i++) {
		//if (verbose)
		//	  printf("%d at %04X: %04X\n", i, OutAddress(), ptrs[i]);
		OutWord(ptrs[i]);
	}
	SetHere(OutAddress());
}

int PutDescTable(char** table, int no)			/* dump a complete table */
{
	int i, length;
	int addr = OutAddress();
	int text = OutAddress() + (no+1) * 2;

	for (i = 0; i < no; i++) {
		OutWord(text);
		Transform(table[i]);
		length = strlen(table[i]);
		if (length > 0)
			length++;
		text += length;
	}
	OutWord(text);
	for (i = 0; i < no; i++) {
		OutString(table[i]);
	}
	return addr;
}

