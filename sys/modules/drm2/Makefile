# $FreeBSD: releng/10.2/sys/modules/drm2/Makefile 282217 2015-04-29 12:54:21Z dumbbell $

.include <bsd.own.mk>

SUBDIR_PARALLEL=

.if ${MACHINE_CPUARCH} == "amd64"
_i915kms=	i915kms
_radeonkms=	radeonkms
. if ${MK_SOURCELESS_UCODE} != "no"
_radeonkmsfw=	radeonkmsfw
. endif
.endif

.if ${MACHINE_CPUARCH} == "i386"
. if ${MACHINE} != "pc98"
_i915kms=	i915kms
_radeonkms=	radeonkms
.  if ${MK_SOURCELESS_UCODE} != "no"
_radeonkmsfw=	radeonkmsfw
.  endif
. endif
.endif

.if ${MACHINE_CPUARCH} == "powerpc"
_radeonkms=	radeonkms
. if ${MK_SOURCELESS_UCODE} != "no"
_radeonkmsfw=	radeonkmsfw
. endif
.endif

SUBDIR = \
	drm2 \
	${_i915kms} \
	${_radeonkms} \
	${_radeonkmsfw}

.include <bsd.subdir.mk>
