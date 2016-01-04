# $FreeBSD: releng/10.2/tests/sys/Makefile 282858 2015-05-13 12:09:01Z ngie $

.include <bsd.own.mk>

TESTSDIR= ${TESTSBASE}/sys

TESTS_SUBDIRS+=		aio
TESTS_SUBDIRS+=		fifo
TESTS_SUBDIRS+=		file
TESTS_SUBDIRS+=		kern
TESTS_SUBDIRS+=		kqueue
TESTS_SUBDIRS+=		mqueue
TESTS_SUBDIRS+=		netinet
TESTS_SUBDIRS+=		vm

# Items not integrated into kyua runs by default
SUBDIR+=		pjdfstest

.include <bsd.test.mk>
