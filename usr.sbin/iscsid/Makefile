# $FreeBSD: releng/10.2/usr.sbin/iscsid/Makefile 274866 2014-11-22 17:39:39Z trasz $

PROG=		iscsid
SRCS=		chap.c discovery.c iscsid.c keys.c log.c login.c pdu.c
CFLAGS+=	-I${.CURDIR}
CFLAGS+=	-I${.CURDIR}/../../sys/cam
CFLAGS+=	-I${.CURDIR}/../../sys/dev/iscsi
#CFLAGS+=	-DICL_KERNEL_PROXY
MAN=		iscsid.8

DPADD=		${LIBCRYPTO} ${LIBSSL} ${LIBUTIL}
LDADD=		-lcrypto -lssl -lutil

WARNS=		6

.include <bsd.prog.mk>
