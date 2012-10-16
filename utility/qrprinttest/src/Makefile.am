## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(QRPRINTTEST_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = qrprinttest

qrprinttest_SOURCES = \
    QrTestMainWindow.cpp \
    QRTestController.cpp \
    QRTestPrintDocument.cpp \
    QRTestWidget.cpp \
    main.cc

qrprinttest_LDFLAGS = 

qrprinttest_LDADD = $(QRPRINTTEST_LIBS)


