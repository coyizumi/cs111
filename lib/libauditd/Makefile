#
# $FreeBSD: releng/10.2/lib/libauditd/Makefile 276486 2014-12-31 23:25:37Z ngie $
#

OPENBSMDIR=		${.CURDIR}/../../contrib/openbsm
LIBAUDITDDIR=		${OPENBSMDIR}/libauditd
LIBBSMDIR=		${OPENBSMDIR}/libbsm

LIB=		auditd

.PATH:		${LIBAUDITDDIR}

SRCS=	auditd_lib.c

#
# Must use BSM include files from within the contrib area, not the system.
#
CFLAGS+=	-I${OPENBSMDIR} -I${LIBBSMDIR}

WARNS?=		3

MAN=

.include <bsd.lib.mk>
