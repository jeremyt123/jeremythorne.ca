/*JEREMY THORNE thornej@uoguelph.ca
Functions for the contact list creator*/

#include "head.h"


int isValidPhone(char num[15]){
    int i;
    /*checks if phone number is 7 or 10 long*/
    if (strlen(num) != 7 && strlen(num) != 10){
        return 0;
    }
    /*makes sure the number is all numeric*/
    for(i = 0; i < strlen(num); i++){
        if(isdigit(num[i]) == 0){
            return 0;
        }
    }
    return 1;
}

int isValidEmail(char email[100]){
    int emailLoc = 0, dotLoc = 0;
    int i;
    /*since entering email isnt mandatory*/
    if(strcmp(email, "") == 0){
        return 1;
    }

    /*finds the last occurance of @ and . then makes sure at least one char is between them and before/after them*/
    for (i = 0; i < strlen(email); i++){
        if (email[i] == '@'){
            emailLoc = i;
        }
        if (email[i] == '.'){
            dotLoc = i;
        }
    }
    if ((emailLoc < (dotLoc - 1)) && isalnum(email[dotLoc + 1]) && isalnum(email[emailLoc - 1])){
        return 1;
    } 
    return 0;
}

int compare_name( const void *a, const void *b){

    struct info *cmp1 = (struct info *)a;
    struct info *cmp2 = (struct info *)b;
    /*simple qsort function with different cases based on what information is available in the contact*/

    if(strcmp(cmp1 -> last_name, "") != 0 && strcmp(cmp2 -> last_name, "") != 0 ){
        return(strcmp(cmp1 -> last_name, cmp2 -> last_name));
    }
    else if (strcmp(cmp1 -> last_name, "") == 0){
        return(strcmp(cmp1 -> company_name, cmp2 -> last_name));
    } 
    else if (strcmp(cmp2 -> last_name, "") == 0){
        return(strcmp(cmp1 -> last_name, cmp2 -> company_name));
    } 
    else{
        return(strcmp(cmp1 -> company_name, cmp2 -> company_name));
    }
}