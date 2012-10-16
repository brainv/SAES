## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src ui po docs
CLEANFILES = *~
ACLOCAL_AMFLAGS = -I m4

smartmaticguidocdir = @DATADIR@/doc/@PACKAGE_NAME@
smartmaticguidoc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(smartmaticguidoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


