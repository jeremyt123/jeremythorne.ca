/*JEREMY THORNE thornej@uoguelph.ca
This Program allows users to add, view, delete and edit contacts
The contacts are stored on disk and can be access between program executions

To compile: make
To run: ./bin/contactList

Contact editing functions include 
A - add new contact
# - select contact
E - edit selected contact
D - delete selected contact
X - exit and save 
*/

#include "head.h"

int main(){
    unsigned long phone = 0;
    char first[100];
    char last[100];
    char cmpyName[100];
    char email[100];
    int pos = 0;

    char phoneString[15];
    char action; 
    int i;  
    int deleted = 0;

    struct contact contactStruct;
    
    /*infoStruct will be the struct array that the contacts are read into*/
    struct info *infoStruct;
    infoStruct = malloc(sizeof(struct info));

    FILE * readContactFile = fopen("myContactList.db", "rb");

    long hold = 0;
    int count = 0;
    /*Reads in the whole file into the struct array*/
    if (readContactFile != NULL){
        /*reads until end of file*/
        while(!feof(readContactFile)){
            fread(&contactStruct, sizeof(struct contact), 1, readContactFile);
            
            /*exit condition if contact is the last one in the file*/
            if (hold == contactStruct.next){
                break;
            }
            
            infoStruct = realloc(infoStruct, sizeof(struct info) * (count + 1));
            
            /*each chunk checks to see if the posn is 0 which would mean nothing was entered
            then moves to the positon in the file then reads the information into vars
            then prints the info*/

            if(contactStruct.first_name_posn != 0){
                fseek(readContactFile, contactStruct.first_name_posn, SEEK_SET);
                fread(infoStruct[count].first_name, sizeof(char) * 100, 1, readContactFile);                            
            }
            else{
                strcpy(infoStruct[count].first_name, "");
            }

            if(contactStruct.last_name_posn != 0){
                fseek(readContactFile, contactStruct.last_name_posn, SEEK_SET);
                fread(infoStruct[count].last_name, sizeof(char) * 100, 1, readContactFile);                            
            }
            else{
                strcpy(infoStruct[count].last_name, "");
            }

            if(contactStruct.company_name_posn != 0){
                fseek(readContactFile, contactStruct.company_name_posn, SEEK_SET);
                fread(infoStruct[count].company_name, sizeof(char) * 100, 1, readContactFile);                            
            }
            else{
                strcpy(infoStruct[count].company_name, "");
            }

            if(contactStruct.email_posn != 0){
                fseek(readContactFile, contactStruct.email_posn, SEEK_SET);
                fread(infoStruct[count].email, sizeof(char) * 100, 1, readContactFile);                            
            }
            else{
                strcpy(infoStruct[count].email, "");
            }
            
            /*checks to see if the contact its reading has been "Deleted" if so adds one to 
            deleted amount which is used later in number of contacts calc*/
            if(strcmp(infoStruct[count].last_name, "") == 0 && strcmp(infoStruct[count].company_name, "") == 0){
                deleted++;
            }

            infoStruct[count].phone = contactStruct.phone_number;
            
            /*seeks to the next stuct in the file using .next*/
            fseek(readContactFile, contactStruct.next, SEEK_SET); 
            hold = contactStruct.next; 
            count++;     
        }
        fclose(readContactFile);
    }

    /*declaring void pointer for q sort*/
    int (*compare)(const void *a, const void *b);
    compare = &compare_name;

    /*main loop for the program*/
    do{
        qsort (infoStruct, count, sizeof(struct info), compare);
        printf("Number of Contacts = %d\n", count - deleted);
        /*prints out the firstlast/company names for the sorted contacts*/
        for(i = 0; i < count; i++){
            if (strcmp(infoStruct[i].last_name, "") != 0){
                printf("%d. %s %s\n", i + 1 - deleted, infoStruct[i].first_name, infoStruct[i].last_name);
            }
            else if(strcmp(infoStruct[i].company_name, "") != 0){
                printf("%d. %s\n", i + 1 - deleted, infoStruct[i].company_name);
            }
        }
        printf("Action: ");
        scanf("%c", &action);
        getchar();
        /*Adding contact statement*/
        if (action == 'A'){
            /*reads in all the parameters and checks to make sure they are valid*/
            printf("First Name: ");
            fgets(first, 100, stdin);
            first[strlen(first) - 1] = 0;

            printf("Last Name: ");
            fgets(last, 100, stdin);
            last[strlen(last) - 1] = 0;

            do{
                printf("Company Name: ");
                fgets(cmpyName, 100, stdin);         
            }while(strcmp(last, "") == 0 && strcmp(cmpyName, "\n") == 0);
            cmpyName[strlen(cmpyName) - 1] = 0;

            do{
                printf("Phone Number (enter only numbers): ");
                fgets(phoneString, 15, stdin);
                strtok(phoneString, "\n");   
            }while(isValidPhone(phoneString) == 0);
            sscanf(phoneString, "%lu", &phone);

            do{
                printf("Email: ");
                fgets(email, 100, stdin);
                email[strlen(email) - 1] = 0;
            }while(isValidEmail(email) == 0);

            do{
                printf("Action: ");
                scanf("%c", &action);
                getchar();
                /*if they save the information is added to the struct*/
                if(action == 'S'){
                    infoStruct = realloc(infoStruct, sizeof(struct info) * (count + 1));
                    strcpy(infoStruct[count].first_name, first);
                    strcpy(infoStruct[count].last_name, last);
                    strcpy(infoStruct[count].company_name, cmpyName);
                    strcpy(infoStruct[count].email, email);
                    infoStruct[count].phone = phone;
                    count++;                
                }
            }while(action != 'S' && action != 'R');
        }
        /*contact selection statement*/
        if (isdigit(action)){
            int index = action - '0';
            index += deleted - 1;
            /*used to make sure it displays the proper contact incase a "deleted" contact is selected*/
            while(strcmp(infoStruct[index].last_name, "") == 0 && strcmp(infoStruct[index].company_name, "") == 0){
                index++;
            }

            printf("First Name: %s\n",infoStruct[index].first_name);
            printf("Last Name: %s\n",infoStruct[index].last_name);
            printf("Company Name: %s\n",infoStruct[index].company_name);
            printf("Phone Number: %lu\n",infoStruct[index].phone);
            printf("Email: %s\n",infoStruct[index].email);


            do{
                printf("Action: ");
                scanf("%c", &action);
                getchar();
                /*"deletes" the contact by setting last name and company name to ""*/ 
                if(action == 'D'){
                    strcpy(infoStruct[index].last_name, "");
                    strcpy(infoStruct[index].company_name, "");
                    deleted++;
                }
                else if(action == 'E'){
                    printf("First Name: %s\n",infoStruct[index].first_name);
                    printf("Last Name: %s\n",infoStruct[index].last_name);
                    printf("Company Name: %s\n",infoStruct[index].company_name);
                    /*reads in phone num and email using same restriction functions as before*/
                    do{                     
                        printf("Phone Number (enter only numbers): ");
                        fgets(phoneString, 15, stdin);
                        strtok(phoneString, "\n");   
                    }while(isValidPhone(phoneString) == 0);
                    sscanf(phoneString, "%lu", &phone);
    
                    do{
                        printf("Email: ");
                        fgets(email, 100, stdin);
                        email[strlen(email) - 1] = 0; 
                    }while(isValidEmail(email) == 0);

                    do{
                        printf("Action: ");
                        scanf("%c", &action);
                        getchar();

                        if(action == 'S'){
                            strcpy(infoStruct[index].email, email);
                            infoStruct[index].phone = phone;
                        }
                        else if(action == 'D'){
                            strcpy(infoStruct[index].last_name, "");
                            strcpy(infoStruct[index].company_name, "");
                            deleted++;
                        }                        
                    }while(action != 'S' && action != 'R' && action != 'D');

                }
            }while(action != 'E' && action != 'R' && action != 'D' && action != 'S');                
        }

    }while(action != 'X');
    /*once the user enters X and ends the program the struct is written to the file
    using wb which replaces what was there before*/
    FILE * contactFile = fopen("myContactList.db", "wb");

    if (contactFile == NULL){
        printf("Error: Unable to write to the file\n");
        exit(1);
    }

    for (i = 0; i < count; i++){
        /*uses pos to calcute what positions the info is stored at (same as A3)*/
        pos += sizeof(long) * 5;
        pos += sizeof(unsigned long);

        if(strcmp(infoStruct[i].first_name, "\n") != 0){
            contactStruct.first_name_posn = pos;
            pos += sizeof(char) * (strlen(infoStruct[i].first_name) + 1);        
        }
        else{
            contactStruct.first_name_posn = 0;
        }

        if(strcmp(infoStruct[i].last_name, "\n") != 0){
            contactStruct.last_name_posn = pos;
            pos += sizeof(char) * (strlen(infoStruct[i].last_name) + 1);                
        }
        else{
            contactStruct.last_name_posn = 0;
        }

        if(strcmp(infoStruct[i].company_name, "\n") != 0){  
            contactStruct.company_name_posn = pos; 
            pos += sizeof(char) * (strlen(infoStruct[i].company_name) + 1);               
        }
        else{
            contactStruct.company_name_posn = 0;
        }

        contactStruct.phone_number = infoStruct[i].phone;

        if(strcmp(infoStruct[i].email, "\n") != 0){           
            contactStruct.email_posn = pos;
            pos += sizeof(char) * (strlen(infoStruct[i].email) + 1);                
        }
        else{
            contactStruct.email_posn = 0;
        }
        contactStruct.next = pos;

        fwrite(&contactStruct, sizeof(struct contact), 1, contactFile);

        /*writes the actaul information to the file*/
        if(strcmp(infoStruct[i].first_name, "\n") != 0){
            fwrite(&infoStruct[i].first_name, sizeof(char) * (strlen(infoStruct[i].first_name) + 1), 1, contactFile);            
        }
        if(strcmp(infoStruct[i].last_name, "\n") != 0){
            fwrite(&infoStruct[i].last_name, sizeof(char) * (strlen(infoStruct[i].last_name) + 1), 1, contactFile);            
        }
        if(strcmp(infoStruct[i].company_name, "\n") != 0){
            fwrite(&infoStruct[i].company_name, sizeof(char) * (strlen(infoStruct[i].company_name) + 1), 1, contactFile);            
        }
        if(strcmp(infoStruct[i].email, "\n") != 0){
            fwrite(&infoStruct[i].email, sizeof(char) * (strlen(infoStruct[i].email) + 1), 1, contactFile);            
        }
    }
    /*closing the file and freeing the struct*/
    fclose(contactFile);

    free(infoStruct);
    return 0;
}