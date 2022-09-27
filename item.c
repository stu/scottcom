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
 * $Id: item.c,v 1.1 1996/01/12 08:01:16 bjorn Exp $
 *
 */

#include "scottcom.h"
#include "adams.h"

static int CurrentItem = 0;
static char *NameTable[256];	/* Name of all items. */
static char OwnerTable[256];	/* Owner of all items. */
static char LinkTable[256];		/* Noun link for all items. */
static int NoTreasures = 0;		/* Count of treasures in game. */


/*----------------------------------------------------------------------
 *
 * GetNextItem --
 *
 *		This function retrieves the number of the next
 *		free item number.  It will generate an error
 *		message if the number would be greater than 255.
 *		This function will never return 9, because that item
 *		number is reserved for the light source.
 *
 * Results:
 *		The number of the next free item.
 *
 *----------------------------------------------------------------------
 */
int
GetNextItem(void)
{
	if (CurrentItem == LIGHT_SOURCE)
		CurrentItem++;
	if (CurrentItem == 256) {
		CurrentItem--;
		error("too many items defined");
	}
	return CurrentItem++;
}


/*----------------------------------------------------------------------
 *
 * SetItem --
 *
 *		This procedure sets the name, owner, and associated noun
 *		for an item.  The item number must have been obtained from
 *		the GetNextItem() function, or be the constant LIGHT_SOURCE.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void
SetItem(
  int item,						/* Number of item. */
  char* name,					/* Description of item. */
  int owner,					/* Owner of item. */
  int link)						/* Noun by which item can be named, */
								/* or 0 if no such noun. */
{
	if (item == LIGHT_SOURCE && NameTable[item] != 0) {
		error("attempt to define more than one light source");
		return;
	}
	ASSERT(NameTable[item] == 0); /* Impossible to assign more than once. */
	NameTable[item] = name;
	if (name[0] == '*')
		NoTreasures++;
	OwnerTable[item] = owner;
	LinkTable[item] = link;
}


/*----------------------------------------------------------------------
 *
 * FixLightSource --
 *
 *		This procedure handles the issues of the light source
 *		(item 9):
 *
 *		1. If the game has no light source, item 9 will get
 *		   a dummy name (to avoid having a null pointer).
 *
 *		2. If there are less than nine items in a game, make
 *		   sure that we define dummy items before item 9.
 *
 *		3. If the game defines a light source, check that the
 *		   the 'light_time' parameter was given.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void
FixLightSource(void)
{
	while (CurrentItem < LIGHT_SOURCE) {
		NameTable[CurrentItem++] = strsave(".");
	}
	if (CurrentItem <= LIGHT_SOURCE) {
		CurrentItem++;
	}
	if (NameTable[9] == 0) {
		NameTable[9] = strsave("."); /* Give the light source a dummy name. */
									 /* The strsave() is necessary to assure */
									 /* that the string can be written to */
									 /* (Transform() will be used). */

	} else if (info.light_time == 0) {
		error("there is a light source, but 'light_time' is not set");
	}
}

void ti99_DumpItems(void)		/* dump item tables */
{
	int i;
	int Owner1, Owner2, Link, Name;

	if (verbose)
		printf("Number of items = %d\n", CurrentItem);
	if (CurrentItem == 0) {
		error("no items defined");
		return;
	}

	/*
	 * Output the first owner table
	 */
	Org(Owner1 = Here());
	for (i = 0; i < CurrentItem; i++)
	{
		if(verbose)
		{
			int k;

			Room *r = room->next;
			k = OwnerTable[i];

			while(k > 0)
			{
				r=r->next;
				k -= 1;
			}

			printf("\t%3i) %-20s => %s, Links to %i (%s)\n", i, NameTable[i], r->name, LinkTable[i], NounNames[(int)LinkTable[i]]->name);
		}
		OutByte(OwnerTable[i]);
	}

	/*
	 * Output the second owner table
	 */
	Owner2 = OutAddress();
	for (i = 0; i < CurrentItem; i++)
		OutByte(OwnerTable[i]);
	Link = OutAddress();

	/*
	 * Output item to noun link table
	 */
	for (i = 0; i < CurrentItem; i++)
		OutByte(LinkTable[i]);

	/*
	 * Output item description table
	 */
	Name = PutDescTable(NameTable, CurrentItem);
	SetHere(OutAddress());
	Org(OBJS);
	OutByte(CurrentItem-1);
	Org(OBJTABLE);
	OutWord(Owner1);
	OutWord(Owner2);
	OutWord(Link);
	OutWord(Name);
	Org(NOTREA);
	OutByte(NoTreasures);
}
