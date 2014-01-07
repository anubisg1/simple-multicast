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

#include "compatibility.h"

#ifdef _WIN32
#include <stdio.h>                  // Required for printf(), sprintf() and perror)

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

int inet_pton(int af, const char *src, void *dst) {
        struct addrinfo hints, *res, *ressave;

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = af;

        if (getaddrinfo(src, NULL, &hints, &res) != 0) {
        //        dolog(LOG_ERR, "Couldn't resolve host %s\n", src);
            perror("getaddrinfo");
            return -1;
        }

        ressave = res;

        while (res) {
                memcpy(dst, res->ai_addr, res->ai_addrlen);
                res = res->ai_next;
        }

        freeaddrinfo(ressave);
        return 0;
}

#else

/* we really don't want to do anything here */
void closesocket(SOCKET sock) {
}

#endif // _WIN32
