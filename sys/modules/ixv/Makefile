#$FreeBSD: releng/10.2/sys/modules/ixv/Makefile 283668 2015-05-28 20:56:11Z erj $

.PATH:  ${.CURDIR}/../../dev/ixgbe

KMOD    = if_ixv
SRCS    = device_if.h bus_if.h pci_if.h
SRCS	+= opt_inet.h opt_inet6.h
SRCS    += if_ixv.c ix_txrx.c
# Shared source
SRCS    += ixgbe_common.c ixgbe_api.c ixgbe_phy.c ixgbe_mbx.c ixgbe_vf.c
SRCS    += ixgbe_dcb.c ixgbe_dcb_82598.c ixgbe_dcb_82599.c
SRCS    += ixgbe_82598.c ixgbe_82599.c ixgbe_x540.c ixgbe_x550.c
CFLAGS+= -I${.CURDIR}/../../dev/ixgbe -DSMP

.include <bsd.kmod.mk>
