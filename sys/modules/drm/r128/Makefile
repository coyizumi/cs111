# $FreeBSD: releng/10.2/sys/modules/drm/r128/Makefile 242203 2012-10-28 02:15:35Z nwhitehorn $

.PATH:	${.CURDIR}/../../../dev/drm
KMOD	= r128
SRCS	= r128_cce.c r128_drv.c r128_irq.c r128_state.c
SRCS	+=device_if.h bus_if.h pci_if.h opt_drm.h

.include <bsd.kmod.mk>

CWARNFLAGS.r128_cce.c=		-Wno-unused ${NO_WCONSTANT_CONVERSION}
CWARNFLAGS.r128_state.c=	-Wno-unused
CWARNFLAGS+=			${CWARNFLAGS.${.IMPSRC:T}}
