CLEANFILES = *~
EXTRA_DIST = ${HEADER_FILES} ${SOURCES_FILES}

votedir=$(includedir)/saes/Voting/Vote
vote_HEADERS = ${HEADER_FILES}

HEADER_FILES= \
	$(top_srcdir)/src/Voting/Vote/TransmissionPackageWrapper.hxx \
	$(top_srcdir)/src/Voting/Vote/VoteWrapper.hxx \
	$(top_srcdir)/src/Voting/Vote/VoteEncoder.h \
	$(top_srcdir)/src/Voting/Vote/VoteRecovery.h \
	$(top_srcdir)/src/Voting/Vote/VoteCode.hxx \
	$(top_srcdir)/src/Voting/Vote/StationTallyWrapper.hxx
	
SOURCES_FILES= \
	$(top_srcdir)/src/Voting/Vote/TransmissionPackageWrapper.cxx \
	$(top_srcdir)/src/Voting/Vote/VoteWrapper.cxx \
	$(top_srcdir)/src/Voting/Vote/VoteEncoder.cpp \
	$(top_srcdir)/src/Voting/Vote/VoteRecovery.cpp \
	$(top_srcdir)/src/Voting/Vote/VoteCode.cxx \
	$(top_srcdir)/src/Voting/Vote/StationTallyWrapper.cxx
