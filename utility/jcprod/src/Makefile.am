## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/jcprod/ui
ui_DATA = jcprod.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(JCPROD_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = jcprod

jcprod_SOURCES = \
	main.cc \
	AppController.cpp \
	AppMainWindow.cpp \
	GpCommandWrapper.cpp \
	CardInstallationWrapper.cpp \
	InstallationDiagnosis.cpp \
	Exceptions/GpCommandException.cpp

jcprod_LDFLAGS = 

jcprod_LDADD = $(JCPROD_LIBS)

EXTRA_DIST = $(ui_DATA)

