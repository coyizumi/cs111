# $FreeBSD: releng/10.2/tools/regression/lib/libc/stdio/Makefile 277446 2015-01-20 21:59:48Z ngie $

TESTS=	test-fopen \
	test-getdelim \
	test-mkostemp \
	test-open_memstream \
	test-open_wmemstream \
	test-perror \
	test-print-positional \
	test-printbasic \
	test-printfloat \
	test-scanfloat 

CFLAGS+= -lm

.PHONY: tests
tests: ${TESTS}
	for p in ${TESTS}; do ${.OBJDIR}/$$p; done

.PHONY: clean
clean:
	-rm -f ${TESTS}
