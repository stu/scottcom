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
 * $Id: scottcom.c,v 1.2 1996/10/17 04:01:57 bjorn Exp $
 *
 */
#include "scottcom.h"
#include <ctype.h>

char acknowledge[] = "***** Compiled by ScottCom, v " VERSION " *****";

char	*progname = "scottcom"; /* for error messages */
int		lineno = 1;
int		fatalerr = NO;
int		verbose = NO;
char	*infile, *outfile;
FILE	*finp;

int		try_index;
byte	*try_level[MAX_TRY_DEPTH+1];

char *err_sbuf;


Action** action;			/* Pointer to action blocks for each verb.
								 * Each pointer will point to the last block
								 * in the chain, and the last block will
								 * back to the first. */

/*
 * Function pointers for the output format.
 */
unsigned (*translate)(unsigned code);
void (*titlestr)(char*);
void (*begaction)(int, int);
void (*endaction)(void);
void (*begcatch)(void);
void (*endcatch)(void);
void (*action0)(unsigned);
void (*action1)(unsigned, unsigned);
void (*action2)(unsigned, unsigned, unsigned);
void (*dump)(void);

char *stripexten(char *name);
void work_filename(char *fn);

int main(int argc, char *argv[])
{
	err_sbuf = malloc(512);

	fprintf(stderr, "ScottCom, version "VERSION"\n");
	ti99_init();

	while (argc > 1 && argv[1][0] == '-')
	{
		switch (tolower(argv[1][1]))
		{
			case 'v':				/* -v: Verbose */
				verbose = YES;
				break;
		}

		argc--;
		argv++;
	}

	init();


	if (argc == 1)
	{
		execerror("source file name must be specified.\n"
				  "\n"
				  "Syntax : {-v} source_file\n\n"
				  "-v\tVerbose.\n"
				  );
	}

	work_filename(argv[1]);

	printf("Source File = %s\n", infile);
	printf("Output File = %s\n", outfile);

	if ((finp = fopen(infile, "r")) == NULL)
		execerror("cannot open source file");

	initprint(outfile);

	yyparse();

	fclose(finp);

	stopprint();

	if (fatalerr) {
		remove(outfile);
		exit(1);
	}
	exit(0);
}

void work_filename(char *fn)
{
	char *f1, *f2;
	int ff1;

	ff1 = 0;

	f1 = getexten(fn);
	if(f1 == NULL)
	{
		f1 = malloc(strlen(fn) + strlen(".apl") + 2);
		strcpy(f1, fn);
		strcat(f1, ".apl");
		ff1 = 1;
	}
	else
	{
		f1 = fn;
	}

	f2 = newexten(f1, ".fiad");

	infile = strdup(f1);
	outfile = strdup(f2);

	if(ff1==1)
		free(f1);

	free(f2);
}

void execerror(char *s)
{
	fprintf(stderr, "%s: %s\n", progname, s);
	exit(1);
}

/*
 * Return pointer to extension or null
 */
char *getexten(char *name)
{
	char *p;

	p = strchr(name, '.');

	if(p!=NULL)
	{
		char *z;

		z = p;
		while(p!=NULL)
		{
			z = p;
			p = strchr(z+1, '.');
		}

		return z;
	}

	return NULL;
}


char *newexten(char *name, char *ext) /* return pointer to name with new extension */
{
	char *p;
	char *xnew;

	xnew = malloc(strlen(name) + strlen(ext) + 2);
	strcpy(xnew, name);

	p = strchr(xnew, 0x0);
	p-=1;

	while(p > xnew && *p!='.')
		p-=1;

	if(*p=='.')
	{
		strcpy(p, ext);
	}
	else
	{
		strcat(xnew, ext);
	}

	return xnew;
}

void _Assert(const char* file, unsigned line)
{
	fflush(stdout);
	fprintf(stderr, "\nAssertion failed: %s, line %u\n", file, line);
	fflush(stderr);
	abort();
}

