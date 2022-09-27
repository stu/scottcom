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
 * $Id: symbol.c,v 1.1 1996/01/12 08:00:50 bjorn Exp $
 *
 */

#include "scottcom.h"

Symbol *lookup(Symbol* root, char* s)   /* find s in symbol table */
{
        Symbol *sp;
        int res;

        sp = root;
        while (sp != (Symbol *) 0)
                if ((res = strcmp(s, sp->name)) == 0)
                        return sp;
                else if (res < 0)
                        sp = sp->left;
                else
                        sp = sp->right;

        return 0;       /* 0 ==> not found */
}

static Symbol *doinstall(Symbol *p, Symbol *new)        /* install new at or below p */
{
        int cond;

        if (p == NULL)                  /* found place in tree, done */
                return new;
        else if ((cond = strcmp(new->name, p->name)) == 0) {
                error("identifier already defined");
                return p;
        } else if (cond < 0)            /* lower goes into left subtree */
                p->left = doinstall(p->left, new);
        else                            /* greater into right subtree */
                p->right = doinstall(p->right, new);
        return p;
}

Symbol *install(Symbol** tptr, char* s, int t)  /* install s in symbol table */
{
        Symbol  *sp;

        sp = (Symbol *) emalloc(sizeof(Symbol));
        sp->name = strsave(s);
        sp->type = t;
        sp->left = NULL;
        sp->right = NULL;
        *tptr = doinstall(*tptr, sp);
        return sp;
}

char *emalloc(n)        /* check return from malloc */
unsigned n;
{
        char *p;

        p = malloc(n);
        if (p == 0)
                execerror("out of memory");
        return p;
}

char *erealloc(p, n)    /* check return from realloc */
char *p;
unsigned n;
{
        p = realloc(p, n);
        if (p == 0)
                execerror("out of memory");
        return p;
}

char *strsave(s)        /* string s somewhere */
char *s;
{
        char *p;

        p = emalloc(strlen(s)+1);
        strcpy(p, s);
        return p;
}
