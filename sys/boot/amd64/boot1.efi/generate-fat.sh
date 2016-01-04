#!/bin/sh

# This script generates the dummy FAT filesystem used for the EFI boot
# blocks. It uses newfs_msdos to generate a template filesystem with the
# relevant interesting files. These are then found by grep, and the offsets
# written to a Makefile snippet.
#
# Because it requires root, and because it is overkill, we do not
# do this as part of the normal build. If makefs(8) grows workable FAT
# support, this should be revisited.

# $FreeBSD: releng/10.2/sys/boot/amd64/boot1.efi/generate-fat.sh 271136 2014-09-04 21:05:04Z emaste $

FAT_SIZE=1600 			#Size in 512-byte blocks of the produced image

BOOT1_SIZE=64k

# Generate 800K FAT image
OUTPUT_FILE=fat.tmpl

dd if=/dev/zero of=$OUTPUT_FILE bs=512 count=$FAT_SIZE
DEVICE=`mdconfig -a -f $OUTPUT_FILE`
newfs_msdos -F 12 $DEVICE
mkdir stub
mount -t msdosfs /dev/$DEVICE stub

# Create and bless a directory for the boot loader
mkdir -p stub/efi/boot

# Make a dummy file for boot1
echo 'Boot1 START' | dd of=stub/efi/boot/BOOTx64.efi cbs=$BOOT1_SIZE count=1 conv=block

umount stub
mdconfig -d -u $DEVICE
rmdir stub

# Locate the offsets of the two fake files
BOOT1_OFFSET=$(hd $OUTPUT_FILE | grep 'Boot1 START' | cut -f 1 -d ' ')

# Convert to numbers of blocks
BOOT1_OFFSET=$(echo 0x$BOOT1_OFFSET | awk '{printf("%x\n",$1/512);}')

echo '# This file autogenerated by generate-fat.sh - DO NOT EDIT' > Makefile.fat
echo '# $FreeBSD: releng/10.2/sys/boot/amd64/boot1.efi/generate-fat.sh 271136 2014-09-04 21:05:04Z emaste $' >> Makefile.fat
echo "BOOT1_OFFSET=0x$BOOT1_OFFSET" >> Makefile.fat

bzip2 $OUTPUT_FILE
echo 'FAT template boot filesystem created by generate-fat.sh' > $OUTPUT_FILE.bz2.uu
echo 'DO NOT EDIT' >> $OUTPUT_FILE.bz2.uu
echo '$FreeBSD: releng/10.2/sys/boot/amd64/boot1.efi/generate-fat.sh 271136 2014-09-04 21:05:04Z emaste $' >> $OUTPUT_FILE.bz2.uu

uuencode $OUTPUT_FILE.bz2 $OUTPUT_FILE.bz2 >> $OUTPUT_FILE.bz2.uu
rm $OUTPUT_FILE.bz2

