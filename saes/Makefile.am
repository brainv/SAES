SUBDIRS = src po ui docs
CLEANFILES = po/*~ *~
ACLOCAL_AMFLAGS = -I m4

saesdocdir = @DATADIR@/doc/@PACKAGE_NAME@
saesdoc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(saesdoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


