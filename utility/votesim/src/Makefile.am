## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = @DATADIR@/@PACKAGE_NAME@/ui
ui_DATA = votesim.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(VOTESIM_CFLAGS)\
	-O0

AM_CFLAGS =\
	 -Wall\
	 -g\
	 -O0
	 
bin_PROGRAMS = votesim

votesim_SOURCES = \
	main.cc \
	SimVoetWindow.h \
	SimVoetWindow.cpp
	

votesim_LDFLAGS = 

votesim_LDADD = $(VOTESIM_LIBS)

EXTRA_DIST = $(ui_DATA)

