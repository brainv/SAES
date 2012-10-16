## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(DUPLICATE_VOTE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = duplicate-vote

duplicate_vote_SOURCES = \
	main.cxx \
	Barcode.hxx \
	PrintVote.hxx \
	VoteRecorder.hxx \
	SaveVote.hxx \
	MyHelpers.hxx \
	Barcode.cxx \
	PrintVote.cxx \
	VoteRecorder.cxx \
	SaveVote.cxx

duplicate_vote_LDFLAGS = 

duplicate_vote_LDADD = $(DUPLICATE_VOTE_LIBS)

