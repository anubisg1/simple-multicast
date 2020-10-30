dnl Process this file with autoconf to produce a configure script.

AC_INIT([multicast], [0.2.5.2], [https://github.com/anubisg1/simple-multicast])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])
AC_PROG_CC
LT_INIT([win32-dll])

######################################################################
# DOXYGEN SUPPORT
######################################################################

DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)

DX_INIT_DOXYGEN([$PACKAGE_NAME],[doxygen.cfg])

dnl ***************************************************************************
dnl Check for Windows
dnl ***************************************************************************
AC_CANONICAL_HOST

case $host_os in
  *mingw*)
    platform_win32=yes
    native_win32=yes
    ;;
  pw32* | *cygwin* | *msys* )
    platform_win32=yes
    native_win32=no
    ;;
  *)
    platform_win32=no
    native_win32=no
    ;;
esac
AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")

AM_COND_IF([PLATFORM_WIN32], [
	AC_CHECK_HEADERS([winsock2.h])
	AC_CHECK_HEADERS([ws2ipdef.h], [], [],
	 [[#ifdef HAVE_WINSOCK2_H
	 #include <winsock2.h>
	 #endif
	 ]])

	AC_MSG_CHECKING([whether to enable libargp])
	AC_ARG_WITH(argp, [ --with-argp 	build also libargp],
		    with_argp=$withval, with_argp=no)
	AC_MSG_RESULT($with_argp)
	AM_CONDITIONAL([WITH_ARGP], [test "$with_argp" = yes])

	AM_COND_IF([WITH_ARGP], AC_CONFIG_SUBDIRS([libargp]), [
		AC_CHECK_HEADERS([argp.h])
		AC_CHECK_LIB(argp, argp_parse, [], [
			echo "Error! You must have libargp on windows. Run configure with --with-argp"
			exit -1
		])
	])
])

AC_OUTPUT([
Makefile
src/Makefile
])

AC_OUTPUT
    echo
    echo simple-multicast............... : Version $VERSION
    echo
    echo Prefix..........................: $prefix
    echo
    echo Build also libargp..............: $with_argp
    echo
    echo
    echo "Ready to make simple-multicast Type 'make' to continue."
    echo
    echo "Type 'make docs' to build documentation."
    echo
