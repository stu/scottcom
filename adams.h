/*
 * $Id: adams.h,v 1.1 1996/01/12 08:00:34 bjorn Exp $
 */

#define OBJS 	0xc20		/* number of objects */
#define VERBS 	0xc21		/* number of verbs */
#define NOUNS 	0xc22		/* number of nouns */
#define REDROOM 0xc23		/* the red room */
#define MAXITEM 0xc24		/* max number of items that can be carried */
#define BEGROOM 0xc25		/* starting room for player */
#define NOTREA  0xc26		/* number of treasuers */
#define ABBREV 	0xc27		/* minimum number of letters in commands */
#define LIGHT 	0xc28		/* maximum light time */
#define TREASURE 0xc2a		/* treasure room */
#define STRANGE	0xc2b		/* unknown */
#define OBJTABLE 0xc2c		/* pointer to object table */
#define ORIGOBJS 0xc2e		/* pointer to original items */
#define OBJLINK	0xc30		/* pointer to link table from noun to object */
#define OBJDESC	 0xc32		/* pointer to object descriptions */
#define MESSAGES 0xc34		/* pointer to message pointers */
#define ROOMEXITS 0xc36		/* pointer to room exits table */
#define ROOMDESC 0xc38		/* pointer to room descriptor pointers */
#define NOUNTABLE 0xc3a		/* pointer to noun table */
#define VERBTABLE 0xc3c		/* pointer to verb table */
#define EXPLICIT  0xc3e		/* pointer to explicit action table */
#define IMPLICIT 0xc40		/* pointer to implicit actions */
#define SAVEDROOM 0xc42		/* saved room */
#define SAVEDTIMER 0xc48	/* saved timer */
#define SAVEAREA   0xc58	/* save area */
#define DYNAMIC_AREA	0xc62	/* dynamic part of file */

