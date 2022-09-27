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
 * $Id: room.c,v 1.1 1996/01/12 08:01:21 bjorn Exp $
 *
 */

#include <ctype.h>
#include <string.h>
#include "scottcom.h"
#include "adams.h"

/*
 * This structure contains the information for one room.
 */


/*
 * The following is the prefix for room descriptions.  Used by MakeRoom().
 */
static const char desc_prefix[] = "I'm in a ";

Room* room;				 /* The root of the room list.	Points to */
								/* the last room in the list, which points */
								/* back to the first room. */
int NumRooms = 0;		 /* Number of rooms defined. */

/*----------------------------------------------------------------------
 *
 * SetExit --
 *
 *		This procedure declares an exit from the current room.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void
SetExit(
  int dir,						/* The direction of the exit (0-5). */
  Symbol* to					/* To where the exit leads. */
)
{
	ASSERT(dir < 6);
	ASSERT(to != 0);
	ASSERT(room != 0);			/* Assure that MakeRoom() has been called. */
	room->exit[dir] = to;
}

/*----------------------------------------------------------------------
 *
 * MakeRoom --
 *
 *		This procedure makes a new room.
 *
 * Results:
 *		Returns the number of the new room.
 *
 *----------------------------------------------------------------------
 */
int
MakeRoom(
  char* desc,				/* The room description. */
  char *name				/* room identifier */
)
{
	Room* newx;

	/*
	 * Create room zero (item storage) if not done.
	 */
	if (room == NULL)
	{
		room = (Room *) emalloc(sizeof(Room));
		memset((void *) room, 0, sizeof(Room));
		room->name = strsave("rm_ZERO");
		room->desc = strsave("*I shouldn't be here (room zero).");
		room->next = room;

		return NumRooms++;
	}

	if (strncmp(desc, desc_prefix, sizeof(desc_prefix)-1) == 0) {
		/*
		 * The description starts with "I'm in a ".	 Since the driver
		 * will automatically print that phrase, we must remove it
		 * from the description.
		 */
		desc += sizeof(desc_prefix)-1;
	} else {
		/*
		 * The description doesn't start in the standard way.
		 * To force the driver to omit "I'm in a ", we must add
		 * a '*' to the beginning of it.
		 */
		char* s = emalloc(strlen(desc)+2);
		*s = '*';
		strcpy(s+1, desc);
		free(desc);
		desc = s;
	}


	/*
	 * Insert the new room at the end of the linked list.
	 */
	newx = (Room *) emalloc(sizeof(Room));
	memset((void *) newx, 0, sizeof(Room));
	newx->name = strsave(name);
	newx->desc = desc;
	newx->def_line = lineno;
	newx->next = room->next;
	room->next = newx;
	room = newx;
	return NumRooms++;
}

/*----------------------------------------------------------------------
 *
 * ti99_DumpRooms --
 *
 *		This procedure dumps the room tables in the TI-99 format.
 *
 * Results:
 *		None.
 *
 *----------------------------------------------------------------------
 */
void ti99_DumpRooms(void)
{
	int i, j;
	int ExitTable;
	int NameTable;
	Room* r;
	char* RoomTable[256];

	if (verbose)
		printf("Number of rooms = %d\n", NumRooms);
	if (room == 0) {
		error("no rooms defined");
		return;
	}
	Org(ExitTable = Here());
	i = 0;

	r = room;
	do
	{
		r = r->next;
		RoomTable[i++] = r->desc;

		if(verbose)
		{
			printf("  Room : %3i) %s\n", i-1, r->name);
		}

		for (j = 0; j < 6; j++)
		{
			Symbol *s = r->exit[j];
			if (s == 0)
				OutByte(0);
			else if (s->value == -1)
			{
				sprintf(err_sbuf, "room '%s' referenced but not defined line (%i)", s->name, r->def_line);
				error(err_sbuf);
			}
			else
			{
				OutByte(s->value);

				if(verbose)
				{
					printf("\t\t");

					switch(j)
					{
						case 0: printf("north_"); break;
						case 1: printf("south_"); break;
						case 2: printf("east_"); break;
						case 3: printf("west_"); break;
						case 4: printf("up_"); break;
						case 5: printf("down_"); break;
					}
					printf("to (%i) %s\n", s->value, s->name);
				}
			}
		}
	} while (r != room);

	NameTable = PutDescTable(RoomTable, NumRooms);
	SetHere(OutAddress());
	Org(ROOMEXITS);
	OutWord(ExitTable);
	OutWord(NameTable);
	Org(REDROOM);
	OutByte(NumRooms-1);
}
