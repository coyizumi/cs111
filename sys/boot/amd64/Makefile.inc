# Common defines for all of /sys/boot/amd64/
#
# $FreeBSD: releng/10.2/sys/boot/amd64/Makefile.inc 281321 2015-04-09 19:36:06Z jhb $

BINDIR?=	/boot

# See conf/kern.mk for the correct set of these
CFLAGS+=	-ffreestanding -mno-red-zone
CFLAGS+=	-mno-mmx -mno-sse -mno-aes -mno-avx -msoft-float
LDFLAGS+=	-nostdlib

.include "../Makefile.inc"
