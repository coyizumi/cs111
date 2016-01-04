/*-
 * Copyright (c) 2009 Yohanes Nugroho <yohanes@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: releng/10.2/sys/arm/cavium/cns11xx/econa_reg.h 201468 2010-01-04 03:35:45Z rpaulo $
 */
#ifndef	_ARM_ECONA_REG_H
#define	_ARM_ECONA_REG_H

#define	ECONA_SRAM_SIZE	0x10000000
#define	ECONA_DRAM_BASE	0x00000000 /* DRAM (via DDR Control Module) */

#define	ECONA_SDRAM_BASE	0x40000000
#define	ECONA_SDRAM_SIZE	0x1000000


#define	ECONA_IO_BASE		0x70000000
#define	ECONA_IO_SIZE		0x0E000000
#define	ECONA_PIC_BASE		0x0D000000
#define	ECONA_PIC_SIZE		0x01000000

#define	ECONA_UART_BASE	0x08000000
#define	ECONA_UART_SIZE	0x01000000
#define	ECONA_IRQ_UART		0xA

#define	ECONA_TIMER_BASE	0x09000000
#define	ECONA_TIMER_SIZE	0x01000000
#define	ECONA_IRQ_TIMER_1	0
#define	ECONA_IRQ_TIMER_2	1
#define	ECONA_IRQ_OHCI		23
#define	ECONA_IRQ_EHCI		24

#define	ECONA_NET_BASE		0x00000000

#define	ECONA_SYSTEM_BASE	0x07000000
#define	ECONA_SYSTEM_SIZE	0x01000000

#define	ECONA_NET_SIZE		0x01000000

#define	ECONA_CFI_PBASE	0x10000000
#define	ECONA_CFI_VBASE	0xD0000000
#define	ECONA_CFI_SIZE		0x10000000

#define	ECONA_IRQ_STATUS	18
#define	ECONA_IRQ_TSTC		19
#define	ECONA_IRQ_FSRC		20
#define	ECONA_IRQ_TSQE		21
#define	ECONA_IRQ_FSQF		22

#define	ECONA_IRQ_SYSTEM	0

#define	ECONA_EHCI_PBASE	0xC8000000
#define	ECONA_EHCI_VBASE	0xF8000000
#define	ECONA_EHCI_SIZE	0x8000000

#define	ECONA_OHCI_PBASE	0xC0000000
#define	ECONA_OHCI_VBASE	0xF0000000
#define	ECONA_OHCI_SIZE	0x8000000

#define	ECONA_USB_SIZE		0xf000000

/*Interrupt controller*/
#define	INTC_LEVEL_TRIGGER	0
#define	INTC_EDGE_TRIGGER	1
#define	INTC_ACTIVE_HIGH	0
#define	INTC_ACTIVE_LOW	1
/*
 * define rising/falling edge for edge trigger mode
 */
#define	INTC_RISING_EDGE	0
#define	INTC_FALLING_EDGE	1

#define	INTC_INTERRUPT_SOURCE_REG_OFFSET		0x00
#define	INTC_INTERRUPT_MASK_REG_OFFSET			0x04
#define	INTC_INTERRUPT_CLEAR_EDGE_TRIGGER_REG_OFFSET	0x08
#define	INTC_INTERRUPT_TRIGGER_MODE_REG_OFFSET		0x0C
#define	INTC_INTERRUPT_TRIGGER_LEVEL_REG_OFFSET	0x10
#define	INTC_INTERRUPT_STATUS_REG_OFFSET		0x14
#define	INTC_FIQ_MODE_SELECT_REG_OFFSET		0x18
#define	INTC_SOFTWARE_INTERRUPT_REG_OFFSET		0x1C


/*
 * define rising/falling edge for edge trigger mode
 */
#define	INTC_RISING_EDGE	0
#define	INTC_FALLING_EDGE	1


#define	TIMER_TM1_COUNTER_REG		0x00
#define	TIMER_TM1_LOAD_REG		0x04
#define	TIMER_TM1_MATCH1_REG		0x08
#define	TIMER_TM1_MATCH2_REG		0x0C

#define	TIMER_TM2_COUNTER_REG		0x10
#define	TIMER_TM2_LOAD_REG		0x14
#define	TIMER_TM2_MATCH1_REG		0x18
#define	TIMER_TM2_MATCH2_REG		0x1C

#define	TIMER_TM_CR_REG		0x30
#define	TIMER_TM_INTR_STATUS_REG	0x34
#define	TIMER_TM_INTR_MASK_REG		0x38

#define	TIMER_TM_REVISION_REG		0x3C


#define	INTC_TIMER1_BIT_INDEX		0

#define	TIMER1_UP_DOWN_COUNT		(1<<9)
#define	TIMER2_UP_DOWN_COUNT		(1<<10)

#define	TIMER1_MATCH1_INTR		(1<<0)
#define	TIMER1_MATCH2_INTR		(1<<1)
#define	TIMER1_OVERFLOW_INTR		(1<<2)


#define	TIMER2_MATCH1_INTR		(1<<3)
#define	TIMER2_MATCH2_INTR		(1<<4)
#define	TIMER2_OVERFLOW_INTR		(1<<5)


#define	TIMER_CLOCK_SOURCE_PCLK	0
#define	TIMER_CLOCK_SOURCE_EXT_CLK	1

/*
 * define interrupt trigger mode
 */
#define	INTC_LEVEL_TRIGGER		0
#define	INTC_EDGE_TRIGGER		1


#define	INTC_TRIGGER_UNKNOWN -1

#define	TIMER1_OVERFLOW_INTERRUPT	(1<<2)
#define	TIMER2_OVERFLOW_INTERRUPT	(1<<5)
#define	TIMER_INTERRUPT_STATUS_REG	0x34


#define	TIMER1_ENABLE			(1<<0)
#define	TIMER1_CLOCK_SOURCE		(1<<1)
#define	TIMER1_OVERFLOW_ENABLE		(1<<2)


#define	TIMER2_ENABLE			(1<<3)
#define	TIMER2_CLOCK_SOURCE		(1<<4)
#define	TIMER2_OVERFLOW_ENABLE		(1<<5)


#define	TIMER_1			1

#define	EC_UART_CLOCK			14769200
#define	EC_UART_REGSHIFT		2

#define	SYSTEM_CLOCK			0x14
#define	RESET_CONTROL			0x4
#define	GLOBAL_RESET			0x1
#define	NET_INTERFACE_RESET		(0x1 << 4)

#endif
