/**
* \file testip.h
*
* \brief Library to test ip validity
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


#ifndef __TESTIP_H__
#define __TESTIP_H__

#include "compatibility.h"


/** \fn int is_valid_ip(const char *my_ip_str);
* Verifies if IP address in "my_ip_str" is a valid ip. Supports IPv4 and IPv6
*
* \param my_ip_str Is a string containing the ip address.
*
* \return AF_INET if the ip is a valid IPv4 address, AF_INET6 is the function is
*  a valid IPv6 address else returns -1
*/
int is_valid_ip(const char *my_ip_str);

/** \fn bool is_valid_mcast_ip4(const char *my_ip_str);
* Verifies if IP address in "my_ip_str" is a valid IPv4 multicast address
*
* \param my_ip_str Is a string containing the ip address.
*
* \return #TRUE if the string is a valid IPv4 Multicast address, #FALSE otherwise
*/
bool is_valid_mcast_ip4(const char *my_ip_str);

/** \fn bool is_valid_ssm_ip4(const char *my_ip_str);
* Verifies if IP address in "my_ip_str" is a valid IPv4 SSM address
*
* \param my_ip_str Is a string containing the ip address.
*
* \return #TRUE if the string is a valid IPv4 SSM address, #FALSE otherwise
*/
bool is_valid_ssm_ip4(const char *my_ip_str);

#endif
