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
 * $Id: parser.y,v 1.2 1996/10/17 04:15:56 bjorn Exp $
 *
 */

%{
#include <ctype.h>

#include "scottcom.h"

static int owner_level;		/* Level of owner */
Symbol* main_table;		/* Main symbol table. */
Symbol* noun_table;		/* Symbol table for nouns. */
Symbol* verb_table;		/* Symbol table for verbs. */
Symbol* label_table;		/* Symbol table for labels. */
Parameters info;		/* The parameters the player must specify. */

/*
 * The current symbol table to use for lookup of identifiers.
 * Normally set to main_table, but can temporarily be set to
 * one of the other tables.
 */
static Symbol** current = &main_table;

/*
 * Private functions for this file.
 */
static int special(int c);
static int skipWhiteSpace(void);
static void yyerror(char *s);
static void printMessage(char* message);
%}
%union {
	int n;			/* Any integer. */
	char *sp;			/* Pointer to a string. */
	Symbol *sym;		/* Pointer to a symbol. */
}

%token	<n> NUMBER
%token	<sp>	STRING
%token	<n> TESTOBJ TESTROOM TESTFLAG TESTNUM PARAMLESS
%token	<n> IF ACTOBJ ACTROOM ACTFLAG ACTNUM ACTROOMOBJ
%token	<n> ACTOBJOBJ TIMER
%token	<n> DIRECT
%token	<n> VLABEL
%token	<n> NLABEL
%token	<n> KW_NOUN KW_VERB KW_FLAG KW_TIMREG KW_ROOMREG KW_OBJECT
%token	<n> KW_ROOM KW_ACTION KW_MESSAGE
%token	<n> OLABEL
%token	<n> FLABEL
%token	<sym>	UNDEF ROOM
%token	<n> VERB NOUN OBJECT MESSAGE FLAG TREG RREG
%token	<n> PARSTART PARTREASURE PARLIGHT PARCARRY PARABBREV PARTITLE
%token	<n> PLAYER
%token	<n> VOID
%token	<n> SWAP

%type	<n> labelref nounref opt_nounref ownerref
%type	<n> noun_expr new_or_old_verb
%type	<n> treglist rreglist
%type	<n> expr
%left	'=' '<' '>'
%left	'+' '-'
%left	'*' '/'
%%
prog:	  stmtlist
	{
		yychar = -1;
		if (info.word_length == 0) {
		info.word_length = 3; /* Silently default. */
		}
		if (info.max_load == 0) {
		info.max_load = 4; /* Silently default. */
		}
		if (info.current_room == 0) {
		error("parameter 'initial' not set");
		}
		FixLightSource();
		if (!fatalerr) {
		dump();
		}
	}
	;

stmtlist: stmt
	| stmtlist stmt
	;

stmt:	  KW_NOUN { current = &noun_table; } nounitem ';'
		  { current = &main_table; }
	| KW_VERB { current = &verb_table; }
	  verbitem { current = &main_table; }
	  ';'
	| KW_ACTION		{ current = &verb_table; }
	  new_or_old_verb	{ current = &noun_table; }
	  noun_expr		{ current = &main_table; begaction($3, $5); }
	  '{' actlist '}'	{ endaction(); }
	| KW_MESSAGE UNDEF '=' STRING ';'	{ $2->type = MESSAGE;
						  $2->value = Message($4);
						}
	| KW_ROOM UNDEF STRING	{ $2->value = owner_level = MakeRoom($3, $2->name);
				  $2->type = ROOM;
				}
	  dirlist ';'
	| KW_FLAG flagitem ';'
	| KW_TIMREG treglist ';'
	| KW_ROOMREG rreglist ';'
	| KW_OBJECT objlist ';'
	| PARSTART '=' ROOM ';'		{ info.current_room = $3->value; }
	| PARTREASURE '=' ROOM ';'	{ info.treasure_room = $3->value; }
	| PARLIGHT '=' expr ';'
		{ info.light_time = RangeCheck("light_time", $3, 1, 32767); }
	| PARCARRY '=' expr ';'
		{ info.max_load = RangeCheck("max_load", $3, 1, 256); }
	| PARABBREV '=' expr ';'
		{ info.word_length = RangeCheck("word_length", $3, 3, 32); }
	| PARTITLE '=' string_list ';'
	;

string_list: STRING		 { titlestr($1); }
	| string_list ',' STRING { titlestr($3); }
	;

verbitem: '('			{ current = &label_table; }
	  VLABEL ')'		{ NumberVerb($3); current = &verb_table; }
	  vlist
	| { NumberVerb(VERB_NEXT); } vlist
	;

vlist:	  UNDEF				{ SetVerb($1, PRIMARY); }
	| vlist ',' UNDEF		{ SetVerb($3, SYNONYM); }
	;

/* Nouns */
nounitem: '('				{ current = &label_table; }
	  NLABEL ')'			{
						NounNo($3);
						current = &noun_table;
					}
	  UNDEF				{ SetNoun($6, PRIMARY); }
	| nlist
	;

nlist:	  UNDEF				{ SetNoun($1, PRIMARY); }
	| nlist ',' UNDEF		{ SetNoun($3, SYNONYM); }
	;

dirlist:  /* empty */
	| diritem
	| dirlist ',' diritem
	;

diritem:  DIRECT ROOM		{ SetExit($1, $2); }
	| DIRECT UNDEF		{ SetExit($1, $2); $2->value = -1; }
	;

/* Item list. */
objlist:  objitem
	| objlist ',' objitem
	;

objitem: labelref UNDEF opt_nounref STRING ownerref
				 { $2->type = OBJECT;
				   $2->value = $1;
				   SetItem($1, $4, $5, $3);
				 }
	;

opt_nounref: /* empty */ { $$ = 0; }
	| '(' { current = &noun_table; }
	  nounref { current = &main_table; } ')' { $$ = $3; }
	;

nounref:  /* empty */		{ $$ = 0; }
	| NOUN			{ $$ = $1; }
	| UNDEF			{ $$ = SetNoun($1, PRIMARY); }
	;

labelref: /* empty */		{ $$ = GetNextItem(); }
	| '('			{ current = &label_table; }
	  OLABEL ')'		{ current = &main_table; $$ = $3; }
	;

ownerref: /* empty */	{ $$ = owner_level; }
	| PLAYER	{ $$ = 255; }
	| ROOM		{ $$ = $1->value; }
	| VOID		{ $$ = 0; }
	;
/*
flaglist: flagitem
	| flaglist ',' flagitem
	;
*/
/*
 * Flags.
 */
flagitem: '('			{ current = &label_table; }
	  FLABEL ')'		{ current = &main_table; }
	  UNDEF
				{ $6->type = FLAG;
				  $6->value = $3;
				  if(verbose)
					printf("flag %s as %i\n", $6->name, $6->value);
				}
	| UNDEF			{ if (($1->value = GetNextFlag()) != -1)
					{
					$1->type = FLAG;
					if(verbose)
					printf("flag %s as %i\n", $1->name, $1->value);
					}
				}
	;

/*
treglist: UNDEF			{ $$ = $1->value = 0; $1->type = TREG; }
	| treglist ',' UNDEF		{ if ($1 > 16) {
						error("too many timer regs");
						$$ = $1;
					  } else {
						$3->type = TREG;
						$$ = $3->value = $1+1;
					  }
					}
	;
*/

treglist: UNDEF			{  if(($1->value = GetNextTimer()) != -1)
							{
								$1->type = TREG;
								if(verbose)
									printf("timer %s as %i\n", $1->name, $1->value);
							}
						}
	;

/*
rreglist: UNDEF				{ $$ = $1->value = 0; $1->type = RREG; }
	| rreglist ',' UNDEF		{ if ($1 >= 5) {
						error("too many room regs");
						$$ = $1;
					  } else {
						$3->type = RREG;
						$$ = $3->value = $1+1;
					  }
					}

	;
*/

rreglist: UNDEF			{  if(($1->value = GetNextRoomReg()) != -1)
							{
								$1->type = RREG;
								if(verbose)
									printf("room reg %s as %i\n", $1->name, $1->value);
							}
						}
	;

noun_expr:
	  expr
	| NOUN			{ if($1 < 0)
					$1 = GetPrimaryNoun($1);
					$$ = $1;
				}
	| UNDEF			{ $$ = SetNoun($1, PRIMARY); }
	;

new_or_old_verb: VERB		{ if($1 < 0)
					$1 = GetPrimaryVerb($1);
					$$ = $1;
				}
	| UNDEF			{ NumberVerb(VERB_NEXT);
				  $$ = SetVerb($1, PRIMARY); }
	;

/* Action lists */
actlist:  action
	| actlist action
	| actlist error ';'		{ yyerrok; }
	;

action:	  TESTOBJ '(' OBJECT ')' ';'	{ action1($1, $3); }
	| TESTROOM '(' ROOM ')' ';' { action1($1, $3->value); }
	| TESTFLAG '(' FLAG ')' ';' { action1($1, $3); }
	| TESTNUM '(' expr ')' ';'	{ action1($1, $3); }
	| PARAMLESS ';'			{ action0($1); }
	| IF '{' { begcatch(); } actlist { endcatch(); } '}'
	| ACTOBJ OBJECT ';'		{ action1($1, $2); }
	| ACTROOM ROOM ';'		{ action1($1, $2->value); }
	| ACTFLAG FLAG ';'		{ actflag($1, $2); }
	| ACTNUM expr ';'		{ action1($1, $2); }
	| ACTROOMOBJ ROOM ',' OBJECT ';'  { action2($1, $2->value, $4); }
	| ACTOBJOBJ OBJECT ',' OBJECT ';' { action2($1, $2, $4); }
	| TIMER expr ';'		{ acttimer($1, $2); }
	| MESSAGE ';'			{ action0($1); }
	| STRING ';'			{ action0(Message($1)); }
	| SWAP RREG ';'
		{
			if ($2 == 0) {
				action0(OP_SELECT_RV);
			} else {
				action1(OP_SWAP_LOC_RV, $2);
			}
		}
	| SWAP TREG ';'			{ action1(OP_SWAP_COUNTER, $2); }
	| SWAP OBJECT ',' OBJECT ';'	{ action2(OP_SWAP_ITEMS, $2, $4); }
	;

expr:	  NUMBER			{ $$ = $1; }
	| expr '+' expr			{ $$ = $1 + $3; }
	| expr '-' expr			{ $$ = $1 - $3; }
	| expr '*' expr			{ $$ = $1 * $3; }
	| expr '/' expr			{ $$ = $1 / $3; }
	| '(' expr ')'			{ $$ = $2; }
	;

%%	/* end of grammar */
void printtok(int t, YYSTYPE val);

int yylex(void)
{
	int c;

	c = skipWhiteSpace();		/* Skip all white space. */

	if (c == EOF)
	return 0;

	/*
	 * Test for a number.
	 */
	if (isdigit(c)) {
	int i;
	int j;

	ungetc(c, finp);
	j = fscanf(finp, "%d", &i);
	yylval.n = i;
	return NUMBER;
	}

	/*
	 * Test for a string constant.
	 */
	if (c == '"') {
	char sbuf[4096];
	char *p;

	p = sbuf;

	catenate_strings:
	for (;;) {
		c = getc(finp);
		if (c == '"' && (c = getc(finp)) != '"') {
		ungetc(c, finp);
		break;
		}
		if (c == '\n' || c == EOF) {
		lineno++;
		error("missing quote");
		}
		if (p >= sbuf + sizeof(sbuf) - 1) {
		*p = '\0';
		error("string constant too long");
		}
		*p++ = c;
	}
	*p = 0;

	/*
	 * Test for new string following this string.
	 */
	c = skipWhiteSpace();
	if (c != '"')
		ungetc(c, finp);
	else
		goto catenate_strings;

	/*
	 * Definite end of string constant.
	 */
	yylval.sp = emalloc(strlen(sbuf)+1);
	strcpy(yylval.sp, sbuf);
	return STRING;
	}

	/*
	 * Test for identifier.
	 */
	if (isalpha(c) || special(c)) {
	Symbol *s;
	char sbuf[100], *p = sbuf;

	do {
		*p++ = c;
	} while ((c=getc(finp)) != EOF && (isalnum(c) || special(c)));
	ungetc(c, finp);
	*p = '\0';
	s = lookup(*current, sbuf);
	if (s == 0) {
		yylval.sym = install(current, sbuf, UNDEF);
		return UNDEF;
	}

	switch (s->type) {
	case UNDEF:
	case ROOM:
		yylval.sym = s;
		return s->type;
	default:
		yylval.n = s->value;
		return s->type;
	}
	}
	return c;
}

/*
 * Skip white space and comments.
 */
static int skipWhiteSpace(void)
{
	int c;

start:
	/*
	 * Skip white space.
	 */
	while ((c=getc(finp)), isspace(c))
		if (c == '\n')
			lineno++;

	/*
	 * Skip # comment.
	 */
	if (c == '#') {
		while (getc(finp) != '\n')
			;
		lineno++;
		goto start; /* Skip more white space */
	}
	return c;
}

static int special(int c)	/* test if special identifier character */
{
	if (strchr("_.!", c) != NULL)
		return YES;
	else
		return NO;
}

void error(char *s)		/* Report fatal error. */
{
	 int old_yychar = yychar;
	 yychar = -1;		/* Suppress printing of last token. */
	 printMessage(s);
	 yychar = old_yychar;
	 fatalerr = YES;		/* Don't produce any output. */
}

void
warn(char *message)		/* Report a warning message. */
{
	 int old_yychar = yychar;
	 yychar = -1;		/* Suppress printing of last token. */
	 printMessage(message);
	 yychar = old_yychar;
}

static void yyerror(char *s)	/* recover from compilation error */
{
	fatalerr = YES;
	printMessage(s);
}


/*----------------------------------------------------------------------
 *
 * printMessage --
 *
 *	This procedure prints the message on the standard output,
 *	together with the name of the input file and line number.
 *	If there is a last token available in yychar, that will
 *	be printed too to help locate the error.
 *
 * Results:
 *	None.
 *
 *----------------------------------------------------------------------
 */
static void
printMessage(char* message) /* Message to print. */
{
	printf("%s(%d): %s", infile, lineno, message);
	if (yychar != -1) {
	printf(": ");
	if (yychar >= ' ' && yychar < 255)
		printf("'%c'", yychar);
	else
		printtok(yychar, yylval);
	}
	printf("\n");
}
