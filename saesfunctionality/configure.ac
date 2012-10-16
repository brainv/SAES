dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(libsaesfunctionality, 1.4.6)
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

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(modules, [libqrencode xerces-c gtkmm-2.4 glib-2.0 libsaes libsmartmatic libsmartmaticgui libsaescommon glibmm-2.4 libsaeshardware libsmartmaticlog])
AC_SUBST(modules_CFLAGS)
AC_SUBST(modules_LIBS)

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


NAMESPACE_SAES_FUNCTIONALITY_CONFIGURATION="http://www.smartmatic.com/SaesFunctionalityConfiguration"
AC_DEFINE_UNQUOTED(NAMESPACE_SAES_FUNCTIONALITY_CONFIGURATION, "$NAMESPACE_SAES_FUNCTIONALITY_CONFIGURATION", [namespace saes functionality configuration])

XSDFLAGS="\
	--char-type char \
	--show-sloc \
	--generate-serialization \
	--generate-default-ctor \
	--generate-comparison \
	--generate-doxygen \
	--type-naming ucc \
	--function-naming java \
	--namespace-map $NAMESPACE_SAES_FUNCTIONALITY_CONFIGURATION=Smartmatic::SAES::Functionality::Configuration "

AC_SUBST(XSDFLAGS)


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

AC_SUBST(GNOMELOCALEDIR, [$LOCALEDIR] )
AC_DEFINE_UNQUOTED(GNOMELOCALEDIR, "$GNOMELOCALEDIR" , [ The gettext package dir ])


dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL()

AC_SUBST(GETTEXT_PACKAGE, [AC_PACKAGE_NAME])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

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
src/libsaesfunctionality.pc
src/Makefile
src/Operation/Makefile
src/Operation/Card/Makefile
src/Operation/Security/Makefile
src/Operation/Voting/Makefile
src/Operation/Authenticator/Makefile
src/Operation/Initiator/Makefile
src/Operation/Diagnosis/Makefile
src/Operation/BCR/Makefile
src/Operation/Alarm/Makefile
src/XSDTemplates/Makefile
src/Configuration/Makefile
src/Configuration/GeneratedClasses/Makefile
src/Configuration/GeneratedClasses/Configuration/Makefile
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

