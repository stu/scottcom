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
 * $Id: code.c,v 1.2 1996/10/17 04:02:35 bjorn Exp $
 *
 */

#include "scottcom.h"
#include "adams.h"

static int OurAddress = DYNAMIC_AREA;

int Here(void)
{
	return OurAddress;
}

void SetHere(int n)
{
	OurAddress = n;
}

/*
 *----------------------------------------------------------------------
 *
 * RangeCheck --
 *
 *		This procedure makes sure that an integer is in the
 *		range min <= value < max.  If the integer is outside
 *		the range, error() will be called to produce an error
 *		message.
 *
 * Results:
 *		Returns value, adjusted to be within range.
 *
 *----------------------------------------------------------------------
 */
int
RangeCheck(
  char* name,					/* Name of value to be check */
								/* (used for the error message). */
  int value,					/* The value to check. */
  int min,						/* The minimum allowed value. */
  int max						/* The maximum (value must be < max). */
)
{
	if (min <= value && value < max)
		return value;
	sprintf(err_sbuf, "the value of '%s' must be at least %d and less than %d",
			name, min, max);
	error(err_sbuf);
	return value < min ? min : max-1;
}

/* set/clear flag */
void actflag(int op, int flag)
{
	if (flag == 0)
		action0(0xe3+op);
	else if (flag == 15)
		action0(0xdf+op);
	else
		action1(0xe1+op, flag);
}

void acttimer(int op, int n)
{
	if (n == 1)
		action0(0xf2+op);
	else
		action1(0xf6+op, n);
}

static int CurrentTimer = 0;

int GetNextTimer(void)
{
	if(CurrentTimer > 15)
	{
		error("too many timers defined.");
		return -1;
	}

	return CurrentTimer++;

}

static int CurrentRoomReg = 0;
int GetNextRoomReg(void)
{
	if(CurrentRoomReg > 15)
	{
		error("too many room registers defined.");
		return -1;
	}

	return CurrentRoomReg++;
}

/****************************
		Flags
*****************************/
static int CurrentFlag = 0;

int GetNextFlag(void)	/* get next available flag */
{
	if (CurrentFlag == 15)
		CurrentFlag = 17;
	if (CurrentFlag >= 32) {
		error("too many flags defined");
		return -1;
	}
	return CurrentFlag++;
}
