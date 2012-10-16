CLEANFILES = *~
EXTRA_DIST = ${HEADER_FILES} ${SOURCE_FILES}

votingdevicedir=$(includedir)/saes/Voting/VotingDevice
votingdevice_HEADERS = ${HEADER_FILES}

HEADER_FILES= \
	$(top_srcdir)/src/Voting/VotingDevice/VotingDeviceWrapper.hxx \
	$(top_srcdir)/src/Voting/VotingDevice/card-data-wrapper.h \
	$(top_srcdir)/src/Voting/VotingDevice/ContingencyCardDataWrapper.hxx

SOURCE_FILES= \
	$(top_srcdir)/src/Voting/VotingDevice/VotingDeviceWrapper.cxx \
	$(top_srcdir)/src/Voting/VotingDevice/card-data-wrapper.cc \
	$(top_srcdir)/src/Voting/VotingDevice/ContingencyCardDataWrapper.cxx
