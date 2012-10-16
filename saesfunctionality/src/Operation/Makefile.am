SUBDIRS = Voting Authenticator Initiator Card Security Diagnosis BCR Alarm
CLEANFILES = *~
EXTRA_DIST = ${HEADER_FILES} ${SOURCES_FILES}

votingdir=$(includedir)/saesfunctionality/Operation
voting_HEADERS = ${HEADER_FILES}

HEADER_FILES= \
	$(top_srcdir)/src/Operation/MachineOperationManager.hxx \
	$(top_srcdir)/src/Operation/PersistSortFile.hxx \
	$(top_srcdir)/src/Operation/InstallMachine.hxx
	
SOURCES_FILES= \
	$(top_srcdir)/src/Operation/MachineOperationManager.cxx \
	$(top_srcdir)/src/Operation/PersistSortFile.cxx \
	$(top_srcdir)/src/Operation/InstallMachine.cxx
