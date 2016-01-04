# $FreeBSD: releng/10.2/gnu/usr.bin/groff/Makefile 276307 2014-12-27 17:10:14Z ngie $

SUBDIR=		contrib doc font man src tmac

.for subdir in ${SUBDIR:Nsrc}
SUBDIR_DEPEND_${subdir}=	src
.endfor

.include <bsd.subdir.mk>
