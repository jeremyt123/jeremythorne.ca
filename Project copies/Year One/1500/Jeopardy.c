//Jeremy Thorne - Jepordy remake
//For this assignment we were given the main program and had to write all the functions
//If you havent checked out my grade 12 projects I highly reccomend to, they are much more interesting than first year assignment imo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_QUESTIONS 7

//function prototypes

void promptPlayerForName (char [50]);
void printWelcomeMessage (char  [50]);
int  calculateCurrentAward (int ,int);
void popUpCurrentQuestion4choices (int);
char askPlayerForLifeLine (void);
void popUpCurrentQuestion2choices (int);
char acceptPlayersFinalAnswer (void);
bool isCorrectFinalAnswer (char, int, char [MAX_QUESTIONS]);
void generateRandomGreeting (char [20]);
int calculateReducedAward (int, int);

int main(){

	char allCorrectAnswers [MAX_QUESTIONS + 1] = "CBCBACA";   // for my set of questions
	char greet [20];
	char nameForGame[50];
	int lifeLineUsed = 0; 
	int questionNumber = 1;
	char playersResponseLifeLine;
	char finalAnswer;
	int currentAwardAmount ;
    int reducedAmount;
    
	promptPlayerForName(nameForGame);
	
	printWelcomeMessage(nameForGame);
	
	while (questionNumber <= MAX_QUESTIONS)
    {
	
		currentAwardAmount = calculateCurrentAward(questionNumber, currentAwardAmount);
		
		popUpCurrentQuestion4choices(currentAwardAmount);
	
		if (lifeLineUsed == 0)
        {
			playersResponseLifeLine = askPlayerForLifeLine();
		
			if (playersResponseLifeLine == 'Y' || playersResponseLifeLine == 'y')
            {
		
				popUpCurrentQuestion2choices(currentAwardAmount);
				lifeLineUsed ++; 
				printf("\nReminder - You get only 1 50-50 lifeline - and you are using it now \n\n");
			}
		}
		
		finalAnswer = acceptPlayersFinalAnswer ();
		
		if (isCorrectFinalAnswer (finalAnswer, questionNumber, allCorrectAnswers) )
        {
		
		 	generateRandomGreeting(greet);
			printf("%s - You just won $ %d\n", greet, currentAwardAmount);
			
			if (questionNumber < MAX_QUESTIONS)
            {
				printf("Let us play the next question now\n\n"); 
			}
		}
		
		else {
			printf  ("Oops - that was incorrect.");
            
            reducedAmount = calculateReducedAward (questionNumber, currentAwardAmount);

			printf("You still won $%d. Well done.\n\n", reducedAmount);
			
            questionNumber = MAX_QUESTIONS;
		}
		questionNumber ++;
	}
	
	printf("It was fun playing with you \n\n");
	
	return 0;

}	

void promptPlayerForName (char fullName[50]){
    //vars to store first and last name
    char first[25];
    char last[25];

    //promts for first and last name then saves to string
    printf("Enter your first name: ");
    scanf("%s", first);

    printf("Enter your last name: ");
    scanf("%s", last);

    //using string commands put firstname into fullName string then adds a space then adds last
    strcpy(fullName, first);
    strcat(fullName, " ");
    strcat(fullName, last);
}

void printWelcomeMessage (char fullName[50]){
    //prints first three lines of stars
    for (int i = 0; i < 3; i++){
        for(int k = 0; k < i; k++){
            printf("*");
        }
        printf("\n");
    }

    //prints line of stars equal to name length + 8
    for (int i = 0; i < strlen(fullName) + 8; i++){
        printf("*");
    }

    printf("\nWelcome %s\n", fullName);
    printf("Let us play WDWM!\n");

    for (int i = 0; i < strlen(fullName) + 8; i++){
        printf("*");
    }
    printf("\n");

    //prints last 3 lines of stars (same as first just backwards)
    for (int i = 3; i > 0; i--){
        for(int k = 0; k < i; k++){
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

}

int calculateCurrentAward (int questionNumber, int awardPreviousQuestion){

    //if statement to check if question number is odd, even, or 1
    //calculates reward based on findings
    if (questionNumber == 1){
        return 100;
    }
    else if (questionNumber % 2 == 0){
        return awardPreviousQuestion * 5;
    }
    else{
        return awardPreviousQuestion * 2;
    }
}

void popUpCurrentQuestion4choices(int currentAwardAmount){

    //prints questions based on reward value for the question
    //question values are {100, 500, 1000, 5000, 10000, 50000, 1000000}
    if (currentAwardAmount == 100){
        printf("Here is the $ 100 question: \n\n");
        printf("Which of the following programming language is taught in\n");
        printf("CIS1500 at the University of Guelph?\n\n");
        printf("A. Python \t B. Cobra\n");
        printf("C. C \t\t D. Java\n\n");
    }
    else if (currentAwardAmount == 500){
        printf("Here is the $ 500 question: \n\n");
        printf("Which Canadian chain first opened in Hamilton in 1964?\n\n");
        printf("A. McDonalds \t\t B. Tim Hortons\n");
        printf("C. Wendys \t\t D. Mr. Sub\n\n");
    }
    else if (currentAwardAmount == 1000){
        printf("Here is the $ 1000 question: \n\n");
        printf("What is Canada's national sport?\n\n");
        printf("A. Hockey \t\t B. Lacrosse\n");
        printf("C. Hockey and Lacrosse \t D. Baseball\n\n");
    }
    else if (currentAwardAmount == 5000){
        printf("Here is the $ 5000 question: \n\n");
        printf("Which Canadian city ranks as most educated in the country?\n\n");
        printf("A. Montreal \t\t B. Ottawa\n");
        printf("C. Vancouver \t\t D. Toronto\n\n");
    }
    else if (currentAwardAmount == 10000){
        printf("Here is the $ 10000 question: \n\n");
        printf("What is Canada's highest mountian?\n\n");
        printf("A. Mount Logan, Yukon \t\t B. Whistler Mountian, BC\n");
        printf("C. Mont Tremblant, Quebec \t D. Tip Top Mountian, Ontario\n\n");
    }
    else if (currentAwardAmount == 50000){
        printf("Here is the $ 50000 question: \n\n");
        printf("What is the easternmost province of Canada\n\n");
        printf("A. Ontario \t\t B. Prince Edward Island\n");
        printf("C. Newfoundland \t D. Nova Scotia\n\n");
    }
    else if (currentAwardAmount == 100000){
        printf("Here is the $ 100000 question: \n\n");
        printf("The southernmost point of mainland Canada is called Point Pelee.\n");
        printf("What province is it in?\n\n");
        printf("A. Ontario \t\t B. Quebec\n");
        printf("C. Newfoundland \t D. Nova Scotia\n\n");
    }
}

char askPlayerForLifeLine (){
    char input;
    //promts user for input and stores in input var
    printf("Would you like to use a lifeline (50-50)?\n");
    printf("Enter Y or y, N or n: ");
    //while loops checks if input is valid
    //used toupper() to make while statement shorter
    while(toupper(input) != 'Y' && toupper(input) != 'N'){ 
        scanf(" %c", &input);
        if(toupper(input) != 'Y' && toupper(input) != 'N'){
            printf("\nInvalid option entered\n\n");
            printf("Enter Y or y, N or n: ");
        }         
    }


    return input;
}

void popUpCurrentQuestion2choices (int currentAwardAmount){
    //gives question based on reward value with only 2 possible answers
    if (currentAwardAmount == 100){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("C. C\n");
        printf("D. Java\n");
    }
    else if (currentAwardAmount == 500){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("A. McDonalds\n");
        printf("B. Tim Hortons\n");
    }
    else if (currentAwardAmount == 1000){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("C. Hockey and Lacrosse\n");
        printf("D. Baseball\n");
    }
    else if (currentAwardAmount == 5000){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("A. Montreal\n");
        printf("B. Ottawa\n");
    }
    else if (currentAwardAmount == 10000){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("A. Mount Logan, Yukon\n");
        printf("C. Mont Tremblant, Quebec\n");
    }
    else if (currentAwardAmount == 50000){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("C. Newfoundland\n");
        printf("D. Nova Scotia\n");
    }
    else if (currentAwardAmount == 100000){
        printf("\nOK - here are your 2 choices after using the 50-50 lifeline\n\n");
        printf("A. Ontario\n");
        printf("D. Nova Scotia\n");
    }

}

char acceptPlayersFinalAnswer (){
    char input;
    //while loop condition checks to make sure input is valid
    while (input != 'A' && input != 'B' && input != 'C' && input != 'D'){
        printf("Enter your FINAL ANSWER ('A', 'B', 'C', OR 'D') here: ");
        scanf(" %c", &input);       
    }
    printf("\n");
    //returns valid input
    return input;
}

bool isCorrectFinalAnswer (char finalAnswer, int questionNumber, char allCorrectAnswers[MAX_QUESTIONS]){
    //checks the answer String with the users answers, if they match returns true
    //subtract one becuase arrays start at 0
    if (allCorrectAnswers[questionNumber - 1] == finalAnswer){
        return true;
    }
    else{
        return false;
    }
}

void generateRandomGreeting (char greet[20]){
    //storing a random number in var random
    int random;
    //%5 + 1 to get numbers between 1-5
    random = (rand() % 5) + 1; 
    //based on random number assings greeting to greet string
    if (random == 1){
        strcpy(greet, "Bravo");
    }
    else if (random == 2){
        strcpy(greet, "Congrats");
    }
    else if (random == 3){
        strcpy(greet, "Well Done");
    }
    else if (random == 4){
        strcpy(greet, "Very Nice");
    }
    else if (random == 5){
        strcpy(greet, "Proud of You");
    }
}

int calculateReducedAward(int questionNumber, int currentAwardAmount){
    //divides by given amount based on if question number is odd or even
    if (questionNumber % 2 == 0){
        return currentAwardAmount / 5;
    }
    else{
        return currentAwardAmount / 2;
    }
}