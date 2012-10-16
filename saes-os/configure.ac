dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(saes-os, 1.4.6)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AC_ISC_POSIX

eval "prefix=$prefix"

if test "$prefix" = "NONE" ; then
    eval "prefix=/usr/local"
fi

eval "exec_prefix=$prefix"
eval "datadir=$datadir"
eval "bindir=$bindir"
eval "sbindir=$sbindir"
eval "sysconfdir=$sysconfdir"

BINDIR=`eval echo $bindir`
SBINDIR=`eval echo $sbindir`
SYSCONFDIR=`eval echo $sysconfdir`

AC_SUBST(BINDIR, [$BINDIR])
AC_SUBST(SBINDIR, [$SBINDIR])
AC_SUBST(UDEVDIR, [/lib/udev/rules.d])
AC_SUBST(CONFDIR, [$SYSCONFDIR/AC_PACKAGE_NAME])
AC_SUBST(APPCONF, [$CONFDIR/AC_PACKAGE_NAME.conf])

AC_CONFIG_FILES(
Makefile
etc/Makefile
etc/saes-os.conf
udev/Makefile
scripts/Makefile
scripts/smtt-dsort
scripts/smtt-movefile
scripts/smtt-printblank
scripts/smtt-smartcard
scripts/smtt-barcode-event
scripts/smtt-event-device
scripts/smtt-event-script
udev/70-saes-os-bcr.rules
udev/70-saes-os-storage.rules
)

AC_OUTPUT()

chmod +x scripts/smtt-dsort
chmod +x scripts/smtt-movefile
chmod +x scripts/smtt-printblank
chmod +x scripts/smtt-smartcard
chmod +x scripts/smtt-barcode-event
chmod +x scripts/smtt-event-device
chmod +x scripts/smtt-event-script

