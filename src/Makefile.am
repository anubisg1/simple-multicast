## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

if PLATFORM_WIN32
 AM_LDADD = -lws2_32
endif

bin_PROGRAMS = multicast

multicast_SOURCES = \
	main.c \
	compatibility.c \
	compatibility.h \
	testip.c \
	testip.h \
	mcast-client.c \
	mcast-client.h \
	ssm-client.c \
	mcast-server.c \
	mcast-server.h \
	inet_pton.c
	
multicast_LDFLAGS =

multicast_LDADD = $(AM_LDADD)
