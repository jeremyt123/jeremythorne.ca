/*JEREMY THORNE 1052007 thornej@uoguelph.ca
Header file for contact list creator*/
#ifndef HEADH
#define HEADH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct contact {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};

struct info {
    unsigned long phone;
    char first_name[100];
    char last_name[100];
    char company_name[100];
    char email[100];
};

int findLast();
int isValidPhone(char[10]);
int isValidEmail(char[100]);
int compare_name( const void *a, const void *b);
#endif