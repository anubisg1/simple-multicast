/*
* compatibility.c
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

#include <string.h>                 // Required for memset()
#include "compatibility.h"

#ifdef _WIN32
#include <stdio.h>                  // Required for printf(), sprintf() and perror()

/*
* MingW defines an extern to this struct, but the actual struct isn't present
* in any library. It's trivial enough that we can safely defined it
* ourselves.
*/
const struct in6_addr in6addr_any = {{ IN6ADDR_ANY_INIT }};
const struct in6_addr in6addr_loopback = {{ IN6ADDR_LOOPBACK_INIT }};

/* we convert seconds in milliseconds and we call windows Sleep */
void sleep(int delay_s) {
    int ms = 1000*delay_s;
    Sleep(ms);
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt) {
        if (af == AF_INET) {
                SOCKADDR_IN in;
                memset(&in, 0, sizeof(in));
                in.sin_family = AF_INET;
                memcpy(&in.sin_addr, src, sizeof(struct in_addr));
                getnameinfo((struct sockaddr *)&in, sizeof(SOCKADDR_IN), dst, cnt, NULL, 0, NI_NUMERICHOST);
                return dst;
        }
        else if (af == AF_INET6) {
                SOCKADDR_IN6 in;
                memset(&in, 0, sizeof(in));
                in.sin6_family = AF_INET6;
                memcpy(&in.sin6_addr, src, sizeof(struct in_addr6));
                getnameinfo((struct sockaddr *)&in, sizeof(SOCKADDR_IN6), dst, cnt, NULL, 0, NI_NUMERICHOST);
                return dst;
        }
        return NULL;
}

#else

/* we really don't want to do anything here */
void closesocket(SOCKET sock) {
}

#endif // _WIN32

/* converts a humand read-able ip address into SOCKADDR_STORAGE */
int j_inet_pton(const char *src, SOCKADDR_STORAGE *dst) {
    struct sockaddr_in *sin;
    struct sockaddr_in6 *sin6;

    memset(dst, 0, sizeof(SOCKADDR_STORAGE));
    sin = (struct sockaddr_in *)dst;
    sin6 = (struct sockaddr_in6 *)dst;

    if(inet_pton(AF_INET, src, &sin->sin_addr) > 0) {
    dst->ss_family = AF_INET;
    return 1;
    }

    if(inet_pton(AF_INET6, src, &sin6->sin6_addr) > 0) {
    dst->ss_family = AF_INET6;
#ifdef SIN6_LEN
    sin6->sin6_len = sizeof(struct sockaddr_in6);
#endif
    return 1;
    }

    return 0;
}