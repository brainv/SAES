CLEANFILES = *~
EXTRA_DIST = ${HEADER_FILES} ${SOURCES_FILES}

securitydir=$(includedir)/saescommon/Security
security_HEADERS = ${HEADER_FILES} 


HEADER_FILES= \
	$(top_srcdir)/src/Security/Encryption.hxx \
	$(top_srcdir)/src/Security/SecretKey.h \
	$(top_srcdir)/src/Security/XmlSecResource.hxx \
	$(top_srcdir)/src/Security/CryptoData.hxx
		
SOURCES_FILES= \
	$(top_srcdir)/src/Security/Encryption.cxx \
	$(top_srcdir)/src/Security/SecretKey.cpp \
	$(top_srcdir)/src/Security/XmlSecResource.cxx \
	$(top_srcdir)/src/Security/CryptoData.cxx