/*
* ssm-client-win.c
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

#ifdef _WIN32

#include <stdio.h>                  // Required for printf() and sprintf()
#include "mcast-client.h"

int ssm_client_win(const char *mcast_group, const char *ssm_source, int receiving_port) {

  struct ip_mreq_source mreq;         // SSM information container
  socklen_t addrlen;                  // Length of recv_sin
  char message[100];                  // ASCII string
  SOCKET sock = INVALID_SOCKET;       // Datagram window socket
  SOCKADDR_IN local_sin,              // Local socket's address
              recv_sin;               // Holds the source address upon recvfrom function returns
  WSADATA WSAData;                    // Contains details of the winsock implementation

  /* Initialize Winsock. */
  if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0) {
    perror("WSAStartup");
    return FALSE;
  }

  /* Create a datagram socket, sock. */
  if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
    perror("sock");
    return FALSE;
  }

  /* Fill in the destination address information */
  local_sin.sin_family = AF_INET;
  local_sin.sin_port = htons(receiving_port);
  local_sin.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Fill in the destination address information */
  if (bind (sock, (struct sockaddr *) &local_sin, sizeof (local_sin)) == SOCKET_ERROR) {
    perror("bind");
    closesocket (sock);
    return FALSE;
  }

  /* Set up the connection to the group */
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  mreq.imr_multiaddr.s_addr  = inet_addr(mcast_group);
  mreq.imr_sourceaddr.s_addr = inet_addr(ssm_source);

  if (setsockopt(sock, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) == SOCKET_ERROR) {
    perror("setsockopt mreq");
    closesocket (sock);
    return FALSE;
  }

  addrlen = sizeof (recv_sin);

  /* Let's receive our traffic */
  while (1) {
    if (recvfrom (sock, message, sizeof (message), 0, (struct sockaddr *) &recv_sin, &addrlen) == SOCKET_ERROR) {
        perror("recvfrom");
        closesocket (sock);
        return FALSE;
    }
    else  {
        printf("%s: message received = \"%s\"\n", inet_ntoa(recv_sin.sin_addr), message);
    }
  }

  // Disable receiving on sock before closing it.
  shutdown (sock, 0x00);
  // Close sock.
  closesocket (sock);
  WSACleanup ();
  return TRUE;
}

#endif // _WIN32
