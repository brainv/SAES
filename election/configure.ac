dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(election, 1.4.6)
AM_INIT_AUTOMAKE()
dnl m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])
BINMAYOR=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $1}') 
BINMINOR=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $2}')
BINFIX=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $3}')

AC_SUBST(BINMAYOR)
AC_SUBST(BINMINOR)
AC_SUBST(BINFIX)
dnl AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_INIT_AUTOMAKE([ filename-length-max=256 tar-ustar ])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC


dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
dnl GETTEXT_PACKAGE=election
AC_SUBST(GETTEXT_PACKAGE, [AC_PACKAGE_NAME])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

AC_CHECK_LIB([xml-security-c], [main],[], [AC_MSG_ERROR(["Error: library xml-security-c not found. Install libxml-security-c-dev package and try again"])]) 

AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])
dnl AM_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(ELECTION, [gtkmm-2.4 >= 2.12 xerces-c libsmartmaticlog libsmartmatic libsmartmaticgui libsaescommon libsaeshardware libsaes libsaesfunctionality libsaesguibase libsmartmaticlog liblog4cxx zlib libcrypto libssl])
AC_SUBST(ELECTION_CFLAGS)
AC_SUBST(ELECTION_LIBS)


dnl Check xsdcxx progrma
AC_CHECK_PROG(HAVE_XSDCXX, xsdcxx, true, false)
AC_CHECK_PROG(HAVE_XSD, xsd, true, false)

if test "x$HAVE_XSDCXX" = "xfalse" && test "x$HAVE_XSD" = "xfalse" ; then
   AC_MSG_ERROR([not found xsdcxx or xsd program])
fi

if test "x$HAVE_XSDCXX" = "xtrue" ; then
   AC_SUBST(XSDCXX, [xsdcxx])
elif test "x$HAVE_XSD" = "xtrue" ; then
   AC_SUBST(XSDCXX, [xsd])
fi


NAMESPACE_APP_CONFIGURATION="http://www.smartmatic.com/SAES/Configuration"

AC_DEFINE_UNQUOTED(NAMESPACE_APP_CONFIGURATION, "$NAMESPACE_APP_CONFIGURATION", [namespace app configuration])


XSDFLAGS="\
	--char-type char \
	--show-sloc \
	--generate-serialization \
	--generate-default-ctor \
	--generate-comparison \
	--generate-doxygen \
	--type-naming ucc \
	--function-naming java \
	--namespace-map $NAMESPACE_APP_CONFIGURATION=Smartmatic::SAES::Configuration "

AC_SUBST(XSDFLAGS)


eval "prefix=$prefix"

if test "$prefix" = "NONE" ; then
    eval "prefix=/usr/local"
fi


eval "exec_prefix=$prefix"
eval "bindir=$bindir"
eval "datadir=$datadir"
eval "sysconfdir=$sysconfdir"
eval "localedir=$localedir"

BINDIR=`eval echo $bindir`
DATADIR=`eval echo $datadir`
SYSCONFDIR=`eval echo $sysconfdir`
LOCALEDIR=`eval echo $localedir`

AC_SUBST(BINDIR)
AC_SUBST(DATADIR)
AC_DEFINE_UNQUOTED(DATADIR, "$DATADIR" , [ The data dir ])

AC_SUBST(AUTOSTARTDIR, [$SYSCONFDIR/AC_PACKAGE_NAME.d/xdg/autostart] )
AC_DEFINE_UNQUOTED(AUTOSTARTDIR, "$AUTOSTARTDIR" , [ The autostart dir ])

AC_SUBST(CONFDIR, [$SYSCONFDIR/AC_PACKAGE_NAME.d/config] )
AC_DEFINE_UNQUOTED(CONFDIR, "$CONFDIR" , [ The config dir ])

AC_SUBST(LOGDATADIR, [$SYSCONFDIR/AC_PACKAGE_NAME.d] )
AC_DEFINE_UNQUOTED(LOGDATADIR, "$LOGDATADIR" , [ The log data dir ])

AC_SUBST(PIXMAPDIR, [$DATADIR/pixmaps] )
AC_DEFINE_UNQUOTED(PIXMAPDIR, "$PIXMAPDIR" , [ The pixmaps dir ])

AC_SUBST(GNOMELOCALEDIR, [$LOCALEDIR] )
AC_DEFINE_UNQUOTED(GNOMELOCALEDIR, "$GNOMELOCALEDIR" , [ The gettext package dir ])

AC_SUBST(CONFDIRMP, [$CONFDIR/MP] )
AC_DEFINE_UNQUOTED(CONFDIRMP, "$CONFDIRMP" , [ The config dir mp ])

AC_SUBST(CONFDIRMV, [$CONFDIR/MV] )
AC_DEFINE_UNQUOTED(CONFDIRMV, "$CONFDIRMV" , [ The config dir mv ])

CXXFLAGS="-Wall -Werror ${CXXFLAGS}"

AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
pixmaps/Makefile
etc/Makefile
etc/election.desktop.in
doc/Makefile
doc/man/Makefile
doc/man/es/Makefile
log/Makefile
log/MV/Makefile
log/MP/Makefile
conf/Makefile
conf/MV/Makefile
conf/MP/Makefile
])

AC_OUTPUT

if test -d po && test -e po/Makefile ; then
   echo "======================================="
   echo ""
   echo "Execute make update-po"
   echo ""
   cd po
   make update-po | perl -ne 'print if /:$/'
   echo ""
   for file in $(ls *.po); do \
       msgattrib --no-location --no-wrap $file -o $file;  \
       sed -i '/^\"POT-Creation-Date:.*\\n.*$/d' $file
   done
   cd ..
   echo "======================================="
fi

