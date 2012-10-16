SUBDIRS = GeneratedClasses
CLEANFILES = *~
EXTRA_DIST = ${HEADER_FILES} ${SOURCES_FILES}

configurationdir=$(includedir)/smartmatic/Configuration
configuration_HEADERS = ${HEADER_FILES}

HEADER_FILES= \
	$(top_srcdir)/src/Configuration/smartmatic-conf-manager.h \
	$(top_srcdir)/src/Configuration/configuration-persistence-manager.h

SOURCES_FILES= \
	$(top_srcdir)/src/Configuration/smartmatic-conf-manager.cc \
	$(top_srcdir)/src/Configuration/configuration-persistence-manager.cc

