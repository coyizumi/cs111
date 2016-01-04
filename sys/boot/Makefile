# $FreeBSD: releng/10.2/sys/boot/Makefile 281843 2015-04-22 01:08:40Z dteske $

.include <bsd.own.mk>
.include <bsd.arch.inc.mk>

.if ${MK_FORTH} != "no"
# Build the add-in FORTH interpreter.
SUBDIR+=		ficl
SUBDIR+=		forth
.endif

# Pick the machine-dependent subdir based on the target architecture.
ADIR=			${MACHINE:S/powerpc64/powerpc/}
.if exists(${.CURDIR}/${ADIR}/.)
SUBDIR+=		${ADIR}
.endif
.if ${MACHINE} == "amd64"
SUBDIR+=		i386
.endif

.include <bsd.subdir.mk>
