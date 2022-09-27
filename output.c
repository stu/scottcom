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
 * $Id: output.c,v 1.1 1996/10/17 04:06:57 bjorn Exp $
 *
 */

/*
 * Note: This file is TI-99 specific.  It should probably be part of
 * ti99.c.
 */

#include <stdio.h>
#include <ctype.h>

#include "scottcom.h"

//#define NO      0
//#define YES     1
static  FILE    *out;

extern unsigned char ti99_font[];

void initprint(char* name)      /* initialize for printout */
{
    int i;
    char* np;                   /* Temporary pointer into name of file. */

    if ((out = fopen(name, "wb")) == NULL)
        execerror("can't open output file");

	/* SGEO : Fix, scan backward for last / */
	np = strchr(name, 0x0);
	np -= 1;
	
	while(np > name && (*np!='/' || *np=='\\'))
		np -= 1;
	
	if(*np=='/' || *np=='\\')
		np++;
	else
		np = name;
	
    /* copy name up to extension.. */
    for (i = 0; *np && i < 10 && *np!='.'; np++, i++) {
        putc(toupper(*np), out);
    }
    
    /* pad name */
    for (; i < 10; i++) {
        putc(' ', out);
    }
    
    putc(0, out); putc(0, out);
    putc(0x09, out); putc(0, out);
    i += 4;
    for (; i < 128; i++) {
        putc(0, out);
    }
    for ( ; i < 128+40*24; i++) {
        putc(' ', out);
    }
    for ( ; i < 128+1024; i++) {
        putc(0, out);
    }
    fwrite(ti99_font, 1, 0x400, out);
    i += 0x400;
    for ( ; i < 0x8A0; i++) {
        putc(0, out);
    }
    fseek(out, 0L, SEEK_SET);
}

/*
sgeo: v9t9 fdr record...

fdrrec	struc
	filenam	db	10 dup (32)
	res10		dw	0
	flags		db	0
	recspersec 	db	0
	secsused	dw	0	; TI-order!  
	eof			db	0
	reclen		db	0
	fixrecs		dw	0	; intel-order  (same as VARSECS)
	res20		db	8 dup (0)
	dcpb		db	100 dup (0)
	
	
		
	0:	filenem,			10
	A:  reserved			2
	C:	flags				1
	D:	recs per sector		1
	E:	secs used			2
   10:	eof					1
   12:	reclen				1
   13:	fixed records		1

*/

void stopprint()
{
    long length;                /* Length of file, excluding header. */
    int sectors;                /* Length in sectors (excluding headers). */
    int last;                   /* Bytes used in last sector. */

    fseek(out, 0L, SEEK_END);
    
    /* file size less header size */
    length = ftell(out)  - 128;
    
    /* round length up to 256 */
    length = ((length+255)/256)*256;
    last = length - (ftell(out)-128);
    
    for( ; last>0; last--)
    	putc(0, out);
 
    sectors = length/256;
    last = length-(long)sectors*256;
    
    
    fseek(out, 0x0E, SEEK_SET);
    putc(sectors/256, out);		/* hi */
    putc(sectors%256, out);		/* lo */
    putc(last, out);			/* remainder */
    fclose(out);
}

void Org(int n)         /* set new origin */
{
    fseek(out, (long)(n-0x380), SEEK_SET);
}

int OutAddress()
{
    return ftell(out) + 0x380;
}

void OutString(char *s)         /* output string */
{
    char *old;
    int count;

    if (strlen(s) == 0)
        return;
    while (*s) {
        old = s;
        count = 0;

        while (*s != ' ' && *s != '\0')
            s++, count++;

        putc(count, out);
        fwrite(old, 1, count, out);

        if (*s == ' ')
            s++;
    }
}

void Transform(char* s)         /* remove all un-necessary spaces */
{
    char *t;
    int last = 'x';

    t = s;
    while (*s == ' ')
        s++;
    while (*s != '\0') {
        if (last != ' ' || *s != ' ') {
            last = *t = *s;
            t++;
        }
        s++;
    }
    if (last == ' ')
        t--;
    *t = '\0';
}

void OutByte(int n)     /* output a byte to the file */
{
    putc(n, out);
}

void OutWord(int n)             /* output two bytes to a file */
{
    putc(n >> 8, out);
    putc(n & 0xff, out);
}

void outbuf(byte* s, unsigned length)
{
    fwrite(s, 1, length, out);
}
