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
#include <time.h>       /* for timestamps */
#include "testip6.h"
#include "mcast6-client.h"          // Required for socks specific headers

int mcast6_client(const char *mcast_group, int receiving_port) {

  socklen_t addrlen;                  // Length of recv_sin
  char message[100];                  // ASCII string
  SOCKET sock = INVALID_SOCKET;       // Datagram window socket
  struct ipv6_mreq mreq;              // Used in adding or dropping multicasting addresses
  struct addrinfo *multicastAddr,     // Multicast Address
                  *localAddr;         // Local address to bind to
  struct addrinfo hints = { 0 };      // Hints for name lookup
  SOCKADDR_IN6 recv_sin;              // Holds the source address upon recvfrom function returns
  char string_port[8] = "";           // Holds the port number as a string
  char buffer[8];                     //output string (already filled with something)
  char ipstr[INET6_ADDRSTRLEN];       // string where we store the source ip address

#ifdef _WIN32
  WSADATA WSAData;                    // Contains details of the winsock implementation

  /* Initialize Winsock. */
  if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0) {
    perror("WSAStartup");
    return FALSE;
  }
#endif // _WIN32

  sprintf(buffer, "%d", receiving_port);
  strcat(string_port, buffer);

  /* Resolve the multicast group address */
  hints.ai_family = PF_UNSPEC;
  hints.ai_flags  = AI_NUMERICHOST;
  if ( getaddrinfo(mcast_group, NULL, &hints, &multicastAddr) != 0 ) {
    perror("getaddrinfo");
    return FALSE;
  }

  /* Get a local address with the same family (IPv4 or IPv6) as our multicast group */
  hints.ai_family   = multicastAddr->ai_family;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags    = AI_PASSIVE; /* Return an address we can bind to */
  if ( getaddrinfo(NULL, string_port, &hints, &localAddr) != 0 ) {
    perror("getaddrinfo");
    return FALSE;
  }

  /* Create socket for receiving datagrams */
  if ((sock = socket(localAddr->ai_family, localAddr->ai_socktype, 0)) == INVALID_SOCKET ) {
    perror("socket");
    return FALSE;
  }

  /* Bind to the multicast port */
  if (bind(sock, localAddr->ai_addr, localAddr->ai_addrlen) == SOCKET_ERROR) {
    perror("bind");
    closesocket(sock);
    return FALSE;
  }

  /* Join the multicast group from which to receive datagrams. */
  /* Specify the multicast group */
  memcpy(&mreq.ipv6mr_multiaddr, &((struct sockaddr_in6*)(multicastAddr->ai_addr))->sin6_addr,  sizeof(mreq.ipv6mr_multiaddr));
  /* Accept multicast from any interface */
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

  freeaddrinfo(localAddr);
  freeaddrinfo(multicastAddr);

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
