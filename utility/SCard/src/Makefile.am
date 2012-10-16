## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(scard_CFLAGS) \
  -std=c++0x

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = scard

scard_SOURCES = \
  any.hxx \
  Parameters.hxx \
  ParameterSetImpl.hxx \
  SCard.hxx \
  PSCIManager.hxx \
  ParameterSetImpl.cxx \
  PSCIManager.cxx \
  main.cxx

scard_LDFLAGS = 

scard_LDADD = $(scard_LIBS)

