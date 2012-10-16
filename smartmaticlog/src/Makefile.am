## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(modules_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g \
	 -Werror

lib_LTLIBRARIES = libsmartmaticlog.la

libsmartmaticlog_la_SOURCES = \
	Log/ISMTTLog.h \
	Log/ISMTTLog.cpp \
	Log/LogImpl.h \
	Log/LogImpl.cpp \
	Log/SMTTLogManager.h \
	Log/SMTTLogManager.cpp \
	log4cxx/DynamicPathRollingFileAppender.cxx \
	log4cxx/DynamicPathRollingFileAppender.hxx \
	log4cxx/CryptoLayout.cxx \
	log4cxx/CryptoLayout.hxx \
	Log/BasePathInterface.cxx \
	Log/BasePathInterface.hxx \
	Log/ICryptoLayoutTransformer.cxx \
	Log/ICryptoLayoutTransformer.hxx \
	Log/LogInterface.cxx \
	Log/LogInterface.hxx

libsmartmaticlog_la_CPPFLAGS = @modules_CFLAGS@
libsmartmaticlog_la_LIBADD = @modules_LIBS@
libsmartmaticlog_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsmartmaticlog_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

smartmaticlog_includedir= $(includedir)/smartmaticlog
nobase_smartmaticlog_include_HEADERS = \
	Log/ISMTTLog.h \
	Log/LogImpl.h \
	Log/SMTTLogManager.h \
	Log/BasePathInterface.hxx \
	Log/ICryptoLayoutTransformer.hxx \
	Log/LogInterface.hxx \
	log4cxx/DynamicPathRollingFileAppender.hxx \
	log4cxx/CryptoLayout.hxx
	
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libsmartmaticlog.pc

EXTRA_DIST = \
	libsmartmaticlog.pc.in

