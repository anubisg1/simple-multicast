/*
* mcast-server.c
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


#include <time.h>                   // Required for time_t type and time() function
#include <stdio.h>                  // Required for printf() and sprintf()
#include <unistd.h>                 // Required for sleep()
#include "mcast-server.h"           // Required for socks specific headers

int mcast_server(const char *mcast_group, int destination_port, int delay_s ) {

  int ttl = 64;                     // IP TTL
  char message[50];                 // Sent message string
  SOCKET sock = INVALID_SOCKET;     // Datagram window socket
  SOCKADDR_IN source_sin,           // Source socket address
              dest_sin;             // Destination socket address
 #ifdef _WIN32
  WSADATA WSAData;                  // Contains details of the Winsock implementation

  /* Initialize Winsock. */
  if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0)  {
    perror("WSAStartup");
    return FALSE;
  }
#endif // _WIN32

  /* Create a datagram window socket, sock. */
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
    perror("sock");
    return FALSE;
  }

  /* Fill out source socket's address information. */
  source_sin.sin_family = AF_INET;
  source_sin.sin_port = htons (SOURCE_PORT);
  source_sin.sin_addr.s_addr = htonl (INADDR_ANY);

  /* Associate the source socket's address with the socket, sock. */
  if (bind (sock, (struct sockaddr *)&source_sin, sizeof(source_sin)) == SOCKET_ERROR) {
    perror("bind");
    closesocket(sock);
    return FALSE;
  }

  /* Set the Time-to-Live of the multicast. */
  if (setsockopt (sock, IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == SOCKET_ERROR) {
    perror("setsockopt");
    closesocket(sock);
    return FALSE;
  }

  /* Fill out the desination socket's address information. */
  dest_sin.sin_family = AF_INET;
  dest_sin.sin_port = htons(destination_port);
  dest_sin.sin_addr.s_addr = inet_addr(mcast_group);

  /* Send packets to the multicasting address every "delay_s". */
  while (1) {
    time_t t = time(0);
    sprintf(message, "time is %-24.24s", ctime(&t));
    printf("sending message: %s\n", message);
    if (sendto (sock, message, sizeof(message), 0, (struct sockaddr *)&dest_sin, sizeof(dest_sin)) == SOCKET_ERROR) {
        perror("sendto");
        closesocket(sock);
        return FALSE;
    }
    sleep(delay_s);
   }
  /* Disable sending on sock before closing it. */
  shutdown(sock, 0x01);
  #ifdef _WIN32
  /* Close sock. */
  closesocket(sock);
  WSACleanup ();
  #endif // _WIN32
  return TRUE;
}

