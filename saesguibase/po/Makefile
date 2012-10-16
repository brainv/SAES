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

GETTEXT_PACKAGE = libsaesguibase
PACKAGE = libsaesguibase
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
install_sh = ${SHELL} /home/smtt/SAES1.4.6/saesguibase/install-sh
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
	../src/Configuration/s-a-e-s-g-u-i-conf-manager.cc \
	../src/Configuration/s-a-e-s-g-u-i-conf-manager.h \
	../src/Configuration/saes-gui-image-resources-manager.cc \
	../src/Configuration/saes-gui-image-resources-manager.h \
	../src/Configuration/saes-gui-language-controller.cc \
	../src/Configuration/saes-gui-language-controller.h \
	../src/Functionalities/ActivationConsolidationFunctionality.cpp \
	../src/Functionalities/ActivationConsolidationFunctionality.h \
	../src/Functionalities/alarm-box-diagnosis-functionality.cc \
	../src/Functionalities/alarm-box-diagnosis-functionality.h \
	../src/Functionalities/all-diagnosis-functionality.cc \
	../src/Functionalities/all-diagnosis-functionality.h \
	../src/Functionalities/assisted-card-generator-functionality.cc \
	../src/Functionalities/assisted-card-generator-functionality.h \
	../src/Functionalities/barcode-diagnosis-functionality.cc \
	../src/Functionalities/barcode-diagnosis-functionality.h \
	../src/Functionalities/brightness-diagnosis-functionality.cc \
	../src/Functionalities/brightness-diagnosis-functionality.h \
	../src/Functionalities/calibration-diagnosis-functionality.cc \
	../src/Functionalities/calibration-diagnosis-functionality.h \
	../src/Functionalities/card-generator-functionality.cc \
	../src/Functionalities/card-generator-functionality.h \
	../src/Functionalities/change-hour-functionality.cc \
	../src/Functionalities/change-hour-functionality.h \
	../src/Functionalities/change-language-functionality.cc \
	../src/Functionalities/change-language-functionality.h \
	../src/Functionalities/close-election-functionality.cc \
	../src/Functionalities/close-election-functionality.h \
	../src/Functionalities/close-votation-functionality.cc \
	../src/Functionalities/close-votation-functionality.h \
	../src/Functionalities/DataUtilsValidatorFunctionality.cxx \
	../src/Functionalities/DataUtilsValidatorFunctionality.hxx \
	../src/Functionalities/diagnosis-functionality.cc \
	../src/Functionalities/diagnosis-functionality.h \
	../src/Functionalities/FillAssistedActivationInfoFunctionality.cpp \
	../src/Functionalities/FillAssistedActivationInfoFunctionality.h \
	../src/Functionalities/flash-diagnosis-functionality.cc \
	../src/Functionalities/flash-diagnosis-functionality.h \
	../src/Functionalities/graphic-display-functionality.h \
	../src/Functionalities/graphic-display-functionality.hpp \
	../src/Functionalities/incident-report-functionality.cc \
	../src/Functionalities/incident-report-functionality.h \
	../src/Functionalities/LogReportFunctionality.cc \
	../src/Functionalities/LogReportFunctionality.h \
	../src/Functionalities/open-election-functionality.cc \
	../src/Functionalities/open-election-functionality.h \
	../src/Functionalities/PoliceNotesFunctionality.cxx \
	../src/Functionalities/PoliceNotesFunctionality.hxx \
	../src/Functionalities/poll-worker-register-functionality.cc \
	../src/Functionalities/poll-worker-register-functionality.h \
	../src/Functionalities/printer-diagnosis-functionality.cc \
	../src/Functionalities/printer-diagnosis-functionality.h \
	../src/Functionalities/print-preview-functionality.cc \
	../src/Functionalities/print-preview-functionality.h \
	../src/Functionalities/Providers/PresidentPassPhraseAuthenticationProvider.cpp \
	../src/Functionalities/Providers/PresidentPassPhraseAuthenticationProvider.h \
	../src/Functionalities/Providers/RoleAuthenticationProvider.cpp \
	../src/Functionalities/Providers/RoleAuthenticationProvider.h \
	../src/Functionalities/recovery-card-generator-functionality.cc \
	../src/Functionalities/recovery-card-generator-functionality.h \
	../src/Functionalities/register-president-notes-functionality.cc \
	../src/Functionalities/register-president-notes-functionality.h \
	../src/Functionalities/ReportPrintingFunctionality.cpp \
	../src/Functionalities/ReportPrintingFunctionality.h \
	../src/Functionalities/s-c-reader-diagnosis-functionality.cc \
	../src/Functionalities/s-c-reader-diagnosis-functionality.h \
	../src/Functionalities/ShutdownMachineFunctionality.cpp \
	../src/Functionalities/ShutdownMachineFunctionality.h \
	../src/Functionalities/statistics-report-functionality.cc \
	../src/Functionalities/statistics-report-functionality.h \
	../src/Functionalities/vote-consolidation-functionality.cc \
	../src/Functionalities/vote-consolidation-functionality.h \
	../src/Functionalities/vote-demo-functionality.cc \
	../src/Functionalities/vote-demo-functionality.h \
	../src/Functionalities/voting-experience-validation-functionality.cpp \
	../src/Functionalities/voting-experience-validation-functionality.h \
	../src/Functionalities/VotingForDisabledFunctionality.cxx \
	../src/Functionalities/VotingForDisabledFunctionality.hxx \
	../src/Functionalities/voting-machine-installation-functionality.cc \
	../src/Functionalities/voting-machine-installation-functionality.h \
	../src/Gui/Widgets/AbstractFactoryWidget.cxx \
	../src/Gui/Widgets/AbstractFactoryWidget.hxx \
	../src/Gui/Widgets/ActivationStatsWidget.cpp \
	../src/Gui/Widgets/ActivationStatsWidget.h \
	../src/Gui/Widgets/activator-card-counter-widget.cc \
	../src/Gui/Widgets/activator-card-counter-widget.h \
	../src/Gui/Widgets/alarm-box-diagnosis-widget.cc \
	../src/Gui/Widgets/alarm-box-diagnosis-widget.h \
	../src/Gui/Widgets/assisted-activation-add-widget.cc \
	../src/Gui/Widgets/assisted-activation-add-widget.h \
	../src/Gui/Widgets/assisted-activation-id-card-widget.cc \
	../src/Gui/Widgets/assisted-activation-id-card-widget.h \
	../src/Gui/Widgets/assisted-activation-id-card-widget-view.cc \
	../src/Gui/Widgets/assisted-activation-id-card-widget-viewer.cc \
	../src/Gui/Widgets/assisted-activation-id-card-widget-viewer.h \
	../src/Gui/Widgets/assisted-activation-id-card-widget-view.h \
	../src/Gui/Widgets/assisted-activation-impugnation-widget.cc \
	../src/Gui/Widgets/assisted-activation-impugnation-widget.h \
	../src/Gui/Widgets/assisted-activation-manager-widget.cc \
	../src/Gui/Widgets/assisted-activation-manager-widget.h \
	../src/Gui/Widgets/assisted-activation-question-widget.cc \
	../src/Gui/Widgets/assisted-activation-question-widget.h \
	../src/Gui/Widgets/assisted-activation-view-widget.cc \
	../src/Gui/Widgets/assisted-activation-view-widget.h \
	../src/Gui/Widgets/AssistedActivationWidget.cpp \
	../src/Gui/Widgets/AssistedActivationWidget.h \
	../src/Gui/Widgets/AuthenticationWidget.cxx \
	../src/Gui/Widgets/AuthenticationWidget.hxx \
	../src/Gui/Widgets/AutomaticDiagnosticWidget.cxx \
	../src/Gui/Widgets/AutomaticDiagnosticWidget.hxx \
	../src/Gui/Widgets/BallotOptionButtonWidget.cxx \
	../src/Gui/Widgets/BallotOptionButtonWidget.hxx \
	../src/Gui/Widgets/ballot-option-selection-widget.cc \
	../src/Gui/Widgets/ballot-option-selection-widget.h \
	../src/Gui/Widgets/BallotOptionTableWidget.cxx \
	../src/Gui/Widgets/BallotOptionTableWidget.hxx \
	../src/Gui/Widgets/ballot-option-widget.cc \
	../src/Gui/Widgets/ballot-option-widget.h \
	../src/Gui/Widgets/BarcodeDetectionWidget.cpp \
	../src/Gui/Widgets/BarcodeDetectionWidget.h \
	../src/Gui/Widgets/bar-code-diagnosis-widget.cc \
	../src/Gui/Widgets/bar-code-diagnosis-widget.h \
	../src/Gui/Widgets/basic-diagnostic-widget.cc \
	../src/Gui/Widgets/basic-diagnostic-widget.h \
	../src/Gui/Widgets/BeidErrorWidget.cxx \
	../src/Gui/Widgets/BeidErrorWidget.hxx \
	../src/Gui/Widgets/BeidWidget.cpp \
	../src/Gui/Widgets/BeidWidget.h \
	../src/Gui/Widgets/brightness-diagnosis-widget.cc \
	../src/Gui/Widgets/brightness-diagnosis-widget.h \
	../src/Gui/Widgets/calibration-diagnosis-widget.cc \
	../src/Gui/Widgets/calibration-diagnosis-widget.h \
	../src/Gui/Widgets/CardActivatorEventBox.cpp \
	../src/Gui/Widgets/CardActivatorEventBox.h \
	../src/Gui/Widgets/change-language-widget.cc \
	../src/Gui/Widgets/change-language-widget.h \
	../src/Gui/Widgets/close-election-confirmation-widget.cc \
	../src/Gui/Widgets/close-election-confirmation-widget.h \
	../src/Gui/Widgets/close-election-status-widget.cc \
	../src/Gui/Widgets/close-election-status-widget.h \
	../src/Gui/Widgets/combo-box-choose-widget.cc \
	../src/Gui/Widgets/combo-box-choose-widget.h \
	../src/Gui/Widgets/complex-ballot-option-widget.cc \
	../src/Gui/Widgets/complex-ballot-option-widget.h \
	../src/Gui/Widgets/confirmation-delete-widget.cc \
	../src/Gui/Widgets/confirmation-delete-widget.h \
	../src/Gui/Widgets/ConsolidationStatsWidget.cpp \
	../src/Gui/Widgets/ConsolidationStatsWidget.h \
	../src/Gui/Widgets/ContingencyCardGenWidget.cpp \
	../src/Gui/Widgets/ContingencyCardGenWidget.h \
	../src/Gui/Widgets/ContingencyWidget.cxx \
	../src/Gui/Widgets/ContingencyWidget.hxx \
	../src/Gui/Widgets/custom-attributes-combo-selections-widget.cc \
	../src/Gui/Widgets/custom-attributes-combo-selections-widget.h \
	../src/Gui/Widgets/custom-attributes-counter-widget.cc \
	../src/Gui/Widgets/custom-attributes-counter-widget.h \
	../src/Gui/Widgets/DataUtilsResultWidget.cxx \
	../src/Gui/Widgets/DataUtilsResultWidget.hxx \
	../src/Gui/Widgets/DataUtilsValidatorWidget.cxx \
	../src/Gui/Widgets/DataUtilsValidatorWidget.hxx \
	../src/Gui/Widgets/DeviceResultWidget.cxx \
	../src/Gui/Widgets/DeviceResultWidget.hxx \
	../src/Gui/Widgets/DiagnosisBlockedWidget.cxx \
	../src/Gui/Widgets/DiagnosisBlockedWidget.hxx \
	../src/Gui/Widgets/DiagnosticResultWidget.cxx \
	../src/Gui/Widgets/DiagnosticResultWidget.hxx \
	../src/Gui/Widgets/duration-verification-widget.cc \
	../src/Gui/Widgets/duration-verification-widget.h \
	../src/Gui/Widgets/event-box-choose-widget.cc \
	../src/Gui/Widgets/event-box-choose-widget.h \
	../src/Gui/Widgets/FactoryMethodWidget.cxx \
	../src/Gui/Widgets/FactoryMethodWidget.hxx \
	../src/Gui/Widgets/FillTableColumnDynamicWidget.cxx \
	../src/Gui/Widgets/FillTableColumnDynamicWidget.hxx \
	../src/Gui/Widgets/FillTableColumnFixedWidget.cxx \
	../src/Gui/Widgets/FillTableColumnFixedWidget.hxx \
	../src/Gui/Widgets/FillTableWidget.cxx \
	../src/Gui/Widgets/FillTableWidget.hxx \
	../src/Gui/Widgets/flash-diagnosis-widget.cc \
	../src/Gui/Widgets/flash-diagnosis-widget.h \
	../src/Gui/Widgets/generate-pv-report-widget.cc \
	../src/Gui/Widgets/generate-pv-report-widget.h \
	../src/Gui/Widgets/HelpWidget.cxx \
	../src/Gui/Widgets/HelpWidget.hxx \
	../src/Gui/Widgets/id-card-widget.cc \
	../src/Gui/Widgets/id-card-widget-close-election.cc \
	../src/Gui/Widgets/id-card-widget-close-election.h \
	../src/Gui/Widgets/IDCardWidgetCloseVotation.cxx \
	../src/Gui/Widgets/IDCardWidgetCloseVotation.hxx \
	../src/Gui/Widgets/id-card-widget.h \
	../src/Gui/Widgets/id-card-widget-open-election.cc \
	../src/Gui/Widgets/id-card-widget-open-election.h \
	../src/Gui/Widgets/id-card-widget-pm-install.cc \
	../src/Gui/Widgets/id-card-widget-pm-install.h \
	../src/Gui/Widgets/IDCardWidgetVMInstall.cxx \
	../src/Gui/Widgets/IDCardWidgetVMInstall.hxx \
	../src/Gui/Widgets/InfoMessageWidget.cxx \
	../src/Gui/Widgets/InfoMessageWidget.hxx \
	../src/Gui/Widgets/InfoStepWidget.cxx \
	../src/Gui/Widgets/InfoStepWidget.hxx \
	../src/Gui/Widgets/InitiatorWidget.cxx \
	../src/Gui/Widgets/InitiatorWidget.hxx \
	../src/Gui/Widgets/InstallMachineWidget.cxx \
	../src/Gui/Widgets/InstallMachineWidget.hxx \
	../src/Gui/Widgets/LanguageInstallWidget.cxx \
	../src/Gui/Widgets/LanguageInstallWidget.hxx \
	../src/Gui/Widgets/ListResultWidget.cxx \
	../src/Gui/Widgets/ListResultWidget.hxx \
	../src/Gui/Widgets/LoginWidget.cxx \
	../src/Gui/Widgets/LoginWidget.hxx \
	../src/Gui/Widgets/LogPagingTreeViewWidget.cc \
	../src/Gui/Widgets/LogPagingTreeViewWidget.h \
	../src/Gui/Widgets/LogTreeViewWidget.cc \
	../src/Gui/Widgets/LogTreeViewWidget.h \
	../src/Gui/Widgets/MachineVotingWidget.cxx \
	../src/Gui/Widgets/MachineVotingWidget.hxx \
	../src/Gui/Widgets/MachineWizardWidget.cxx \
	../src/Gui/Widgets/MachineWizardWidget.hxx \
	../src/Gui/Widgets/MemoryStateWidget.cxx \
	../src/Gui/Widgets/MemoryStateWidget.hxx \
	../src/Gui/Widgets/MenuWidget.cxx \
	../src/Gui/Widgets/MenuWidget.hxx \
	../src/Gui/Widgets/OpenElectionStatusWidget.cxx \
	../src/Gui/Widgets/OpenElectionStatusWidget.hxx \
	../src/Gui/Widgets/OpenNoteWidget.cxx \
	../src/Gui/Widgets/OpenNoteWidget.hxx \
	../src/Gui/Widgets/PartyButtonWidget.cxx \
	../src/Gui/Widgets/PartyButtonWidget.hxx \
	../src/Gui/Widgets/party-contest-viewer-widget.cc \
	../src/Gui/Widgets/party-contest-viewer-widget.h \
	../src/Gui/Widgets/party-contest-widget.cc \
	../src/Gui/Widgets/party-contest-widget.h \
	../src/Gui/Widgets/party-contest-zoom-widget.cc \
	../src/Gui/Widgets/party-contest-zoom-widget.h \
	../src/Gui/Widgets/party-selection-widget.cc \
	../src/Gui/Widgets/party-selection-widget.h \
	../src/Gui/Widgets/party-widget.cc \
	../src/Gui/Widgets/party-widget.h \
	../src/Gui/Widgets/PersistAllResultWidget.cxx \
	../src/Gui/Widgets/PersistAllResultWidget.hxx \
	../src/Gui/Widgets/PersistCodiFilesWidget.cxx \
	../src/Gui/Widgets/PersistCodiFilesWidget.hxx \
	../src/Gui/Widgets/persist-transmission-package-widget.cc \
	../src/Gui/Widgets/persist-transmission-package-widget.h \
	../src/Gui/Widgets/PMAuthenticationPollingPlaceInfoWidget.cxx \
	../src/Gui/Widgets/PMAuthenticationPollingPlaceInfoWidget.hxx \
	../src/Gui/Widgets/PMAuthenticationWidget.cxx \
	../src/Gui/Widgets/PMAuthenticationWidget.hxx \
	../src/Gui/Widgets/PMInstallMachineWidget.cxx \
	../src/Gui/Widgets/PMInstallMachineWidget.hxx \
	../src/Gui/Widgets/PMPollingPlaceInfoWidget.cxx \
	../src/Gui/Widgets/PMPollingPlaceInfoWidget.hxx \
	../src/Gui/Widgets/PMProgressWidget.cxx \
	../src/Gui/Widgets/PMProgressWidget.hxx \
	../src/Gui/Widgets/PollingPlaceInfoWidget.cxx \
	../src/Gui/Widgets/PollingPlaceInfoWidget.hxx \
	../src/Gui/Widgets/printer-diagnosis-widget.cc \
	../src/Gui/Widgets/printer-diagnosis-widget.h \
	../src/Gui/Widgets/print-pv-report-widget.cc \
	../src/Gui/Widgets/print-pv-report-widget.h \
	../src/Gui/Widgets/ProgressWidget.cxx \
	../src/Gui/Widgets/ProgressWidget.hxx \
	../src/Gui/Widgets/radio-button-choose-widget.cc \
	../src/Gui/Widgets/radio-button-choose-widget.h \
	../src/Gui/Widgets/recovery-card-generator-widget.cc \
	../src/Gui/Widgets/recovery-card-generator-widget.h \
	../src/Gui/Widgets/referendum-selection-widget.cc \
	../src/Gui/Widgets/referendum-selection-widget.h \
	../src/Gui/Widgets/referendum-widget.cc \
	../src/Gui/Widgets/referendum-widget.h \
	../src/Gui/Widgets/ReportInstallWidget.cxx \
	../src/Gui/Widgets/ReportInstallWidget.hxx \
	../src/Gui/Widgets/ReportLogWidget.cc \
	../src/Gui/Widgets/ReportLogWidget.h \
	../src/Gui/Widgets/report-printing-close-widget.cc \
	../src/Gui/Widgets/report-printing-close-widget.h \
	../src/Gui/Widgets/ReportPrintingWidget.cpp \
	../src/Gui/Widgets/ReportPrintingWidget.h \
	../src/Gui/Widgets/ResultWidget.cxx \
	../src/Gui/Widgets/ResultWidget.hxx \
	../src/Gui/Widgets/RunMachineWidget.cxx \
	../src/Gui/Widgets/RunMachineWidget.hxx \
	../src/Gui/Widgets/select-language-widget.cc \
	../src/Gui/Widgets/select-language-widget.h \
	../src/Gui/Widgets/sign-election-resource-widget.cc \
	../src/Gui/Widgets/sign-election-resource-widget.h \
	../src/Gui/Widgets/sign-transmission-package-widget.cc \
	../src/Gui/Widgets/sign-transmission-package-widget.h \
	../src/Gui/Widgets/smart-card-reader-diagnosis-widget.cc \
	../src/Gui/Widgets/smart-card-reader-diagnosis-widget.h \
	../src/Gui/Widgets/VMAuthenticationPollingPlaceInfoWidget.cxx \
	../src/Gui/Widgets/VMAuthenticationPollingPlaceInfoWidget.hxx \
	../src/Gui/Widgets/VMAuthenticationWidget.cxx \
	../src/Gui/Widgets/VMAuthenticationWidget.hxx \
	../src/Gui/Widgets/VMInstallationConfirmation.cxx \
	../src/Gui/Widgets/VMInstallationConfirmation.hxx \
	../src/Gui/Widgets/VMInstallMachineWidget.cxx \
	../src/Gui/Widgets/VMInstallMachineWidget.hxx \
	../src/Gui/Widgets/VMPollingPlaceInfoWidget.cxx \
	../src/Gui/Widgets/VMPollingPlaceInfoWidget.hxx \
	../src/Gui/Widgets/VMProgressWidget.cxx \
	../src/Gui/Widgets/VMProgressWidget.hxx \
	../src/Gui/Widgets/Voting/CardRemovedWidget.cxx \
	../src/Gui/Widgets/Voting/CardRemovedWidget.hxx \
	../src/Gui/Widgets/Voting/contest-null-selection-widget.cc \
	../src/Gui/Widgets/Voting/contest-null-selection-widget.h \
	../src/Gui/Widgets/Voting/custom-attribute-widget.cc \
	../src/Gui/Widgets/Voting/custom-attribute-widget.h \
	../src/Gui/Widgets/Voting/EndPrintVoteWidget.cxx \
	../src/Gui/Widgets/Voting/EndPrintVoteWidget.hxx \
	../src/Gui/Widgets/Voting/EndVotingWidget.cxx \
	../src/Gui/Widgets/Voting/EndVotingWidget.hxx \
	../src/Gui/Widgets/Voting/FactoryVotingWidget.cxx \
	../src/Gui/Widgets/Voting/FactoryVotingWidget.hxx \
	../src/Gui/Widgets/voting-frame-base.cc \
	../src/Gui/Widgets/voting-frame-base.h \
	../src/Gui/Widgets/Voting/InterruptVotingWidget.cxx \
	../src/Gui/Widgets/Voting/InterruptVotingWidget.hxx \
	../src/Gui/Widgets/Voting/InterruptWidget.cxx \
	../src/Gui/Widgets/Voting/InterruptWidget.hxx \
	../src/Gui/Widgets/Voting/KeypadVotingPasswordWidget.cxx \
	../src/Gui/Widgets/Voting/KeypadVotingPasswordWidget.hxx \
	../src/Gui/Widgets/Voting/language-selection-widget.cc \
	../src/Gui/Widgets/Voting/language-selection-widget.h \
	../src/Gui/Widgets/voting-machine-installation-wizard-widget.cc \
	../src/Gui/Widgets/voting-machine-installation-wizard-widget.h \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteInfoWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteInfoWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteRegisterInfoWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteRegisterInfoWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteRegisterWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteRegisterWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/CloseNoteWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/incident-report-dialog-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/incident-report-dialog-widget.h \
	../src/Gui/Widgets/Voting/PBReports/incident-report-tree-view.cc \
	../src/Gui/Widgets/Voting/PBReports/incident-report-tree-view.h \
	../src/Gui/Widgets/Voting/PBReports/incident-report-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/incident-report-widget.h \
	../src/Gui/Widgets/Voting/PBReports/note-statistics-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/note-statistics-widget.h \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteInfoWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteInfoWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteRegisterInfoWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteRegisterInfoWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteRegisterWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteRegisterWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/PoliceNoteWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-id-card-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-id-card-widget.h \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-member-register-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-member-register-widget.h \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-member-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-member-widget.h \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-note-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/poll-worker-note-widget.h \
	../src/Gui/Widgets/Voting/PBReports/statistic-counter-register-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/statistic-counter-register-widget.h \
	../src/Gui/Widgets/Voting/PBReports/statistic-counter-widget.cc \
	../src/Gui/Widgets/Voting/PBReports/statistic-counter-widget.h \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledInfoWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledInfoWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledQuestionWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledQuestionWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledRegisterInfoWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledRegisterInfoWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledRegisterWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledRegisterWidget.hxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledWidget.cxx \
	../src/Gui/Widgets/Voting/PBReports/VotingForDisabledWidget.hxx \
	../src/Gui/Widgets/Voting/PreviewWidget.cxx \
	../src/Gui/Widgets/Voting/PreviewWidget.hxx \
	../src/Gui/Widgets/Voting/PrintTimeOutWidget.cxx \
	../src/Gui/Widgets/Voting/PrintTimeOutWidget.hxx \
	../src/Gui/Widgets/Voting/PrintVoteErrorWidget.cxx \
	../src/Gui/Widgets/Voting/PrintVoteErrorWidget.hxx \
	../src/Gui/Widgets/Voting/PrintVoteWidget.cxx \
	../src/Gui/Widgets/Voting/PrintVoteWidget.hxx \
	../src/Gui/Widgets/Voting/question-selection-widget.cc \
	../src/Gui/Widgets/Voting/question-selection-widget.h \
	../src/Gui/Widgets/Voting/RemoveCardWidget.cxx \
	../src/Gui/Widgets/Voting/RemoveCardWidget.hxx \
	../src/Gui/Widgets/Voting/ScreenVotingWidget.cxx \
	../src/Gui/Widgets/Voting/ScreenVotingWidget.hxx \
	../src/Gui/Widgets/Voting/selection-widget-base.cc \
	../src/Gui/Widgets/Voting/selection-widget-base.h \
	../src/Gui/Widgets/Voting/SimulationWidget.cxx \
	../src/Gui/Widgets/Voting/SimulationWidget.hxx \
	../src/Gui/Widgets/Voting/super-null-selection-widget.cc \
	../src/Gui/Widgets/Voting/super-null-selection-widget.h \
	../src/Gui/Widgets/Voting/TimeOutPreviewWidget.cxx \
	../src/Gui/Widgets/Voting/TimeOutPreviewWidget.hxx \
	../src/Gui/Widgets/Voting/VotePreviewWidget.cxx \
	../src/Gui/Widgets/Voting/VotePreviewWidget.hxx \
	../src/Gui/Widgets/Voting/vote-statistics-widget.cc \
	../src/Gui/Widgets/Voting/vote-statistics-widget.h \
	../src/Gui/Widgets/Voting/VotingExperienceValidationWidget.cxx \
	../src/Gui/Widgets/Voting/VotingExperienceValidationWidget.hxx \
	../src/Gui/Widgets/Voting/VotingExperienceWidget.cxx \
	../src/Gui/Widgets/Voting/VotingExperienceWidget.hxx \
	../src/Gui/Widgets/Voting/WaitingForCardWidget.cxx \
	../src/Gui/Widgets/Voting/WaitingForCardWidget.hxx \
	../src/Gui/Widgets/Voting/welcome-message-widget.cc \
	../src/Gui/Widgets/Voting/welcome-message-widget.h \
	../src/Gui/Widgets/voting-widget-base.cc \
	../src/Gui/Widgets/voting-widget-base.h \
	../src/Gui/Windows/choose-option-window.cc \
	../src/Gui/Windows/choose-option-window.h \
	../src/Gui/Windows/empty-window.cc \
	../src/Gui/Windows/empty-window.h \
	../src/Gui/Windows/initial-calib-window.cc \
	../src/Gui/Windows/initial-calib-window.h \
	../src/Gui/Windows/language-selection-window.cc \
	../src/Gui/Windows/language-selection-window.h \
	../src/Gui/Windows/menu-window.cc \
	../src/Gui/Windows/menu-window.h \
	../src/Gui/Windows/PMWindow.cxx \
	../src/Gui/Windows/PMWindow.hxx \
	../src/Gui/Windows/RunMachineWindow.cxx \
	../src/Gui/Windows/RunMachineWindow.hxx \
	../src/Gui/Windows/VMWindow.cxx \
	../src/Gui/Windows/VMWindow.hxx \
	../src/Gui/Windows/voting-machine-installation-wizard-window.cc \
	../src/Gui/Windows/voting-machine-installation-wizard-window.h \
	../src/Operation/AlarmMessage.cxx \
	../src/Operation/AlarmMessage.hxx \
	../src/Operation/authenticator-user-rol.cc \
	../src/Operation/authenticator-user-rol.h \
	../src/Operation/FormatLabel.cxx \
	../src/Operation/FormatLabel.hxx \
	../src/Operation/functionality-initiator.cc \
	../src/Operation/functionality-initiator.h \
	../src/Operation/GenerateXMLImage.cpp \
	../src/Operation/GenerateXMLImage.h \
	../src/Operation/ValidateWidget.cxx \
	../src/Operation/ValidateWidget.hxx \
	../src/Operation/Voting/VotingOperation.cxx \
	../src/Operation/Voting/VotingOperation.hxx \
	../src/Operation/Voting/VotingWidgetManager.cxx \
	../src/Operation/Voting/VotingWidgetManager.hxx \
	../ui/alarmbox-diagnostic.glade \
	../ui/all-diagnostics-result.glade \
	../ui/assisted-card-activator.glade \
	../ui/authentication-win.glade \
	../ui/auto-calib.glade \
	../ui/ballot-option-selection-widget.glade \
	../ui/BallotOptionSeparateButtonWidget.glade \
	../ui/ballot-option-widget.glade \
	../ui/barcode-diagnostic.glade \
	../ui/calibrate_brightness.glade \
	../ui/calibration_diagnosis.glade \
	../ui/calibration_failure.glade \
	../ui/calibration_success.glade \
	../ui/card-activator.glade \
	../ui/change-hour.glade \
	../ui/ContingencyCardGenWidget.glade \
	../ui/ContingencyWidget.glade \
	../ui/DeviceResultWidget.glade \
	../ui/DiagnosisBlockedWidget.glade \
	../ui/DiagnosticResultWidget.glade \
	../ui/HelpWidget.glade \
	../ui/InfoMessageWidget.glade \
	../ui/InterruptVotingWidget.glade \
	../ui/LoginWidget.glade \
	../ui/MemoryStateWidget.glade \
	../ui/PagingTreeViewWidget.glade \
	../ui/PMAuthenticationWidget.glade \
	../ui/preview-in-waiting-widget.glade \
	../ui/printer-diagnostic.glade \
	../ui/ProgressWidget.glade \
	../ui/recovery-card-activator.glade \
	../ui/ReportLogWidget.glade \
	../ui/ReportPrintingWidget.glade \
	../ui/ResultWidget.glade \
	../ui/show_brightness.glade \
	../ui/VMAuthenticationWidget.glade \
	../ui/vm_installation_confirmation.glade \
	../ui/vote-consolidation-functionality.glade \
	../ui/vote-preview-functionality.glade \
	../ui/vote-process-demo.glade \
	../ui/voting-experience-validation.glade \
	../ui/VotingExperienceValidationWidget.glade \
	../ui/VotingForDisabledIDInfoWidget.glade \
	../ui/VotingForDisabledInfoWidget.glade \
	../ui/VotingForDisabledQuestionWidget.glade \
	../ui/WaitingForCardWidget.glade

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
