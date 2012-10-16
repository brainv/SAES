dnl Created by Anjuta application wizard.

AC_INIT(libsmartmatic, 1.4.6)
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

AC_CHECK_LIB([xml-security-c], [main],[], [AC_MSG_ERROR(["Error: library xml-security-c not found. Install libxml-security-c-dev package and try again"])]) 

dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************

IT_PROG_INTLTOOL()
AM_GLIB_GNU_GETTEXT

AC_SUBST(GETTEXT_PACKAGE, [AC_PACKAGE_NAME])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])


PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(modules, [xerces-c glibmm-2.4 uuid gtkmm-2.4 libsmartmaticlog zlib libcrypto libssl])
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


libcryptoversion=$(pkg-config --modversion libcrypto | awk '/^0\.9\.8/ { print "0.9.8" }')

if test "$libcryptoversion" = "0.9.8" ; then
	AC_MSG_WARN([Continuing without CMS signer support, only in openssl >= 1.0.0])
	AC_DEFINE_UNQUOTED(USE_PKCS5_PBKDF2_HMAC,"", [use PKCS5_PBKDF2_HMAC])
else
	AC_DEFINE_UNQUOTED(USE_CMS_SIGNER,"", [use CMS_SIGNER])
fi


NAMESPACE_CONFIGURATION="http://www.smartmatic.com/Configuration"
NAMESPACE_SMARTMATIC_CONFIGURATION="http://www.smartmatic.com/SmartmaticConfiguration"

AC_DEFINE_UNQUOTED(NAMESPACE_CONFIGURATION, "$NAMESPACE_CONFIGURATION", [namespace configuration])
AC_DEFINE_UNQUOTED(NAMESPACE_SMARTMATIC_CONFIGURATION, "$NAMESPACE_SMARTMATIC_CONFIGURATION", [namespace smartmatic configuration])

XSDFLAGS="\
	--char-type char \
	--show-sloc \
	--generate-serialization \
	--generate-default-ctor \
	--generate-comparison \
	--generate-doxygen \
	--type-naming ucc \
	--function-naming java \
	--namespace-map $NAMESPACE_CONFIGURATION=Smartmatic::Configuration \
	--namespace-map $NAMESPACE_SMARTMATIC_CONFIGURATION=Smartmatic::Configuration "

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

AC_SUBST(SOUNDDIR, sound )
AC_DEFINE_UNQUOTED(SOUNDDIR, "$SOUNDDIR" , [ The sound dir ])

AC_SUBST(SOUNDDATADIR, [$DATADIR/AC_PACKAGE_NAME/$SOUNDDIR] )
AC_DEFINE_UNQUOTED(SOUNDDATADIR, "$SOUNDDATADIR" , [ The sound data dir ])


CXXFLAGS="-Wall -Werror  ${CXXFLAGS}"

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
src/libsmartmatic.pc
src/Makefile
src/System/Makefile
src/System/XSLFO/Makefile
src/System/Utils/Makefile
src/System/Exception/Makefile
src/System/Security/Makefile
src/System/Security/Cryptography/Makefile
src/XSDTemplates/Makefile
src/Configuration/Makefile
src/Configuration/GeneratedClasses/Makefile
src/Configuration/GeneratedClasses/Configuration/Makefile
docs/Makefile
sound/Makefile
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

