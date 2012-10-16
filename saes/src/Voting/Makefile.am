SUBDIRS = Election VotingDevice PBReports GeneratedClasses Status VotingCenters Vote Screen Codi
CLEANFILES = *~
EXTRA_DIST = ${HEADER_FILES} ${SOURCES_FILES}

votingdir=$(includedir)/saes/Voting
voting_HEADERS = ${HEADER_FILES} 


HEADER_FILES= \
	$(top_srcdir)/src/Voting/ElectoralFactory.hxx \
	$(top_srcdir)/src/Voting/ElectoralConfiguration.hxx \
	$(top_srcdir)/src/Voting/operation-status.h \
	$(top_srcdir)/src/Voting/set-language-functionality.h

SOURCES_FILES= \
	$(top_srcdir)/src/Voting/ElectoralFactory.cxx \
	$(top_srcdir)/src/Voting/ElectoralConfiguration.cxx \
	$(top_srcdir)/src/Voting/operation-status.cc \
	$(top_srcdir)/src/Voting/set-language-functionality.cc
