## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src log

scard_docdir = @DATADIR@/doc/@PACKAGE_NAME@
scard_doc_DATA = \
	README\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(scarddoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(scarddocdir)
