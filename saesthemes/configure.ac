AC_INIT([saesthemes], [1.4.6])
AM_INIT_AUTOMAKE([ filename-length-max=256 tar-ustar ])
AC_CONFIG_SRCDIR([icon-themes])

AM_MAINTAINER_MODE

IT_PROG_INTLTOOL()
PKG_PROG_PKG_CONFIG()
AM_GLIB_GNU_GETTEXT

AC_SUBST(GETTEXT_PACKAGE, [AC_PACKAGE_NAME])

localedir='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(localedir)

AC_SUBST(ACLOCAL_AMFLAGS, "\${ACLOCAL_FLAGS}")

PKG_CHECK_MODULES(THEME_ENGINE,
 [gtk+-2.0 >= 2.0.0 dnl
  gdk-pixbuf-2.0 >= 2.0.0])

GTK_VERSION=`$PKG_CONFIG --variable=gtk_binary_version gtk+-2.0`
AC_SUBST(GTK_VERSION)

AC_MSG_CHECKING([development series build])

# Check for icon-naming-utils
ICONMAP="true"
if test "x$enable_mapping" != "xno"; then
   UTILS_REQUIRED=0.8.7

   AC_MSG_CHECKING([icon-naming-utils >= $UTILS_REQUIRED])
   PKG_CHECK_EXISTS(icon-naming-utils >= $UTILS_REQUIRED, have_utils=yes, have_utils=no)
   if test "x$have_utils" = "xyes"; then
      UTILS_PATH="`$PKG_CONFIG --variable=program_path icon-naming-utils`"
      ICONMAP="$UTILS_PATH/icon-name-mapping"
      AC_MSG_RESULT([yes])
   else
	AC_MSG_RESULT([no])
   	AC_MSG_ERROR([icon-naming-utils >= $UTILS_REQUIRED is required to build and install saes-themes])
   fi
fi

AC_SUBST(ICONMAP)
AM_CONDITIONAL(LEGACY_ICON_MAPPING, test "x$enable_mapping" != "xno")

### Icon sizes for all large print themes

LARGEPRINT_DND="48,48"
LARGEPRINT_MENU="32,32"
LARGEPRINT_PANEL_MENU="48,48"
LARGEPRINT_LARGE_TOOLBAR="48,48"
LARGEPRINT_SMALL_TOOLBAR="32,32"
LARGEPRINT_BUTTON="32,32"
LARGEPRINT_DIALOG="64,64"
LARGEPRINT_MINI_COMMANDER="24,24"

LARGEPRINT_ICON_SIZES="mini-commander-icon=$LARGEPRINT_MINI_COMMANDER:print-manager=$LARGEPRINT_DIALOG:panel-button=$LARGEPRINT_BUTTON:gtk-dnd=$LARGEPRINT_DND:gtk-menu=$LARGEPRINT_MENU:panel-menu=$LARGEPRINT_PANEL_MENU:gtk-large-toolbar=$LARGEPRINT_LARGE_TOOLBAR:gtk-small-toolbar=$LARGEPRINT_SMALL_TOOLBAR:gtk-button=$LARGEPRINT_BUTTON:gtk-dialog=$LARGEPRINT_DIALOG"

LARGEPRINT_FONT="sans 18"
LARGEPRINT_DOCUMENTS_FONT="sans 18"
LARGEPRINT_DESKTOP_FONT="sans 18"
LARGEPRINT_WINDOW_FONT="sans 18"
LARGEPRINT_MONOSPACE_FONT="monospace 18"


AC_SUBST(LARGEPRINT_ICON_SIZES)
AC_SUBST(LARGEPRINT_FONT)
AC_SUBST(LARGEPRINT_DOCUMENTS_FONT)
AC_SUBST(LARGEPRINT_DESKTOP_FONT)
AC_SUBST(LARGEPRINT_WINDOW_FONT)
AC_SUBST(LARGEPRINT_MONOSPACE_FONT)

dnl used to substitute in common sections of theme gtkrc files
gtk_stock_icons_rc=${srcdir}/common/gtk-stock-icons.rc
panel_stock_icons_rc=${srcdir}/common/panel-stock-icons.rc
media_stock_icons_rc=${srcdir}/common/media-stock-icons.rc
capplet_stock_icons_rc=${srcdir}/common/capplet-stock-icons.rc
metacity_stock_icons_rc=${srcdir}/common/metacity-stock-icons.rc
AC_SUBST_FILE(gtk_stock_icons_rc)
AC_SUBST_FILE(panel_stock_icons_rc)
AC_SUBST_FILE(media_stock_icons_rc)
AC_SUBST_FILE(capplet_stock_icons_rc)
AC_SUBST_FILE(metacity_stock_icons_rc)

AC_CONFIG_FILES([
Makefile
saes-themes.spec
common/Makefile
metacity-themes/Makefile
desktop-themes/Makefile
desktop-themes/SaesDefault/Makefile
gtk-themes/Makefile
gtk-themes/SaesDefault/Makefile
icon-themes/Makefile
icon-themes/SaesDefault/Makefile
po/Makefile.in
])

AC_OUTPUT

