## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src docs
CLEANFILES = *~
ACLOCAL_AMFLAGS = -I m4

smartmaticlogdocdir = @DATADIR@/doc/@PACKAGE_NAME@
smartmaticlogdoc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(smartmaticlogdoc_DATA) \
	$(INTLTOOL_FILES)

uninstall-local:
	@rm -rf $(smartmaticlogdocdir)/*	