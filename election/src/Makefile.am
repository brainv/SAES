## Process this file with automake to produce Makefile.in

## Created by Anjuta

#SUBDIRS = XSDTemplates Configuration

#CLEANFILES = *~ *.pc ${BUILT_SOURCES}
CLEANFILES = *~ *.pc

#BUILT_SOURCES = \
#	configuration-list 

XSDDIR = $(top_srcdir)/src/XSDTemplates

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(ELECTION_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g \
	 -Werror

bin_PROGRAMS = election

election_SOURCES = \
	main.cc \
	Config.cxx \
	Config.hxx \
	PMachine.hxx \
	PMachine.cxx \
	VMachine.hxx \
	VMachine.cxx \
	Diagnostics.hxx \
	Diagnostics.cxx \
	RunFunctionality.hxx \
	RunFunctionality.cxx
	
election_LDFLAGS = 

election_LDADD = $(ELECTION_LIBS) @INTLLIBS@

#configuration-list: ${XSDDIR}/ApplicationConfiguration-schema.xsd

#	$(XSDCXX) cxx-tree \
#	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
#	$(XSDFLAGS) \
#	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
#	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
#	--file-list $@ \
#	 $<

