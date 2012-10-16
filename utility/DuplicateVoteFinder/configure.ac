dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(duplicate-vote, 1.4.0)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC


PKG_CHECK_MODULES(DUPLICATE_VOTE, [libsmartmatic libsmartmaticgui libsmartmaticlog libsaes libsaeshardware libsaescommon glibmm-2.4 gtkmm-2.4 >= 2.12])

eval "prefix=$prefix"

if test "$prefix" = "NONE" ; then
    eval "prefix=/usr/local"
fi


eval "exec_prefix=$prefix"
eval "datadir=$datadir"
eval "localedir=$localedir"

DATADIR=`eval echo $datadir`
LOCALEDIR=`eval echo $localedir`

AC_SUBST(LOGDATADIR, "$DATADIR/AC_PACKAGE_NAME/log")
AC_DEFINE_UNQUOTED(LOGDATADIR, "$LOGDATADIR" , [ The log data dir ])

AC_SUBST(DATADIR)
AC_DEFINE_UNQUOTED(DATADIR, "$DATADIR" , [ The data dir ])

AC_OUTPUT([
Makefile
src/Makefile
log/Makefile
])
