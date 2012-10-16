dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(votesim, 1.4.6)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC




dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=votesim
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])



AM_PROG_LIBTOOL

AC_CHECK_LIB([xml-security-c], [main],[], [AC_MSG_ERROR(["Error: library xml-security-c not found. Install libxml-security-c-dev package and try again"])]) 


PKG_CHECK_MODULES(VOTESIM, [gtkmm-2.4 >= 2.12 xerces-c libpcsclite libsmartmaticlog libsmartmatic libsmartmaticgui libsaescommon libsaeshardware libsaes libsaesfunctionality libsmartmaticlog liblog4cxx openssl])

eval "prefix=$prefix"

if test "$prefix" = "NONE" ; then
    eval "prefix=/usr/local"
fi


eval "exec_prefix=$prefix"
eval "datadir=$datadir"
eval "sysconfdir=$sysconfdir"
eval "localedir=$localedir"

DATADIR=`eval echo $datadir`
SYSCONFDIR=`eval echo $sysconfdir`
LOCALEDIR=`eval echo $localedir`

AC_SUBST(LOGDATADIR, "$DATADIR/AC_PACKAGE_NAME/log")
AC_DEFINE_UNQUOTED(LOGDATADIR, "$LOGDATADIR" , [ The log data dir ])

AC_SUBST(DATADIR)
AC_DEFINE_UNQUOTED(DATADIR, "$DATADIR" , [ The data dir ])


AC_OUTPUT([
Makefile
src/Makefile
log/Makefile
po/Makefile.in
])
