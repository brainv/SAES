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

GETTEXT_PACKAGE = libsaes
PACKAGE = libsaes
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
install_sh = ${SHELL} /home/smtt/SAES1.4.6/saes/install-sh
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
	../src/Configuration/s-a-e-s-conf-manager.cc \
	../src/Configuration/s-a-e-s-conf-manager.h \
	../src/Configuration/saes-language-controller.cc \
	../src/Configuration/saes-language-controller.h \
	../src/Exceptions/Voting/Vote/QRVoteInvalidFormatException.cpp \
	../src/Exceptions/Voting/Vote/QRVoteInvalidFormatException.h \
	../src/Exceptions/Voting/Vote/QRVoteSignatureException.cpp \
	../src/Exceptions/Voting/Vote/QRVoteSignatureException.h \
	../src/Printing/AuditLogPrintDocument.cpp \
	../src/Printing/AuditLogPrintDocument.h \
	../src/Printing/BarcodeConfigPrinting.cxx \
	../src/Printing/BarcodeConfigPrinting.hxx \
	../src/Printing/BarcodePrinting.cxx \
	../src/Printing/BarcodePrinting.hxx \
	../src/Printing/ContingencyCardReport.cpp \
	../src/Printing/ContingencyCardReport.h \
	../src/Printing/ErrorLogPrintDocument.cpp \
	../src/Printing/ErrorLogPrintDocument.h \
	../src/Printing/HelpPrinting.cxx \
	../src/Printing/HelpPrinting.hxx \
	../src/Printing/InstallationPrintDocument.cc \
	../src/Printing/InstallationPrintDocument.h \
	../src/Printing/LogPrintDocument.cpp \
	../src/Printing/LogPrintDocument.h \
	../src/Printing/ReportPrintingController.cpp \
	../src/Printing/ReportPrintingController.h \
	../src/Printing/SmartcardRemovedPrintDocument.cc \
	../src/Printing/SmartcardRemovedPrintDocument.h \
	../src/Printing/TestPrinting.cxx \
	../src/Printing/TestPrinting.hxx \
	../src/Printing/TimeoutPrintDocument.cc \
	../src/Printing/TimeoutPrintDocument.h \
	../src/Printing/TranslatorTextConfiguration.cc \
	../src/Printing/TranslatorTextConfiguration.h \
	../src/Printing/VotePrintDocument.cc \
	../src/Printing/VotePrintDocument.h \
	../src/Resources/election-image-resources-manager.cc \
	../src/Resources/election-image-resources-manager.h \
	../src/Resources/election-string-resources-manager.cc \
	../src/Resources/election-string-resources-manager.h \
	../src/Voting/Codi/CodiBuffer.cxx \
	../src/Voting/Codi/CodiBuffer.hxx \
	../src/Voting/Codi/CodiFile.cpp \
	../src/Voting/Codi/CodiFile.h \
	../src/Voting/Codi/CodiFileManager.cxx \
	../src/Voting/Codi/CodiFileManager.hxx \
	../src/Voting/Codi/CodiFileWrapper.cxx \
	../src/Voting/Codi/CodiFileWrapper.hxx \
	../src/Voting/Codi/CodiFormatUtillity.cpp \
	../src/Voting/Codi/CodiFormatUtillity.h \
	../src/Voting/Codi/CodiInfo.cxx \
	../src/Voting/Codi/CodiInfo.hxx \
	../src/Voting/Codi/CodiRegisterBase.cpp \
	../src/Voting/Codi/CodiRegisterBase.h \
	../src/Voting/Codi/CodiRegisterC.cpp \
	../src/Voting/Codi/CodiRegisterC.h \
	../src/Voting/Codi/CodiRegisterL.cpp \
	../src/Voting/Codi/CodiRegisterL.h \
	../src/Voting/Codi/CodiRegisterS.cpp \
	../src/Voting/Codi/CodiRegisterS.h \
	../src/Voting/Codi/SelectableCodiRegister.cpp \
	../src/Voting/Codi/SelectableCodiRegister.h \
	../src/Voting/Codi/X7SCodiFileWrapper.cxx \
	../src/Voting/Codi/X7SCodiFileWrapper.hxx \
	../src/Voting/Codi/X7SSecurity.cxx \
	../src/Voting/Codi/X7SSecurity.hxx \
	../src/Voting/Election/ElectionInstalationLanguages.cpp \
	../src/Voting/Election/ElectionInstalationLanguages.h \
	../src/Voting/Election/ElectionWrapper.cxx \
	../src/Voting/Election/ElectionWrapper.hxx \
	../src/Voting/ElectoralConfiguration.cxx \
	../src/Voting/ElectoralConfiguration.hxx \
	../src/Voting/ElectoralFactory.cxx \
	../src/Voting/ElectoralFactory.hxx \
	../src/Voting/operation-status.cc \
	../src/Voting/operation-status.h \
	../src/Voting/PBReports/activated-card-statistics-wrapper.cc \
	../src/Voting/PBReports/activated-card-statistics-wrapper.h \
	../src/Voting/PBReports/assisted-activation-wrapper.cc \
	../src/Voting/PBReports/assisted-activation-wrapper.h \
	../src/Voting/PBReports/closing-notes-wrapper.cc \
	../src/Voting/PBReports/closing-notes-wrapper.h \
	../src/Voting/PBReports/id-card-info-wrapper.cc \
	../src/Voting/PBReports/id-card-info-wrapper.h \
	../src/Voting/PBReports/incident-report-wrapper.cc \
	../src/Voting/PBReports/incident-report-wrapper.h \
	../src/Voting/PBReports/PoliceNoteWrapper.cxx \
	../src/Voting/PBReports/PoliceNoteWrapper.hxx \
	../src/Voting/PBReports/pollworkers-wrapper.cc \
	../src/Voting/PBReports/pollworkers-wrapper.h \
	../src/Voting/PBReports/PVFormWrapper.cxx \
	../src/Voting/PBReports/PVFormWrapper.hxx \
	../src/Voting/PBReports/StatisticGroup.cxx \
	../src/Voting/PBReports/StatisticGroup.hxx \
	../src/Voting/PBReports/StatisticManager.cxx \
	../src/Voting/PBReports/StatisticManager.hxx \
	../src/Voting/PBReports/statistic-resources-keys.h \
	../src/Voting/PBReports/StatisticWrapper.cxx \
	../src/Voting/PBReports/StatisticWrapper.hxx \
	../src/Voting/PBReports/VoteStatistic.cxx \
	../src/Voting/PBReports/VoteStatistic.hxx \
	../src/Voting/PBReports/vote-statistics.cc \
	../src/Voting/PBReports/vote-statistics.h \
	../src/Voting/PBReports/VotingDisabledWrapper.cxx \
	../src/Voting/PBReports/VotingDisabledWrapper.hxx \
	../src/Voting/Screen/GeneratedImagesWrapper.cxx \
	../src/Voting/Screen/GeneratedImagesWrapper.hxx \
	../src/Voting/set-language-functionality.cc \
	../src/Voting/set-language-functionality.h \
	../src/Voting/Status/CardGeneratedListWrapper.cxx \
	../src/Voting/Status/CardGeneratedListWrapper.hxx \
	../src/Voting/Status/ElectionStatusWrapper.cxx \
	../src/Voting/Status/ElectionStatusWrapper.hxx \
	../src/Voting/Status/VMStatusWrapper.cxx \
	../src/Voting/Status/VMStatusWrapper.hxx \
	../src/Voting/Vote/StationTallyWrapper.cxx \
	../src/Voting/Vote/StationTallyWrapper.hxx \
	../src/Voting/Vote/TransmissionPackageWrapper.cxx \
	../src/Voting/Vote/TransmissionPackageWrapper.hxx \
	../src/Voting/Vote/VoteCode.cxx \
	../src/Voting/Vote/VoteCode.hxx \
	../src/Voting/Vote/VoteEncoder.cpp \
	../src/Voting/Vote/VoteEncoder.h \
	../src/Voting/Vote/VoteRecovery.cpp \
	../src/Voting/Vote/VoteRecovery.h \
	../src/Voting/Vote/VoteWrapper.cxx \
	../src/Voting/Vote/VoteWrapper.hxx \
	../src/Voting/VotingCenters/VotingCentersWrapper.cxx \
	../src/Voting/VotingCenters/VotingCentersWrapper.hxx \
	../src/Voting/VotingDevice/card-data-wrapper.cc \
	../src/Voting/VotingDevice/card-data-wrapper.h \
	../src/Voting/VotingDevice/ContingencyCardDataWrapper.cxx \
	../src/Voting/VotingDevice/ContingencyCardDataWrapper.hxx \
	../src/Voting/VotingDevice/VotingDeviceWrapper.cxx \
	../src/Voting/VotingDevice/VotingDeviceWrapper.hxx

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
