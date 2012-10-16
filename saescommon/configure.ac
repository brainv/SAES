dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(libsaescommon, 1.4.6)
AM_INIT_AUTOMAKE([ filename-length-max=256 tar-ustar ])
LT_INIT([ disable-static ])

LIBMAYOR=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $1}') 
LIBMINOR=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $2}')
LIBFIX=$(echo AC_PACKAGE_VERSION | awk -F. '{ print $3}')
eval "((LIBVERSION=$LIBMAYOR + $LIBMINOR))"

AC_SUBST(LIBVERSION)
AC_SUBST(LIBMAYOR)
AC_SUBST(LIBMINOR)
AC_SUBST(LIBFIX)

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_HEADER_STDC

AC_DISABLE_STATIC
AM_DISABLE_STATIC

dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************

IT_PROG_INTLTOOL()
AM_GLIB_GNU_GETTEXT

AC_SUBST(GETTEXT_PACKAGE, [AC_PACKAGE_NAME])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(modules, [xerces-c libsmartmatic libsmartmaticgui gtkmm-2.4 libsmartmaticlog libpcsclite globalplatform libqrencode libcrypto libssl])
AC_SUBST(modules_CFLAGS)
AC_SUBST(modules_LIBS)

AC_CHECK_LIB([dl], [main],[], [AC_MSG_ERROR(["Error: library dl not found. Install libc6-dev package and try again"])]) 
AC_CHECK_LIB([barcode], [main],[], [AC_MSG_ERROR(["Error: library barcode not found. Install barcode package and try again"])]) 
AC_CHECK_LIB([cups], [main],[], [AC_MSG_ERROR(["Error: library cups not found. Install libcups2-dev package and try again"])]) 
AC_CHECK_LIB([xml-security-c], [main],[], [AC_MSG_ERROR(["Error: library xml-security-c not found. Install libxml-security-c-dev package and try again"])]) 
AC_CHECK_LIB([beidlib], [main],[], [AC_MSG_ERROR(["Error: library beid not found. Install libbeidlib3-dev package and try again"])]) 

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
else
   AC_MSG_ERROR([not found xsd program])
fi

NAMESPACE_SAES_COMMON_CONFIGURATION="http://www.smartmatic.com/SaesCommonConfiguration"
AC_DEFINE_UNQUOTED(NAMESPACE_SAES_COMMON_CONFIGURATION, "$NAMESPACE_SAES_COMMON_CONFIGURATION", [namespace saes common configuration])

NAMESPACE_SAES_COMMON_RESOURCES="http://www.smartmatic.com/Saes/Resources"
AC_DEFINE_UNQUOTED(NAMESPACE_SAES_COMMON_RESOURCES, "$NAMESPACE_SAES_COMMON_RESOURCES", [namespace saes common resources])


XSDFLAGS="\
	--char-type char \
	--show-sloc \
	--generate-serialization \
	--generate-default-ctor \
	--generate-comparison \
	--generate-doxygen \
	--type-naming ucc \
	--function-naming java \
	--namespace-map $NAMESPACE_SAES_COMMON_CONFIGURATION=Smartmatic::SAES::Common::Configuration \
	--namespace-map $NAMESPACE_SAES_COMMON_RESOURCES=Smartmatic::SAES::Resources "

AC_SUBST(XSDFLAGS)


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

AC_SUBST(GNOMELOCALEDIR, [$LOCALEDIR] )
AC_DEFINE_UNQUOTED(GNOMELOCALEDIR, "$GNOMELOCALEDIR" , [ The gettext package dir ])


AC_SUBST(UIDATADIR, [$DATADIR/AC_PACKAGE_NAME/ui] )
AC_DEFINE_UNQUOTED(UIDATADIR, "$UIDATADIR" , [ The ui data dir ])

CXXFLAGS="-Wall -Werror ${CXXFLAGS}"

AC_ARG_ENABLE(add-release, AS_HELP_STRING([--disable-add-release],
	[build without release in library name (default=no) ]),[use_add_release=$enableval],
	[use_add_release=yes])

AM_CONDITIONAL([ADD_RELEASE],[test "$use_add_release" = "yes"])

AC_ARG_ENABLE(sec-channel, AS_HELP_STRING([--disable-smartcard-applet-sec-channel],
	[build withou smartcard sec channel (default=no) ]),[use_sec_channel=$enableval],
	[use_sec_channel=yes])

if test "$use_sec_channel" = "yes" ; then
	AC_DEFINE([SMARTCARD_APPLET_SEC_CHANNEL], [], [enable sec channel])
fi

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
src/libsaescommon.pc
src/Makefile
src/Security/Makefile
src/XSDTemplates/Makefile
src/Configuration/Makefile
src/Configuration/GeneratedClasses/Makefile
src/Configuration/GeneratedClasses/Configuration/Makefile
src/Resources/Makefile
src/Resources/GeneratedClasses/Makefile
src/Resources/GeneratedClasses/Resources/Makefile
docs/Makefile
po/Makefile.in])

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
