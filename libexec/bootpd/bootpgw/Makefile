# Makefile
# $FreeBSD: releng/10.2/libexec/bootpd/bootpgw/Makefile 276486 2014-12-31 23:25:37Z ngie $

PROG=	bootpgw
MAN=
SRCS=	bootpgw.c getif.c hwaddr.c report.c rtmsg.c

SRCDIR=	${.CURDIR}/..
CFLAGS+=-I${SRCDIR}
.PATH:	${SRCDIR}

.include <bsd.prog.mk>
