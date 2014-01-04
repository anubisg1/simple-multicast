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
#include "mcast-server.h"
#include "mcast-client.h"
#include "testip.h"

int main() {
   char mcast_group[15] = "0.0.0.0";
   char ssm_source[15] = "0.0.0.0";
   int destination_port = 1;
   int delay = 1;
   char choice[100] = "0";

/* FIX ME - I don't like this solution */
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif

   printf("simple-multicast version 0.1.2\n\n");
   do {
    printf("Menu:\n\n");
    printf("1. Multicast Server\n");
    printf("2. Simple Multicast Client\n");
    printf("3. Source Specific Multicast Client\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%s", choice);

    if (strcmp(choice,"1") == 0 ) {
        printf("Enter the multicast destination address, in case of SSM\n");
        printf("the IP must be in the range 232.0.0.0/8: ");
        scanf("%s", mcast_group);
        if (is_valid_mcast_ip(mcast_group) == 0 ) {
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
#ifdef _WIN32
        delay = delay*1000;
        mcast_server_win(mcast_group, destination_port, delay);
#else
        mcast_server_unix(mcast_group, destination_port, delay);
#endif // _WIN32
    }
    else if (strcmp(choice,"2") == 0 ) {
        printf("Enter the multicast group address to join: ");
        scanf("%s", mcast_group);
        if (is_valid_mcast_ip(mcast_group) == 0 ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }
        printf("Enter the port number to listen to: ");
        scanf("%d", &destination_port);
        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }
#ifdef _WIN32
        mcast_client_win(mcast_group, destination_port);
#else
        mcast_client_unix(mcast_group, destination_port);
#endif // _WIN32
    }
    else if (strcmp(choice,"3") == 0 ) {
        printf("Enter the multicast group address to join,\n");
        printf("the IP must be in the range 232.0.0.0/8: ");
        scanf("%s", mcast_group);
        if (is_valid_ssm_ip(mcast_group) == 0 ) {
            printf("Invalid multicast group address!\n");
            return 0;
        }
        printf("Enter the ip address of the authorized source: ");
        scanf("%s", ssm_source);
        if (is_valid_ip(ssm_source) == 0 ) {
            printf("Invalid IP address!\n");
            return 0;
        }
        printf("Enter the port number to listen to: ");
        scanf("%d", &destination_port);
        if (destination_port < 0 || destination_port > 65535) {
            printf("Invalid port number!\n");
            return 0;
        }
#ifdef _WIN32
        ssm_client_win(mcast_group, ssm_source, destination_port);
#else
        ssm_client_unix(mcast_group, ssm_source, destination_port);
#endif // _WIN32
    }
    else if (strcmp(choice,"4") == 0 ) {
        printf("Quitting program!\n");
        return 0;
    }
    else {
        printf("Invalid choice! \n");
/* FIX ME - I don't like this solution */
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
   } while (strcmp(choice,"4") != 0);

   return 0;
}
