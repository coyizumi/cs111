# $FreeBSD: releng/10.2/etc/periodic/daily/Makefile 277520 2015-01-22 02:24:09Z gjb $

.include <bsd.own.mk>

FILES=	100.clean-disks \
	110.clean-tmps \
	120.clean-preserve \
	200.backup-passwd \
	210.backup-aliases \
	330.news \
	400.status-disks \
	401.status-graid \
	406.status-gmirror \
	407.status-graid3 \
	408.status-gstripe \
	409.status-gconcat \
	420.status-network \
	450.status-security \
	510.status-world-kernel \
	999.local

# NB: keep these sorted by MK_* knobs

.if ${MK_ACCT} != "no"
FILES+=	310.accounting
.endif

.if ${MK_CALENDAR} != "no"
FILES+=	300.calendar
.endif

.if ${MK_MAIL} != "no"
FILES+=	130.clean-msgs
.endif

.if ${MK_NTP} != "no"
FILES+=	480.status-ntpd
.endif

.if ${MK_PKGTOOLS} != "no"
FILES+=	220.backup-pkgdb \
	490.status-pkg-changes
.endif

.if ${MK_RCMDS} != "no"
FILES+=	140.clean-rwho \
	430.status-rwho
.endif

.if ${MK_SENDMAIL} != "no"
FILES+=	150.clean-hoststat \
	440.status-mailq \
	460.status-mail-rejects \
	500.queuerun
.endif

.if ${MK_ZFS} != "no"
FILES+=	404.status-zfs \
	800.scrub-zfs
.endif

.include <bsd.prog.mk>
