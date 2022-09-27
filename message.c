/*
 *    ScottCom -- Compiles adventures into the Scott Adams format.
 *    Copyright (C) 1985-1996  Bjorn Gustavsson
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: message.c,v 1.2 1996/10/17 04:15:13 bjorn Exp $
 *
 */

#include "scottcom.h"
#include "adams.h"

#define MAX_MESSAGES    0xb6

static int CurrentMessage = 0;
static char *MsgString[MAX_MESSAGES];

int Message(char *s)
{
	int i;

    if (CurrentMessage == MAX_MESSAGES) {
        error("too many messages");
        return CurrentMessage;
    }

	/* SGEO : Checks for duplicate messages. */
	/*        Start from 1, as 0 is special message. */
	if(CurrentMessage>0)
	{
		for(i=0; i < CurrentMessage; i += 1)
		{
			if(strcmp(s, MsgString[i]) == 0)
			{
				if(verbose)
					printf("Folding [%s] into string %i\n", s, i);

				return i;
			}
		}
	}

	MsgString[CurrentMessage] = s;
	return CurrentMessage++;
}

void DumpMessages(void)
{
    int MsgTable;
	int i;

    if (verbose)
    {
        printf("Number of messages = %d\n", CurrentMessage);
        for(i=0; i<CurrentMessage; i+=1)
        {
        	printf("\t %03i - %s\n", i, MsgString[i]);
        }
    }

    //MsgString[0] = strsave("");
    Org(Here());
    MsgTable = PutDescTable(MsgString, CurrentMessage);
    SetHere(OutAddress());
    Org(MESSAGES);
    OutWord(MsgTable);
}
