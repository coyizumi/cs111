# $FreeBSD: releng/10.2/tests/Makefile 283846 2015-05-31 22:39:48Z ngie $

.include <bsd.own.mk>

SUBDIR+= etc
SUBDIR+= sys

TESTSDIR= ${TESTSBASE}
KYUAFILE= yes

afterinstall: install-tests-local
install-tests-local: .PHONY
	${INSTALL_SYMLINK} ../local/tests ${DESTDIR}${TESTSDIR}/local

.include <bsd.test.mk>
