/**
* \file compatibility.h
*
* \brief Common definitions to make unix and win more compatible
*
* \author Andrea Florio <andrea@opensuse.org>
*
* \version 0.1
* \date 2013
*
* \section License
* Copyright (C) 2013 \n
* <b>Andrea Florio 2013 <andrea@opensuse.org></b> \n
*
* This Project is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the \n
* Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This Project is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of \n
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/** Simple multicast Server/Client application.
* Supports:
*
* * Multicast Server
* * Multicast client
* * Source Specific Multicast client
*
* Builds on Windows, *unix (tested on linux only), and Android
* (for android you need c4droid to compile it , i will provide apk soon
* https://play.google.com/store/apps/details?id=com.n0n3m4.droidc&hl=en )
*
* Due to Android BIONIC bug 64374 (https://code.google.com/p/android/issues/detail?id=64374 )
* when compiling on Android with c4droid, please select as compiler "TCC + uClibc"
*/

#ifndef __COMPATIBILITY_H__
#define __COMPATIBILITY_H__

/** \typedef int bool;
* Standard boolean type, this kind of variable should be #TRUE or #FALSE only.
*/
typedef int bool;

/** \def SOURCE_PORT (0)
 *   A dummy source port number.
 */
#define SOURCE_PORT  0

#ifdef _WIN32
#ifndef _WIN32_WINNT
/** \def _WIN32_WINNT 0x0501
 *  Windows version must be >= XP or getaddrinfo will not be supported.
 */
#define _WIN32_WINNT 0x0501
#endif // _WIN32_WINNT
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

/** \fn void sleep(int delay_s);
* A wrapper for Windows. converts Unix sleep() to windows Sleep()
*
* \param delay_s Is a int indicating how long to sleep.
*
*/
void sleep(int delay_s);

/* wrapper for windows */
const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
int inet_pton(int af, const char *src, void *dst);

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

/** \typedef int SOCKET;
* A simple declaration to make code more clear and compatible with winsock.
*/
typedef int SOCKET;

#ifndef SOCKET_ERROR
/** \def SOCKET_ERROR (-1)
*  simple declaration to make code more clear and compatible with winsock.
*/
#define SOCKET_ERROR (-1)
#endif // SOCKET_ERROR

#ifndef INVALID_SOCKET
/** \def INVALID_SOCKET (SOCKET)(~0)
*  simple declaration to make code more clear and compatible with winsock.
*/
#define INVALID_SOCKET (SOCKET)(~0)
#endif // INVALID_SOCKET

/** \typedef struct sockaddr_in SOCKADDR_IN;
* A simple declaration to make code more clear and compatible with winsock.
*/
typedef struct sockaddr_in SOCKADDR_IN;

/** \typedef struct sockaddr_in6 SOCKADDR_IN6;
* A simple declaration to make code more clear and compatible with winsock.
*/
typedef struct sockaddr_in6 SOCKADDR_IN6;

/** \def FALSE (0)
* Define the bool value \b FALSE as \b 0.
*/
#ifndef FALSE
#define FALSE (0)
#endif // FALSE

/** \def TRUE (!FALSE)
* Define the bool value \b TRUE as \b !FALSE.
*/
#ifndef TRUE
#define TRUE !FALSE
#endif // TRUE

void closesocket(SOCKET sock);

#endif // _WIN32

#endif
