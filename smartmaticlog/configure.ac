dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(libsmartmaticlog, 1.4.6)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([no])])
LT_INIT([ disable-static ])

AM_INIT_AUTOMAKE([ filename-length-max=256 tar-ustar ])

LIBMAYOR=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $1}') 
LIBMINOR=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $2}')
LIBFIX=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $3}')
eval "((LIBVERSION=$LIBMAYOR + $LIBMINOR))"

AC_SUBST(LIBVERSION)
AC_SUBST(LIBMAYOR)
AC_SUBST(LIBMINOR)
AC_SUBST(LIBFIX)

AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AC_PROG_INSTALL
AC_HEADER_STDC
AM_PROG_LIBTOOL


PKG_CHECK_MODULES(modules, [liblog4cxx])
AC_SUBST(modules_CFLAGS)
AC_SUBST(modules_LIBS)

eval "prefix=$prefix"

if test "$prefix" = "NONE" ; then
    eval "prefix=/usr/local"
fi

eval "exec_prefix=$prefix"
eval "datadir=$datadir"
eval "localedir=$localedir"

DATADIR=`eval echo $datadir`
LOCALEDIR=`eval echo $localedir`

AC_SUBST(DATADIR)
AC_DEFINE_UNQUOTED(DATADIR, "$DATADIR" , [ The data dir ])

CXXFLAGS="-Wall -Werror ${CXXFLAGS}"

AC_ARG_ENABLE(add-release, AS_HELP_STRING([--disable-add-release],
	[build without release in library name (default=no) ]),[use_add_release=$enableval],
	[use_add_release=yes])

AM_CONDITIONAL([ADD_RELEASE],[test "$use_add_release" = "yes"])

dnl Doxygen config
AC_CHECK_PROGS([DOXYGEN], [doxygen])

AC_ARG_ENABLE(doxygen-doc,
	AS_HELP_STRING([--enable-doxygen-doc],
	[build doxygen doc (default=no) ]),
	[make_doxygen_doc=$enableval],
	[make_doxygen_doc=no])

AC_SUBST(DOXYGEN_LOG_FILE, ["doxygen.log"])

AM_CONDITIONAL([MAKE_DOXYGEN_DOC],[test -n "$DOXYGEN" && test "$make_doxygen_doc" = "yes"])
AM_COND_IF([MAKE_DOXYGEN_DOC],
	[AC_CONFIG_FILES([docs/Doxyfile])],
	[AC_MSG_WARN([Continuing without doxygen support])])

AC_CONFIG_FILES([
Makefile
src/libsmartmaticlog.pc
src/Makefile
docs/Makefile
])

AC_OUTPUT
