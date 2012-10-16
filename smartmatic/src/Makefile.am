## Process this file with automake to produce Makefile.in

## Created by Anjuta
SUBDIRS = System XSDTemplates Configuration
CLEANFILES = *~ *.pc ${BUILT_SOURCES}

BUILT_SOURCES = \
	configuration-list \
	configuration-base-list

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


lib_LTLIBRARIES = libsmartmatic.la

libsmartmatic_la_SOURCES = \
	${BUILT_SOURCES} \
	Functionalities/functionality.cc \
	Functionalities/functionality.h \
	Functionalities/functionality-manager.cc \
	Functionalities/functionality-manager.h \
	Functionalities/functionality-manager.hpp \
	Configuration/configuration-persistence-manager.h \
	Configuration/configuration-persistence-manager.cc \
	Configuration/smartmatic-conf-manager.h \
	Configuration/smartmatic-conf-manager.cc \
	Configuration/smartmatic-language-controller.h \
	Configuration/smartmatic-language-controller.cc \
	Environment/Configurations/base-language-controller.h \
	Environment/Configurations/base-language-controller.cc \
	$(top_srcdir)/src/Configuration/GeneratedClasses/Configuration/ConfigurationBase-schema.cxx \
	$(top_srcdir)/src/Configuration/GeneratedClasses/Configuration/SmartmaticConfiguration-schema.cxx \
	Environment/Configurations/resource-path-provider.h \
	Environment/Configurations/resource-path-provider.cc \
	System/IO/Path.h \
	System/IO/Path.cc \
	System/IO/Directory.h \
	System/IO/Directory.cc \
	System/IO/File.h \
	System/IO/File.cc \
	$(top_srcdir)/src/System/Exception/BaseException.cxx \
	System/Exception/SecretKeyException.h \
	System/Exception/QREncodingException.h \
	System/Exception/LoginCardException.h \
	System/Exception/GuIdException.h \
	System/Compression/compression-class.h \
	System/Compression/compression-class.cc \
	System/guid-class.h \
	System/guid-class.cc \
	Functionalities/menu-option-descriptor.h \
	Functionalities/menu-option-descriptor.cc \
	System/XML/Serialization/DomWriter.h \
	System/XML/Serialization/DomWriter.cpp \
	$(top_srcdir)/src/System/XML/DomXml.hxx \
	$(top_srcdir)/src/System/XML/DomXml.cxx \
	System/Sounds/beep-manager.h \
	System/Sounds/beep-manager.cc \
	System/Sounds/beep-descriptor.h \
	System/Sounds/beep-descriptor.cc \
	System/Sounds/smartmatic-sounds-manager.h \
	System/Sounds/smartmatic-sounds-manager.cc \
	Environment/Configurations/image-resources-manager-base.h \
	Environment/Configurations/image-resources-manager-base.cc \
	Functionalities/time-functionality.h \
	Functionalities/time-functionality.cc \
	$(top_srcdir)/src/System/Security/Signed.cxx \
	$(top_srcdir)/src/System/Security/Crypto.cxx \
	$(top_srcdir)/src/System/Security/SecurityBase.cxx \
	$(top_srcdir)/src/System/Security/CRC32Calculator.cxx \
	$(top_srcdir)/src/System/Security/Cryptography/CryptoBase.cxx \
	$(top_srcdir)/src/System/Security/Cryptography/CryptoPKCS12.cxx \
	$(top_srcdir)/src/System/Security/Cryptography/CryptoAES.cxx \
	$(top_srcdir)/src/System/Security/Cryptography/DigestAlgorithmLookup.h \
	$(top_srcdir)/src/System/Security/Cryptography/DigestAlgorithmLookup.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/MsgDigestUtil.h \
	$(top_srcdir)/src/System/Security/Cryptography/MsgDigestUtil.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/RsaUtil.h \
	$(top_srcdir)/src/System/Security/Cryptography/RsaUtil.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/PBEKeyDerivatorHMAC.h \
	$(top_srcdir)/src/System/Security/Cryptography/PBEKeyDerivatorHMAC.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/PKCS7Signer.hxx \
	$(top_srcdir)/src/System/Security/Cryptography/PKCS7Signer.cxx \
	$(top_srcdir)/src/System/Security/Cryptography/CMSSigner.hxx \
	$(top_srcdir)/src/System/Security/Cryptography/CMSSigner.cxx \
	$(top_srcdir)/src/System/Security/Cryptography/CryptoPKCS7.hxx \
	$(top_srcdir)/src/System/Security/Cryptography/CryptoPKCS7.cxx \
	$(top_srcdir)/src/System/Exception/MessageDigestException.h \
	$(top_srcdir)/src/System/Security/Cryptography/CertificateValidator.h \
	$(top_srcdir)/src/System/Security/Cryptography/CertificateValidator.cpp \
	$(top_srcdir)/src/System/SafeBuffer.h \
	$(top_srcdir)/src/System/SafeBuffer.cpp \
	$(top_srcdir)/src/System/Enqueuer.h \
	$(top_srcdir)/src/System/Enqueuer.hpp \
	$(top_srcdir)/src/System/OptParser.hxx \
	$(top_srcdir)/src/System/OptParser.cxx \
	Functionalities/FunctionalityChallengeConfiguration.h \
	Functionalities/FunctionalityChallengeConfiguration.cpp \
	Functionalities/FunctionalityAuthenticationProvider.h \
	Functionalities/FunctionalityAuthenticationProvider.cpp \
	$(top_srcdir)/src/System/Threading/ThreadSleep.h \
	$(top_srcdir)/src/System/Threading/ThreadSleep.cpp \
	$(top_srcdir)/src/System/Runtime/ProcessLauncher.h \
	$(top_srcdir)/src/System/Runtime/ProcessLauncher.cpp \
	$(top_srcdir)/src/System/Runtime/ProcessMonitor.h \
	$(top_srcdir)/src/System/Runtime/ProcessMonitor.cpp \
	$(top_srcdir)/src/System/Encoding/Base64Encoder.h \
	$(top_srcdir)/src/System/Encoding/Base64Encoder.cpp \
	$(top_srcdir)/src/System/Utils/StringUtils.cxx \
	$(top_srcdir)/src/System/XSLFO/FOPTransformer.cxx \
	$(top_srcdir)/src/System/XSLFO/XMLRoffTransformer.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/SignatureAlgorithm.h \
	$(top_srcdir)/src/System/Security/Cryptography/SignatureAlgorithm.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/ECDSASigner.h \
	$(top_srcdir)/src/System/Security/Cryptography/ECDSASigner.cpp \
	$(top_srcdir)/src/System/Security/Cryptography/CertUtil.h \
	$(top_srcdir)/src/System/Security/Cryptography/CertUtil.cpp \
	$(top_srcdir)/src/System/Exception/SignatureAlgorithmKeyException.h \
	$(top_srcdir)/src/System/Exception/SignatureAlgorithmKeyException.cpp \
	$(top_srcdir)/src/System/Exception/ECDSException.h \
	$(top_srcdir)/src/System/Exception/ECDSException.cpp \
	$(top_srcdir)/src/System/Exception/InvalidCardContentException.hxx \
	$(top_srcdir)/src/System/Exception/IOCardException.h \
	$(top_srcdir)/src/System/Exception/CardCanNotWriteException.h \
	$(top_srcdir)/src/System/ZenityWrapper.hxx \
	$(top_srcdir)/src/System/ZenityWrapper.cxx

libsmartmatic_la_CPPFLAGS = @modules_CFLAGS@           \
	-I$(top_srcdir)/src                                \
	-I$(top_srcdir)/src/Configuration/GeneratedClasses

libsmartmatic_la_LIBADD = @modules_LIBS@ @INTLLIBS@

libsmartmatic_la_LDFLAGS = -version-info @LIBVERSION@:@LIBFIX@:@LIBMINOR@

if ADD_RELEASE
 libsmartmatic_la_LDFLAGS += -release @LIBMAYOR@.@LIBMINOR@ 
endif

smttincludedir= $(includedir)/smartmatic
nobase_smttinclude_HEADERS = \
	Functionalities/functionality.h \
	Functionalities/functionality-manager.h \
	Functionalities/functionality-manager.hpp \
	Functionalities/menu-option-descriptor.h \
	Environment/Configurations/resource-path-provider.h \
	Configuration/smartmatic-language-controller.h \
	Configuration/configuration-persistence-manager.h \
	Environment/Configurations/base-language-controller.h \
	Environment/Configurations/image-resources-manager-base.h \
	System/Sounds/smartmatic-sounds-manager.h \
	System/IO/Path.h \
	System/IO/Directory.h	\
	System/IO/File.h \
	System/Compression/compression-class.h \
	System/guid-class.h \
	System/XML/Serialization/DomWriter.h \
	System/Sounds/beep-manager.h \
	Functionalities/time-functionality.h \
	System/Sounds/beep-descriptor.h \
	System/XML/DomXml.hxx\
	System/Security/Cryptography/RsaUtil.h \
	System/Exception/MessageDigestException.h \
	System/Exception/VoteRecoveryException.hxx \
	System/Exception/QREncodingException.h \
	System/Exception/GuIdException.h \
	System/Exception/LoginCardException.h \
	System/Enqueuer.h \
	System/Enqueuer.hpp \
	System/SafeBuffer.h \
	System/OptParser.hxx \
	Functionalities/FunctionalityChallengeConfiguration.h \
	Functionalities/FunctionalityAuthenticationProvider.h \
	System/Threading/ThreadSleep.h \
	System/Runtime/ProcessLauncher.h \
	System/Runtime/ProcessMonitor.h \
	System/Encoding/Base64Encoder.h \
	System/Security/Cryptography/SignatureAlgorithm.h \
	System/Security/Cryptography/ECDSASigner.h \
	System/Security/Cryptography/CertUtil.h \
	System/Exception/SignatureAlgorithmKeyException.h \
	System/Exception/ECDSException.h \
	System/ZenityWrapper.hxx

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libsmartmatic.pc

EXTRA_DIST = \
	libsmartmatic.pc.in

configuration-list: ${XSDDIR}/SmartmaticConfiguration-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<

configuration-base-list: ${XSDDIR}/ConfigurationBase-schema.xsd

	$(XSDCXX) cxx-tree \
	--output-dir $(top_srcdir)/src/Configuration/GeneratedClasses/Configuration \
	$(XSDFLAGS) \
	--namespace-map http://www.w3.org/2001/XMLSchema=Smartmatic::ConfigurationTypes \
	--enumerator-regex '/(.+)/CONFIGURATION_\U$$1/' \
	--file-list $@ \
	 $<

