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

/* TO DO - Verify that IPs given in input are valid IPs */
#include <stdio.h>                  // Required for printf() and sprintf()
#include "mcast-server.h"
#include "mcast-client.h"

int main() {
   char mcast_group[15] = "0.0.0.0";
   char ssm_source[15] = "0.0.0.0";
   int destination_port = 1;
   int delay = 1;
   int choice = 0;

   do {
    printf("Menu:\n\n");
    printf("1. Multicast Server\n");
    printf("2. Simple Multicast Client\n");
    printf("3. Source Specific Multicast Client\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Enter the multicast destination address, in case of SSM\n");
            printf("the IP must be in the range 232.0.0.0/8: ");
            scanf("%s", mcast_group);
            printf("Enter the destination port number: ");
            scanf("%d", &destination_port);
            printf("Enter the interval between packets in seconds: ");
            scanf("%d", &delay);
#ifdef _WIN32
            delay = delay*1000;
            mcast_server_win(mcast_group, destination_port, delay);
#else
            mcast_server_unix(mcast_group, destination_port, delay);
#endif // _WIN32
            break;
        case 2:
            printf("Enter the multicast group address to join: ");
            scanf("%s", mcast_group);
            printf("Enter the port number to listen to: ");
            scanf("%d", &destination_port);
#ifdef _WIN32
            mcast_client_win(mcast_group, destination_port);
#else
            mcast_client_unix(mcast_group, destination_port);
#endif // _WIN32
            break;
        case 3:
            printf("Enter the multicast group address to join,\n");
            printf("the IP must be in the range 232.0.0.0/8: ");
            scanf("%s", mcast_group);
            printf("Enter the ip address of the authorized source: ");
            scanf("%s", ssm_source);
            printf("Enter the port number to listen to: ");
            scanf("%d", &destination_port);
#ifdef _WIN32
            ssm_client_win(mcast_group, ssm_source, destination_port);
#else
            ssm_client_unix(mcast_group, ssm_source, destination_port);
#endif // _WIN32
            break;
        case 4:
            printf("Quitting program!\n");
            return 0;
            break;
        default:
            printf("Invalid choice! \n");
            break;
    }
   } while (choice != 4);

   return 0;
}
