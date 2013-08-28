Name: geoclue
Version: 0.12.99
Release: 1
Summary: Geoinformation Service
Group: System/Libraries
URL: http://www.freedesktop.org/wiki/Software/GeoClue/
License: LGPLv2
Source: %{name}-%{version}.tar.gz
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(gobject-2.0)
BuildRequires: pkgconfig(dbus-glib-1)
BuildRequires: pkgconfig(libxml-2.0)
BuildRequires: pkgconfig(gio-2.0)
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: autoconf
BuildRequires: libxslt

%description
%{summary}.

%files
%defattr(-,root,root,-)
%{_libdir}/*.so.*
%{_datadir}/GConf/gsettings/geoclue
%{_datadir}/glib-2.0/schemas/*.xml
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Master.service
%{_libexecdir}/geoclue-master


%package devel
Summary: Development files for %{name}
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}

%description devel
%{summary}.

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}/*.h
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc


%package provider-example
Summary: Example provider for %{name}
Group: System/Libraries

%description provider-example
%{summary}.

%files provider-example
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Example.service
%{_datadir}/geoclue-providers/geoclue-example.provider
%{_libexecdir}/geoclue-example


%package provider-geonames
Summary: Geonames provider for %{name}
Group: System/Libraries

%description provider-geonames
%{summary}.

%files provider-geonames
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Geonames.service
%{_datadir}/geoclue-providers/geoclue-geonames.provider
%{_libexecdir}/geoclue-geonames


%package provider-gsmloc
Summary: Gsmloc provider for %{name}
Group: System/Libraries

%description provider-gsmloc
%{summary}.

%files provider-gsmloc
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Gsmloc.service
%{_datadir}/geoclue-providers/geoclue-gsmloc.provider
%{_libexecdir}/geoclue-gsmloc


%package provider-hostip
Summary: Hostip provider for %{name}
Group: System/Libraries

%description provider-hostip
%{summary}.

%files provider-hostip
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Hostip.service
%{_datadir}/geoclue-providers/geoclue-hostip.provider
%{_libexecdir}/geoclue-hostip


%package provider-localnet
Summary: Localnet provider for %{name}
Group: System/Libraries

%description provider-localnet
%{summary}.

%files provider-localnet
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Localnet.service
%{_datadir}/geoclue-providers/geoclue-localnet.provider
%{_libexecdir}/geoclue-localnet


%package provider-manual
Summary: Manual provider for %{name}
Group: System/Libraries

%description provider-manual
%{summary}.

%files provider-manual
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Manual.service
%{_datadir}/geoclue-providers/geoclue-manual.provider
%{_libexecdir}/geoclue-manual


%package provider-nominatim
Summary: Nominatim provider for %{name}
Group: System/Libraries

%description provider-nominatim
%{summary}.

%files provider-nominatim
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Nominatim.service
%{_datadir}/geoclue-providers/geoclue-nominatim.provider
%{_libexecdir}/geoclue-nominatim


%package provider-plazes
Summary: Plazes provider for %{name}
Group: System/Libraries

%description provider-plazes
%{summary}.

%files provider-plazes
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Plazes.service
%{_datadir}/geoclue-providers/geoclue-plazes.provider
%{_libexecdir}/geoclue-plazes


%package provider-yahoo
Summary: provider for %{name}
Group: System/Libraries

%description provider-yahoo
%{summary}.

%files provider-yahoo
%defattr(-,root,root,-)
%{_datadir}/dbus-1/services/org.freedesktop.Geoclue.Providers.Yahoo.service
%{_datadir}/geoclue-providers/geoclue-yahoo.provider
%{_libexecdir}/geoclue-yahoo




%prep
%setup -q -n %{name}-%{version}/%{name}


%build
autoreconf -vfi
%configure --enable-static=no --enable-connman=yes
make %{?_smp_mflags}


%install
make DESTDIR=%{buildroot} install
rm -f %{buildroot}/%{_libdir}/*.la

%post -p /sbin/ldconfig

%postun
/sbin/ldconfig
if [ $1 -eq 0 ]; then
    /usr/bin/glib-compile-schemas %{_datadir}/glib-2.0/schemas &>/dev/null || :
fi

%posttrans
/usr/bin/glib-compile-schemas %{_datadir}/glib-2.0/schemas &>/dev/null || :

