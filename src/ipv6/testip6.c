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
#include <string.h>
#include "testip6.h"
#include "../compatibility.h"

int validate_ip(const char *ip_address) {

  struct addrinfo hint, *res = NULL;
  int ret;
 #ifdef _WIN32
  WSADATA WSAData;                    // Contains details of the winsock implementation

  /* Initialize Winsock. */
  if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0) {
    perror("WSAStartup");
    return FALSE;
  }
#endif // _WIN32
  memset(&hint, '\0', sizeof hint);

  hint.ai_family = PF_UNSPEC;
  hint.ai_flags = AI_NUMERICHOST;

  ret = getaddrinfo(ip_address, NULL, &hint, &res);
  if (ret) {
  /* put perror */
    puts("Invalid address");
    puts(gai_strerror(ret));
    return -1;
  }
  if(res->ai_family == AF_INET) {
	freeaddrinfo(res);
	return AF_INET;
  } else if (res->ai_family == AF_INET6) {
	freeaddrinfo(res);
    return AF_INET6;
  } else {
    /* put perror */
    return -1;
  }

  freeaddrinfo(res);
#ifdef _WIN32
  WSACleanup ();
#endif // _WIN32
  return -1;
}
