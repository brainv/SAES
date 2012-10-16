## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/cryptotest/ui
ui_DATA = cryptotest.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(CRYPTOTEST_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = cryptotest

cryptotest_SOURCES = \
	main.cc \
	CryptoTestForm.h \
	CryptoTestForm.cpp\
	PBETestController.h \
	PBETestController.cpp \
	SigantureTestController.h \
	SigantureTestController.cpp \
	SymmetricCipherTestController.h \
	SymmetricCipherTestController.cpp \
	CertificateValidationController.h \
	CertificateValidationController.cpp \
	CFEncryptorController.h \
	CFEncryptorController.cpp \
	RsaController.h \
	RsaController.cpp \
	CFEncryptor.h \
	CFEncryptor.cpp

cryptotest_LDFLAGS = 

cryptotest_LDADD = $(CRYPTOTEST_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/cryptotest
