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
  SOCKET sock;                      // Socket
  struct addrinfo* multicastAddr;   // Multicast Address
  struct addrinfo* localAddr;       // Local address to bind to
  struct addrinfo  hints = { 0 };   // Hints for name lookup
  char string_port[8] = "";
  char buffer[8]; //output string (already filled with something)

  sprintf(buffer, "%d", receiving_port);
  strcat(string_port, buffer);

 #ifdef _WIN32
  WSADATA WSAData;                    // Contains details of the winsock implementation

  /* Initialize Winsock. */
  if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0) {
    perror("WSAStartup");
    return FALSE;
  }
#endif // _WIN32

    /* Resolve the multicast group address */
    hints.ai_family = PF_UNSPEC;
    hints.ai_flags  = AI_NUMERICHOST;
    if ( getaddrinfo(mcast_group, NULL, &hints, &multicastAddr) != 0 ) {
        perror("getaddrinfo");
    }

    /* Get a local address with the same family (IPv4 or IPv6) as our multicast group */
    hints.ai_family   = multicastAddr->ai_family;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_PASSIVE; /* Return an address we can bind to */
    if ( getaddrinfo(NULL, string_port, &hints, &localAddr) != 0 ) {
        perror("getaddrinfo");
    }

    /* Create socket for receiving datagrams */
    if ( (sock = socket(localAddr->ai_family, localAddr->ai_socktype, 0)) == INVALID_SOCKET ) {
        perror("socket");
    }

    /* Bind to the multicast port */
    if ( bind(sock, localAddr->ai_addr, localAddr->ai_addrlen) != 0 ) {
        perror("bind");
    }

    // Join the multicast group.
    if ( multicastAddr->ai_family  == PF_INET6 && multicastAddr->ai_addrlen == sizeof(struct sockaddr_in6)) {
        struct ipv6_mreq multicastRequest;  /* Multicast address join structure */

        /* Specify the multicast group */
        memcpy(&multicastRequest.ipv6mr_multiaddr,
               &((struct sockaddr_in6*)(multicastAddr->ai_addr))->sin6_addr,
               sizeof(multicastRequest.ipv6mr_multiaddr));

        /* Accept multicast from any interface */
        multicastRequest.ipv6mr_interface = 0;

        /* Join the multicast address */
        if ( setsockopt(sock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char*) &multicastRequest, sizeof(multicastRequest)) != 0 )
        {
            perror("setsockopt");
        }
    }

    freeaddrinfo(localAddr);
    freeaddrinfo(multicastAddr);

    while (1) {
        time_t timer;
        char   recvString[500];      /* Buffer for received string */
        int    recvStringLen;        /* Length of received string */

        /* Receive a single datagram from the server */
        if ((recvStringLen = recvfrom(sock, recvString, sizeof(recvString) - 1, 0, NULL, 0)) < 0 ) {
            perror("recvfrom");
        }

        recvString[recvStringLen] = '\0';

        /* Print the received string */
        time(&timer);  /* get time stamp to print with recieved data */
        printf("Time Received: %.*s : %s\n", strlen(ctime(&timer)) - 1, ctime(&timer), recvString);
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
