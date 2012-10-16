## Process this file with automake to produce Makefile.in

## Created by Anjuta
SUBDIRS = XSDTemplates Configuration
CLEANFILES = *~ *.pc ${BUILT_SOURCES}

BUILT_SOURCES = \
	configuration-list

XSDDIR = $(top_srcdir)/src/XSDTemplates

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(modules_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g \
	 -Werror

lib_LTLIBRARIES = libsaeshardware.la

libsaeshardware_la_SOURCES = \
	${BUILT_SOURCES} \
	Connections/i-connection.cc \
	Connections/i-connection.h \
	Connections/serial-port-connection.cc \
	Connections/serial-port-connection.h \
	Commands/command-structure.cc \
	Commands/command-structure.h \
	Commands/command-base-alarm.h \
	Commands/command-base-alarm.cc\
	Devices/alarm-device.h \
	Devices/alarm-device.cc \
	Configuration/GeneratedClasses/Configuration/SaesHardwareConfiguration-schema.cxx \
	Devices/i-m-t-5123-card-reader.h \
	Devices/i-m-t-5123-card-reader.cc \
	Devices/a-u9520-card-reader.h \
	Devices/a-u9520-card-reader.cc \
	Configuration/s-a-e-s-hardware-conf-manager.h \
	Configuration/s-a-e-s-hardware-conf-manager.cc \
	Configuration/saes-hardware-language-controller.h \
	Configuration/saes-hardware-language-controller.cc \
	Commands/alarm-red-led-command.h \
	Commands/alarm-red-led-command.cc \
	Commands/alarm-green-led-command.h \
	Commands/alarm-green-led-command.cc \
	Commands/alarm-buzzer-command.h \
	Commands/alarm-buzzer-command.cc \
	Commands/alarm-ping-command.h \
	Commands/alarm-ping-command.cc \
	Devices/barcode-device.h \
	Devices/barcode-device.cc \
	Commands/command-base-barcode.h \
	Commands/command-base-barcode.cc \
	Commands/barcode-enter-serial-program-command.h \
	Commands/barcode-enter-serial-program-command.cc \
	Devices/p168-a-device.h \
	Devices/p168-a-device.cc \
	Commands/command-base-p168-a.h \
	Commands/command-base-p168-a.cc \
	Commands/p168-a-bright-command.h \
	Commands/p168-a-bright-command.cc \
	Devices/athena-card-reader.cc \
	Devices/athena-card-reader.h \
	Devices/smart-card-reader.cc \
	Devices/smart-card-reader.h \
	Devices/SerialPathManager.cxx \
	Devices/SerialPathManager.hxx \
	Devices/SerialPathDevice.cxx \
	Devices/SerialPathDevice.hxx \
	Commands/BarcodeCommandWrapper.cpp \
	Commands/BarcodeCommandWrapper.h

libsaeshardware_la_CPPFLAGS = @modules_CFLAGS@ -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/Configuration/GeneratedClasses \
	$(modules_CFLAGS)
libsaeshardware_la_LIBADD = @modules_LIBS@ \
	$(modules_LIBS) @INTLLIBS@
	
libsaeshardware_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsaeshardware_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

saeshwincludedir= $(includedir)/saeshardware
nobase_saeshwinclude_HEADERS = \
	Connections/i-connection.h \
	Connections/serial-port-connection.h \
	Commands/command-base-alarm.h \
	Commands/command-base-p168-a.h \
	Commands/p168-a-bright-command.h \
	Configuration/s-a-e-s-hardware-conf-manager.h \
	Configuration/saes-hardware-language-controller.h \
	Commands/command-structure.h \
	Devices/alarm-device.h \
	Devices/i-m-t-5123-card-reader.h \
	Devices/a-u9520-card-reader.h \
	Devices/athena-card-reader.h \
	Devices/smart-card-reader.h \
	Devices/barcode-device.h \
	Devices/p168-a-device.h \
	Commands/alarm-red-led-command.h \
	Commands/alarm-green-led-command.h \
	Commands/alarm-ping-command.h \
	Commands/command-base-barcode.h \
	Commands/barcode-enter-serial-program-command.h \
	Commands/alarm-buzzer-command.h \
	Commands/BarcodeCommandWrapper.h
	
	
pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libsaeshardware.pc

EXTRA_DIST = \
	libsaeshardware.pc.in


configuration-list: ${XSDDIR}/SaesHardwareConfiguration-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<

