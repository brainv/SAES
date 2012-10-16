## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src log

duplicate_vote_docdir = @DATADIR@/doc/@PACKAGE_NAME@
duplicate_vote_doc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(duplicate_votedoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(duplicate_vote_finderdocdir)
