## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po log

votesimdocdir = @DATADIR@/doc/@PACKAGE_NAME@
votesimdoc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(votesimdoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache
