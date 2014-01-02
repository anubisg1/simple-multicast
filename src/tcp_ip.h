/**
* \file tc_pip.h
*
* \brief Common definitions
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


#ifndef __TCP_IP_H__
#define __TCP_IP_H__

#ifdef _WIN32

#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif
typedef int SOCKET;

/** \def TRUE (0)
* Define the bool value \b TRUE as \b 0.
*/
#define TRUE (0)
/** \def FALSE (!TRUE)
* Define the bool value \b FALSE as \b !TRUE.
*/
#define FALSE !TRUE
/** \typedef int bool;
* Standard boolean type, this kind of variable should be #TRUE or #FALSE only.
*/
typedef int bool;

/* Not everyone has the headers for this so improvise */

#endif // _WIN32

#endif