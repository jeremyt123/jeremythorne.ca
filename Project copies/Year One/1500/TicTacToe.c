//Jeremy Thorne - Tic Tac Toe remake
//For this assignment we were given main and had to create the functions
//play against the computer and try to win
//side note: this assignment was interesting since it was a road block for a large amount of students and contributed to the %20 dropout rate of the year significantly 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
int computerPlaysToBlock(char [N][N], int * , int * );


int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';
   
   srand(time(NULL));
    
   printf("This tic-tac-toe board is of size %d by %d\n", N, N);
   
   printf("Player symbol: X \n Computer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);			// create a 3 X 3 board with '?' in each cell 

   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {	   
	   taken = 0;
	   
		while (!(taken))                  // loop used to accept valid row and col values from the user
		{
			readUserMove(&userRow, &userCol);                  //get user's move
			printf("You chose row %d and column %d \n", userRow, userCol);
			
			while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
			{
				printf("That's is an invalid row or column number - try again\n");
				readUserMove(&userRow, &userCol);
				printf("You chose row %d and column %d \n", userRow, userCol);
			}
				   
			if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
			{
				board[userRow-1][userCol-1] = 'X';			// store an X there
				taken = 1;
			}
			else
			{
				taken = 0;									// otherwise inform the user to enter values again
				printf("That spot is taken - please try another one\n");
			}
			
		} //end of while (!taken)
	
	   if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
	   {
		   printf("Congrats - you won against the computer :)\n");
		   winner = 'Y';
	   }
	   
	   else  if (!(isBoardFull(board)))            //check if the board is already full
	   {
		   taken = 0;
		   
		   while (!(taken))
		   {
				getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col
		   
				if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
				{
					board[computerRow][computerCol] = 'O';
					taken = 1;
	
				}
				else
				{
					taken = 0;		//That spot is taken - computer - try another one
				}	
		   }
		   
		   printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
		   
		   if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
		   {
			   printf("Oh the computer won this time :(( think hard next time\n");
			   winner = 'Y';
		   }  
	   }
	 
	printCurrentBoard(board);  
	
	printf("\nPress enter to continue \n");             
	getchar();
		   
   } //end of while
   
   if (winner != 'Y')
			printf("Game was a tie - no winner!\n\n");
		
   return 0;
}

int isInputValid(int entered, int minimum, int maximum){
    //statement checks if value is greater or equal to min and less or equal to the max
    if(entered >= minimum && entered <= maximum){
        return 1;
    }
    return 0;
}

int isBoardFull(char board [N][N]){
    //checks every value in board and returns 0 if any are indexs are equal to ? (empty)
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            if(board[i][k] == '?'){
                return 0;
            }
        }
    }
    return 1;
}

void createInitialBoard (char board [N][N]){
    //sets every value in board to ? 
	for (int i = 0; i < N; i++){
		for (int k = 0; k < N; k++){
			board[i][k] = '?';
		}
	}
    //calls printCurrentBoard to print the board
    printCurrentBoard(board);
}

void readUserMove(int * userRow, int * userCol){
    printf("Your move - enter numbers between 1 and 3\n\n");
    //gets user row and column and passes them to userRow and userCol
    printf("Enter row number: ");
    scanf("%d", userRow);

    printf("Enter column number: ");
    scanf("%d", userCol);
}

void printCurrentBoard (char board[N][N]){
    printf("\nCurrent board is: \n\n");
    //uses nested for loops to print every index and prints dividing lines between the inner sections
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            printf(" %c ", board[i][k]);
            if (k < N - 1){
                printf("|");
            }
        }
        if (i < N - 1){
            printf("\n------------\n");
        }
    }
    printf("\n\n");
}

int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
   int winningSpot = 0;
   int blocked = 1;
   
   //checks if computer can win
   winningSpot = computerPlaysToWin(board, computerRow, computerCol);
   
   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user 
   {
	   blocked = computerPlaysToBlock(board, computerRow, computerCol);
       //if the computer cant block or win it plays random (This sometimes takes a little while)
	   if (blocked == 0)
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);
   }
 
   return winningSpot;
}

int gameWon(char board[N][N], char symbol){
    //declaring vars to use in sumAllDimensions
    int sumR[N] = {0,0,0};
    int sumC[N] = {0,0,0};
    int sumLD = 0;
    int sumRD = 0;

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

    //if the sums of the row equal 12 O wins if they equal 3 X wins
	if (symbol == 'O') {
		if (sumLD == 12 || sumRD == 12 || memberOf(12, sumR) == 1 || memberOf(12, sumC) == 1) {
			return 1;
		}
	}
	else if (symbol == 'X') {
		if (sumLD == 3 || sumRD == 3 || memberOf(3, sumR) == 1 || memberOf(3, sumC) == 1) {
			return 1;
		}
	}
    return 0;
}

int computerPlaysToWin(char board[N][N], int * cRow, int * cCol){
    //declaring vars to use in sumAllDimensions
    int sumR[N] = {0,0,0};
    int sumC[N] = {0,0,0};
    int sumLD = 0;
    int sumRD = 0;

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

    //if the sum is equal to 8 the row has two O's and an empty spot
    if (sumLD == 8){
        for (int i = 0; i < N; i++){
            //finds the empty spot in the left diagonal row
            if (board[i][i] == '?'){
                *cRow = i;
                *cCol = i;
                return 1;
            }
        }
    }

    //if the sum is equal to 8 the row has two O's and an empty spot
    if (sumRD == 8){
        for (int i = 0; i < N; i++){
            //finds the empty spot in the right diagonal row
            if (board[i][((N - 1) - i)] == '?'){
                *cRow = i;
                *cCol = (N - 1) - i;
                return 1;
            }
        }
    }

    //uses member of to see if any of the rows have only 2 O's in them
    if (memberOf(8, sumR) == 1){
        for (int i = 0; i < N; i++){
            //finds what row has the two O's
            if (sumR[i] == 8){
                for (int k = 0; k < N; k++){
                    //finds the empty spot in that row
                    if (board[i][k] == '?'){
                        *cRow = i;
                        *cCol = k;
                        return 1;
                    }
                }
            }
        }
    }

    //uses member of to see if any of the columns have only 2 O's in them
    if (memberOf(8, sumC) == 1){
        for (int i = 0; i < N; i++){
            //finds what column has the two O's
            if (sumC[i] == 8){
                for (int k = 0; k < N; k++){
                    //finds the empty spot in that column
                    if (board[k][i] == '?'){
                        *cRow = k;
                        *cCol = i;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void computerPlaysRandom(int * cRow, int * cCol, int uRow, int uCol){
    //sets the rand seed to time
    srand(time(NULL));

    //randomNum will chose if the computer plays in the same row/col/diag as the user
    //0 = same row, 1 = same col, 2 = same diag
    int randomNum = 0;
    randomNum = rand() % 3;

    //this section creates a random number that can either be -2, -1, 1, or 2
    //since the row/col will stay the same adding 0 to the other (col/row) will just return the same spot that the user plays
    int difSpot = 0;
    while (difSpot == 0){
        difSpot = ((rand() % 5) - 2);    
    }

    if (randomNum == 0){
        //changes the Column but stays in the same row
        *cRow = uRow;
        *cCol = uCol + difSpot;
    }
    else if (randomNum == 1){
        //changes the Row but stays in the same col
        *cCol = uCol;
        *cRow = uRow + difSpot;
    }
    else if (randomNum == 2){
        //adds the same number to col and row so it will be diagonal to the user move
        *cCol = uCol + difSpot;
        *cRow = uRow + difSpot; 
    }
    
}

void sumAllDimensions(char board [N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD){
    //creates an int array to store the converted X's, O's, and ?'s
    int tempHold[N][N];

    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            //if the index in board holds an O sets the index in the hold array to 4
            if (board[i][k] == 'O'){
                tempHold[i][k] = 4;
            }
            //if the index in board holds an X sets the index in the hold array to 1
            else if (board[i][k] == 'X'){
                tempHold[i][k] = 1;
            }
            //if the index in board holds anything else sets the index in the hold array to 0
            else{
                tempHold[i][k] = 0;
            }
        }
    }

    //adds all the values in tempHold to their respective vars
    for (int i = 0; i < N; i++){
        *sumLD += tempHold[i][i];
        *sumRD += tempHold[i][((N - 1) - i)];
        for (int k = 0; k < N; k++){
            sumR[i] += tempHold[i][k];
            sumC[i] += tempHold[k][i];
        }
    }
    
}

int memberOf(int aNum, int someArray [N]){
    //checks every num in the array to see if they match aNum
    for (int i = 0; i < N; i++){
        if(aNum == someArray[i]){
            return 1;
        }
    }
    return 0;
}

int computerPlaysToBlock(char board[N][N], int * cRow, int * cCol){
    //function is basically identical to computerPlaysToWin
    //declaring vars to use in sumAllDimensions
    int sumR[N] = {0,0,0};
    int sumC[N] = {0,0,0};
    int sumLD = 0;
    int sumRD = 0;

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

    //if the sum is equal to 2 the row has two X's and an empty spot
    if (sumLD == 2){
        for (int i = 0; i < N; i++){
            //finds the empty spot in the row and sets the cRow and cCol to fill it
            if (board[i][i] == '?'){
                *cRow = i;
                *cCol = i;
                return 1;
            }
        }
    }

    //if the sum is equal to 2 the row has two X's and an empty spot
    if (sumRD == 2){
        for (int i = 0; i < N; i++){
            //finds the empty spot in the row and sets the cRow and cCol to fill it
            if (board[i][((N - 1) - i)] == '?'){
                *cRow = i;
                *cCol = (N - 1) - i;
                return 1;
            }
        }
    }

    //uses memberOf to see if any of the horizontal rows have 2 X's
    if (memberOf(2, sumR) == 1){
        for (int i = 0; i < N; i++){
            //finds the row that has 2 X's
            if (sumR[i] == 2){
                for (int k = 0; k < N; k++){
                    //finds the empty spot in that row and sets cRow and cCol to that index
                    if (board[i][k] == '?'){
                        *cRow = i;
                        *cCol = k;
                        return 1;
                    }
                }
            }
        }
    }

    //uses memberOf to see if any of the columns have 2 X's
    if (memberOf(2, sumC) == 1){
        for (int i = 0; i < N; i++){
            //finds the column with 2 X's
            if (sumC[i] == 2){
                for (int k = 0; k < N; k++){
                    //finds the empty spot in the row and sets cRow and cCol to the index
                    if (board[k][i] == '?'){
                        *cRow = k;
                        *cCol = i;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;    
}