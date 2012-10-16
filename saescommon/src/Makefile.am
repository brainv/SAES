## Process this file with automake to produce Makefile.in

## Created by Anjuta
SUBDIRS = XSDTemplates Configuration Resources Security
CLEANFILES = *~ *.pc ${BUILT_SOURCES}

BUILT_SOURCES = \
	configuration-list \
	strings-resources-list

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

lib_LTLIBRARIES = libsaescommon.la

libsaescommon_la_SOURCES = \
	${BUILT_SOURCES} \
	Configuration/GeneratedClasses/Configuration/SaesCommonConfiguration-schema.cxx \
	Resources/string-resources-manager-base.h \
	Resources/string-resources-manager-base.cc \
	Configuration/s-a-e-s-common-conf-manager.cc \
	Configuration/s-a-e-s-common-conf-manager.h \
	Configuration/saes-common-language-controller.cc \
	Configuration/saes-common-language-controller.h \
	Resources/GeneratedClasses/Resources/strings-resources-schema.cxx \
	Runtime/Environment/filename-hasher.h \
	Runtime/Environment/filename-hasher.cc \
	Runtime/Environment/saes-directories.h \
	Runtime/Environment/saes-directories.cc \
	Runtime/Environment/SaesInstallDirectories.hxx \
	Runtime/Environment/SaesInstallDirectories.cxx \
	Runtime/Environment/SaesProgramUnitDirectories.hxx \
	Runtime/Environment/SaesProgramUnitDirectories.cxx \
	Runtime/Environment/EnvironmentBuilder.hxx \
	Runtime/Environment/EnvironmentBuilder.cxx \
	Printing/BasePrintDocument.h \
	Printing/BasePrintDocument.cpp \
	Printing/DirectPrintingBackend.h \
	Printing/DirectPrintingBackend.cpp \
	Printing/LPSpooler.h \
	Printing/LPSpooler.cpp \
	Printing/PrinterTwoColumnsElement.h \
	Printing/PrinterTwoColumnsElement.cc \
	Printing/DocumentOptions.h \
	Printing/DocumentOptions.cpp \
	Printing/printer-element.h \
	Printing/printer-element.cc \
	Printing/printer-client.cc \
    Printing/printer-client.h \
    Printing/printer-status.cc \
    Printing/printer-status.h \
	Printing/GraphicContextPrintingBackend.h \
	Printing/GraphicContextPrintingBackend.cpp \
	Printing/IPrintingBackend.h \
	Printing/IPrintingBackend.cpp \
	Printing/PrinterStatusNotifier.h \
	Printing/PrinterStatusNotifier.cpp \
	Printing/PrintDocumentResult.h \
	Printing/PrintDocumentResult.cpp \
	Printing/PrintPreviewWidget.h \
	Printing/PrintPreviewWidget.cpp \
	Printing/GraphicContentPage.h \
	Printing/GraphicContentPage.cpp \
	Printing/PrintDocumentClient.h \
	Security/SecretKey.h \
	Security/SecretKey.cpp \
	$(top_srcdir)/src/Operation/Initiator/CheckDirectoryStructure.cxx \
	$(top_srcdir)/src/Operation/Initiator/CheckFilesPresence.cxx \
	$(top_srcdir)/src/Operation/Initiator/ICheckCondition.cxx \
	$(top_srcdir)/src/Operation/Initiator/InitializationStatus.cxx \
	$(top_srcdir)/src/Voting/IStateWrapper.cxx \
	Runtime/Environment/saes-temporal-directories.h \
	Runtime/Environment/saes-temporal-directories.cc \
	$(top_srcdir)/src/Runtime/Environment/DirectoryManager.cxx \
	$(top_srcdir)/src/Runtime/Environment/DirectoryManager.hxx \
	$(top_srcdir)/src/Operation/Initiator/CheckFlashPresence.cxx \
	$(top_srcdir)/src/Operation/Initiator/CheckFlashPresence.hxx \
	$(top_srcdir)/src/Operation/Initiator/CheckFlashStructure.cxx \
	$(top_srcdir)/src/Operation/Initiator/CheckFlashStructure.hxx \
	$(top_srcdir)/src/Security/Encryption.cxx \
	$(top_srcdir)/src/Security/XmlSecResource.cxx \
	$(top_srcdir)/src/Security/CryptoData.cxx \
	$(top_srcdir)/src/eid/pkcs11/cryptoki.h \
	$(top_srcdir)/src/eid/pkcs11/pkcs11.h \
	$(top_srcdir)/src/eid/pkcs11/pkcs11f.h \
	$(top_srcdir)/src/eid/pkcs11/pkcs11t.h \
	$(top_srcdir)/src/eid/beidlib/eidlib.h \
	$(top_srcdir)/src/eid/beidlib/eidlibdefines.h \
	$(top_srcdir)/src/eid/beidlib/eidlibException.h \
	$(top_srcdir)/src/eid/CitizenInfo.cpp \
	$(top_srcdir)/src/eid/CitizenInfo.h \
	$(top_srcdir)/src/eid/EIDManager.cxx \
	$(top_srcdir)/src/eid/EIDManager.hxx \
	$(top_srcdir)/src/eid/EIDPin.cxx \
	$(top_srcdir)/src/eid/EIDPin.hxx \
	$(top_srcdir)/src/eid/EIDRead.cxx \
	$(top_srcdir)/src/eid/EIDRead.hxx \
	$(top_srcdir)/src/eid/EIDSign.cxx \
	$(top_srcdir)/src/eid/EIDSign.hxx \
	$(top_srcdir)/src/eid/EIDUtils.cxx \
	$(top_srcdir)/src/eid/EIDUtils.hxx \
	$(top_srcdir)/src/eid/EIDEvent.cxx \
	$(top_srcdir)/src/eid/EIDEvent.hxx \
	$(top_srcdir)/src/eid/EIDEventInterface.hxx \
	Log/LogReader.cc \
	Log/LogReader.h \
	Log/LogPage.cc \
	Log/LogPage.h \
	Log/LogLine.cc \
	Log/LogLine.h \
	Log/LogBasePath.cxx \
	Log/LogBasePath.hxx \
	Log/LogCryptoBase64.cxx \
	Log/LogCryptoBase64.hxx \
	Log/LogCryptoGlobal.cxx \
	Log/LogCryptoGlobal.hxx \
	Log/LogCryptoPool.cxx \
	Log/LogCryptoPool.hxx \
	Runtime/Environment/MemoryPathController.h \
	Runtime/Environment/MemoryPathController.cpp \
	Runtime/Environment/MemoryInfo.h \
	Runtime/Environment/MemoryInfo.cpp \
	Runtime/Environment/MasterMemoryParser.h \
	Runtime/Environment/MasterMemoryParser.cpp \
	Runtime/Environment/MemoryEventParser.h \
	Runtime/Environment/MemoryEventParser.cpp \
	Operation/Initiator/CheckForUsedMemory.h \
	Operation/Initiator/CheckForUsedMemory.cpp \
	Operation/Initiator/CheckForMemoryComplete.h \
	Operation/Initiator/CheckForMemoryComplete.cpp \
	Card/ICardController.hxx \
	Card/ICardController.cxx \
	Card/SaesSmartCard.hxx \
	Card/SaesSmartCard.cxx \
	Card/SmartCardCommand.hxx \
	Card/SmartCardCommand.cxx \
	Card/SmartCard.hxx \
	Card/SmartCard.cxx \
	Card/SmartcardConnected.h \
	Card/SmartcardConnected.cpp \
	pcscd/PCSCDManager.hxx \
	pcscd/PCSCDManager.cxx

libsaescommon_la_CPPFLAGS = -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/Configuration/GeneratedClasses \
	-I$(top_srcdir)/src/Resources/GeneratedClasses \
	$(modules_CFLAGS)

libsaescommon_la_LIBADD = \
	$(modules_LIBS) @INTLLIBS@

libsaescommon_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsaescommon_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

saescommonincludedir= $(includedir)/saescommon
nobase_saescommoninclude_HEADERS = \
	Resources/string-resources-manager-base.h \
	Configuration/s-a-e-s-common-conf-manager.h \
	Configuration/saes-common-language-controller.h \
	Runtime/Environment/saes-directories.h \
	Runtime/Environment/saes-temporal-directories.h \
	Runtime/Environment/SaesInstallDirectories.hxx \
	Runtime/Environment/SaesProgramUnitDirectories.hxx \
	Runtime/Environment/EnvironmentBuilder.hxx \
	Runtime/Environment/filename-hasher.h \
	Printing/BasePrintDocument.h \
	Printing/DirectPrintingBackend.h \
	Printing/LPSpooler.h \
	Printing/PrinterTwoColumnsElement.h \
	Printing/DocumentOptions.h \
	Printing/PrinterStatusNotifier.h \
	Printing/PrintDocumentResult.h \
	Operation/Initiator/CheckDirectoryStructure.hxx \
	Operation/Initiator/CheckFilesPresence.hxx \
	Operation/Initiator/ICheckCondition.hxx \
	Operation/Initiator/InitializationStatus.hxx \
	Voting/IStateWrapper.hxx \
	Printing/IPrintingBackend.h \
	Printing/GraphicContextPrintingBackend.h \
	Printing/PrintPreviewWidget.h \
	Printing/PrintDocumentClient.h \
	Printing/GraphicContentPage.h \
    Printing/printer-status.h \
    Printing/printer-client.h \
    Runtime/Environment/DirectoryManager.hxx \
    Operation/Initiator/CheckFlashPresence.hxx \
	Operation/Initiator/CheckFlashStructure.hxx \
	eid/CitizenInfo.h \
	eid/EIDManager.hxx \
	eid/EIDEventInterface.hxx \
	Log/LogReader.h \
	Log/LogLine.h \
	Log/LogPage.h \
	Log/LogBasePath.hxx \
	Log/LogCryptoPool.hxx \
	Runtime/Environment/MemoryPathController.h \
	Runtime/Environment/MemoryInfo.h \
	Runtime/Environment/MasterMemoryParser.h \
	Runtime/Environment/MemoryEventParser.h \
	Operation/Initiator/CheckForUsedMemory.h \
	Operation/Initiator/CheckForMemoryComplete.h \
	Card/ICardController.hxx \
	Card/SmartCard.hxx \
	pcscd/PCSCDManager.hxx

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libsaescommon.pc

EXTRA_DIST = \
	libsaescommon.pc.in

configuration-list: ${XSDDIR}/SaesCommonConfiguration-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<

strings-resources-list: ${XSDDIR}/strings-resources-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Resources/GeneratedClasses/Resources \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ResourcesTypes \
	--enumerator-regex '/(.+)/STRING_RESOURCES_\U$$1/' \
	--file-list $@ \
	 $<


