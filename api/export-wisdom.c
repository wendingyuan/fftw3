/*
 * Copyright (c) 2002 Matteo Frigo
 * Copyright (c) 2002 Steven G. Johnson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "api.h"

typedef struct {
     printer super;
     void (*absorber)(char c, void *);
     void *data;
} P;

static void putchr_generic(printer * p_, char c)
{
     P *p = (P *) p_;
     (p->absorber)(c, p->data);
}

void X(export_wisdom)(void (*absorber)(char c, void *), void *data)
{
     P *p = (P *) X(mkprinter)(sizeof(P), putchr_generic, 0);
     planner *plnr = X(the_planner)();

     p->absorber = absorber;
     p->data = data;
     plnr->adt->exprt(plnr, (printer *) p);
     X(printer_destroy)((printer *) p);
}
