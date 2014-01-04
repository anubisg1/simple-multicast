/*
* testip.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testip.h"

/* return 1 if string contain only digits, else return 0 */
int valid_digit(const char *ip_str) {
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return 0;
    }
    return 1;
}

/* return 1 if IP string is valid, else return 0 */
int is_valid_ip(const char *my_ip_str) {
    int num, dots = 0;
    char *ptr;

    if (my_ip_str == NULL)
        return 0;

    // See following link for strtok()
    // http://pubs.opengroup.org/onlinepubs/009695399/functions/strtok_r.html
   char *ip_str = malloc (1 + strlen (my_ip_str));
   if (ip_str)
       strcpy (ip_str, my_ip_str);
   else
	fprintf (stderr, "malloc failure!");

    ptr = strtok(ip_str, DELIM);

    if (ptr == NULL)
        return 0;

    while (ptr) {

        /* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return 0;

        num = atoi(ptr);

        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        } else
            return 0;
    }

    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return 0;
    return 1;
}

/* return 1 if IP string is valid, else return 0 */
int is_valid_mcast_ip(const char *my_ip_str) {
    int num, dots = 0;
    char *ptr;

    if (my_ip_str == NULL)
        return 0;

    // See following link for strtok()
    // http://pubs.opengroup.org/onlinepubs/009695399/functions/strtok_r.html
   char *ip_str = malloc (1 + strlen (my_ip_str));
   if (ip_str)
       strcpy (ip_str, my_ip_str);
   else
        fprintf (stderr, "malloc failure!");

    ptr = strtok(ip_str, DELIM);

    if (ptr == NULL)
        return 0;

    /* First octect but be checked to be in range */
    /* after parsing string, it must contain only digits */
    if (!valid_digit(ptr))
        return 0;

    num = atoi(ptr);
    /* check for valid IP range */
    if (num >= 224 && num <= 239) {
        /* parse remaining string */
        ptr = strtok(NULL, DELIM);
        if (ptr != NULL)
            ++dots;
    } else
        return 0;

    while (ptr) {

		/* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return 0;

        num = atoi(ptr);
        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        } else
            return 0;
    }

    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return 0;
    return 1;
}

/* return 1 if IP string is valid, else return 0 */
int is_valid_ssm_ip(const char *my_ip_str) {
    int num, dots = 0;
    char *ptr;

    if (my_ip_str == NULL)
        return 0;

    // See following link for strtok()
    // http://pubs.opengroup.org/onlinepubs/009695399/functions/strtok_r.html
   char *ip_str = malloc (1 + strlen (my_ip_str));
   if (ip_str)
       strcpy (ip_str, my_ip_str);
   else
        fprintf (stderr, "malloc failure!");

    ptr = strtok(ip_str, DELIM);

    if (ptr == NULL)
        return 0;

    /* First octect but be checked to be in range */
    /* after parsing string, it must contain only digits */
    if (!valid_digit(ptr))
        return 0;

    num = atoi(ptr);
    /* check for valid IP range */
    if (num == 232) {
        /* parse remaining string */
        ptr = strtok(NULL, DELIM);
        if (ptr != NULL)
            ++dots;
    } else
        return 0;

    while (ptr) {

		/* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return 0;

        num = atoi(ptr);
        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        } else
            return 0;
    }

    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return 0;
    return 1;
}
