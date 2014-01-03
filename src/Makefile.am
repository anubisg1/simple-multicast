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
	mcast-client.h \
	mcast-client-unix.c \
	mcast-client-win.c \
	mcast-server.h \
	mcast-server-unix.c \
	mcast-server-win.c \
	ssm-client-unix.c \
	ssm-client-win.c \
	testip.c \
	testip.h \
	tcp_ip.h

multicast_LDFLAGS = 

multicast_LDADD = 

