AC_INIT(libsaes, 1.4.6)
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

AC_CHECK_LIB([gmp], [__gmpz_init],[], [AC_MSG_ERROR(["Error: library gmp not found. Install libgmp3-dev package and try again"])]) 

PKG_CHECK_MODULES(modules, [xerces-c libsmartmatic libsaescommon gtkmm-2.4 libsmartmaticgui libqrencode glibmm-2.4 libsmartmaticlog gthread-2.0])
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


NAMESPACE_CONFIGURATION="http://www.smartmatic.com/SaesConfiguration"
NAMESPACE_VOTING="http://www.smartmatic.com/Saes/Voting"
NAMESPACE_VOTING_ELECTION="http://www.smartmatic.com/Saes/Voting/Election"
NAMESPACE_VOTING_VOTINGDEVICE="http://www.smartmatic.com/Saes/Voting/VotingDevice"
NAMESPACE_VOTING_STATIONTALLY="http://www.smartmatic.com/Saes/Voting/StationTally"
NAMESPACE_VOTING_VOTE="http://www.smartmatic.com/Saes/Voting/Vote"
NAMESPACE_VOTING_STATUS="http://www.smartmatic.com/Saes/Voting/Status"
NAMESPACE_VOTING_CENTERS="http://www.smartmatic.com/Saes/Voting/VotingCenters"
NAMESPACE_PBREPORTS="http://www.smartmatic.com/Saes/Voting/PBReports"
NAMESPACE_SCREEN="http://www.smartmatic.com/Saes/Voting/Screen"
NAMESPACE_VOTING_CODI="http://www.smartmatic.com/Saes/Voting/Codi"

AC_DEFINE_UNQUOTED(NAMESPACE_CONFIGURATION, "$NAMESPACE_CONFIGURATION", [namespace configuration])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING, "$NAMESPACE_VOTING", [namespace voting])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING_ELECTION, "$NAMESPACE_VOTING_ELECTION", [namespace election])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING_VOTINGDEVICE, "$NAMESPACE_VOTING_VOTINGDEVICE", [namespace voting devices])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING_VOTE, "$NAMESPACE_VOTING_VOTE", [namespace vote])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING_STATUS, "$NAMESPACE_VOTING_STATUS", [namespace status])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING_CENTERS, "$NAMESPACE_VOTING_CENTERS", [namespace voting center])
AC_DEFINE_UNQUOTED(NAMESPACE_PBREPORTS, "$NAMESPACE_PBREPORTS", [namespace pbreports])
AC_DEFINE_UNQUOTED(NAMESPACE_SCREEN, "$NAMESPACE_SCREEN", [namespace screen])
AC_DEFINE_UNQUOTED(NAMESPACE_VOTING_CODI, "$NAMESPACE_VOTING_CODI", [namespace voting codi files xml])

XSDFLAGS="\
	--char-type char \
	--show-sloc \
	--generate-serialization \
	--generate-default-ctor \
	--generate-comparison \
	--generate-doxygen \
	--type-naming ucc \
	--function-naming java \
	--namespace-map $NAMESPACE_CONFIGURATION=Smartmatic::SAES::Configuration \
	--namespace-map $NAMESPACE_VOTING=Smartmatic::SAES::Voting \
	--namespace-map $NAMESPACE_VOTING_ELECTION=Smartmatic::SAES::Voting::Election \
	--namespace-map $NAMESPACE_VOTING_VOTINGDEVICE=Smartmatic::SAES::Voting::VotingDevice \
	--namespace-map $NAMESPACE_VOTING_VOTE=Smartmatic::SAES::Voting::Vote \
	--namespace-map $NAMESPACE_VOTING_STATUS=Smartmatic::SAES::Voting::Status \
	--namespace-map $NAMESPACE_PBREPORTS=Smartmatic::SAES::Voting::PBReports \
	--namespace-map $NAMESPACE_VOTING_CENTERS=Smartmatic::SAES::Voting::VotingCenters \
	--namespace-map $NAMESPACE_SCREEN=Smartmatic::SAES::Voting::Screen \
	--namespace-map $NAMESPACE_VOTING_CODI=Smartmatic::SAES::Voting::Codi"


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

AC_SUBST(UIDATADIR, [$DATADIR/AC_PACKAGE_NAME/ui] )
AC_DEFINE_UNQUOTED(UIDATADIR, "$UIDATADIR" , [ The ui data dir ])

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
po/Makefile.in
src/Makefile
src/libsaes.pc
src/Resources/Makefile
src/Voting/Makefile
src/Voting/Election/Makefile
src/Voting/VotingDevice/Makefile
src/Voting/PBReports/Makefile
src/Voting/Status/Makefile
src/Voting/VotingCenters/Makefile
src/Voting/Vote/Makefile
src/Voting/Screen/Makefile
src/Voting/Codi/Makefile
src/Configuration/Makefile
src/Voting/GeneratedClasses/Makefile
src/Voting/GeneratedClasses/Voting/Makefile
src/Voting/GeneratedClasses/Voting/Codi/Makefile
src/Voting/GeneratedClasses/Voting/Election/Makefile
src/Voting/GeneratedClasses/Voting/VotingDevice/Makefile
src/Voting/GeneratedClasses/Voting/Screen/Makefile
src/Voting/GeneratedClasses/Voting/Status/Makefile
src/Voting/GeneratedClasses/Voting/Vote/Makefile
src/Voting/GeneratedClasses/Voting/VotingCenters/Makefile
src/Voting/GeneratedClasses/Voting/PBReports/Makefile
src/Configuration/GeneratedClasses/Makefile
src/Configuration/GeneratedClasses/Configuration/Makefile
src/XSDTemplates/Makefile
src/Printing/Makefile
src/Exceptions/Makefile
src/Exceptions/Voting/Makefile
src/Exceptions/Voting/Vote/Makefile
docs/Makefile
ui/Makefile])

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
