/*
* testip6.c
* Copyright (C) Andrea Florio 2013 <andrea@opensuse.org>
*
* This Project is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This Project is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testip6.h"

/* return 1 if string contain only digits, else return 0 */
int valid_ipv6_digit(const char *ip_str) {
    while (*ip_str) {
        if ( (*ip_str >= '0' && *ip_str <= '9') || (*ip_str >= 'a' && *ip_str <= 'f') || (*ip_str >= 'A' && *ip_str <= 'F'))
            ++ip_str;
        else
            return 0;
    }
    return 1;
}
