/*
 * $Id: scottcom.h,v 1.1 1996/01/12 07:59:01 bjorn Exp bjorn $
 */

#ifndef SCOTTCOM_H
#define SCOTTCOM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

/* can only be X.YY of 3 characters */
#define VERSION		"2.05"


#define NO	0
#define YES 1

#define PRIMARY 0
#define SYNONYM 1

/*
 * Macro to return the number of elements in an array.
 */
#define ARRAYSIZE(a) (sizeof(a) / sizeof((a)[0]))

/*
 * Here is the number of the light-source item.
 * (This number must NOT be changed.)
 */
#define LIGHT_SOURCE 9

/*
 * Here are names for the verbs with magic numbers.
 * VERB_NEXT can be passed to NumberVerb(), which means
 * that the next verb should use the next free verb number.
 */
#define VERB_NEXT -1
#define VERB_AUTO 0
#define VERB_GO 1
#define VERB_GET 10
#define VERB_DROP 18

#define MAX_VERBS 256		/* Maximum number of verbs to be defined.
				 * This value may not be increased past 256. */

#define MAX_TRY_DEPTH	16

#if !defined(DEBUG)
#define ASSERT(x)
#else
#define ASSERT(x) \
 if (x) \
	; \
 else \
	_Assert(__FILE__, __LINE__)
#endif

typedef unsigned char byte;

/*
 * Function pointers for the output format.
 */
extern unsigned (*translate)(unsigned code);
extern void (*createfile)(char*);
extern void (*titlestr)(char*);
extern void (*begcatch)(void);
extern void (*endcatch)(void);
extern void (*begaction)(int, int);
extern void (*endaction)(void);
extern void (*action0)(unsigned);
extern void (*action1)(unsigned, unsigned);
extern void (*action2)(unsigned, unsigned, unsigned);
extern void (*dump)(void);

/*
 * Definitions for format-independent codes.  These must
 * be translated by the output format.	The names are based
 * on the mnemonics in P.D. Doherty's Scottdec program, because
 * they are clear and non-ambigous.	 The values are based on
 * the values for the TI-99 format, with OP_BASE added.
 * For the TRS-80 format, the value must be converted.
 */
#define OP_BASE 256

/*
 * The following two operations are not part of the TI-99 format,
 * but are provided for compatibility with the TRS-80 format.
 * The TI-99 format will never include these operations, and the
 * the TRS-80 format will translate to the appropriate codes.
 */
#define OP_CLS (OP_BASE+0xD4)
#define OP_SHOW_PIC (OP_BASE+0xD5)

#define OP_SWAP_ITEMS (OP_BASE+0xEC)
#define OP_SWAP_COUNTER (OP_BASE+0xFA)
#define OP_SELECT_RV (OP_BASE+0xF8)
#define OP_SWAP_LOC_RV (OP_BASE+0xF9)

#define OP_IGNORE 512		/* Internal code used by formats to ignore */
				/* an unsupported operation. */

/*
 * This structure is an entry for the symbol tables.
 * Each symbol table is a binary tree.
 */
typedef struct Symbol Symbol;
struct Symbol {
	char *name;			/* The name of the identifier. */
	short type;			/* Type to return from yylex(). */
	int value;			/* Integer value for identifier. */
	Symbol *left;		/* Pointer to left child. */
	Symbol *right;		/* Pointer to right child. */
};

/*
 * This structure associates an identifier with the token type
 * and value.
 */
typedef struct Keyword {
	char *name;			/* Name of identifier. */
	int token;			/* Token type to be returned by yylex(). */
	int value;			/* Value to be stored in yylval.n. */
} Keyword;

/*
 * The following structure contains the header parameters which
 * the player must specify.
 */
typedef struct Parameters {
	int max_load;		/* Maximum # of items the player can carry. */
	int word_length;		/* Maximum length of dictionary words (3-9). */
	int current_room;		/* The room the game starts in. */
	int treasure_room;		/* The room to store treasures in. */
	int light_time;		/* Number of turns light should last. */
} Parameters;


/*
 * The following structure is used to store action blocks
 * before they are output to file.	This structure will only be
 * used when a code block is completed; for building a code block
 * static variables are used.
 */
typedef struct Action Action;
struct Action
{
	Action* next;				/* Pointer to next action block for */
								/* this verb. */
	byte verb;					/* The verb this action is for. */
	byte noun;					/* The noun this action is for. */
	int length;					/* Length in byte of code which follows. */
	byte code[1];				/* The compiled code for this action block.
								 * (The actual size of the code array must - 1
								 * must be added to the size of this structure
								 * when allocating space.)
								 */
};


extern Parameters info;		/* Contains the user-given parameters. */
extern int	lineno, fatalerr;
extern int	verbose;
extern char *infile, *outfile;
extern FILE *finp;

extern Action** action;
extern int	try_index;
extern byte *try_level[MAX_TRY_DEPTH+1];

extern int FixedVerb;

extern char *err_sbuf;

/*** code.c ***/
int Here(void);
void SetHere(int n);
int RangeCheck(char* name, int value, int min, int max);
void actflag(int op, int flag);
void acttimer(int op, int n);
int GetNextFlag(void);
int GetNextTimer(void);
int GetNextRoomReg(void);

/*** dict.c ***/
extern Symbol *NounNames[256];
extern Symbol *Verbs[MAX_VERBS];
int GetPrimaryVerb(int j);
int GetPrimaryNoun(int k);
void NounNo(int n);
int SetNoun(struct Symbol *s,int noun_type);
void DumpNouns(void );
int GetNoVerbs(void);
void NumberVerb(int n);
int SetVerb(struct Symbol *s, int verb_type);
void DumpVerbs(void);
void outdictword(char *s);

/*** init.c ***/
void init(void);
void install_keywords(Symbol** table, Keyword* keywords, int size);

int string(char *s);

/*** item.c ***/
int GetNextItem(void);
void SetItem(int item, char* name, int owner, int link);
void FixLightSource(void);
void ti99_DumpItems(void);

/*** main.c ***/
int main(int argc,char **argv );
void execerror(char *s);
char *getexten(char *name);
char *newexten(char *name,char *ext);
void _Assert(const char* file, unsigned line);

/*** message.c ***/
int StartMessage(void);
int Message(char *s);
void DumpMessages(void);

/*** output.c ***/
void initprint(char *name);
void stopprint(void);
void Org(int n);
int OutAddress(void);
void OutString(char *s);
void Transform(char *s);
void OutByte(int n);
void OutWord(int n);
void outbuf(byte* s, unsigned length);

/*** room.c ***/
void SetExit(int dir, struct Symbol *to);
int MakeRoom(char* desc, char *name);
void ti99_DumpRooms(void);

typedef struct Room Room;
struct Room {
	char *name;
	char* desc;					/* The description for the room. */
	Symbol* exit[6];			/* What the exits lead to. */
	Room* next;					/* Pointer to next room. */

	int def_line;				/* line defined on */
};

extern Room *room;
extern int NumRooms;

/*** sym.c ***/
extern	struct Symbol *lookup(Symbol* root, char *s);
extern	struct Symbol *install(Symbol** tptr, char *s,int t);
extern	char *emalloc(unsigned int n);
extern	char *erealloc(char *p,unsigned int n);
extern	char *strsave(char *s);

/*** formats ***/
void ti99_init(void);
int PutDescTable(char **table, int no);

/*** parser.y ***/
int yylex(void);
void warn(char* message);
void error(char *s);
int yyparse(void);

#endif
