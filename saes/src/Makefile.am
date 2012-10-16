SUBDIRS = Configuration Voting XSDTemplates Resources Printing Exceptions
EXTRA_DIST = libsaes.pc.in ${HEADER_FILES}
CLEANFILES = *~ *.pc ${BUILT_SOURCES}

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
	 
BUILT_SOURCES = \
	generated-images-list \
	election-list \
	voting-devices-list \
	configuration-list \
	vote-list \
	election-status-list \
	voting-machine-status-list \
	card-data-list \
	contingency-card-data-list \
	card-generated-list \
	voting-centers-list \
	pollworkers-list \
	assisted-activation-list \
	close-election-notes-list \
	incident-report-list \
	statistics-list \
	vote-statistics-list \
	activated-card-statistics-list \
	id-card-info-list \
	election-language-list \
	transmission-package-list \
	station-tally-list \
	pvform-list \
	id-card-members-list \
	x7s-codi-file-list \
	voting-disabled-information-list \
	police-notes-list

XSDDIR = $(top_srcdir)/src/XSDTemplates

lib_LTLIBRARIES = libsaes.la
libsaes_la_SOURCES = \
	${BUILT_SOURCES} \
	$(top_srcdir)/src/Voting/ElectoralFactory.cxx \
	$(top_srcdir)/src/Voting/ElectoralConfiguration.cxx \
	$(top_srcdir)/src/Voting/operation-status.cc \
	$(top_srcdir)/src/Voting/Election/ElectionWrapper.cxx \
	$(top_srcdir)/src/Voting/VotingCenters/VotingCentersWrapper.cxx \
	$(top_srcdir)/src/Voting/Vote/VoteWrapper.cxx \
	$(top_srcdir)/src/Voting/Vote/VoteCode.cxx \
	$(top_srcdir)/src/Voting/Vote/VoteEncoder.cpp \
	$(top_srcdir)/src/Voting/Vote/VoteRecovery.cpp \
	$(top_srcdir)/src/Voting/Screen/GeneratedImagesWrapper.cxx \
	$(top_srcdir)/src/Voting/Vote/TransmissionPackageWrapper.cxx \
	$(top_srcdir)/src/Voting/VotingDevice/VotingDeviceWrapper.cxx \
	$(top_srcdir)/src/Voting/VotingDevice/card-data-wrapper.cc \
	$(top_srcdir)/src/Voting/VotingDevice/ContingencyCardDataWrapper.cxx \
	$(top_srcdir)/src/Voting/PBReports/pollworkers-wrapper.cc \
	$(top_srcdir)/src/Voting/PBReports/closing-notes-wrapper.cc \
	$(top_srcdir)/src/Voting/PBReports/incident-report-wrapper.cc \
	$(top_srcdir)/src/Voting/PBReports/id-card-info-wrapper.cc \
	$(top_srcdir)/src/Voting/PBReports/assisted-activation-wrapper.cc \
	$(top_srcdir)/src/Voting/PBReports/vote-statistics.cc \
	$(top_srcdir)/src/Voting/PBReports/VoteStatistic.cxx \
	$(top_srcdir)/src/Voting/PBReports/VotingDisabledWrapper.cxx \
	$(top_srcdir)/src/Voting/PBReports/PoliceNoteWrapper.cxx \
	$(top_srcdir)/src/Voting/PBReports/activated-card-statistics-wrapper.cc \
	$(top_srcdir)/src/Voting/PBReports/StatisticManager.cxx \
	$(top_srcdir)/src/Voting/PBReports/StatisticGroup.cxx \
	$(top_srcdir)/src/Voting/PBReports/StatisticWrapper.cxx \
	$(top_srcdir)/src/Voting/PBReports/PVFormWrapper.cxx \
	$(top_srcdir)/src/Voting/Vote/StationTallyWrapper.cxx \
	$(top_srcdir)/src/Voting/Codi/CodiFormatUtillity.cpp \
	$(top_srcdir)/src/Voting/Codi/CodiFile.cpp \
	$(top_srcdir)/src/Voting/Codi/CodiRegisterBase.cpp \
	$(top_srcdir)/src/Voting/Codi/SelectableCodiRegister.cpp \
	$(top_srcdir)/src/Voting/Codi/CodiRegisterS.cpp \
	$(top_srcdir)/src/Voting/Codi/CodiRegisterL.cpp \
	$(top_srcdir)/src/Voting/Codi/CodiRegisterC.cpp \
	$(top_srcdir)/src/Voting/Codi/CodiFileManager.cxx \
	$(top_srcdir)/src/Voting/Codi/CodiFileManager.hxx \
	$(top_srcdir)/src/Voting/Codi/CodiFileWrapper.cxx \
	$(top_srcdir)/src/Voting/Codi/CodiFileWrapper.hxx \
	$(top_srcdir)/src/Voting/Codi/X7SCodiFileWrapper.cxx \
	$(top_srcdir)/src/Voting/Codi/X7SCodiFileWrapper.hxx \
	$(top_srcdir)/src/Voting/Codi/X7SSecurity.cxx \
	$(top_srcdir)/src/Voting/Codi/X7SSecurity.hxx \
	$(top_srcdir)/src/Voting/Codi/CodiBuffer.cxx \
	$(top_srcdir)/src/Voting/Codi/CodiBuffer.hxx \
	$(top_srcdir)/src/Voting/Codi/CodiInfo.cxx \
	$(top_srcdir)/src/Voting/Codi/CodiInfo.hxx \
	$(top_srcdir)/src/Voting/Status/ElectionStatusWrapper.cxx \
	$(top_srcdir)/src/Voting/Status/VMStatusWrapper.cxx \
	$(top_srcdir)/src/Configuration/s-a-e-s-conf-manager.cc \
	$(top_srcdir)/src/Configuration/saes-language-controller.cc \
	$(top_srcdir)/src/Resources/election-string-resources-manager.cc \
	$(top_srcdir)/src/Resources/election-image-resources-manager.cc \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Election/election-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Election/election-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Codi/x7s-codi-file-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Codi/x7s-codi-file-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote/vote-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote/vote-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote/transmission-package-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote/transmission-package-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote/station-tally-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote/station-tally-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status/election-status-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status/election-status-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status/card-generated-list-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status/card-generated-list-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status/voting-machine-status-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status/voting-machine-status-schema.hxx \
	$(top_srcdir)/src/Configuration/GeneratedClasses/Configuration/SaesConfiguration-schema.cxx \
	$(top_srcdir)/src/Configuration/GeneratedClasses/Configuration/SaesConfiguration-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice/voting-devices-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice/voting-devices-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice/card-data-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice/card-data-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice/contingency-card-data-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice/contingency-card-data-schema.hxx \
	$(top_srcdir)/src/Printing/VotePrintDocument.h \
	$(top_srcdir)/src/Printing/VotePrintDocument.cc \
	$(top_srcdir)/src/Printing/TimeoutPrintDocument.h \
	$(top_srcdir)/src/Printing/TimeoutPrintDocument.cc \
	$(top_srcdir)/src/Printing/SmartcardRemovedPrintDocument.h \
	$(top_srcdir)/src/Printing/SmartcardRemovedPrintDocument.cc \
	$(top_srcdir)/src/Printing/InstallationPrintDocument.h \
	$(top_srcdir)/src/Printing/InstallationPrintDocument.cc \
	$(top_srcdir)/src/Printing/TranslatorTextConfiguration.h \
	$(top_srcdir)/src/Printing/TranslatorTextConfiguration.cc \
	$(top_srcdir)/src/Printing/ReportPrintingController.h \
	$(top_srcdir)/src/Printing/ReportPrintingController.cpp \
	$(top_srcdir)/src/Printing/AuditLogPrintDocument.h \
	$(top_srcdir)/src/Printing/AuditLogPrintDocument.cpp \
	$(top_srcdir)/src/Printing/ErrorLogPrintDocument.h \
	$(top_srcdir)/src/Printing/ErrorLogPrintDocument.cpp \
	$(top_srcdir)/src/Printing/LogPrintDocument.h \
	$(top_srcdir)/src/Printing/LogPrintDocument.cpp \
	$(top_srcdir)/src/Printing/ContingencyCardReport.cpp \
	$(top_srcdir)/src/Printing/ContingencyCardReport.h \
	$(top_srcdir)/src/Printing/TestPrinting.cxx \
	$(top_srcdir)/src/Printing/BarcodePrinting.cxx \
	$(top_srcdir)/src/Printing/BarcodeConfigPrinting.cxx \
	$(top_srcdir)/src/Printing/HelpPrinting.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingCenters/voting-centers-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingCenters/voting-centers-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Screen/generated-images-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Screen/generated-images-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/pollworkers-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/pollworkers-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/statistics-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/statistics-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/vote-statistics-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/vote-statistics-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/assisted-activation-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/assisted-activation-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/close-election-notes-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/close-election-notes-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/id-card-info-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/id-card-info-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/id-card-members-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/id-card-members-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/voting-disabled-information-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/voting-disabled-information-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/police-notes-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/police-notes-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/incident-report-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/incident-report-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/activated-card-statistics-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/activated-card-statistics-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/pvform-schema.cxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports/pvform-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Election/election-language-schema.hxx \
	$(top_srcdir)/src/Voting/GeneratedClasses/Voting/Election/election-language-schema.cxx \
	$(top_srcdir)/src/Voting/Election/ElectionInstalationLanguages.h \
	$(top_srcdir)/src/Voting/Election/ElectionInstalationLanguages.cpp \
	$(top_srcdir)/src/Voting/set-language-functionality.cc \
	$(top_srcdir)/src/Voting/set-language-functionality.h \
	$(top_srcdir)/src/Voting/Status/CardGeneratedListWrapper.cxx \
	$(top_srcdir)/src/Voting/Status/CardGeneratedListWrapper.hxx \
	$(top_srcdir)/src/Exceptions/Voting/Vote/QRVoteInvalidFormatException.h \
	$(top_srcdir)/src/Exceptions/Voting/Vote/QRVoteInvalidFormatException.cpp \
	$(top_srcdir)/src/Exceptions/Voting/Vote/QRVoteSignatureException.h \
	$(top_srcdir)/src/Exceptions/Voting/Vote/QRVoteSignatureException.cpp

libsaes_la_CPPFLAGS = @modules_CFLAGS@ -I$(top_srcdir)/src -I$(top_srcdir)/src/Voting/GeneratedClasses -I$(top_srcdir)/src/Configuration/GeneratedClasses
libsaes_la_LIBADD = @modules_LIBS@ @INTLLIBS@
libsaes_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsaes_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libsaes.pc


election-list: ${XSDDIR}/election-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Election \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::ElectionTypes \
	--anonymous-regex '%.* .* (.+/)*(region)%\u$$2Tag%' \
	--anonymous-regex-trace \
	--enumerator-regex '/(.+)/ELECTION_\U$$1/' \
	--file-list $@ \
	 $<
	 
generated-images-list: ${XSDDIR}/generated-images-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Screen \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::Screen \
	--anonymous-regex '%.* .* (.+/)*(region)%\u$$2Tag%' \
	--anonymous-regex-trace \
	--enumerator-regex '/(.+)/GENERATED_IMAGES_\U$$1/' \
	--file-list $@ \
	 $<

voting-devices-list: ${XSDDIR}/voting-devices-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::VotingDeviceTypes \
	--enumerator-regex '/(.+)/VOTING_DEVICES_\U$$1/' \
	--include-regex %election-language-schema.hxx%Voting/Election/election-language-schema.hxx% \
	--file-list $@ \
	 $<

configuration-list: ${XSDDIR}/SaesConfiguration-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<

vote-list: ${XSDDIR}/vote-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::VoteTypes \
	--enumerator-regex '/(.+)/VOTE_\U$$1/' \
	--anonymous-regex '%.* .* (.+/)*(v)%Vote%' \
	--anonymous-regex '%.* .* (.+/)*(s)%Selection%' \
	--accessor-regex /c/getContest/ --modifier-regex /c/setContest/ \
	--accessor-regex /cs/getContestCodedSelections/ --modifier-regex /cs/setContestCodedSelections/ \
	--accessor-regex /v/getVotingDeviceCode/ --modifier-regex /v/setVotingDeviceCode/ \
	--accessor-regex /l/getLogicalVoterGroup/ --modifier-regex /l/setLogicalVoterGroup/ \
	--accessor-regex /s/getSelections/ --modifier-regex /s/setSelections/ \
	--accessor-regex /b/getBallotOptions/ --modifier-regex /b/setBallotOptions/ \
	--accessor-regex /m/getMode/ --modifier-regex /m/setMode/ \
	--file-list $@ \
	 $<

station-tally-list: ${XSDDIR}/station-tally-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::StationTallyTypes \
	--enumerator-regex '/(.+)/STATION_TALLY_\U$$1/' \
	--anonymous-regex '%.* .* (.+/)*(stn-tly)%StationTally%' \
	--anonymous-regex '%.* .* (.+/)*(r)%Register%' \
	--anonymous-regex '%.* .* (.+/)*(empty-votes)%EmptyVotes%' \
	--anonymous-regex '%.* .* (.+/)*(selected-votes)%SelectedVotes%' \
	--anonymous-regex '%.* .* (.+/)*(codi-checksum)%CodiChecksum%' \
	--anonymous-regex '%.* .* (.+/)*(processed-votes)%ProcessedVotes%' \
	--anonymous-regex '%.* .* (.+/)*(bo)%BallotOption%' \
	--anonymous-regex '%.* .* (.+/)*(t)%Total%' \
	--accessor-regex /r/getRegisters/ --modifier-regex /r/setRegisters/ \
	--accessor-regex /empty-votes/getEmptyVotes/ --modifier-regex /empty-votes/setEmptyVotes/ \
	--accessor-regex /selected-votes/getSelectedVotes/ --modifier-regex /selected-votes/setSelectedVotes/ \
	--accessor-regex /codi-checksum/getCodiChecksum/ --modifier-regex /codi-checksum/setCodiChecksum/ \
	--accessor-regex /processed-votes/getProcessedVotes/ --modifier-regex /processed-votes/setProcessedVotes/ \
	--accessor-regex /bo/getBallotOption/ --modifier-regex /bo/setBallotOption/ \
	--accessor-regex /t/getTotal/ --modifier-regex /t/setTotal/ \
	--accessor-regex /l1/getCountList/ --modifier-regex /l1/setCountList/ \
	--accessor-regex /l2/getCountListP/ --modifier-regex /l2/setCountListP/ \
	--accessor-regex /l3/getCountListPS/ --modifier-regex /l3/setCountListPS/ \
	--accessor-regex /l4/getCountListS/ --modifier-regex /l4/setCountListS/ \
	--accessor-regex /c-sum/getCheckSum/ --modifier-regex /c-sum/setCheckSum/ \
	--file-list $@ \
	 $<

election-status-list: ${XSDDIR}/election-status-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::ElectionStatusTypes \
	--enumerator-regex '/(.+)/ELECTION_STATUS_\U$$1/' \
	--file-list $@ \
	 $<
	 
voting-machine-status-list: ${XSDDIR}/voting-machine-status-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::VMStatusTypes \
	--enumerator-regex '/(.+)/VOTING_MACHINE_STATUS_\U$$1/' \
	--file-list $@ \
	 $<

card-data-list: ${XSDDIR}/card-data-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::CardDataTypes \
	--enumerator-regex '/(.+)/CARD_DATA_\U$$1/' \
	--custom-type custom-attribute \
	--custom-type custom-attributes \
	--custom-type logical-voter-group \
	--custom-type vote=Smartmatic::SAES::Voting::Vote::Vote \
	--custom-type VoteMode=Smartmatic::SAES::Voting::Vote::VoteMode \
	--custom-type s=Smartmatic::SAES::Voting::Vote::Selection \
	--hxx-prologue '#include "voting-devices-schema.hxx"' \
	--hxx-prologue '#include <Voting/Vote/vote-schema.hxx>' \
	--file-list $@ \
	 $<

contingency-card-data-list: ${XSDDIR}/contingency-card-data-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingDevice \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::ContingencyCardDataTypes \
	--enumerator-regex '/(.+)/CONTINGENCY_CARD_DATA_\U$$1/' \
	--file-list $@ \
	 $<

card-generated-list: ${XSDDIR}/card-generated-list-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Status \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::CardDataGeneratedTypes \
	--enumerator-regex '/(.+)/CARD_GENERATED_\U$$1/' \
	--file-list $@ \
	 $<

voting-centers-list: ${XSDDIR}/voting-centers-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/VotingCenters \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::VotingCenters \
	--enumerator-regex '/(.+)/VOTING_CENTER_\U$$1/' \
	--file-list $@ \
	 $<
	 
pollworkers-list: ${XSDDIR}/pollworkers-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/POLLWORKERS_\U$$1/' \
	--custom-type IDCardInfo \
	--custom-type ProcessStatus=Smartmatic::SAES::Voting::Status::ProcessStatus \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--hxx-prologue '#include <Voting/Status/election-status-schema.hxx>' \
	--file-list $@ \
	 $<

id-card-info-list: ${XSDDIR}/id-card-info-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/IDCARDINFO_\U$$1/' \
	--file-list $@ \
	 $<

statistics-list: ${XSDDIR}/statistics-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/STATISTICS_\U$$1/' \
	--file-list $@ \
	 $<
	 
vote-statistics-list: ${XSDDIR}/vote-statistics-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/VOTE_STATISTICS_\U$$1/' \
	--file-list $@ \
	 $<

activated-card-statistics-list: ${XSDDIR}/activated-card-statistics-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/ACTIVATED_CARD_STATISTICS_\U$$1/' \
	--file-list $@ \
	 $<

assisted-activation-list: ${XSDDIR}/assisted-activation-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/ASSISTED_ACTIVATION_\U$$1/' \
	--custom-type IDCardInfo \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--file-list $@ \
	 $<
	 
close-election-notes-list: ${XSDDIR}/close-election-notes-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/CLOSE_NOTES_\U$$1/' \
	--custom-type IDCardInfo \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--file-list $@ \
	 $<
	 
incident-report-list: ${XSDDIR}/incident-report-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/INCIDENT_REPORT_\U$$1/' \
	--custom-type IDCardInfo \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--file-list $@ \
	 $<
	 
election-language-list: ${XSDDIR}/election-language-schema.xsd
	
	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Election \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::ElectionLanguageTypes \
	--enumerator-regex '/(.+)/ELECTION_LANGUAGE_\U$$1/' \
	--custom-type languages \
	--custom-type language \
	--file-list $@ \
	 $<

transmission-package-list: ${XSDDIR}/transmission-package-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Vote \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::TransmissionPackagesTypes \
	--enumerator-regex '/(.+)/TRANSMISSION_\U$$1/' \
	--custom-type vote \
	--custom-type Selection \
	--custom-type VoteMode \
	--custom-type StationTally \
	--custom-type Register \
	--custom-type type \
	--anonymous-regex '%.* .* (.+/)*(s)%Selection%' \
	--anonymous-regex '%.* .* (.+/)*(stn-tly)%StationTally%' \
	--anonymous-regex '%.* .* (.+/)*(r)%Register%' \
	--anonymous-regex '%.* .* (.+/)*(transmission-package)%TransmissionPackage%' \
	--anonymous-regex '%.* .* (.+/)*(stn-tly-pcks)%StationTallyPackages%' \
	--anonymous-regex '%.* .* (.+/)*(stn-tly-pck)%StationTallyPackage%' \
	--anonymous-regex '%.* .* (.+/)*(valid-votes)%ValidVotes%' \
	--anonymous-regex '%.* .* (.+/)*(spoiled-votes)%SpoiledVotes%' \
	--accessor-regex /transmission-package/getTransmissionPackage/ --modifier-regex /transmission-package/setTransmissionPackage/ \
	--accessor-regex /stn-tly-pcks/getStationTallyPackages/ --modifier-regex /stn-tly-pcks/setStationTallyPackages/ \
	--accessor-regex /stn-tly-pck/getStationTallyPackage/ --modifier-regex /stn-tly-pck/setStationTallyPackage/ \
	--accessor-regex /stn-tly/getStationTally/ --modifier-regex /stn-tly/setStationTally/ \
	--accessor-regex /valid-votes/getValidVotes/ --modifier-regex /valid-votes/setValidVotes/ \
	--accessor-regex /spoiled-votes/getSpoiledVotes/ --modifier-regex /spoiled-votes/setSpoiledVotes/ \
	--accessor-regex /v/getVotes/ --modifier-regex /v/setVotes/ \
	--accessor-regex /s-v/getSVotes/ --modifier-regex /s-v/setSVotes/ \
	--hxx-prologue '#include "vote-schema.hxx"' \
	--hxx-prologue '#include "station-tally-schema.hxx"' \
	--file-list $@ \
	 $<

pvform-list: ${XSDDIR}/pvform-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/PVFORM_\U$$1/' \
	--custom-type Statistics \
	--custom-type StatisticType \
	--custom-type StatisticElementType \
	--custom-type Pollworkers \
	--custom-type Worker \
	--custom-type WorkerMemberType \
	--custom-type Workers \
	--custom-type Presidents \
	--custom-type Secretaries \
	--custom-type DeputySecretaries \
	--custom-type Assistents \
	--custom-type Witnesses \
	--custom-type PresidentSubstitutes \
	--custom-type Notes \
	--custom-type Note \
	--custom-type NoteWorkerMemberType \
	--custom-type IDCardInfo \
	--custom-type VoteStatistics \
	--custom-type VotesByCA \
	--custom-type VoteByCA \
	--custom-type IncidentReports \
	--custom-type Reports \
	--custom-type Report \
	--custom-type NamesOfTechnicians \
	--custom-type ActivatedCardStatistics \
	--custom-type ActivatedCardByCA \
	--custom-type AssistedActivations \
	--custom-type ActivatedDemoNonAudioByCA \
	--custom-type ActivatedOfficialAudioByCA \
	--custom-type ActivatedDemoAudioByCA \
	--custom-type ActivatedOfficialNonAudioByCA \
	--custom-type Activations \
	--custom-type Activation \
	--custom-type activationMode \
	--custom-type ActivatedOfficialNonAudioByCA \
	--custom-type CloseElectionNotes \
	--custom-type CloseNotes \
	--custom-type CloseNote \
	--custom-type writer-name \
	--custom-type IDCardMembers \
	--custom-type IDCardInfoType \
	--custom-type VotingDisabledInformation \
	--custom-type VotingDisabled \
	--custom-type VotingDisabledType \
	--custom-type PoliceNotes \
	--custom-type PoliceNote \
	--custom-type ProcessStatus=Smartmatic::SAES::Voting::Status::ProcessStatus \
	--hxx-prologue '#include "activated-card-statistics-schema.hxx"' \
	--hxx-prologue '#include "assisted-activation-schema.hxx"' \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--hxx-prologue '#include "incident-report-schema.hxx"' \
	--hxx-prologue '#include "pollworkers-schema.hxx"' \
	--hxx-prologue '#include "statistics-schema.hxx"' \
	--hxx-prologue '#include "vote-statistics-schema.hxx"' \
	--hxx-prologue '#include "close-election-notes-schema.hxx"' \
	--hxx-prologue '#include "id-card-members-schema.hxx"' \
	--hxx-prologue '#include "voting-disabled-information-schema.hxx"' \
	--hxx-prologue '#include "police-notes-schema.hxx"' \
	--file-list $@ \
	 $<

id-card-members-list: ${XSDDIR}/id-card-members-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--custom-type IDCardInfo \
	--custom-type IDCardInfoType \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--file-list $@ \
	 $<

x7s-codi-file-list: ${XSDDIR}/x7s-codi-file-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/Codi \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::Codi \
	--anonymous-regex '%.* .* (.+/)*(FinalData)%X7SCodiFile%' \
	--anonymous-regex '%.* .* (.+/)*(SignedPV)%PVFile%' \
	--anonymous-regex '%.* .* (.+/)*(DocType)%PVType%' \
	--accessor-regex /FinalData/getX7SCodiFile/ --modifier-regex /FinalData/setX7SCodiFile/ \
	--accessor-regex /SignedPV/getPVFile/ --modifier-regex /SignedPV/setPVFile/ \
	--accessor-regex /DocType/getPVType/ --modifier-regex /DocType/setPVType/ \
	--file-list $@ \
	 $<

voting-disabled-information-list: ${XSDDIR}/voting-disabled-information-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/VOTING_DISABLED_\U$$1/' \
	--custom-type IDCardInfo \
	--custom-type IDCardInfoType \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--file-list $@ \
	 $<

police-notes-list: ${XSDDIR}/police-notes-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Voting/GeneratedClasses/Voting/PBReports \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::SAES::Voting::PBReports \
	--enumerator-regex '/(.+)/POLICE_NOTES_\U$$1/' \
	--custom-type IDCardInfo \
	--custom-type IDCardInfoType \
	--hxx-prologue '#include "id-card-info-schema.hxx"' \
	--file-list $@ \
	 $<


