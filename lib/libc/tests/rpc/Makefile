# $FreeBSD: releng/10.2/lib/libc/tests/rpc/Makefile 274075 2014-11-04 00:56:25Z ngie $

TESTSDIR=		${TESTSBASE}/lib/libc/rpc
SRCS.xdr_test=		${RPCSRC:.x=_xdr.c} t_xdr.c ${RPCSRC:.x=.h}

NETBSD_ATF_TESTS_C=	rpc_test
NETBSD_ATF_TESTS_C+=	xdr_test

RPCSRC=			h_testbits.x
RPCGEN=			RPCGEN_CPP=${CPP:Q} rpcgen -L -C

h_testbits.h: ${RPCSRC}
	${RPCGEN} -h -o ${.TARGET} ${.ALLSRC}

h_testbits_xdr.c: ${RPCSRC} h_testbits.h
	${RPCGEN} ${.ALLSRC:M*.x}

CLEANFILES+=	${RPCSRC:.x=.h} ${RPCSRC:.x=.c} h_testbits_xdr.c
CFLAGS+=	-I${.OBJDIR}
DPSRCS+=	h_testbits.h

LDADD+=		-lrpcsvc -lutil
DPADD+=		${LIBRPCSVC} ${LIBUTIL}

.include "../Makefile.netbsd-tests"

.include <bsd.test.mk>
