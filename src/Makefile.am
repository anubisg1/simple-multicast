## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = multicast

multicast_SOURCES = \
	main.c \
	compatibility.c \
	compatibility.h \
	ipv4/mcast-client.c \
	ipv4/mcast-client.h \
	ipv4/mcast-server.c \
	ipv4/mcast-server.h \
	ipv4/ssm-client.c \
	ipv4/testip.c \
	ipv4/testip.h \
	ipv6/testip6.c \
	ipv6/testip6.h \
	ipv6/mcast6-client.c \
	ipv6/mcast6-client.h \
	ipv6/mcast-server.c \
	ipv6/mcast-server.h
	
multicast_LDFLAGS = 

multicast_LDADD = 

