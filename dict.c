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
 * $Id: dict.c,v 1.1 1996/01/12 08:01:57 bjorn Exp $
 *
 */

#include <ctype.h>
#include "scottcom.h"
#include "adams.h"
#include "parser.h"

/****************************
		VERB TABLES
*****************************/
static int CurrentVerb = 0;
Symbol *Verbs[MAX_VERBS];
static int synonymsLeft;		/* The number of synonyms left for the
								 * verb being currently defined.  Generally set
								 * set to MAX_VERBS (no limitations), except
								 * for the special verbs GO and GET. */
static int last_verb = 1;		/* The highest verb number encounted (last in
								 * in Verbs[]). */
static int plain_verbs_only = NO; /* If NO, special verbs can still be defined.
								   * When set to YES, only non-special verbs
								   * can be defined. */
/****************************
  NOUN TABLES
  *****************************/
static int CurrentNoun = -1;
static int NounSeq = 7;
Symbol *NounNames[256];
static int NumberOfNouns = 0;

int FixedVerb;

void NounNo(int n)		/* set current noun number */
{
	CurrentNoun = n;
}

/*
 * Register the symbol as a noun.
 */
int SetNoun(Symbol* s, int noun_type)
{
	s->type = NOUN;
	if (CurrentNoun == -1)
		CurrentNoun = NounSeq++;
	if (CurrentNoun > sizeof(NounNames)/sizeof(NounNames[0]))
		error("too many nouns defined");
	NounNames[CurrentNoun] = s;
	s->value = CurrentNoun;
	if (noun_type != PRIMARY)
		s->value = -s->value;
	CurrentNoun = -1;
	if (s->value >= NumberOfNouns)
		NumberOfNouns = s->value + 1;
	return s->value;
}

void DumpNouns(void)
{
	int P[256];
	int i;

	if (verbose)
		printf("Number of nouns = %d\n", NumberOfNouns);

	Org(Here());
	for (i = 0; i < NumberOfNouns; i++) {

		P[i] = OutAddress();
		if (NounNames[i]) {
			if (NounNames[i]->value < 0)
				OutByte('*');

			outdictword(NounNames[i]->name);
			if (verbose)
				printf("\t%2d at %04X: %s%s\n",
					   i, OutAddress(), NounNames[i]->value < 0 ? "*" : "", NounNames[i]->name);
		}
	}
	P[i] = OutAddress();
	for (i = 0; i <= NumberOfNouns; i++)
		OutWord(P[i]);
	SetHere(OutAddress());
	Org(NOUNS);
	OutByte(NumberOfNouns-1);
	Org(NOUNTABLE);
	OutWord(P[NumberOfNouns]);
}


/*----------------------------------------------------------------------
 *
 * specialVerb --
 *
 *		This procedure sets the number for the next special verb.
 *		An error message will be printed if the special verb is
 *		already defined.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
static void specialVerb(
  int n,						/* Number of special verb. */
  const char* name,				/* Name of special verb (for error message). */
  int synonyms					/* Number of synonyms allowed. */
)
{
	if (Verbs[n] == (Symbol *) 0) {
		CurrentVerb = n;
		synonymsLeft = synonyms;
	} else {
		sprintf(err_sbuf, "more than one definition for %s verb", name);
		error(err_sbuf);
	}
}

int GetNoVerbs()				/* return number of verbs */
{
	return last_verb+1;
}

int GetPrimaryVerb(int k)
{
	int i;
	int j=k;

	if(k>=0)
		return k;

	if(j<0)
		j = 0-j;

	ASSERT(j>0);

	for(i=j; i>=0; i-=1)
	{
		if(Verbs[i]->value > 0)
			return Verbs[i]->value;
	}

	return 0;
}

int GetPrimaryNoun(int k)
{
	int i;
	int j=k;

	if(k>=0)
		return k;

	if(j<0)
		j = 0-j;

	ASSERT(j>0);

	for(i=j; i>=0; i-=1)
	{
		if(NounNames[i]->value > 0)
			return NounNames[i]->value;
	}

	return 0;
}


/*----------------------------------------------------------------------
 *
 * NumberVerb --
 *
 *		This procedure stores the number that the next verb
 *		to be defined with SetVerb() should have.  It also makes
 *		sure that the three special verbs (go, get, drop), is
 *		defined before any other verbs.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void NumberVerb(
		int n					/* Number that the next verb should have. */
								/* Only one of VERB_GO, VERB_GET, VERB_DROP, */
								/* or VERB_NEXT is allowed. */
)
{
	switch (n)
	{
		case VERB_AUTO:
			specialVerb(n, "AUTO", 1);
			FixedVerb = 1;
			break;
		case VERB_GO:
			specialVerb(n, "GO", VERB_GET-VERB_GO);
			FixedVerb = 1;
			break;
		case VERB_GET:
			specialVerb(n, "GET", VERB_DROP-VERB_GET);
			FixedVerb = 1;
			break;
		case VERB_DROP:
			specialVerb(n, "DROP", MAX_VERBS);
			FixedVerb = 1;
			break;
		case VERB_NEXT:
			FixedVerb = 0;
			if (plain_verbs_only)	/* CurrentVerb is already set. */
				return;

			/*
			 * Since the definition of the first non-special verb
			 * follows, we must check that all special verbs have
			 * been defined.
			 */
			if (Verbs[VERB_GO] == NULL)
				error("the GO verb not defined before first plain verb");
			else if (Verbs[VERB_GET] == NULL)
				error("the GET verb not defined before first plain verb");
			else if (Verbs[VERB_DROP] == NULL)
				error("the DROP verb not defined before first plain verb");
			else
			{
				/* Okay, find the first empty verb slot. */
				for (CurrentVerb = 1; CurrentVerb < MAX_VERBS; CurrentVerb++)
				{
					if (Verbs[CurrentVerb] == NULL)
					{
						synonymsLeft = MAX_VERBS;
						plain_verbs_only = YES;
						return;
					}
				}

				/*
				 * The next error is unlikely, but can occur if 238 synonyms
				 * for DROP were defined.
				 */
				error("attempt to define too many verbs");
			}
			break;

		default:					/* Can't happen -- logical error. */
			ASSERT(0);
	}
}

/*----------------------------------------------------------------------
 *
 * SetVerb --
 *
 *		This function registers a verb in the dictionary.
 *
 * Results:
 *		This function returns the number of the verb.
 *
 *----------------------------------------------------------------------
 */
int SetVerb(Symbol *s, int verb_type)
{
	int i;

	if(verb_type == PRIMARY && FixedVerb == 0)
	{
		for(i=0; i<MAX_VERBS; i+=1)
		{
			if(Verbs[i] == NULL)
			{
				CurrentVerb = i;
				break;
			}
		}
	}

	if (CurrentVerb >= MAX_VERBS)
		error("attempt to define too many verbs");
	else if (synonymsLeft-- <= 0) {
		error("too many synonyms for this verb");
	}
	else
	{
		if (Verbs[CurrentVerb] != NULL)
		{
			int new_slot;

			/*
			 * The slot we want to use is already occupied
			 * (by one of the special verbs GET or DROP).
			 * First we'll have to find a new slot.
			 */
			if (verb_type == PRIMARY)
			{
				new_slot = CurrentVerb+1;
			}
			else
			{
				new_slot = VERB_DROP+1;
			}

			while(new_slot < MAX_VERBS && Verbs[new_slot] != NULL)
				new_slot++;

			if (new_slot >= MAX_VERBS)
				error("attempt to define too many verbs");

			if (verb_type == SYNONYM)
			{
				/*
				 * The verb to be registred is a synonym to a previously
				 * registred primary verb, so we must move the primary
				 * verb along with its synonyms to the new slot too.
				 * This will change its verb number, but this is safe to do,
				 * because there can't be any references to it yet.
				 * (You must define any synonyms for a verb before you
				 * use it in an action.)
				 */
				int primary;	/* Number of verb for which a synonym
								 * is about to be defined. */

				/*
				 * Locate the primary verb.
				 */
				primary = CurrentVerb-1;
				while (Verbs[primary]->value < 0)
				{
					ASSERT(primary >= 1);
					primary--;
				}

				/*
				 * Move the primary verb and all its previous synonyms.
				 */
				while (primary < CurrentVerb)
				{
					if (new_slot >= MAX_VERBS)
						error("attempt to define too many verbs");
					if(verbose)
						printf("Moving %s from %i to %i\n", Verbs[primary]->name, primary, new_slot);

					Verbs[new_slot] = Verbs[primary];

					if(Verbs[new_slot]->value < 0)
						Verbs[new_slot]->value = -new_slot;
					else
						Verbs[new_slot]->value = new_slot;

					Verbs[primary] = NULL;
					new_slot++, primary++;
				}
			}
			CurrentVerb = new_slot;
		}

		/*
		 * The slot is free.  Time to insert the verb into the slot.
		 */


		Verbs[CurrentVerb] = s;
		s->type = VERB;
		s->value = CurrentVerb;

		if(verbose)
			printf("Verb %s (%c) = %i\n", s->name, verb_type == PRIMARY ? 'P' : 'S', s->value);

		if (verb_type != PRIMARY)
			s->value = -s->value;
		if (CurrentVerb > last_verb)
			last_verb = CurrentVerb;
		CurrentVerb++;


		return s->value;
	}
	return 0;					/* Dummy return value in case of error. */
}

void DumpVerbs(void)
{
	int P[256];
	int i;

	if (verbose)
		printf("Last verb has number %d\n", last_verb);
	Org(Here());
	for (i = 0; i <= last_verb; i++)
	{
		P[i] = OutAddress();
		if (Verbs[i]) {
			if (Verbs[i]->value < 0)
				OutByte('*');
			outdictword(Verbs[i]->name);
			if (verbose)
				printf("\t%2d at %04X: %s%s\n", i, P[i], Verbs[i]->value < 0 ? "*" : "", Verbs[i]->name);
		}
	}
	P[i] = OutAddress();
	for (i = 0; i <= last_verb+1; i++)
		OutWord(P[i]);
	SetHere(OutAddress());
	Org(VERBS);
	OutByte(last_verb);
	Org(VERBTABLE);
	OutWord(P[last_verb+1]);
}

/*----------------------------------------------------------------------
 *
 * outdictword --
 *
 *		This function outputs a dictionary word to the output file.
 *		Only the number of letter given by info.word_length will
 *		output and each letter will be converted to upper case.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void outdictword(char *s)
{
	int n = info.word_length;

	char x[16];
	char *z;

	strcpy(x, s);

	z=(char *)x;
	while (*z && n-- > 0) {
		OutByte(toupper(*z++));
	}
}
