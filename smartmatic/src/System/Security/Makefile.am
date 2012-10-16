CLEANFILES = *~
SUBDIRS = Cryptography

EXTRA_DIST = ${HEADER_FILES} ${SOURCE_FILES}

securitydir=$(includedir)/smartmatic/System/Security
security_HEADERS = ${HEADER_FILES}

HEADER_FILES= \
	$(top_srcdir)/src/System/Security/Signed.hxx \
	$(top_srcdir)/src/System/Security/Crypto.hxx \
	$(top_srcdir)/src/System/Security/SecurityBase.hxx \
	$(top_srcdir)/src/System/Security/CRC32Calculator.hxx

SOURCE_FILES= \
	$(top_srcdir)/src/System/Security/Signed.cxx \
	$(top_srcdir)/src/System/Security/Crypto.cxx \
	$(top_srcdir)/src/System/Security/SecurityBase.cxx \
	$(top_srcdir)/src/System/Security/CRC32Calculator.cxx

