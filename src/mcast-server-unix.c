/*
* mcast-server-unix.c
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

#ifndef _WIN32

#include <stdio.h>                  // Required for printf() and sprintf()
#include <strings.h>                // Required for bzero() and strcasecmp()
#include <time.h>                   // Required for time_t type and time() function
#include <unistd.h>                 // Required for sleep()
#include "mcast-server.h"           // Required for socks specific headers

int mcast_server_unix(const char *mcast_group, int destination_port, int delay_s) {

  int ttl = 64;                     // IP TTL
  char message[50];                 // Sent message string
  SOCKET sock = INVALID_SOCKET;     // Datagram window socket
  SOCKADDR_IN source_sin,           // Source socket address
              dest_sin;             // Destination socket addresss

  /* Create a datagram socket, sock. */
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
    perror("socket");
    return FALSE;
  }

  /* Set the Time-to-Live of the multicast. */
  if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) == SOCKET_ERROR) {
    perror("setsockopt");
    return FALSE;
  }

  /* Fill in the source address information */
  bzero((char *)&source_sin, sizeof(source_sin));
  source_sin.sin_family = AF_INET;
  source_sin.sin_addr.s_addr = htonl(INADDR_ANY);
  source_sin.sin_port = htons(SOURCE_PORT);

  /* Associate the source socket's address with the socket, sock. */
  if (bind (sock, (struct sockaddr *)&source_sin, sizeof(source_sin)) == SOCKET_ERROR) {
    perror("bind");
    return FALSE;
  }

  /* Fill in the destination address information */
  bzero((char *)&dest_sin, sizeof(dest_sin));
  dest_sin.sin_family = AF_INET;
  dest_sin.sin_addr.s_addr = inet_addr(mcast_group);
  dest_sin.sin_port = htons(destination_port);

  /* Send packets to the multicast address ever "delay_s" seconds */
  while (1) {
    time_t t = time(0);
    sprintf(message, "time is %-24.24s", ctime(&t));
    printf("sending message: %s\n", message);
    if (sendto(sock, message, sizeof(message), 0, (struct sockaddr *)&dest_sin, sizeof(dest_sin)) == SOCKET_ERROR) {
        perror("sendto");
        return FALSE;
    }
    sleep(delay_s);
  }
  return TRUE;
}

#endif // _WIN32
