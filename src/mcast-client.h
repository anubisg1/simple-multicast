/**
* \file mcast-client.h
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

#ifndef __MCAST_CLIENT_H__
#define __MCAST_CLIENT_H__

#include "tcp_ip.h"

#ifdef _WIN32
int mcast_client_win(const char *mcast_group, int receiving_port);
int ssm_client_win(const char *mcast_group, const char *ssm_source, int receiving_port);

#else
int mcast_client_unix(const char *mcast_group, int receiving_port);
int ssm_client_unix(const char *mcast_group, const char *ssm_source, int receiving_port);

#endif // _WIN32


#ifndef IP_ADD_SOURCE_MEMBERSHIP
#define IP_ADD_SOURCE_MEMBERSHIP 39 /* ip_mreq_source: join source group */
#define IP_DROP_SOURCE_MEMBERSHIP 40 /* ip_mreq_source: leave source group */

struct ip_mreq_source
  {
    /* IP multicast address of group.  */
    struct in_addr imr_multiaddr;

    /* IP address of source.  */
    struct in_addr imr_interface;

    /* IP address of interface.  */
    struct in_addr imr_sourceaddr;
  };

#endif // IP_ADD_SOURCE_MEMBERSHIP

#endif
