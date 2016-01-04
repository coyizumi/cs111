# $FreeBSD: releng/10.2/tests/sys/kern/Makefile 283021 2015-05-16 23:39:54Z ngie $

TESTSDIR=	${TESTSBASE}/sys/kern

ATF_TESTS_C+=	kern_descrip_test
ATF_TESTS_C+=	unix_seqpacket_test
TEST_METADATA.unix_seqpacket_test+=	timeout="15"

LDADD.unix_seqpacket_test+=		-lpthread

WARNS?=	5

TESTS_SUBDIRS+=	execve

.include <bsd.test.mk>
