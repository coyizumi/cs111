# $FreeBSD: releng/10.2/usr.sbin/bsdinstall/distextract/Makefile 283859 2015-06-01 01:06:33Z dteske $

BINDIR= /usr/libexec/bsdinstall
PROG=	distextract
DPADD=	${LIBARCHIVE} ${LIBDPV} ${LIBFIGPAR} ${LIBDIALOG} ${LIBM}
LDADD=	-larchive -ldpv -lfigpar -ldialog -lm

WARNS?=	6
MAN=

.include <bsd.own.mk>

.if ${MK_NCURSESW} == "no"
DPADD+=	${LIBNCURSES}
LDADD+=	-lncurses
.else
DPADD+=	${LIBNCURSESW}
LDADD+=	-lncursesw
.endif

.include <bsd.prog.mk>
