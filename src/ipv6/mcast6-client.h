/**
* \file mcast6-client.h
*
* \brief Mulitcast client definitions
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

#ifndef __MCAST6_CLIENT_H__
#define __MCAST6_CLIENT_H__

#include "../compatibility.h"

/** \fn int mcast6_client(const char *mcast_group, int receiving_port);
* Executes multicast client application. Supports IPv6 only
*
* \param mcast_group Is a string containing the multicast group address.
*
* \param receiving_port Is an int containing the UDP port number the client will listen to.
*
* \return #FALSE in case of error and the description where error occurred.
* In case of success the function will loop and never reach the end
*/
int mcast6_client(const char *mcast_group, int receiving_port);

/** \fn int ssm6_client(const char *mcast_group, const char *ssm_source, int receiving_port);
* Executes source specific multicast client application. Supports IPv6 only
*
* \param mcast_group Is a string containing the multicast group address.
*
* \param ssm_source Is a string containing the authorized source ip address.
*
* \param receiving_port Is an int containing the UDP port number the client will listen to.
*
* \return #FALSE in case of error and the description where error occurred.
* In case of success the function will loop and never reach the end
*/
int ssm6_client(SOCKADDR_STORAGE *mcast_group, SOCKADDR_STORAGE *ssm_source, int receiving_port);

#endif
