# Makefile for mrsas driver
# $FreeBSD: releng/10.2/sys/modules/mrsas/Makefile 275976 2014-12-21 02:35:22Z smh $

KMOD=mrsas
.PATH: ${.CURDIR}/../../dev/${KMOD}

.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "amd64"
SUBDIR+= mrsas_linux
.endif

SRCS=mrsas.c mrsas_cam.c mrsas_ioctl.c mrsas_fp.c
SRCS+=  device_if.h bus_if.h pci_if.h opt_cam.h opt_scsi.h

#CFLAGS+= -MRSAS_DEBUG
.include <bsd.kmod.mk>
CFLAGS+= -fgnu89-inline

TARGET_ARCH = ${MACHINE_ARCH}
.if ${TARGET_ARCH} == "amd64"
CFLAGS+= -DCOMPAT_FREEBSD32 -D_STANDALONE
.endif

clean_cscope:
	rm -f cscope*

cscope:	clean_cscope
	/usr/local/bin/cscope -b *.[ch]

cleanall:	clean clean_cscope
	rm -f '@' machine
