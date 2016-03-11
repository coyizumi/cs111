/*-
 * Copyright (c) 1992-2015 The FreeBSD Project.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#define SCCSSTR "@(#)FreeBSD 10.2-RELEASE #0 1524322(asgn4)-dirty: Tue Mar  8 21:35:56 PST 2016"
#define VERSTR "FreeBSD 10.2-RELEASE #0 1524322(asgn4)-dirty: Tue Mar  8 21:35:56 PST 2016\n    root@timmymakwan:/cmps111/cs111/include\n"
#define RELSTR "10.2-RELEASE"

char sccs[sizeof(SCCSSTR) > 128 ? sizeof(SCCSSTR) : 128] = SCCSSTR;
char version[sizeof(VERSTR) > 256 ? sizeof(VERSTR) : 256] = VERSTR;
char compiler_version[] = "FreeBSD clang version 3.4.1 (tags/RELEASE_34/dot1-final 208032) 20140512";
char ostype[] = "FreeBSD";
char osrelease[sizeof(RELSTR) > 32 ? sizeof(RELSTR) : 32] = RELSTR;
int osreldate = 1002000;
char kern_ident[] = "";