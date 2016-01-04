#
# $FreeBSD: releng/10.2/tools/regression/acct/Makefile 276486 2014-12-31 23:25:37Z ngie $
#
# "make" will compile the acct test programs
#

PROG=	pack
SRCS=	pack.c
MAN=
CFLAGS+= -I${.OBJDIR}

pack.o:	convert.c

CLEANFILES+= convert.c
convert.c: ../../../sys/kern/kern_acct.c
	sed -n -e 's/log(/syslog(/g' \
	       -e '/FLOAT_CONVERSION_START/,/FLOAT_CONVERSION_END/p' $? >$@

regress: pack regress.t
	${.CURDIR}/regress.t

.include <bsd.prog.mk>
