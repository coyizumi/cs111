/*-
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <beat@chruetertee.ch> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.          Beat Gätzi
 * ----------------------------------------------------------------------------
 *
 * $FreeBSD: releng/10.2/usr.sbin/pkg_install/updating/pathnames.h 228976 2011-12-30 00:59:08Z uqs $
 *
 */

/* Where the updating file lives by default */
#define DEF_UPDATING "/usr/ports/UPDATING"
/* macro to define location of the UPDATING file */
#define UPDATING (getenv(PORTSDIR) ? strcat(getenv(PORTSDIR), \
        "/UPDATING") : DEF_UPDATING)
