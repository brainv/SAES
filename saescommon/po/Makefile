# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
# Copyright (C) 2004-2008 Rodney Dawes <dobey.pwns@gmail.com>
#
# This file may be copied and used freely without restrictions.  It may
# be used in projects which are not available under a GNU Public License,
# but which still want to provide support for the GNU gettext functionality.
#
# - Modified by Owen Taylor <otaylor@redhat.com> to use GETTEXT_PACKAGE
#   instead of PACKAGE and to look for po2tbl in ./ not in intl/
#
# - Modified by jacob berkman <jacob@ximian.com> to install
#   Makefile.in.in and po2tbl.sed.in for use with glib-gettextize
#
# - Modified by Rodney Dawes <dobey.pwns@gmail.com> for use with intltool
#
# We have the following line for use by intltoolize:
# INTLTOOL_MAKEFILE

GETTEXT_PACKAGE = libsaescommon
PACKAGE = libsaescommon
VERSION = 1.4.6

SHELL = /bin/bash

srcdir = .
top_srcdir = ..
top_builddir = ..


prefix = /usr/local
exec_prefix = /usr/local
datadir = ${prefix}/share
datarootdir = ${prefix}/share
libdir = ${exec_prefix}/lib
DATADIRNAME = share
itlocaledir = $(prefix)/$(DATADIRNAME)/locale
subdir = po
install_sh = ${SHELL} /home/smtt/SAES1.4.6/saescommon/install-sh
# Automake >= 1.8 provides /bin/mkdir -p.
# Until it can be supposed, use the safe fallback:
mkdir_p = $(install_sh) -d

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

GMSGFMT = /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext
INTLTOOL_UPDATE = /usr/bin/intltool-update
INTLTOOL_EXTRACT = /usr/bin/intltool-extract
MSGMERGE = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --dist
GENPOT   = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --pot

ALL_LINGUAS = 

PO_LINGUAS=$(shell if test -r $(srcdir)/LINGUAS; then grep -v "^\#" $(srcdir)/LINGUAS; else echo "$(ALL_LINGUAS)"; fi)

USER_LINGUAS=$(shell if test -n "$(LINGUAS)"; then LLINGUAS="$(LINGUAS)"; ALINGUAS="$(ALL_LINGUAS)"; for lang in $$LLINGUAS; do if test -n "`grep \^$$lang$$ $(srcdir)/LINGUAS 2>/dev/null`" -o -n "`echo $$ALINGUAS|tr ' ' '\n'|grep \^$$lang$$`"; then printf "$$lang "; fi; done; fi)

USE_LINGUAS=$(shell if test -n "$(USER_LINGUAS)" -o -n "$(LINGUAS)"; then LLINGUAS="$(USER_LINGUAS)"; else if test -n "$(PO_LINGUAS)"; then LLINGUAS="$(PO_LINGUAS)"; else LLINGUAS="$(ALL_LINGUAS)"; fi; fi; for lang in $$LLINGUAS; do printf "$$lang "; done)

POFILES=$(shell LINGUAS="$(PO_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.po "; done)

DISTFILES = Makefile.in.in POTFILES.in $(POFILES)
EXTRA_DISTFILES = ChangeLog POTFILES.skip Makevars LINGUAS

POTFILES = \
	../src/Card/ICardController.cxx \
	../src/Card/ICardController.hxx \
	../src/Card/SaesSmartCard.cxx \
	../src/Card/SaesSmartCard.hxx \
	../src/Card/SmartCardCommand.cxx \
	../src/Card/SmartCardCommand.hxx \
	../src/Card/SmartcardConnected.cpp \
	../src/Card/SmartcardConnected.h \
	../src/Card/SmartCard.cxx \
	../src/Card/SmartCard.hxx \
	../src/Configuration/s-a-e-s-common-conf-manager.cc \
	../src/Configuration/s-a-e-s-common-conf-manager.h \
	../src/Configuration/saes-common-language-controller.cc \
	../src/Configuration/saes-common-language-controller.h \
	../src/eid/beidlib/eidlibdefines.h \
	../src/eid/beidlib/eidlibException.h \
	../src/eid/beidlib/eidlib.h \
	../src/eid/CitizenInfo.cpp \
	../src/eid/CitizenInfo.h \
	../src/eid/EIDEvent.cxx \
	../src/eid/EIDEvent.hxx \
	../src/eid/EIDEventInterface.hxx \
	../src/eid/EIDManager.cxx \
	../src/eid/EIDManager.hxx \
	../src/eid/EIDPin.cxx \
	../src/eid/EIDPin.hxx \
	../src/eid/EIDRead.cxx \
	../src/eid/EIDRead.hxx \
	../src/eid/EIDSign.cxx \
	../src/eid/EIDSign.hxx \
	../src/eid/EIDUtils.cxx \
	../src/eid/EIDUtils.hxx \
	../src/eid/pkcs11/cryptoki.h \
	../src/eid/pkcs11/pkcs11f.h \
	../src/eid/pkcs11/pkcs11.h \
	../src/eid/pkcs11/pkcs11t.h \
	../src/Log/LogBasePath.cxx \
	../src/Log/LogBasePath.hxx \
	../src/Log/LogCryptoBase64.cxx \
	../src/Log/LogCryptoBase64.hxx \
	../src/Log/LogCryptoGlobal.cxx \
	../src/Log/LogCryptoGlobal.hxx \
	../src/Log/LogCryptoPool.cxx \
	../src/Log/LogCryptoPool.hxx \
	../src/Log/LogLine.cc \
	../src/Log/LogLine.h \
	../src/Log/LogPage.cc \
	../src/Log/LogPage.h \
	../src/Log/LogReader.cc \
	../src/Log/LogReader.h \
	../src/Operation/Initiator/CheckDirectoryStructure.cxx \
	../src/Operation/Initiator/CheckDirectoryStructure.hxx \
	../src/Operation/Initiator/CheckFilesPresence.cxx \
	../src/Operation/Initiator/CheckFilesPresence.hxx \
	../src/Operation/Initiator/CheckFlashPresence.cxx \
	../src/Operation/Initiator/CheckFlashPresence.hxx \
	../src/Operation/Initiator/CheckFlashStructure.cxx \
	../src/Operation/Initiator/CheckFlashStructure.hxx \
	../src/Operation/Initiator/CheckForMemoryComplete.cpp \
	../src/Operation/Initiator/CheckForMemoryComplete.h \
	../src/Operation/Initiator/CheckForUsedMemory.cpp \
	../src/Operation/Initiator/CheckForUsedMemory.h \
	../src/Operation/Initiator/ICheckCondition.cxx \
	../src/Operation/Initiator/ICheckCondition.hxx \
	../src/Operation/Initiator/InitializationStatus.cxx \
	../src/Operation/Initiator/InitializationStatus.hxx \
	../src/pcscd/PCSCDManager.cxx \
	../src/pcscd/PCSCDManager.hxx \
	../src/Printing/BasePrintDocument.cpp \
	../src/Printing/BasePrintDocument.h \
	../src/Printing/DirectPrintingBackend.cpp \
	../src/Printing/DirectPrintingBackend.h \
	../src/Printing/DocumentOptions.cpp \
	../src/Printing/DocumentOptions.h \
	../src/Printing/GraphicContentPage.cpp \
	../src/Printing/GraphicContentPage.h \
	../src/Printing/GraphicContextPrintingBackend.cpp \
	../src/Printing/GraphicContextPrintingBackend.h \
	../src/Printing/IPrintingBackend.cpp \
	../src/Printing/IPrintingBackend.h \
	../src/Printing/LPSpooler.cpp \
	../src/Printing/LPSpooler.h \
	../src/Printing/PrintDocumentClient.h \
	../src/Printing/PrintDocumentResult.cpp \
	../src/Printing/PrintDocumentResult.h \
	../src/Printing/printer-client.cc \
	../src/Printing/printer-client.h \
	../src/Printing/printer-element.cc \
	../src/Printing/printer-element.h \
	../src/Printing/printer-status.cc \
	../src/Printing/printer-status.h \
	../src/Printing/PrinterStatusNotifier.cpp \
	../src/Printing/PrinterStatusNotifier.h \
	../src/Printing/PrinterTwoColumnsElement.cc \
	../src/Printing/PrinterTwoColumnsElement.h \
	../src/Printing/PrintPreviewWidget.cpp \
	../src/Printing/PrintPreviewWidget.h \
	../src/Resources/string-resources-manager-base.cc \
	../src/Resources/string-resources-manager-base.h \
	../src/Runtime/Environment/DirectoryManager.cxx \
	../src/Runtime/Environment/DirectoryManager.hxx \
	../src/Runtime/Environment/EnvironmentBuilder.cxx \
	../src/Runtime/Environment/EnvironmentBuilder.hxx \
	../src/Runtime/Environment/filename-hasher.cc \
	../src/Runtime/Environment/filename-hasher.h \
	../src/Runtime/Environment/MasterMemoryParser.cpp \
	../src/Runtime/Environment/MasterMemoryParser.h \
	../src/Runtime/Environment/MemoryEventParser.cpp \
	../src/Runtime/Environment/MemoryEventParser.h \
	../src/Runtime/Environment/MemoryInfo.cpp \
	../src/Runtime/Environment/MemoryInfo.h \
	../src/Runtime/Environment/MemoryPathController.cpp \
	../src/Runtime/Environment/MemoryPathController.h \
	../src/Runtime/Environment/saes-directories.cc \
	../src/Runtime/Environment/saes-directories.h \
	../src/Runtime/Environment/SaesInstallDirectories.cxx \
	../src/Runtime/Environment/SaesInstallDirectories.hxx \
	../src/Runtime/Environment/SaesProgramUnitDirectories.cxx \
	../src/Runtime/Environment/SaesProgramUnitDirectories.hxx \
	../src/Runtime/Environment/saes-temporal-directories.cc \
	../src/Runtime/Environment/saes-temporal-directories.h \
	../src/Security/CryptoData.cxx \
	../src/Security/CryptoData.hxx \
	../src/Security/Encryption.cxx \
	../src/Security/Encryption.hxx \
	../src/Security/SecretKey.cpp \
	../src/Security/SecretKey.h \
	../src/Security/XmlSecResource.cxx \
	../src/Security/XmlSecResource.hxx \
	../src/Voting/IStateWrapper.cxx \
	../src/Voting/IStateWrapper.hxx

CATALOGS=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.gmo "; done)

.SUFFIXES:
.SUFFIXES: .po .pox .gmo .mo .msg .cat

.po.pox:
	$(MAKE) $(GETTEXT_PACKAGE).pot
	$(MSGMERGE) $< $(GETTEXT_PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f ../intl/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && gencat $@ $*.msg


all: all-yes

all-yes: $(CATALOGS)
all-no:

$(GETTEXT_PACKAGE).pot: $(POTFILES)
	$(GENPOT)

install: install-data
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  dir=$(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $$dir; \
	  if test -r $$lang.gmo; then \
	    $(INSTALL_DATA) $$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $$lang.gmo as $$dir/$(GETTEXT_PACKAGE).mo"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $(srcdir)/$$lang.gmo as" \
		 "$$dir/$(GETTEXT_PACKAGE).mo"; \
	  fi; \
	  if test -r $$lang.gmo.m; then \
	    $(INSTALL_DATA) $$lang.gmo.m $$dir/$(GETTEXT_PACKAGE).mo.m; \
	    echo "installing $$lang.gmo.m as $$dir/$(GETTEXT_PACKAGE).mo.m"; \
	  else \
	    if test -r $(srcdir)/$$lang.gmo.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$lang.gmo.m \
		$$dir/$(GETTEXT_PACKAGE).mo.m; \
	      echo "installing $(srcdir)/$$lang.gmo.m as" \
		   "$$dir/$(GETTEXT_PACKAGE).mo.m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done

# Empty stubs to satisfy archaic automake needs
dvi info ctags tags CTAGS TAGS ID:

# Define this as empty until I found a useful application.
install-exec installcheck:

uninstall:
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo; \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo.m; \
	done

check: all $(GETTEXT_PACKAGE).pot
	rm -f missing notexist
	srcdir=$(srcdir) $(INTLTOOL_UPDATE) -m
	if [ -r missing -o -r notexist ]; then \
	  exit 1; \
	fi

mostlyclean:
	rm -f *.pox $(GETTEXT_PACKAGE).pot *.old.po cat-id-tbl.tmp
	rm -f .intltool-merge-cache

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES stamp-it
	rm -f *.mo *.msg *.cat *.cat.m *.gmo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f Makefile.in.in

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: $(DISTFILES)
	dists="$(DISTFILES)"; \
	extra_dists="$(EXTRA_DISTFILES)"; \
	for file in $$extra_dists; do \
	  test -f $(srcdir)/$$file && dists="$$dists $(srcdir)/$$file"; \
	done; \
	for file in $$dists; do \
	  test -f $$file || file="$(srcdir)/$$file"; \
	  ln $$file $(distdir) 2> /dev/null \
	    || cp -p $$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(GETTEXT_PACKAGE).pot
	tmpdir=`pwd`; \
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  echo "$$lang:"; \
	  result="`$(MSGMERGE) -o $$tmpdir/$$lang.new.po $$lang`"; \
	  if $$result; then \
	    if cmp $(srcdir)/$$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	      rm -f $$tmpdir/$$lang.new.po; \
            else \
	      if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	        :; \
	      else \
	        echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	        rm -f $$tmpdir/$$lang.new.po; \
	        exit 1; \
	      fi; \
	    fi; \
	  else \
	    echo "msgmerge for $$lang.gmo failed!"; \
	    rm -f $$tmpdir/$$lang.new.po; \
	  fi; \
	done

Makefile POTFILES: stamp-it
	@if test ! -f $@; then \
	  rm -f stamp-it; \
	  $(MAKE) stamp-it; \
	fi

stamp-it: Makefile.in.in $(top_builddir)/config.status POTFILES.in
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/Makefile.in CONFIG_HEADERS= CONFIG_LINKS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
