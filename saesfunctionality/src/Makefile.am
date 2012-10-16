## Process this file with automake to produce Makefile.in

## Created by Anjuta

SUBDIRS = Operation XSDTemplates Configuration
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

lib_LTLIBRARIES = libsaesfunctionality.la

libsaesfunctionality_la_SOURCES = \
	${BUILT_SOURCES} \
	Functionalities/saes-functionality-manager.cc \
	Functionalities/saes-functionality-manager.h \
	Functionalities/saes-functionality.cc \
	Functionalities/saes-functionality.h \
	Functionalities/saes-menu-option-descriptor.cc \
	Functionalities/saes-menu-option-type.cc \
	Configuration/s-a-e-s-functionality-conf-manager.cc \
	Configuration/s-a-e-s-functionality-conf-manager.h \
	Configuration/saes-functionality-language-controller.cc \
	Configuration/saes-functionality-language-controller.h \
	$(top_srcdir)/src/Configuration/GeneratedClasses/Configuration/SaesFunctionalityConfiguration-schema.cxx \
	$(top_srcdir)/src/Operation/Voting/VotingExperienceController.cxx \
	$(top_srcdir)/src/Operation/MachineOperationManager.cxx \
	$(top_srcdir)/src/Operation/PersistSortFile.cxx \
	$(top_srcdir)/src/Operation/Authenticator/IAuthenticator.cxx \
	$(top_srcdir)/src/Operation/Authenticator/PMachineAuthenticator.cxx \
	$(top_srcdir)/src/Operation/Authenticator/VMachineAuthenticator.cxx \
	$(top_srcdir)/src/Operation/Initiator/IMachineInitiator.cxx \
	$(top_srcdir)/src/Operation/Initiator/PMachineInitiator.cxx \
	$(top_srcdir)/src/Operation/Initiator/VMachineInitiator.cxx \
	$(top_srcdir)/src/Operation/Voting/VotingMemento.cxx \
	$(top_srcdir)/src/Operation/Voting/VotingOriginator.cxx \
	$(top_srcdir)/src/Operation/Voting/VotingState.cxx \
	$(top_srcdir)/src/Operation/Card/CardController.cxx \
	$(top_srcdir)/src/Operation/Card/CardMonitor.cxx \
	$(top_srcdir)/src/Operation/Alarm/AlarmController.cxx \
	$(top_srcdir)/src/Operation/Alarm/AlarmBoxMonitor.cxx \
	$(top_srcdir)/src/Operation/Card/SmartCardController.cxx \
	$(top_srcdir)/src/Operation/Card/MemoryCardController.cxx \
	$(top_srcdir)/src/Operation/Security/CryptoCard.cxx \
	$(top_srcdir)/src/Operation/Security/CryptoSmartCard.cxx \
	$(top_srcdir)/src/Operation/Security/CryptoMemoryCard.cxx \
	$(top_srcdir)/src/Operation/Security/CryptoContingencyMemoryCard.cxx \
	$(top_srcdir)/src/Operation/Security/CryptoToken.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/IDiagnosis.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/AlarmBoxDiagnosis.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/BarCodeDiagnosis.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/SmartCardReaderDiagnosis.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/PrinterDiagnosis.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/FlashDiagnosis.cxx \
	$(top_srcdir)/src/Operation/Diagnosis/CalibrationDiagnosis.cxx \
	$(top_srcdir)/src/Operation/BCR/BCRController.cxx \
	$(top_srcdir)/src/Operation/SaesEnqueuer.h \
	$(top_srcdir)/src/Operation/SaesEnqueuer.cc \
	$(top_srcdir)/src/Operation/Voting/FillVote.cxx \
	$(top_srcdir)/src/Operation/InstallMachine.cxx
	
libsaesfunctionality_la_CPPFLAGS = \
	-I$(top_srcdir)/src/Configuration/GeneratedClasses \
	$(modules_CFLAGS)

libsaesfunctionality_la_LIBADD = \
	$(modules_LIBS) @INTLLIBS@

libsaesfunctionality_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsaesfunctionality_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

saesfuncincludedir= $(includedir)/saesfunctionality
nobase_saesfuncinclude_HEADERS = \
	Functionalities/saes-functionality.h \
	Configuration/s-a-e-s-functionality-conf-manager.h \
	Configuration/saes-functionality-language-controller.h \
	Functionalities/saes-functionality-manager.h \
	Functionalities/saes-menu-option-type.h \
	Functionalities/saes-menu-option-descriptor.h \
	Operation/SaesEnqueuer.h 

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libsaesfunctionality.pc

EXTRA_DIST = \
	libsaesfunctionality.pc.in


configuration-list: ${XSDDIR}/SaesFunctionalityConfiguration-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<

