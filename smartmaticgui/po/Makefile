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

GETTEXT_PACKAGE = libsmartmaticgui
PACKAGE = libsmartmaticgui
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
install_sh = ${SHELL} /home/smtt/SAES1.4.6/smartmaticgui/install-sh
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
	../src/Configuration/label-configuration.cc \
	../src/Configuration/label-configuration.h \
	../src/Configuration/smartmaticgui-language-controller.cc \
	../src/Configuration/smartmaticgui-language-controller.h \
	../src/Configuration/s-m-t-t-g-u-i-conf-manager.cc \
	../src/Configuration/s-m-t-t-g-u-i-conf-manager.h \
	../src/Configuration/smtt-gui-image-resource-manager.cc \
	../src/Configuration/smtt-gui-image-resource-manager.h \
	../src/Graphics/Capture/PrintScreenManager.cpp \
	../src/Graphics/Capture/PrintScreenManager.h \
	../src/Graphics/Encoding2D/QREncoding.cc \
	../src/Graphics/Encoding2D/QREncoding.h \
	../src/Graphics/Image/CheckImageFile.cxx \
	../src/Graphics/Image/CheckImageFile.hxx \
	../src/Graphics/Image/Compose.cxx \
	../src/Graphics/Image/Compose.hxx \
	../src/Operation/WindowsManager.cxx \
	../src/Operation/WindowsManager.hxx \
	../src/Widgets/banner-widget.cc \
	../src/Widgets/banner-widget.h \
	../src/Widgets/BoolStatWidget.cxx \
	../src/Widgets/BoolStatWidget.hxx \
	../src/Widgets/ButtonsWidget.cxx \
	../src/Widgets/ButtonsWidget.hxx \
	../src/Widgets/choose-dialog-button-info.cc \
	../src/Widgets/choose-dialog-button-info.h \
	../src/Widgets/choose-dialog-info.cc \
	../src/Widgets/choose-dialog-info.h \
	../src/Widgets/choose-dialog-info-interface.cc \
	../src/Widgets/choose-dialog-info-interface.h \
	../src/Widgets/choose-dialog-widget.cc \
	../src/Widgets/choose-dialog-widget-child-base.cc \
	../src/Widgets/choose-dialog-widget-child-base.h \
	../src/Widgets/choose-dialog-widget.h \
	../src/Widgets/ChooseSelectionWidget.cxx \
	../src/Widgets/ChooseSelectionWidget.hxx \
	../src/Widgets/circle-widget.cc \
	../src/Widgets/circle-widget.h \
	../src/Widgets/confirmation-dialog-widget.cc \
	../src/Widgets/confirmation-dialog-widget.h \
	../src/Widgets/counter-stat-widget.cc \
	../src/Widgets/counter-stat-widget.h \
	../src/Widgets/CustomStatWidget.cxx \
	../src/Widgets/CustomStatWidget.hxx \
	../src/Widgets/dialog-widget-base.cc \
	../src/Widgets/dialog-widget-base.h \
	../src/Widgets/EventboxSelectionWidget.cpp \
	../src/Widgets/EventboxSelectionWidget.h \
	../src/Widgets/exit-button-listener.cc \
	../src/Widgets/exit-button-listener.h \
	../src/Widgets/GenderComboBox.cxx \
	../src/Widgets/GenderComboBox.hxx \
	../src/Widgets/help-button-listener.cc \
	../src/Widgets/help-button-listener.h \
	../src/Widgets/HelpExitButtons.cc \
	../src/Widgets/HelpExitButtons.h \
	../src/Widgets/ImageEventBox.cpp \
	../src/Widgets/ImageEventBox.h \
	../src/Widgets/image-selection-widget.cc \
	../src/Widgets/image-selection-widget.h \
	../src/Widgets/ImageViewerFileManager.cpp \
	../src/Widgets/ImageViewerFileManager.h \
	../src/Widgets/ImageViewerWidget.cpp \
	../src/Widgets/ImageViewerWidget.h \
	../src/Widgets/info-widget.cc \
	../src/Widgets/info-widget.h \
	../src/Widgets/ISmartmaticText.cxx \
	../src/Widgets/ISmartmaticText.hxx \
	../src/Widgets/IStatWidget.cxx \
	../src/Widgets/IStatWidget.hxx \
	../src/Widgets/key-board-widget.cc \
	../src/Widgets/key-board-widget.h \
	../src/Widgets/key-board-widget-interface.cc \
	../src/Widgets/key-board-widget-interface.h \
	../src/Widgets/key-code.cc \
	../src/Widgets/key-code.h \
	../src/Widgets/keypad-widget.cc \
	../src/Widgets/keypad-widget.h \
	../src/Widgets/key-pad-widget-interface.cc \
	../src/Widgets/key-pad-widget-interface.h \
	../src/Widgets/keyword-navigation-interface.cc \
	../src/Widgets/keyword-navigation-interface.h \
	../src/Widgets/menu-option.cc \
	../src/Widgets/menu-option.h \
	../src/Widgets/menu-widget-configuration.cc \
	../src/Widgets/menu-widget-configuration.h \
	../src/Widgets/menu-widgetmm.cc \
	../src/Widgets/menu-widgetmm.h \
	../src/Widgets/message-widget.cc \
	../src/Widgets/message-widget.h \
	../src/Widgets/notebook-container.cc \
	../src/Widgets/notebook-container.h \
	../src/Widgets/NumericStatWidget.cxx \
	../src/Widgets/NumericStatWidget.hxx \
	../src/Widgets/operation-key.cc \
	../src/Widgets/operation-key.h \
	../src/Widgets/PreviewArea.cpp \
	../src/Widgets/PreviewArea.h \
	../src/Widgets/RefreshListener.cxx \
	../src/Widgets/RefreshListener.hxx \
	../src/Widgets/RegisterActionWidget.hpp \
	../src/Widgets/RegisterActionWidget.hxx \
	../src/Widgets/RegisterInfoWidget.cxx \
	../src/Widgets/RegisterInfoWidget.hxx \
	../src/Widgets/RegisterWidget.cxx \
	../src/Widgets/RegisterWidget.hxx \
	../src/Widgets/smartmatic-button.cc \
	../src/Widgets/smartmatic-button.h \
	../src/Widgets/smartmatic-combo-box.cc \
	../src/Widgets/smartmatic-combo-box.h \
	../src/Widgets/smartmatic-entry.cc \
	../src/Widgets/smartmatic-entry-date-time.cc \
	../src/Widgets/smartmatic-entry-date-time.h \
	../src/Widgets/smartmatic-entry-divided.cc \
	../src/Widgets/smartmatic-entry-divided.h \
	../src/Widgets/smartmatic-entry.h \
	../src/Widgets/smartmatic-entry-hours.cc \
	../src/Widgets/smartmatic-entry-hours.h \
	../src/Widgets/smartmatic-entry-number.cc \
	../src/Widgets/smartmatic-entry-number.h \
	../src/Widgets/smartmatic-label.cc \
	../src/Widgets/smartmatic-label.h \
	../src/Widgets/SmartmaticTextView.cpp \
	../src/Widgets/SmartmaticTextView.h \
	../src/Widgets/smartmatic-tree-view.cc \
	../src/Widgets/smartmatic-tree-view.h \
	../src/Widgets/StateListener.cxx \
	../src/Widgets/StateListener.hxx \
	../src/Widgets/StatisticWidget.cpp \
	../src/Widgets/StatisticWidget.h \
	../src/Widgets/StepWidget.cxx \
	../src/Widgets/StepWidget.hxx \
	../src/Widgets/StringStatWidget.cxx \
	../src/Widgets/StringStatWidget.hxx \
	../src/Widgets/TableCenterWidget.cxx \
	../src/Widgets/TableCenterWidget.hxx \
	../src/Widgets/TableWidget.cxx \
	../src/Widgets/TableWidget.hxx \
	../src/Widgets/text-view-complex.cc \
	../src/Widgets/text-view-complex.h \
	../src/Widgets/ToolkitElement.cpp \
	../src/Widgets/ToolkitElement.h \
	../src/Widgets/vm-installation-widget.cc \
	../src/Widgets/vm-installation-widget.h \
	../src/Widgets/WizardTimeline.cpp \
	../src/Widgets/WizardTimeline.h \
	../src/Widgets/WizardToolkit.cpp \
	../src/Widgets/WizardToolkit.h \
	../src/Widgets/wizard-widget-base.cc \
	../src/Widgets/wizard-widget-base.h \
	../src/Widgets/WizardWidgetConfiguration.cpp \
	../src/Widgets/WizardWidgetConfiguration.h \
	../src/Widgets/WizardWidget.cpp \
	../src/Widgets/WizardWidget.h \
	../src/Widgets/wizard-widget-manager.cc \
	../src/Widgets/wizard-widget-manager.h \
	../src/Windows/basic-window.cc \
	../src/Windows/basic-window.h \
	../src/Windows/help-item.cc \
	../src/Windows/help-item.h \
	../src/Windows/help-window.cc \
	../src/Windows/help-window.h \
	../src/Windows/password-window.cc \
	../src/Windows/password-window.h \
	../src/Windows/pop-up-message-window.cc \
	../src/Windows/pop-up-message-window.h \
	../ui/base_window.glade \
	../ui/BasicWindow.glade \
	../ui/key-board.glade \
	../ui/keypad.glade \
	../ui/RegisterInfoWidget.glade \
	../ui/vm_installation_confirmation.glade \
	../ui/vm_installation.glade

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
