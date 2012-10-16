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


lib_LTLIBRARIES = libsmartmaticgui.la

libsmartmaticgui_la_SOURCES = \
	${BUILT_SOURCES} \
	Windows/help-item.cc \
	Windows/help-item.h \
	Windows/help-window.cc \
	Windows/help-window.h \
	Widgets/smartmatic-button.h \
	Widgets/smartmatic-button.cc \
	Widgets/keypad-widget.cc \
	Widgets/keypad-widget.h \
	Widgets/key-pad-widget-interface.cc \
	Widgets/key-pad-widget-interface.h \
	Widgets/menu-option.cc \
	Widgets/menu-option.h \
	Widgets/menu-widgetmm.cc \
	Widgets/menu-widgetmm.h \
	Widgets/menu-widget-configuration.cc \
	Widgets/menu-widget-configuration.h \
	Widgets/keyword-navigation-interface.cc \
	Widgets/keyword-navigation-interface.h \
	Widgets/operation-key.cc \
	Widgets/operation-key.h \
	Widgets/key-code.cc \
	Widgets/key-code.h \
	Configuration/s-m-t-t-g-u-i-conf-manager.h \
	Configuration/s-m-t-t-g-u-i-conf-manager.cc \
	Configuration/smartmaticgui-language-controller.h \
	Configuration/smartmaticgui-language-controller.cc \
	$(top_srcdir)/src/Configuration/GeneratedClasses/Configuration/SmartmaticGUIConfiguration-schema.cxx \
	$(top_srcdir)/src/Widgets/StepWidget.hxx \
	$(top_srcdir)/src/Widgets/StepWidget.cxx \
	$(top_srcdir)/src/Widgets/RefreshListener.hxx \
	$(top_srcdir)/src/Widgets/RefreshListener.cxx \
	$(top_srcdir)/src/Widgets/StateListener.cxx \
	$(top_srcdir)/src/Widgets/StateListener.hxx \
	Windows/basic-window.h \
	Windows/basic-window.cc \
	Windows/password-window.h \
	Windows/password-window.cc \
	Widgets/banner-widget.h \
	Widgets/banner-widget.cc \
	Widgets/exit-button-listener.h \
	Widgets/exit-button-listener.cc \
	Widgets/help-button-listener.h \
	Widgets/help-button-listener.cc \
	Widgets/info-widget.h \
	Widgets/info-widget.cc \
	Graphics/Encoding2D/QREncoding.h \
	Graphics/Encoding2D/QREncoding.cc \
	Widgets/choose-dialog-button-info.h \
	Widgets/choose-dialog-button-info.cc \
	Widgets/choose-dialog-info-interface.h \
	Widgets/choose-dialog-info-interface.cc \
	Widgets/choose-dialog-info.h \
	Widgets/choose-dialog-info.cc \
	Widgets/choose-dialog-widget.h \
	Widgets/choose-dialog-widget.cc \
	Widgets/smartmatic-label.cc \
	Widgets/smartmatic-label.h \
	Widgets/vm-installation-widget.h \
	Widgets/vm-installation-widget.cc \
	Widgets/key-board-widget.h \
	Widgets/key-board-widget.cc \
	Widgets/key-board-widget-interface.h \
	Widgets/key-board-widget-interface.cc \
	Widgets/confirmation-dialog-widget.h \
	Widgets/confirmation-dialog-widget.cc \
	Widgets/dialog-widget-base.h \
	Widgets/dialog-widget-base.cc \
	Widgets/message-widget.h \
	Widgets/message-widget.cc \
	Widgets/image-selection-widget.h \
	Widgets/image-selection-widget.cc \
	Widgets/choose-dialog-widget-child-base.h \
	Widgets/choose-dialog-widget-child-base.cc \
	Configuration/smtt-gui-image-resource-manager.h \
	Configuration/smtt-gui-image-resource-manager.cc \
	Configuration/label-configuration.h \
	Configuration/label-configuration.cc \
	Widgets/circle-widget.h \
	Widgets/circle-widget.cc \
	Windows/pop-up-message-window.h \
	Windows/pop-up-message-window.cc \
	Widgets/smartmatic-tree-view.h \
	Widgets/smartmatic-tree-view.cc \
	Widgets/smartmatic-entry.h \
	Widgets/smartmatic-entry.cc \
	Widgets/smartmatic-combo-box.h \
	Widgets/smartmatic-combo-box.cc \
	Widgets/text-view-complex.h \
	Widgets/text-view-complex.cc \
	Widgets/counter-stat-widget.h \
	Widgets/counter-stat-widget.cc \
	Graphics/Capture/PrintScreenManager.h \
	Graphics/Capture/PrintScreenManager.cpp \
	Graphics/Image/Compose.cxx \
	Graphics/Image/Compose.hxx \
	Graphics/Image/CheckImageFile.cxx \
	Graphics/Image/CheckImageFile.hxx \
	Widgets/PreviewArea.cpp \
	Widgets/PreviewArea.h \
	Widgets/ImageEventBox.cpp \
	Widgets/ImageEventBox.h \
	Widgets/ImageViewerWidget.cpp \
	Widgets/ImageViewerWidget.h \
	Widgets/ImageViewerFileManager.h \
	Widgets/ImageViewerFileManager.cpp \
	Widgets/smartmatic-entry-date-time.h \
	Widgets/smartmatic-entry-date-time.cc \
	Widgets/smartmatic-entry-hours.h \
	Widgets/smartmatic-entry-hours.cc \
	Widgets/smartmatic-entry-number.h \
	Widgets/smartmatic-entry-number.cc \
	Widgets/wizard-widget-base.h \
	Widgets/wizard-widget-base.cc \
	Widgets/wizard-widget-manager.h \
	Widgets/wizard-widget-manager.cc \
	Widgets/notebook-container.h \
	Widgets/notebook-container.cc \
	Widgets/smartmatic-entry-divided.h \
	Widgets/smartmatic-entry-divided.cc \
	Widgets/WizardWidget.h \
	Widgets/WizardWidget.cpp \
	Widgets/WizardWidgetConfiguration.h \
	Widgets/WizardWidgetConfiguration.cpp \
	Widgets/WizardToolkit.h \
	Widgets/WizardToolkit.cpp \
	Widgets/WizardTimeline.h \
	Widgets/WizardTimeline.cpp \
	Widgets/ToolkitElement.h \
	Widgets/ToolkitElement.cpp \
	Widgets/HelpExitButtons.h \
	Widgets/HelpExitButtons.cc \
	Widgets/SmartmaticTextView.cpp \
	Widgets/SmartmaticTextView.h \
	Widgets/EventboxSelectionWidget.h \
	Widgets/EventboxSelectionWidget.cpp \
	Widgets/StatisticWidget.h \
	Widgets/StatisticWidget.cpp \
	$(top_srcdir)/src/Operation/WindowsManager.hxx \
	$(top_srcdir)/src/Operation/WindowsManager.cxx \
	$(top_srcdir)/src/Widgets/ChooseSelectionWidget.cxx \
	$(top_srcdir)/src/Widgets/ChooseSelectionWidget.hxx \
	$(top_srcdir)/src/Widgets/TableWidget.cxx \
	$(top_srcdir)/src/Widgets/TableWidget.hxx \
	$(top_srcdir)/src/Widgets/TableCenterWidget.cxx \
	$(top_srcdir)/src/Widgets/TableCenterWidget.hxx \
	$(top_srcdir)/src/Widgets/ButtonsWidget.cxx \
	$(top_srcdir)/src/Widgets/ButtonsWidget.hxx \
	$(top_srcdir)/src/Widgets/IStatWidget.cxx \
	$(top_srcdir)/src/Widgets/IStatWidget.hxx \
	$(top_srcdir)/src/Widgets/NumericStatWidget.cxx \
	$(top_srcdir)/src/Widgets/NumericStatWidget.hxx \
	$(top_srcdir)/src/Widgets/CustomStatWidget.cxx \
	$(top_srcdir)/src/Widgets/CustomStatWidget.hxx \
	$(top_srcdir)/src/Widgets/BoolStatWidget.cxx \
	$(top_srcdir)/src/Widgets/BoolStatWidget.hxx \
	$(top_srcdir)/src/Widgets/StringStatWidget.cxx \
	$(top_srcdir)/src/Widgets/StringStatWidget.hxx \
	$(top_srcdir)/src/Widgets/RegisterWidget.cxx \
	$(top_srcdir)/src/Widgets/RegisterWidget.hxx \
	$(top_srcdir)/src/Widgets/RegisterActionWidget.hxx \
	$(top_srcdir)/src/Widgets/RegisterActionWidget.hpp \
	$(top_srcdir)/src/Widgets/RegisterInfoWidget.cxx \
	$(top_srcdir)/src/Widgets/RegisterInfoWidget.hxx \
	$(top_srcdir)/src/Widgets/ISmartmaticText.hxx \
	$(top_srcdir)/src/Widgets/ISmartmaticText.cxx \
	$(top_srcdir)/src/Widgets/GenderComboBox.cxx \
	$(top_srcdir)/src/Widgets/GenderComboBox.hxx

libsmartmaticgui_la_CPPFLAGS = \
	-I$(top_srcdir)/src                                \
	-I$(top_srcdir)/src/Configuration/GeneratedClasses \
	$(modules_CFLAGS)

libsmartmaticgui_la_LIBADD = \
	$(modules_LIBS) @INTLLIBS@

libsmartmaticgui_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsmartmaticgui_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

smttguiincludedir= $(includedir)/smartmaticgui
nobase_smttguiinclude_HEADERS = \
	Windows/help-item.h \
	Widgets/smartmatic-button.h \
	Widgets/smartmatic-entry-hours.h \
	Widgets/keypad-widget.h \
	Widgets/key-pad-widget-interface.h \
	Widgets/menu-widgetmm.h \
	Widgets/menu-option.h \
	Widgets/menu-widget-configuration.h \
	Widgets/operation-key.h \
	Widgets/key-code.h \
	Widgets/banner-widget.h \
	Widgets/info-widget.h \
	Widgets/exit-button-listener.h \
	Widgets/help-button-listener.h \
	Widgets/choose-dialog-button-info.h \
	Widgets/choose-dialog-info-interface.h \
	Widgets/choose-dialog-info.h \
	Widgets/choose-dialog-widget.h \
	Widgets/keyword-navigation-interface.h \
	Configuration/s-m-t-t-g-u-i-conf-manager.h \
	Configuration/smartmaticgui-language-controller.h \
	Configuration/smtt-gui-image-resource-manager.h \
	Windows/basic-window.h \
	Windows/password-window.h \
	Graphics/Encoding2D/QREncoding.h \
	Graphics/Image/Compose.hxx \
	Widgets/smartmatic-label.h \
	Widgets/vm-installation-widget.h \
	Widgets/key-board-widget.h \
	Widgets/key-board-widget-interface.h \
	Widgets/dialog-widget-base.h \
	Widgets/confirmation-dialog-widget.h \
	Widgets/message-widget.h \
	Widgets/image-selection-widget.h \
	Widgets/choose-dialog-widget-child-base.h \
	Widgets/circle-widget.h \
	Windows/pop-up-message-window.h \
	Widgets/smartmatic-tree-view.h \
	Widgets/smartmatic-combo-box.h \
	Widgets/smartmatic-entry.h \
	Widgets/smartmatic-entry-date-time.h \
	Widgets/smartmatic-entry-number.h \
	Widgets/text-view-complex.h \
	Widgets/counter-stat-widget.h \
	Configuration/label-configuration.h \
	Widgets/wizard-widget-base.h \
	Widgets/wizard-widget-manager.h \
	Graphics/Capture/PrintScreenManager.h \
	Widgets/notebook-container.h \
	Widgets/smartmatic-entry-divided.h \
	Widgets/WizardWidget.h \
	Widgets/WizardWidgetConfiguration.h \
	Widgets/WizardToolkit.h \
	Widgets/WizardTimeline.h \
	Widgets/ToolkitElement.h \
	Widgets/HelpExitButtons.h \
	Widgets/SmartmaticTextView.h \
	Widgets/EventboxSelectionWidget.h \
	Widgets/StatisticWidget.h \
	Widgets/StepWidget.hxx \
	Widgets/RefreshListener.hxx \
	Widgets/StateListener.hxx \
	Operation/WindowsManager.hxx \
	Widgets/ChooseSelectionWidget.hxx \
	Widgets/TableWidget.hxx \
	Widgets/TableCenterWidget.hxx \
	Widgets/ButtonsWidget.hxx \
	Widgets/IStatWidget.hxx \
	Widgets/NumericStatWidget.hxx \
	Widgets/CustomStatWidget.hxx \
	Widgets/BoolStatWidget.hxx \
	Widgets/StringStatWidget.hxx \
	Widgets/RegisterWidget.hxx \
	Widgets/RegisterActionWidget.hxx \
	Widgets/RegisterActionWidget.hpp \
	Widgets/RegisterInfoWidget.hxx \
	Widgets/ISmartmaticText.hxx \
	Widgets/GenderComboBox.hxx \
	Graphics/Image/CheckImageFile.hxx

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libsmartmaticgui.pc

EXTRA_DIST = \
libsmartmaticgui.pc.in


configuration-list: ${XSDDIR}/SmartmaticGUIConfiguration-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<


