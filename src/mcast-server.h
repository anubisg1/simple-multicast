/**
* \file mcast-server.h
*
* \brief Mulitcast server definitions
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

#ifndef __MCAST_SERVER_H__
#define __MCAST_SERVER_H__

#include "tcp_ip.h"

/** \def SOURCE_PORT (0)
 *   A dummy source port number.
 */
#define SOURCE_PORT  0

#ifdef _WIN32
/** \fn int mcast_server_win(const char *mcast_group, int destination_port, int delay_ms);
* Executes multicast server application for windows.
*
* \param mcast_group Is a string containing the multicast group address.
*
* \param destination_port Is an int containing the destinaion UDP port number.
*
* \param delay_ms Is an int (in milliseconds) defining the sleep period between packets.
*/
int mcast_server_win(const char *mcast_group, int destination_port, int delay_ms);
#else

/** \fn int mcast_server_unix(const char *mcast_group, int destination_port, int delay_s);
* Executes multicast server application for unix.
*
* \param mcast_group Is a string containing the multicast group address.
*
* \param destination_port Is an int containing the destinaion UDP port number.
*
* \param delay_s Is an int (in seconds) defining the sleep period between packets.
*/
int mcast_server_unix(const char *mcast_group, int destination_port, int delay_s);
#endif // _WIN32

#endif
