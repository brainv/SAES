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

GETTEXT_PACKAGE = libsmartmatic
PACKAGE = libsmartmatic
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
install_sh = ${SHELL} /home/smtt/SAES1.4.6/smartmatic/install-sh
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
	../src/Configuration/configuration-persistence-manager.cc \
	../src/Configuration/configuration-persistence-manager.h \
	../src/Configuration/smartmatic-conf-manager.cc \
	../src/Configuration/smartmatic-conf-manager.h \
	../src/Configuration/smartmatic-language-controller.cc \
	../src/Configuration/smartmatic-language-controller.h \
	../src/Environment/Configurations/base-language-controller.cc \
	../src/Environment/Configurations/base-language-controller.h \
	../src/Environment/Configurations/image-resources-manager-base.cc \
	../src/Environment/Configurations/image-resources-manager-base.h \
	../src/Environment/Configurations/resource-path-provider.cc \
	../src/Environment/Configurations/resource-path-provider.h \
	../src/Functionalities/FunctionalityAuthenticationProvider.cpp \
	../src/Functionalities/FunctionalityAuthenticationProvider.h \
	../src/Functionalities/functionality.cc \
	../src/Functionalities/FunctionalityChallengeConfiguration.cpp \
	../src/Functionalities/FunctionalityChallengeConfiguration.h \
	../src/Functionalities/functionality.h \
	../src/Functionalities/functionality-manager.cc \
	../src/Functionalities/functionality-manager.h \
	../src/Functionalities/functionality-manager.hpp \
	../src/Functionalities/menu-option-descriptor.cc \
	../src/Functionalities/menu-option-descriptor.h \
	../src/Functionalities/time-functionality.cc \
	../src/Functionalities/time-functionality.h \
	../src/System/Compression/compression-class.cc \
	../src/System/Compression/compression-class.h \
	../src/System/Encoding/Base64Encoder.cpp \
	../src/System/Encoding/Base64Encoder.h \
	../src/System/Enqueuer.h \
	../src/System/Enqueuer.hpp \
	../src/System/Exception/BaseException.cxx \
	../src/System/Exception/BaseException.hxx \
	../src/System/Exception/CardCanNotWriteException.h \
	../src/System/Exception/CardReaderUnresponsiveException.hxx \
	../src/System/Exception/CodiException.hxx \
	../src/System/Exception/ConfigurationException.hxx \
	../src/System/Exception/CryptoException.hxx \
	../src/System/Exception/ECDSException.cpp \
	../src/System/Exception/ECDSException.h \
	../src/System/Exception/ElectionException.hxx \
	../src/System/Exception/FileSystemException.hxx \
	../src/System/Exception/GuIdException.h \
	../src/System/Exception/InvalidCardContentException.hxx \
	../src/System/Exception/IOCardException.h \
	../src/System/Exception/LoginCardException.h \
	../src/System/Exception/LogReaderException.h \
	../src/System/Exception/MessageDigestException.h \
	../src/System/Exception/PrintOperationException.h \
	../src/System/Exception/QREncodingException.h \
	../src/System/Exception/RSAException.h \
	../src/System/Exception/SecretKeyException.h \
	../src/System/Exception/SignatureAlgorithmKeyException.cpp \
	../src/System/Exception/SignatureAlgorithmKeyException.h \
	../src/System/Exception/SignByCardIDException.h \
	../src/System/Exception/SignedException.hxx \
	../src/System/Exception/StationTallyException.hxx \
	../src/System/Exception/VoteException.hxx \
	../src/System/Exception/VoteRecoveryException.hxx \
	../src/System/Exception/VotingDeviceException.hxx \
	../src/System/Exception/XmlException.hxx \
	../src/System/guid-class.cc \
	../src/System/guid-class.h \
	../src/System/IO/Directory.cc \
	../src/System/IO/Directory.h \
	../src/System/IO/File.cc \
	../src/System/IO/File.h \
	../src/System/IO/Path.cc \
	../src/System/IO/Path.h \
	../src/System/OptParser.cxx \
	../src/System/OptParser.hxx \
	../src/System/Runtime/ProcessLauncher.cpp \
	../src/System/Runtime/ProcessLauncher.h \
	../src/System/Runtime/ProcessMonitor.cpp \
	../src/System/Runtime/ProcessMonitor.h \
	../src/System/SafeBuffer.cpp \
	../src/System/SafeBuffer.h \
	../src/System/Security/CRC32Calculator.cxx \
	../src/System/Security/CRC32Calculator.hxx \
	../src/System/Security/Crypto.cxx \
	../src/System/Security/Cryptography/CertificateValidator.cpp \
	../src/System/Security/Cryptography/CertificateValidator.h \
	../src/System/Security/Cryptography/CertUtil.cpp \
	../src/System/Security/Cryptography/CertUtil.h \
	../src/System/Security/Cryptography/CMSSigner.cxx \
	../src/System/Security/Cryptography/CMSSigner.hxx \
	../src/System/Security/Cryptography/CryptoAES.cxx \
	../src/System/Security/Cryptography/CryptoAES.hxx \
	../src/System/Security/Cryptography/CryptoBase.cxx \
	../src/System/Security/Cryptography/CryptoBase.hxx \
	../src/System/Security/Cryptography/CryptoPKCS12.cxx \
	../src/System/Security/Cryptography/CryptoPKCS12.hxx \
	../src/System/Security/Cryptography/CryptoPKCS7.cxx \
	../src/System/Security/Cryptography/CryptoPKCS7.hxx \
	../src/System/Security/Cryptography/DigestAlgorithmLookup.cpp \
	../src/System/Security/Cryptography/DigestAlgorithmLookup.h \
	../src/System/Security/Cryptography/ECDSASigner.cpp \
	../src/System/Security/Cryptography/ECDSASigner.h \
	../src/System/Security/Cryptography/MsgDigestUtil.cpp \
	../src/System/Security/Cryptography/MsgDigestUtil.h \
	../src/System/Security/Cryptography/PBEKeyDerivatorHMAC.cpp \
	../src/System/Security/Cryptography/PBEKeyDerivatorHMAC.h \
	../src/System/Security/Cryptography/PKCS7Signer.cxx \
	../src/System/Security/Cryptography/PKCS7Signer.hxx \
	../src/System/Security/Cryptography/RsaUtil.cpp \
	../src/System/Security/Cryptography/RsaUtil.h \
	../src/System/Security/Cryptography/SignatureAlgorithm.cpp \
	../src/System/Security/Cryptography/SignatureAlgorithm.h \
	../src/System/Security/Crypto.hxx \
	../src/System/Security/SecurityBase.cxx \
	../src/System/Security/SecurityBase.hxx \
	../src/System/Security/Signed.cxx \
	../src/System/Security/Signed.hxx \
	../src/System/Sounds/beep-descriptor.cc \
	../src/System/Sounds/beep-descriptor.h \
	../src/System/Sounds/beep-manager.cc \
	../src/System/Sounds/beep-manager.h \
	../src/System/Sounds/smartmatic-sounds-manager.cc \
	../src/System/Sounds/smartmatic-sounds-manager.h \
	../src/System/Threading/ThreadSleep.cpp \
	../src/System/Threading/ThreadSleep.h \
	../src/System/Utils/StringUtils.cxx \
	../src/System/Utils/StringUtils.hxx \
	../src/System/XML/DomXml.cxx \
	../src/System/XML/DomXml.hxx \
	../src/System/XML/Serialization/DomWriter.cpp \
	../src/System/XML/Serialization/DomWriter.h \
	../src/System/XSLFO/FOPTransformer.cxx \
	../src/System/XSLFO/FOPTransformer.hxx \
	../src/System/XSLFO/XMLRoffTransformer.cpp \
	../src/System/XSLFO/XMLRoffTransformer.h \
	../src/System/XSLFO/XSLFOTransformer.h \
	../src/System/ZenityWrapper.cxx \
	../src/System/ZenityWrapper.hxx

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
