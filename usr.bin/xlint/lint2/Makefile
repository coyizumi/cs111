#	$NetBSD: Makefile,v 1.2 1995/07/03 21:24:39 cgd Exp $
# $FreeBSD: releng/10.2/usr.bin/xlint/lint2/Makefile 276486 2014-12-31 23:25:37Z ngie $

.PATH:	${.CURDIR}/../lint1

PROG=	lint2
SRCS=	main2.c hash.c read.c mem.c mem2.c chk.c msg.c emit.c emit2.c inittyp.c
MAN=
CFLAGS+=-I${.CURDIR}/../lint1
LINTFLAGS=-abehrz

BINDIR=	/usr/libexec

.include <bsd.prog.mk>
