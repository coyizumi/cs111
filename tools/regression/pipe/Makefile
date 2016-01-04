#
# $FreeBSD: releng/10.2/tools/regression/pipe/Makefile 276486 2014-12-31 23:25:37Z ngie $
#
# "make" then "make regress".
#
PROG=	bigpipetest
MAN=

regress:
	@if ./bigpipetest; then \
		echo "PASS"; \
	else \
		echo "FAIL"; \
	fi

.include <bsd.prog.mk>
