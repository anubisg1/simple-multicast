/*
* main.c
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

#include <stdio.h>                  // Required for printf() and sprintf()
#include <string.h>                 // Required for strcmp()
#include <stdlib.h>		            // Required for system()
#include "ipv4/mcast-server.h"
#include "ipv4/mcast-client.h"
#include "testip.h"
#include "ipv6/mcast6-server.h"
#include "ipv6/mcast6-client.h"

#define VERSION "0.2.2"

void clean_screen() {
/* FIX ME - I don't like this solution */
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}

void PressEnterToContinue() {
  int c;
  printf( "Press ENTER to continue... " );
  fflush( stdout );
  do c = getchar(); while ((c != '\n') && (c != EOF));
  }

int main() {
   char mcast_group[INET6_ADDRSTRLEN] = "0.0.0.0";
   char ssm_source[INET6_ADDRSTRLEN] = "0.0.0.0";
   struct in6_addr ip_address;
   int destination_port = 1;
   int delay = 1;
   char choice[100] = "0";

   clean_screen();

   printf("simple-multicast version %s\n\n",  VERSION);
   do {
    printf("Menu:\n\n");
    printf("1. IPv4 - Multicast Server\n");
    printf("2. IPv4 - Simple Multicast Client\n");
    printf("3. IPv4 - Source Specific Multicast Client\n");
    printf("4. IPv6 - Multicast Server\n");
    printf("5. IPv6 - Simple Multicast Client\n");
    printf("6. IPv6 - Source Specific Multicast Client\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%s", choice);

    if (strcmp(choice,"1") == 0 ) {
        printf("Enter the multicast destination address, in case of SSM\n");
        printf("the IP must be in the range 232.0.0.0/8: ");
        scanf("%s", mcast_group);

        if (is_valid_mcast_ip4(mcast_group) == FALSE ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }

        printf("Enter the destination port number: ");
        scanf("%d", &destination_port);
        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }

        printf("Enter the interval between packets in seconds: ");
        scanf("%d", &delay);

	/* we are ready , let start the server */
        mcast_server(mcast_group, destination_port, delay);
    }
    else if (strcmp(choice,"2") == 0 ) {
        printf("Enter the multicast group address to join: ");
        scanf("%s", mcast_group);

        if (is_valid_mcast_ip4(mcast_group) == FALSE ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }

        printf("Enter the port number to listen to: ");
        scanf("%d", &destination_port);

        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }

        /* we are ready , let start the client */
        mcast_client(mcast_group, destination_port);
    }
    else if (strcmp(choice,"3") == 0 ) {
        printf("Enter the multicast group address to join,\n");
        printf("the IP must be in the range 232.0.0.0/8: ");
        scanf("%s", mcast_group);

        if (is_valid_ssm_ip4(mcast_group) == FALSE ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }

        printf("Enter the ip address of the authorized source: ");
        scanf("%s", ssm_source);

        if (is_valid_ip(ssm_source) != AF_INET ) {
            printf("Invalid IP address!\n");
            return 0;
        }

        printf("Enter the port number to listen to: ");
        scanf("%d", &destination_port);

        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }

        /* we are ready , let start the client */
       ssm_client(mcast_group, ssm_source, destination_port);
    }
    else if (strcmp(choice,"4") == 0 ) {
        printf("Enter the multicast destination address, in case of SSM\n");
        printf("the IP must be in the range FF3x::/32: ");
        scanf("%s", mcast_group);

        inet_pton(AF_INET6, mcast_group, &ip_address);
        if (IN6_IS_ADDR_MULTICAST(&ip_address) == FALSE ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }

        printf("Enter the destination port number: ");
        scanf("%d", &destination_port);
        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }

        printf("Enter the interval between packets in seconds: ");
        scanf("%d", &delay);

	/* we are ready , let start the server */
        mcast6_server(mcast_group, destination_port, delay);
    }
    else if (strcmp(choice,"5") == 0 ) {
        printf("Enter the multicast group address to join: ");
        scanf("%s", mcast_group);

        inet_pton(AF_INET6, mcast_group, &ip_address);
        if (IN6_IS_ADDR_MULTICAST(&ip_address) == FALSE ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }

        printf("Enter the port number to listen to: ");
        scanf("%d", &destination_port);

        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }

        /* we are ready , let start the client */
        mcast6_client(mcast_group, destination_port);
    }
    else if (strcmp(choice,"6") == 0 ) {
        printf("IPv6 - Source Specific Multicast Client not implemented yet\n");
        fflush(stdin);
        PressEnterToContinue();
        clean_screen();
/*
        printf("Enter the multicast group address to join: ");
        scanf("%s", mcast_group);

        inet_pton(AF_INET6, mcast_group, &ip_address);
        if (IN6_IS_ADDR_MULTICAST(&ip_address) == FALSE ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }

        printf("Enter the ip address of the authorized source: ");
        scanf("%s", ssm_source);

        if (is_valid_ip(ssm_source) != AF_INET6) {
            printf("Invalid multicast group address!\n");
            return 0;
        }
        printf("Enter the port number to listen to: ");
        scanf("%d", &destination_port);

        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }

        // we are ready , let start the client
       ssm_client6(mcast_group, ssm_source, destination_port); */

    }
    else if (strcmp(choice,"7") == 0 ) {
        printf("Quitting program!\n");
        return 0;
    }
    else {
        printf("Invalid choice! \n");
        fflush(stdin);
        PressEnterToContinue();
        clean_screen();
       }
   } while (strcmp(choice,"7") != 0);

   return 0;
}

