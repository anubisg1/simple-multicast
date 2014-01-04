/**
* \file testip6.h
*
* \brief Library to test ip6 validity
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


#ifndef __TESTIP6_H__
#define __TESTIP6_H__

#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif //_WIN32

#define DELIM ":"
/** \def DELIM ":"
*  The dot is use to divide ipv6 groups.
*/

int valid_ipv6_digit(const char *ip_str);

#endif
