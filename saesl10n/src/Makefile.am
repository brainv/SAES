CLEANFILES = *~
EXTRA_DIST = LINGUAS
SUBDIRS = \
	election \
	saes \
	saescommon \
	saesfunctionality \
	saesguibase \
	saeshardware \
	smartmatic \
	smartmaticgui

PO_LINGUAS=$(shell if test -r LINGUAS; then grep -v "^\#" LINGUAS; fi)

all-local:
	@for folder in $(SUBDIRS); do \
	  echo "Localization for $$folder project"; \
	  for lang in $(PO_LINGUAS); do \
	    if test -r "$(top_srcdir)/src/$$folder/po/$$lang.po"; then \
	      $(MSGFMT) "$(top_srcdir)/src/$$folder/po/$$lang.po" -o "$(top_srcdir)/src/$$folder/po/$$lang.gmo"; \
	    fi; \
	  done; \
	done

install-data-local: uninstall-local
	@for folder in $(SUBDIRS); do \
	  if test "$$folder" != "election" ; then \
	    project="lib$$folder"; \
	  else \
	  project=$$folder; \
	  fi; \
	  for lang in $(PO_LINGUAS); do \
	    if test -r "$(top_srcdir)/src/$$folder/po/$$lang.gmo"; then \
	      dir=$(DESTDIR)$(LOCALEDIR)/$$lang/LC_MESSAGES; \
	      $(mkdir_p) $$dir; \
	      $(INSTALL_DATA) "$(top_srcdir)/src/$$folder/po/$$lang.gmo" $$dir/$$project.mo; \
	    fi; \
	  done; \
	done

uninstall-local:
	@for folder in $(SUBDIRS); do \
	  if test "$$folder" != "election" ; then \
	    project="lib$$folder"; \
	  else \
	    project=$$folder; \
	  fi; \
	  for lang in $(PO_LINGUAS); do \
	    rm -f $(DESTDIR)$(LOCALEDIR)/$$lang/LC_MESSAGES/$$project.mo; \
	  done; \
	done

