# $FreeBSD: releng/10.2/tools/regression/p1003_1b/Makefile 276486 2014-12-31 23:25:37Z ngie $

PROG=p1003_1b

SRCS=\
	fifo.c \
	main.c \
	memlock.c \
	prutil.c \
	p26.c \
	sched.c \
	yield.c

MAN=

CFLAGS+=-DNO_MEMLOCK
.include <bsd.prog.mk>
