/*
* ssm-client.c
* Copyright (C) Andrea Florio 2020 <andrea@opensuse.org>
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


#include <stdio.h>                  // Required for printf() and sprintf()
#include <string.h>		    // Required for memset()
#include "mcast-client.h"

int ssm_client4(const char *mcast_group, const char *ssm_source, int receiving_port) {

  struct ip_mreq_source mreq;         // SSM information container
  socklen_t addrlen;                  // Length of recv_sin
  char message[100];                  // ASCII string
  SOCKET sock = INVALID_SOCKET;       // Datagram window socket
  SOCKADDR_IN local_sin,              // Local socket's address
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
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
    perror("sock");
    return FALSE;
  }

  /* Fill in the destination address information */
  memset(&local_sin, 0, sizeof(SOCKADDR_IN));
  local_sin.sin_family = AF_INET;
  local_sin.sin_port = htons(receiving_port);
  local_sin.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Fill in the destination address information */
  if (bind (sock, (struct sockaddr *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR) {
    perror("bind");
    closesocket(sock);
    return FALSE;
  }

  /* Set up the connection to the group */
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  mreq.imr_multiaddr.s_addr  = inet_addr(mcast_group);
  mreq.imr_sourceaddr.s_addr = inet_addr(ssm_source);

#ifdef _WIN32
  if (setsockopt(sock, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) == SOCKET_ERROR) {
#else
  if (setsockopt(sock, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, &mreq, sizeof(mreq)) == SOCKET_ERROR) {
#endif // _WIN32
    perror("setsockopt mreq");
    closesocket(sock);
    return FALSE;
  }

  addrlen = sizeof(recv_sin);

  /* Let's receive our traffic */
  while (1) {
    if (recvfrom (sock, message, sizeof(message), 0, (struct sockaddr *)&recv_sin, &addrlen) == SOCKET_ERROR) {
        perror("recvfrom");
        closesocket(sock);
        return FALSE;
    }
    printf("%s: message received = \"%s\"\n", inet_ntoa(recv_sin.sin_addr), message);
  }

  /* Disable receiving on sock before closing it. */
  shutdown(sock, 0x00);
#ifdef _WIN32
  /* Close sock. */
  closesocket(sock);
  WSACleanup ();
#endif // _WIN32
  return TRUE;
}

int ssm_client6(const char *mcast_group, const char *ssm_source, int receiving_port) {

  struct group_source_req mreq;       // SSM information container
  socklen_t addrlen;                  // Length of recv_sin
  char message[100];                  // ASCII string
  char ipstr[INET6_ADDRSTRLEN];       // string where we store the source ip address
  SOCKET sock = INVALID_SOCKET;       // Datagram window socket
  SOCKADDR_IN6 local_sin,             // Local socket's address
               recv_sin;              // Holds the source address upon recvfrom function returns
  SOCKADDR_STORAGE buffer;            // Holds the IPv6 address, just a buffer

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

  /* Set up the connection to the group */
  memset(&mreq, 0, sizeof(mreq));
  mreq.gsr_interface = 0;

  /* clean buffer and set the group address */
  memset(&buffer, 0, sizeof(SOCKADDR_STORAGE));
  j_inet_pton(mcast_group, &buffer);
  mreq.gsr_group = buffer;

  /* clean buffer and set the source address */
  memset(&buffer, 0, sizeof(SOCKADDR_STORAGE));
  j_inet_pton(ssm_source, &buffer);
  mreq.gsr_source = buffer;


#ifdef _WIN32
  if (setsockopt(sock, IPPROTO_IPV6, MCAST_JOIN_SOURCE_GROUP, (char *)&mreq, sizeof(mreq)) == SOCKET_ERROR) {
#else
  if (setsockopt(sock, IPPROTO_IPV6, MCAST_JOIN_SOURCE_GROUP, &mreq, sizeof(mreq)) == SOCKET_ERROR) {
#endif // _WIN32
    perror("setsockopt mreq");
    closesocket(sock);
    return FALSE;
  }

  addrlen = sizeof(recv_sin);

  /* Let's receive our traffic */
  while (1) {
    if (recvfrom (sock, message, sizeof(message), 0, (struct sockaddr *)&recv_sin, &addrlen) == SOCKET_ERROR) {
        perror("recvfrom");
        closesocket(sock);
        return FALSE;
    }
    getpeername(sock, (struct sockaddr*)&recv_sin, &addrlen);
    inet_ntop(AF_INET6, &recv_sin.sin6_addr, ipstr, sizeof ipstr);
    printf("%s: message received = \"%s\"\n", ipstr, message);
    }

  /* Disable receiving on sock before closing it. */
  shutdown(sock, 0x00);
#ifdef _WIN32
  /* Close sock. */
  closesocket(sock);
  WSACleanup ();
#endif // _WIN32
  return TRUE;
}
