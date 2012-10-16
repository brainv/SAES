Summary: Themes collection for GNOME
Name: saes-themes
Version: 1.4.6
Release: 0
License: GPL
Group: User Interface/Desktop
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root

%description
Themes collection for GNOME

%prep
%setup

%build
%configure
make

%install
rm -rf ${RPM_BUILD_ROOT}
%makeinstall

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-, root, root)
%{_libdir}/gtk-2.0/@GTK_BINARY_VERSION@/engines/*.so*
%{_datadir}/eazel-engine
%{_datadir}/icons/*
%{_datadir}/themes/*
%doc AUTHORS ChangeLog COPYING NEWS README

%changelog
* Thu Feb 24 2011 Yadickson Soto <yadickson.soto@smartmatic.com>
- New release

