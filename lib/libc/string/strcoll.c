/*-
 * Copyright (c) 1995 Alex Tatmanjants <alex@elvisti.kiev.ua>
 *		at Electronni Visti IA, Kiev, Ukraine.
 *			All rights reserved.
 *
 * Copyright (c) 2011 The FreeBSD Foundation
 * All rights reserved.
 * Portions of this software were developed by David Chisnall
 * under sponsorship from the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/10.2/lib/libc/string/strcoll.c 228202 2011-12-02 15:41:09Z eadler $");

#include <stdlib.h>
#include <string.h>
#include "collate.h"

#include <stdio.h>

int
strcoll_l(const char *s, const char *s2, locale_t locale)
{
	int len, len2, prim, prim2, sec, sec2, ret, ret2;
	const char *t, *t2;
	char *tt, *tt2;
	FIX_LOCALE(locale);
	struct xlocale_collate *table =
		(struct xlocale_collate*)locale->components[XLC_COLLATE];

	if (table->__collate_load_error)
		return strcmp(s, s2);

	len = len2 = 1;
	ret = ret2 = 0;
	if (table->__collate_substitute_nontrivial) {
		t = tt = __collate_substitute(table, s);
		t2 = tt2 = __collate_substitute(table, s2);
	} else {
		tt = tt2 = NULL;
		t = s;
		t2 = s2;
	}
	while(*t && *t2) {
		prim = prim2 = 0;
		while(*t && !prim) {
			__collate_lookup(table, t, &len, &prim, &sec);
			t += len;
		}
		while(*t2 && !prim2) {
			__collate_lookup(table, t2, &len2, &prim2, &sec2);
			t2 += len2;
		}
		if(!prim || !prim2)
			break;
		if(prim != prim2) {
			ret = prim - prim2;
			goto end;
		}
		if(!ret2)
			ret2 = sec - sec2;
	}
	if(!*t && *t2)
		ret = -(int)((u_char)*t2);
	else if(*t && !*t2)
		ret = (u_char)*t;
	else if(!*t && !*t2)
		ret = ret2;
  end:
	free(tt);
	free(tt2);

	return ret;
}

int
strcoll(const char *s, const char *s2)
{
	return strcoll_l(s, s2, __get_locale());
}

