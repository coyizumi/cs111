#-
# Copyright (c) 2011 Google, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
# $FreeBSD: releng/10.2/libexec/atf/atf-check/Makefile 275988 2014-12-21 08:30:18Z ngie $

.include <bsd.init.mk>

ATF=		${.CURDIR:H:H:H}/contrib/atf
.PATH:		${ATF}/atf-sh

PROG_CXX=	atf-check
SRCS=		atf-check.cpp
MAN=		atf-check.1

CFLAGS+=	-I${ATF}
CFLAGS+=	-DATF_SHELL='"/bin/sh"'

LDFLAGS+=	-L${.OBJDIR}/../../../lib/atf/libatf-c++
LDFLAGS+=	-L${.OBJDIR}/../../../lib/atf/libatf-c
DPADD+=		${LIBATF_CXX} ${LIBATF_C}
LDADD+=		-latf-c++ -latf-c
USEPRIVATELIB=	atf-c++ atf-c

.if ${MK_TESTS} != "no"
SUBDIR+=	tests
.endif

.include <bsd.prog.mk>
