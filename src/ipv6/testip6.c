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

#include <stdio.h>                  // Required for printf(), sprintf() and perror)
#include "../compatibility.h"
#include "testip6.h"

int getaddrfamily(const char *addr) {
    struct addrinfo hint, *info =0;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    // Uncomment this to disable DNS lookup
    //hint.ai_flags = AI_NUMERICHOST;
    int ret = getaddrinfo(addr, 0, &hint, &info);
    if (ret)
        return -1;
    int result = info->ai_family;
    freeaddrinfo(info);
    return result;
}
