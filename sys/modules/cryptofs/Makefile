# $FreeBSD: releng/10.2/sys/modules/cryptofs/Makefile 89260 2002-01-11 15:49:02Z ru $

.PATH: ${.CURDIR}/../../fs/cryptofs

KMOD=	cryptofs
SRCS=	vnode_if.h rijndael.h\
	crypto_subr.c crypto_vfsops.c crypto_vnops.c rijndael.c

.include <bsd.kmod.mk>
