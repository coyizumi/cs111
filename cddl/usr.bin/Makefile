# $FreeBSD: releng/10.2/cddl/usr.bin/Makefile 283853 2015-05-31 23:00:35Z ngie $

.include <bsd.own.mk>

SUBDIR= \
	ctfconvert \
	ctfdump \
	ctfmerge \
	sgsmsg \
	${_tests} \
	${_zinject} \
	${_zlook} \
	${_zstreamdump} \
	${_ztest}

.if ${MK_TESTS} != "no"
_tests=	tests
.endif

.if ${MK_ZFS} != "no"
_zinject= zinject
#_zlook= zlook
.if ${MK_LIBTHR} != "no"
_ztest=	ztest
_zstreamdump = zstreamdump
.endif
.endif

SUBDIR_PARALLEL=

.include <bsd.subdir.mk>
