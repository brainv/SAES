SUBDIRS = src po log pixmaps doc etc conf

electiondocdir = @DATADIR@/doc/@PACKAGE_NAME@
electiondoc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(electiondoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache

