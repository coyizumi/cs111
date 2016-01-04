/*-
 * Copyright (c) 2006 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/10.2/sys/boot/amd64/efi/conf.c 281323 2015-04-09 19:51:55Z jhb $");

#include <stand.h>
#include <bootstrap.h>
#include <efi.h>
#include <efilib.h>

struct devsw *devsw[] = {
	&efipart_dev,
	&efinet_dev,
	NULL
};

struct fs_ops *file_system[] = {
	&dosfs_fsops,
	&ufs_fsops,
	&cd9660_fsops,
	&nfs_fsops,
	&gzipfs_fsops,
	&bzipfs_fsops,
	NULL
};

struct netif_driver *netif_drivers[] = {
	&efinetif,
	NULL
};

extern struct file_format amd64_elf;
extern struct file_format amd64_elf_obj;

struct file_format *file_formats[] = {
	&amd64_elf,
	&amd64_elf_obj,
	NULL
};

extern struct console efi_console;
extern struct console comconsole;
extern struct console nullconsole;

struct console *consoles[] = {
	&efi_console,
	&comconsole,
	&nullconsole,
	NULL
};
