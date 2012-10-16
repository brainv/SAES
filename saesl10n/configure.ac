dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(saesl10n, 1.4.6)
AM_INIT_AUTOMAKE([ filename-length-max=256 tar-ustar ])

AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_INSTALL

eval "prefix=$prefix"

if test "$prefix" = "NONE" ; then
    eval "prefix=/usr/local"
fi

eval "exec_prefix=$prefix"
eval "datadir=$datadir"
eval "localedir=$localedir"

LOCALEDIR=`eval echo $localedir`

AC_SUBST(LOCALEDIR, [$LOCALEDIR] )

AC_CHECK_PROGS([MSGFMT], [msgfmt])

AM_CONDITIONAL([HAVE_MSGFMT],[test -n "$MSGFMT"])
AM_COND_IF([HAVE_MSGFMT],
	[AC_MSG_RESULT([Msgfmt found - translate])],
	[AC_MSG_ERROR([Msgfmt not found - install gettext package and try again])])

AC_CONFIG_FILES([
Makefile
src/Makefile
src/election/Makefile
src/saes/Makefile
src/saescommon/Makefile
src/saesfunctionality/Makefile
src/saesguibase/Makefile
src/saeshardware/Makefile
src/smartmatic/Makefile
src/smartmaticgui/Makefile
src/election/po/Makefile
src/saes/po/Makefile
src/saescommon/po/Makefile
src/saesfunctionality/po/Makefile
src/saesguibase/po/Makefile
src/saeshardware/po/Makefile
src/smartmatic/po/Makefile
src/smartmaticgui/po/Makefile
])

AC_OUTPUT

