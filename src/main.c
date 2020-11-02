/*
* main.c
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
#include <string.h>                 // Required for strcmp()
#include <stdlib.h>                 // Required for system()
#include "mcast-server.h"
#include "mcast-client.h"
#include "testip.h"
#ifdef HAVE_ARGP_H
#include <argp.h>
#else
#include "../libargp/gllib/argp.h"
#endif

void clean_screen() {
/* FIX ME - I don't like this solution */
#ifdef _WIN32
   if(system("cls")){};
#else
   if(system("clear")){};
#endif
}

void press_enter_to_continue() {
  int c;
  fflush(stdin);
  printf("Press ENTER to continue... ");
  fflush(stdout);
  do c = getchar(); while ((c != '\n') && (c != EOF));
}

void print_help() {
    printf("Usage: ./multicast [PROTOCOL] [OPERATIONAL MODE] [OPTION] [OPTION] ... \n\n");
    printf("  -V, --version\tprint current version and exit\n");
    printf("  --help\tprint this help and exit\n\n");
    printf("Run without arguments to run the interactive console.\n");
    printf("To run without interaction, use the options below.\n");
    printf("One per each group is required.\n\n");
    printf("IP protocol version:\n");
    printf("  -v4\t\t\twill use IPv4\n");
    printf("  -v6\t\t\twill use IPv6\n\n");
    printf("Operational mode:\n");
    printf("  -server\t\tRun as a multicast server\n");
    printf("  -client\t\tRun as a multicast client\n");
    printf("  -client-ssm\t\tRun as a multicast client with SSM support\n\n");
    printf("Options:\n");
    printf("  -group [IP ADDRESS]\tSpecify the Multicast group's IP address\n");
    printf("  -source [IP ADDRESS]\tONLY if '-client-ssm' is used\n\t\t\tSpecify the IP address of the authorized source\n");
    printf("  -port [NUMBER]\tSelect the port number. Below 1024 requires\n\t\t\tadministator rights\n");
    printf("  -delay [NUMBER]\tONLY if '-server' is used\n\t\t\tSet the delay, in seconds, beteween packets\n");
    printf("  -ttl [NUMBER]\t\tONLY if '-server' is used\n\t\t\tSet the ttl, between 1 and 255\n");
    printf("Example of usage:\n");
    printf("  multicast -v4 -server -group 239.1.2.3 -port 9999 -ttl 64 -delay 1\n");
    printf("  multicast -v6 -client -group FF05::3232 -port 9999\n");
    printf("  multicast -v4 -client-ssm -group 232.1.2.3 -source 10.0.0.1 -port 9999\n");
}

void print_error() {
    printf("invalid options. Run again with \"--help\" for usage manual\n");
}

void interactive_menu() {

   char mcast_group[INET6_ADDRSTRLEN] = "0.0.0.0";
   char ssm_source[INET6_ADDRSTRLEN] = "0.0.0.0";
   int destination_port = 1;
   int delay = 1;
   int ttl = 1;
   struct in6_addr ip_address;
   char choice[100] = "0";

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
    if(scanf("%s", choice)){};

    if (strcmp(choice,"1") == 0 ) {
        printf("Enter the multicast destination address, in case of SSM\n");
        printf("the IP must be in the range 232.0.0.0/8: ");
        if(scanf("%s", mcast_group)){};
        if (is_valid_mcast_ip4(mcast_group) == TRUE ) {
            printf("Enter the destination port number: ");
            if(scanf("%d", &destination_port)){};
            if (destination_port >= 0 && destination_port <= 65535) {
                    printf("Enter the TTL value: ");
                    if(scanf("%d", &ttl)){};
                    if (ttl >= 1 && ttl <= 255) {
                        printf("Enter the interval between packets in seconds: ");
                        if(scanf("%d", &delay)){};
                        /* we are ready , let start the server */
                        mcast_server4(mcast_group, destination_port, delay, ttl);
                        
                    }
                    else {
                        printf("invalid TTL value!\n");
                        
                    }
            }
            else {
                    printf("Invalid port number!\n");
            }
        }
        else {
            printf("Invalid multicast group address!\n");
        }
        press_enter_to_continue();
        clean_screen();
    }
    else if (strcmp(choice,"2") == 0 ) {
        printf("Enter the multicast group address to join: ");
        if(scanf("%s", mcast_group)){};

        if (is_valid_mcast_ip4(mcast_group) == TRUE ) {
            printf("Enter the port number to listen to: ");
            if(scanf("%d", &destination_port)){};
            if (destination_port >= 0 && destination_port <= 65535) {

                    /* we are ready , let start the client */
                    mcast_client4(mcast_group, destination_port);
            }
            else {
                    printf("Invalid port number!\n");
            }
        }
        else {
            printf("Invalid multicast group address!\n");
        }
        press_enter_to_continue();
        clean_screen();
    }
    else if (strcmp(choice,"3") == 0 ) {
        printf("Enter the multicast group address to join,\n");
        printf("the IP must be in the range 232.0.0.0/8: ");
        if(scanf("%s", mcast_group)){};

        if (is_valid_ssm_ip4(mcast_group) == TRUE ) {
            printf("Enter the ip address of the authorized source: ");
            if(scanf("%s", ssm_source)){};

            if (is_valid_ip(ssm_source) == AF_INET ) {
                    printf("Enter the destination port number: ");
                    if(scanf("%d", &destination_port)){};
                    if (destination_port >= 0 && destination_port <= 65535) {

                        /* we are ready , let start the client */
                        ssm_client4(mcast_group, ssm_source, destination_port);
                    }
                    else {
                        printf("Invalid port number!\n");
                    }
            }
            else {
                printf("Invalid IP address!\n");
            }
        }
        else {
            printf("Invalid multicast group address!\n");
        }
        press_enter_to_continue();
        clean_screen();
    }
    else if (strcmp(choice,"4") == 0 ) {
        printf("Enter the multicast destination address, in case of SSM\n");
        printf("the IP must be in the range FF3x::/32: ");
        if(scanf("%s", mcast_group)){};

        inet_pton(AF_INET6, mcast_group, &ip_address);
        if (IN6_IS_ADDR_MULTICAST(&ip_address) == TRUE ) {
            printf("Enter the destination port number: ");
            if(scanf("%d", &destination_port)){};
            if (destination_port >= 0 && destination_port <= 65535) {
                    printf("Enter the TTL value: ");
                    if(scanf("%d", &ttl)){};
                    if (ttl >= 1 && ttl <= 255) {
                        printf("Enter the interval between packets in seconds: ");
                        if(scanf("%d", &delay)){};
                        /* we are ready , let start the server */
                        mcast_server6(mcast_group, destination_port, delay, ttl);
                        
                    }
                    else {
                        printf("invalid TTL value!\n");
                        
                    }
            }
            else {
                    printf("Invalid port number!\n");
            }
        }
        else {
            printf("Invalid multicast group address!\n");
        }
        press_enter_to_continue();
        clean_screen();
    }
    else if (strcmp(choice,"5") == 0 ) {
        printf("Enter the multicast group address to join: ");
        if(scanf("%s", mcast_group)){};

        inet_pton(AF_INET6, mcast_group, &ip_address);
        if (IN6_IS_ADDR_MULTICAST(&ip_address) == TRUE ) {
			printf("Enter the port number to listen to: ");
            if(scanf("%d", &destination_port)){};
            if (destination_port >= 0 && destination_port <= 65535) {

                    /* we are ready , let start the client */
                    mcast_client6(mcast_group, destination_port);
            }
            else {
                    printf("Invalid port number!\n");
            }
        }
        else {
            printf("Invalid multicast group address!\n");
        }
        press_enter_to_continue();
        clean_screen();
    }
    else if (strcmp(choice,"6") == 0 ) {
        printf("IPv6 - Source Specific Multicast Client is still experimental\n");
        /* still not working properly */
        printf("Enter the multicast destination address,\n");
        printf("the IP must be in the range FF3x::/32: ");

        if(scanf("%s", mcast_group)){};

        inet_pton(AF_INET6, mcast_group, &ip_address);
        if (IN6_IS_ADDR_MULTICAST(&ip_address) == TRUE ) {
            printf("Enter the ip address of the authorized source: ");
            if(scanf("%s", ssm_source)){};

            if (is_valid_ip(ssm_source) == AF_INET6 ) {
                    printf("Enter the destination port number: ");
                    if(scanf("%d", &destination_port)){};
                    if (destination_port >= 0 && destination_port <= 65535) {

                        // we are ready , let start the client
                        ssm_client6(mcast_group, ssm_source, destination_port);
                    }
                    else {
                        printf("Invalid port number!\n");
                    }
            }
            else {
                printf("Invalid IP address!\n");
            }
       }
        else {
            printf("Invalid multicast group address!\n");
        }
        press_enter_to_continue();
        clean_screen();

    }
    else if (strcmp(choice,"7") == 0 ) {
        printf("Quitting program!\n");
    }
    else {
        printf("Invalid choice! \n");
        press_enter_to_continue();
        clean_screen();
       }
   } while (strcmp(choice,"7") != 0);
}

int main(int argc, char *argv[]) {

   struct in6_addr ip_address;

   if (argc == 1) {
        interactive_menu();
   }
   else if (argc == 2) {
        if (strcmp(argv[1],"--help") == 0) {
            print_help();
        }
        else if ((strcmp(argv[1],"--version") == 0) || (strcmp(argv[1],"-V")) ) {
            printf("simple-%s - version %s\n", PACKAGE_NAME, PACKAGE_VERSION);
	    printf("\nWritten by Andrea Florio <andrea@opensuse.org>\n");
        }
        else {
            print_error();
        }
   }
   else if (argc == 7) {
       /* I don't like this, i want to allow to put options in any order */
        if ((strcmp(argv[2],"-client") == 0) &&
            (strcmp(argv[3],"-group") == 0) &&
            (strcmp(argv[5],"-port") == 0)) {

            if (strcmp(argv[1],"-v4") == 0) { /* we are using IPv4 */
                if (is_valid_mcast_ip4(argv[4]) == TRUE ) {
                        if (atoi(argv[6]) >= 1 && atoi(argv[6]) <= 65535) {
                            /* we are ready , let start the client */
                            mcast_client4(argv[4], atoi(argv[6]));
                        }
                        else {
                            printf("Invalid port number!\n");
                        }
                }
                else {
                    printf("Invalid multicast group address!\n");
                }
            }
            else if (strcmp(argv[1],"-v6") == 0) { /* we are using IPv6 */
                inet_pton(AF_INET6, argv[4], &ip_address);
                if (IN6_IS_ADDR_MULTICAST(&ip_address) == TRUE ) {
                        if (atoi(argv[6]) >= 0 && atoi(argv[6]) <= 65535) {
                            /* we are ready , let start the client */
                            mcast_client6(argv[4], atoi(argv[6]));
                        }
                        else {
                            printf("Invalid port number!\n");
                        }
                }
                else {
                    printf("Invalid multicast group address!\n");
                }

            }
            else {
                print_error();
            }
        }
        else {
            print_error();
        }
   }
   else if (argc == 11) {
        if ((strcmp(argv[2],"-server") == 0) &&
            (strcmp(argv[3],"-group") == 0) &&
            (strcmp(argv[5],"-port") == 0) &&
            (strcmp(argv[7],"-ttl") == 0) &&
            (strcmp(argv[9],"-delay") == 0)) {

            if (strcmp(argv[1],"-v4") == 0) { /* we are using IPv4 */
                if (is_valid_mcast_ip4(argv[4]) == TRUE ) {
                        if (atoi(argv[6]) >= 1 && atoi(argv[6]) <= 65535) {
                            if(atoi(argv[8]) >= 1 && atoi(argv[8]) <= 255) {
                                /* we are ready , let start the server */
                                mcast_server4(argv[4], atoi(argv[6]), atoi(argv[10]), atoi(argv[8]));
                            }
                            else {
                                printf("invalid TTL value!\n");
                            }
                        }
                        else {
                            printf("Invalid port number!\n");
                        }
                }
                else {
                    printf("Invalid multicast group address!\n");
                }
            }
            else if (strcmp(argv[1],"-v6") == 0) { /* we are using IPv6 */
                inet_pton(AF_INET6, argv[4], &ip_address);
                if (IN6_IS_ADDR_MULTICAST(&ip_address) == TRUE ) {
                        if (atoi(argv[6]) >= 1 && atoi(argv[6]) <= 65535) {
                            if(atoi(argv[8]) >= 1 && atoi(argv[10]) <= 8) {
                                /* we are ready , let start the server */
                                mcast_server6(argv[4], atoi(argv[6]), atoi(argv[10]), atoi(argv[8]));
                            }
                            else {
                                printf("invalid TTL value!\n");
                            }
                        }
                        else {
                            printf("Invalid port number!\n");
                        }
                }
                else {
                    printf("Invalid multicast group address!\n");
                }
            }
            else {
                print_error();
            }
        }
        else if ((strcmp(argv[2],"-client-ssm") == 0) &&
                 (strcmp(argv[3],"-group") == 0) &&
                 (strcmp(argv[5],"-source") == 0) &&
                 (strcmp(argv[7],"-port") == 0)) {

            if (strcmp(argv[1],"-v4") == 0) { /* we are using IPv4 */
                if (is_valid_ssm_ip4(argv[4]) == TRUE ) {
			if (is_valid_ip(argv[6]) == AF_INET ) {
				if (atoi(argv[8]) >= 0 && atoi(argv[8]) <= 65535) {
					/* we are ready , let start the client */
					ssm_client4(argv[4], argv[6], atoi(argv[8]));
					}
				else {
					printf("Invalid port number!\n");
				}
			}
			else {
				printf("Invalid IP address\n");
			}
                }
                else {
                    printf("Invalid multicast group address!\n");
                }
            }
            else if (strcmp(argv[1],"-v6") == 0) { /* we are using IPv6 */
                inet_pton(AF_INET6, argv[4], &ip_address);
                if (IN6_IS_ADDR_MULTICAST(&ip_address) == TRUE ) {
			if (is_valid_ip(argv[6]) == AF_INET6 ) {
				if (atoi(argv[8]) >= 0 && atoi(argv[8]) <= 65535) {
					/* we are ready , let start the client */
					ssm_client6(argv[4], argv[6], atoi(argv[8]));
				}
				else {
					printf("Invalid port number!\n");
				}
			}
			else {
				printf("Invalid IP address\n");
			}
		}
                else {
                    printf("Invalid multicast group address!\n");
                }
            }
            else {
                print_error();
            }
        }
        else {
            print_error();
        }

   }
   else {
        print_error();
   }

   return 0;
}
