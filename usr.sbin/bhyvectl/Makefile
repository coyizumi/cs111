#
# $FreeBSD: releng/10.2/usr.sbin/bhyvectl/Makefile 276486 2014-12-31 23:25:37Z ngie $
#

PROG=	bhyvectl
SRCS=	bhyvectl.c

MAN=

DPADD=	${LIBVMMAPI} ${LIBUTIL}
LDADD=	-lvmmapi -lutil

WARNS?=	3

CFLAGS+= -I${.CURDIR}/../../sys/amd64/vmm

.include <bsd.prog.mk>
