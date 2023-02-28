/**
* \file mcast-server.h
*
* \brief Mulitcast server definitions
*
* \author Andrea Florio <andrea@opensuse.org>
*
* \version 0.3
* \date 2020
*
* \section License
* Copyright (C) 2020 \n
* <b>Andrea Florio 2020 <andrea@opensuse.org></b> \n
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

#include "compatibility.h"

/** \fn int mcast_server4(const char *mcast_group, int destination_port, int delay_s);
* Executes multicast server application. Supports IPv4 only
*
* \param mcast_group Is a string containing the multicast group address.
*
* \param destination_port Is an int containing the destinaion UDP port number.
*
* \param delay_s Is an int (in seconds) defining the sleep period between packets.
*
* \return #FALSE in case of error and the description where error occurred.
* In case of success the function will loop and never reach the end
*/
int mcast_server4(const char *mcast_group, int destination_port, int delay_s, int ttl);

/** \fn int mcast_server6(const char *mcast_group, int destination_port, int delay_s);
* Executes multicast server application. Supports IPv6 only
*
* \param mcast_group Is a string containing the multicast group address.
*
* \param destination_port Is an int containing the destinaion UDP port number.
*
* \param delay_s Is an int (in seconds) defining the sleep period between packets.
*
* \return #FALSE in case of error and the description where error occurred.
* In case of success the function will loop and never reach the end
*/
int mcast_server6(const char *mcast_group, int destination_port, int delay_s, int ttl);

#endif
