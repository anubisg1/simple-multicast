/*
* mcast6-client.c
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
#include "mcast6-client.h"          // Required for socks specific headers

int mcast6_client(const char *mcast_group, int receiving_port) {

  socklen_t addrlen;                  // Length of recv_sin
  char message[100];                  // ASCII string
  char ipstr[INET6_ADDRSTRLEN];       // string where we store the source ip address
  SOCKET sock = INVALID_SOCKET;       // Datagram window socket
  struct ipv6_mreq mreq;              // Used in adding or dropping multicasting addresses
  SOCKADDR_IN6 local_sin,             // Local socket's address
              recv_sin;               // Holds the source address upon recvfrom function returns
 #ifdef _WIN32
  WSADATA WSAData;                    // Contains details of the winsock implementation

  /* Initialize Winsock. */
  if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0) {
    perror("WSAStartup");
    return FALSE;
  }
#endif // _WIN32

  /* Create a datagram socket, sock. */
  if ((sock = socket(AF_INET6, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
    perror("sock");
    return FALSE;
  }

  /* Fill in the destination address information */
  memset(&local_sin, 0, sizeof(SOCKADDR_IN6));
  local_sin.sin6_family = AF_INET6;
  local_sin.sin6_port = htons (receiving_port);
  local_sin.sin6_addr = in6addr_any;

  /* Associate the local address with the sock */
  if (bind(sock, (struct sockaddr *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR) {
    perror("bind");
    closesocket(sock);
    return FALSE;
  }

  /* Join the multicast group from which to receive datagrams. */
  inet_pton(AF_INET6, mcast_group, &(mreq.ipv6mr_multiaddr) );
  mreq.ipv6mr_interface = 0;

#ifdef _WIN32
  if (setsockopt(sock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) == SOCKET_ERROR) {
#else
  if (setsockopt(sock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == SOCKET_ERROR) {
#endif //_WIN32
    perror("setsockopt mreq");
    closesocket(sock);
    return FALSE;
  }

  addrlen = sizeof(recv_sin);

  /* Let's receive our traffic */
  while (1) {
    if (recvfrom(sock, message, sizeof(message), 0, (struct sockaddr *)&recv_sin, &addrlen) == SOCKET_ERROR) {
        perror("recvfrom");
        closesocket(sock);
        return FALSE;
    }
    getpeername(sock, (struct sockaddr*)&recv_sin, &addrlen);
    inet_ntop(AF_INET6, &recv_sin.sin6_addr, ipstr, sizeof ipstr);
    printf("%s: message received = \"%s\"\n", ipstr, message);
  }

  // Disable receiving on sock before closing it.
  shutdown(sock, 0x00);
#ifdef _WIN32
  // Close sock.
  closesocket(sock);
  WSACleanup ();
#endif // _WIN32
  return TRUE;
}
