/**
* \file testip.h
*
* \brief Library to test ip validity
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


#ifndef __TESTIP_H__
#define __TESTIP_H__

#define DELIM "."
/** \def DELIM "."
*  The dot is use to divide ipv4 octects.
*/

int valid_digit(const char *ip_str);
int is_valid_ip(const char *ip_str);
int is_valid_mcast_ip(const char *ip_str);
int is_valid_ssm_ip(const char *ip_str);

#endif