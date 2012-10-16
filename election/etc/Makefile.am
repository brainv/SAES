CLEANFILES = *~ $(electiondesktop:.desktop.in.in=.desktop)

autostartdir = @AUTOSTARTDIR@
autostart_DATA = $(electiondesktop:.desktop.in.in=.desktop)

@INTLTOOL_DESKTOP_RULE@

electiondesktop = election.desktop.in.in

EXTRA_DIST = \
$(electiondesktop) \
$(electiondesktop:.desktop.in.in=.desktop.in)

