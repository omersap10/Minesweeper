/*ID - 206992505
Description of the prorgam - the prorgam is the minesweeper game*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define ROWS 23 //define the physical size of array.
#define COLS 23 //define the physical size of array.
#define BOMB -1 //define the value of bomb.
#define EMPTY 0 //define the value of empty cell.
#define CLOSECELL -2 //define the value of close cell.
#define FLAG -3 //define the value of cell with flag.

//funcations declerion:
void userGame(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum);
void hiddenGame(int realBoard[][COLS], int rowsNum, int colsNum);
void printBoard(int userBoard[][COLS], int rowsNum, int colsNum, int rows, int cols);
bool playerMove(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum);
void emptyCellFill(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum, int rows, int cols);
void uncoverBoard(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum, int cols);
bool isClearBoard(int userBoard[][COLS], int rowsNum, int colsNum);
void bombPlacement(int realBoard[][COLS], int rowsNum, int colsNum);
void printFullBoard(int realBoard[][COLS], int rowsNum, int colsNum);

void main()
{
	int userBoard[ROWS][COLS];
	int realBoard[ROWS][COLS];
	int sizeOption;
	int personalSizelRows, personalSizeCols;

	printf("Welcome to Minesweeper!\n\nPlease choose the field size (1-4): \n\n");
	printf("1 - for size 8X8\n\n2 - for size 12X12\n\n3 - for size 15X15\n\n4 - for custom size\n\n0 - Exit\n\n");
	scanf("%d", &sizeOption);

	while (sizeOption < 0 || sizeOption > 4) //check for valid size choice.
	{
		printf("Invalid input, please chose option from 0-4\n");
		scanf("%d", &sizeOption);
	}

	switch (sizeOption)
	{
	case 0: //exit option.
		printf("Goodbye!\n\n"); 
		break; 

	case 1: //8X8 board option.
		hiddenGame(realBoard, 9, 9);
		userGame(realBoard, userBoard, 8, 8);
		break;

	case 2: //12X12 board option.
		hiddenGame(realBoard, 13, 13);
		userGame(realBoard, userBoard, 12, 12);
		break;

	case 3: //15X15 board option.
		hiddenGame(realBoard, 16, 16);
		userGame(realBoard, userBoard, 15, 15);
		break;

	case 4: //free size choice.
		printf("Please enter the board size you want - from 1 to 22 rows and cols: ");
		scanf("%d %d", &personalSizelRows, &personalSizeCols);
		while (personalSizelRows > 22 || personalSizelRows < 1 || personalSizeCols > 22 || personalSizeCols < 1)
		{
			printf("Invalid choice, please enter size between 1 to 22: ");
			scanf("%d %d", &personalSizelRows, &personalSizeCols);
		}
		hiddenGame(realBoard, personalSizelRows + 1, personalSizeCols + 1);
		userGame(realBoard, userBoard, personalSizelRows, personalSizeCols);
	};
}

//functions:

/*userGame:
The purpose: The function is basically the board of the game that the user see. 
* it will print the board with close cells and for each move the user will chose the right cell will open up. 
* if the user will hit a bomb, the game will end and the appropriate message will print out and will print the full board.
* if the user success to open all the close cells, without hit a bomb, the user win the game and the appropriate message will print out.

Parameters:
userBoard - userBoard is a 2D array, this is the board that print out for the user during the game.
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data. 
			for each move the user board will recive data from the "real board".
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
rows - local variable for loop.
cols - local variable for loop.
moveCountetr - for each move the player do we will raise the couter by 1. we will cheack the counter in order to check for the max possible moves to win.
isBomb - boolean variable, which get is value from the boolian function "playerMove", and cheack for a bomb hit. 
*/

void userGame(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum)
{
	int rows;
	int cols;
	bool isBomb = false;
	bool isClear = false;

	//starting the user board to close cells:
	for (rows = 0; rows < rowsNum; rows++)
	{
		for (cols = 0; cols < colsNum; cols++)
		{
			userBoard[rows][cols] = CLOSECELL;
		}
	}
	
	//print the user board and check for end game options:
	while (isClear != true && isBomb != true)
	{
		printBoard(userBoard, rowsNum, colsNum, rows, cols);

		//recive player move and check if the move was on bomb. if do - finish game.
		isBomb = playerMove(realBoard, userBoard, rowsNum, colsNum);

		isClear = isClearBoard(userBoard, rowsNum, colsNum);
	}
	if (isBomb == true) //if the player hit a bomb - finish game, player lose.
	{
		printFullBoard(realBoard, rowsNum, colsNum);
		printf("GAME OVER! you lose, try again next time!\n");
	}
	else //if the player clear the borad without hit a bomb - finish game, player win.
	{
		printFullBoard(realBoard, rowsNum, colsNum);
		printf("YOU WON! very well! see you next time!\n");
	}
}

/*printBoard:
The purpose: The function will print the board changes to the user by each move. 

Parameters:
userBoard - userBoard is a 2D array, this is the board that print out for the user during the game.
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
rows - variable for loops and checks on the board.
cols - variable for loops and checks on the board.
*/

void printBoard(int userBoard[][COLS], int rowsNum, int colsNum, int rows, int cols)
{
	printf("     |");
	for (cols = 0; cols < colsNum; cols++)
	{
		printf(" %2d |", cols); //print the board lines.
	}
	printf("\n");
	for (cols = 0; cols < colsNum; cols++)
	{
		printf("______"); //print the board lines.
	}
	printf("\n");

	for (rows = 0; rows < rowsNum; rows++)
	{
		printf(" %2d  |", rows); //print the board rows lines.
		for (cols = 0; cols < colsNum; cols++)
		{
			if (userBoard[rows][cols] == CLOSECELL) //if the cell close print X.
				printf("  X |");
			else if (userBoard[rows][cols] == FLAG) //if the cell empty print _.
				printf("  F |");
			else if (userBoard[rows][cols] == EMPTY) //if the cell empty print _.
				printf("    |");
			else if (userBoard[rows][cols] == BOMB) //if the cell has bomb print *.
				printf("  * |");
			else
				printf("  %d |", userBoard[rows][cols]);
		}
		printf("\n");
	}
	printf("\n");
}

/*playerMove:
The purpose: The function will recive the player move from the player, check for valid input, and by that will change the user board for each move.
			Additionally, if the player will chose for row -1, for the board will open by the number of cols the player will enter.
			The function is a boolean funcation, and the value is change for is the player will hit the bomb and end game, or not.

Parameters:
userBoard - userBoard is a 2D array, this is the board that print out for the user during the game.
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data.
			for each move the user board will recive data from the "real board".
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
rows - local variable for loops and checks on the board.
cols - local variable for loops and checks on the board.
uncoverBoard - function which will open cols in the user board by the choice of the user. 
*/

bool playerMove(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum)
{
	int rows;
	int cols;
	char letterMove;

	printf("Please enter your move - row and column. for flag enter F, for open enter O: \n"); //recive move from the player - ask for rows and cols to array.
	scanf("%d %d %c", &rows, &cols, &letterMove);

	if (rows == -1) //operate special move to open the borad by out-game step.
	{
		uncoverBoard(realBoard, userBoard, rowsNum, colsNum, cols);
	}

	else
	{
		while (rows > rowsNum || rows < -1 || cols > colsNum || cols < 0) //if enter invalid input.
		{
			printf("Invalid input, Please chose another move inside the board size: \n");
			scanf("%d %d %c", &rows, &cols, &letterMove);
		}

		while (userBoard[rows][cols] != CLOSECELL && userBoard[rows][cols] != FLAG) //if enter move that already made.
		{
			printf("Please chose another move: \n");
			scanf("%d %d %c", &rows, &cols, &letterMove);
		}

		//checkValidMove(userBoard, rowsNum, colsNum, rows, cols, letterMove);

		if (letterMove == 'f' || letterMove == 'F')
			userBoard[rows][cols] = FLAG;

		if (letterMove == 'o' || letterMove == 'O')
		{
			emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows, cols);

			if (userBoard[rows][cols] == BOMB) //if the player hit a bomb - the boolean value will be true and the game will finished by the user lose.
				return true;
			else
				return false;
		}
	}
}

/*emptyCellFill:
The purpose: The function will execute the player move. if the player move was on the empty cell, all his neighbors cells will open to by Recursion,
			till they reach to a cell with a number that is neighbor to them, which also will be open. cells with bombs will remain close.  

Parameters:
userBoard - userBoard is a 2D array, this is the board that print out for the user during the game.
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data.
			for each move the user board will recive data from the "real board".
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
rows - local variable for loops and checks on the board.
cols - local variable for loops and checks on the board.
uncoverBoard - function which will open cols in the user board by the choice of the user.
*/

void emptyCellFill(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum, int rows, int cols)
{
	//Base Case
	if (realBoard[rows + 1][cols + 1] != EMPTY)
	{
		userBoard[rows][cols] = realBoard[rows + 1][cols + 1]; //copying the cell from full board to the empty board.
		return;
	}
	if (userBoard[rows][cols] != CLOSECELL) //if the cell already open.
	{
		return;
	}

	userBoard[rows][cols] = realBoard[rows + 1][cols + 1]; //copying the cell from full board to the empty board.

	if (rows < rowsNum - 1) //rec calls
	{
		emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows + 1, cols);

		if (cols > 0)
			emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows + 1, cols + 1);

		if (cols < colsNum - 1)
			emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows + 1, cols - 1);
	}
	if (cols < colsNum - 1)
		emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows, cols + 1);
	if (rows > 0)
	{
		emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows - 1, cols);

		if (cols < colsNum)
			emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows - 1, cols + 1);

		if (cols > 0)
			emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows - 1, cols - 1);
	}
	if (cols > 0)
		emptyCellFill(realBoard, userBoard, rowsNum, colsNum, rows, cols - 1);

	return;

}

/*uncoverBoard:
The purpose: The function is used for an out-game move.
			If the player will chose for row -1, for the board will open by the number of cols the player will enter.

Parameters:
userBoard - userBoard is a 2D array, this is the board that print out for the user during the game.
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data.
			for each move the user board will recive data from the "real board".
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
i - local variable for loops and checks on the board.
j - local variable for loops and checks on the board.
cols - the number of cols the user chose to open by the out-game step.
*/

void uncoverBoard(int realBoard[][COLS], int userBoard[][COLS], int rowsNum, int colsNum, int cols)
{
	int i, j;

	for (i = 0; i < rowsNum; i++)
		for (j = 0; j < colsNum; j++)
		{
			if (cols > 0)
			{
				if (userBoard[i][j] == CLOSECELL && realBoard[i+1][j+1] != BOMB) //copying data from full board to empty board if the cell is not bomb or close.
				{
					userBoard[i][j] = realBoard[i + 1][j + 1];
					cols--;

				}
			}
		}
}

/*isClearBoard:
The purpose: The function is a boolean which will check for each player move if the board is clean from close cells, except the close cells with bomb.
			If the board is clean, the boolean value will be true, and the game will stop and the player will be crowned as winner.

Parameters:
userBoard - userBoard is a 2D array, this is the board that print out for the user during the game.
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
i - local variable for loops and checks on the board.
j - local variable for loops and checks on the board.
countToClean - counter for close cells in the board, and used for check if there are more close cells that there are without the cells with bombs.
*/


bool isClearBoard(int userBoard[][COLS], int rowsNum, int colsNum)
{
	int i, j, countToClean=0;
	int numberOfBombs = sqrt(rowsNum * colsNum);

	for (i = 0; i < rowsNum; i++)
	{
		for (j = 0; j < colsNum; j++)
		{
			if (userBoard[i][j] == CLOSECELL) //check the array for close cells (with the cells with bombs) and count them.
				countToClean++;
		}
	}
	if (countToClean <= numberOfBombs) //need to change rowsNum to the new calculate of bombs... 
		return true;
}

/*printFullBoard:
The purpose: The function used for hit bomb and end-game option.
			If the user will hit a bomb the game will print appropriate message and this function will print the full board, without any close cells.

Parameters:
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data.
			For each move the user board will recive data from the "real board".
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
rows - local variable for loops and checks on the board.
cols - local variable for loops and checks on the board.
*/


void printFullBoard(int realBoard[][COLS], int rowsNum, int colsNum)
{
	int rows;
	int cols;

	printf("     |");
	for (cols = 0; cols < colsNum; cols++)
	{
		printf(" %2d |", cols); //print the board lines.
	}
	printf("\n");
	for (cols = 0; cols < colsNum; cols++)
	{
		printf("______"); //print the board lines.
	}
	printf("\n");

	for (rows = 0; rows < rowsNum; rows++)
	{
		printf(" %2d  |", rows);
		for (cols = 0; cols < colsNum; cols++)
		{
			if (realBoard[rows+1][cols + 1] == CLOSECELL) //if the cell close print X.
				printf("  X |");
			else if (realBoard[rows + 1][cols + 1] == EMPTY) //if the cell empty print _.
				printf("    |");
			else if (realBoard[rows + 1][cols + 1] == BOMB) //if the cell has bomb print *.
				printf("  * |");
			else
				printf("  %d |", realBoard[rows + 1][cols + 1]);
		}
		printf("\n");
	}
	printf("\n");
}

/*hiddenGame:
The purpose: The function is basically the full board with all the data (bomb placment, numbering cells and more) in it,
				and it will be full from the moment the game begin. the player will not be aware of the hidden game.
			The function will enter all the data to the 2D array "realBoard".

Parameters:
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data.
			for each move the user board will recive data from the "real board".
rowsNum - the number of rows of the board. changed by the user board size's choice.
colsNum - the number of cols of the board. changed by the user board size's choice.
rows - local variable for loops and checks on the board.
cols - local variable for loops and checks on the board.
bombPlacement - function which will enter bombs to the board randomly.
bombCounter - the counter will be used for numbering each cell (that dosen't have a bomb) by the number of bombs around him.
*/

void hiddenGame(int realBoard[][COLS], int rowsNum, int colsNum)
{
	int rows;
	int cols;

	//zero the realboard
	for (rows = 0; rows < rowsNum; rows++)
	{
		for (cols = 0; cols < colsNum; cols++)
		{
			realBoard[rows][cols] = 0;
		}
	}

	bombPlacement(realBoard, rowsNum, colsNum);

	//check for bombs
	for (rows = 1; rows < rowsNum; rows++)
	{
		for (cols = 1; cols < colsNum; cols++)
		{
			if (realBoard[rows][cols] != BOMB)
			{
				int bombcounter = 0;

				if (realBoard[rows - 1][cols - 1] == BOMB)
					bombcounter++;
				if (realBoard[rows - 1][cols] == BOMB)
					bombcounter++;
				if (realBoard[rows - 1][cols+1] == BOMB)
					bombcounter++;
				if (realBoard[rows][cols+1] == BOMB)
					bombcounter++;
				if (realBoard[rows + 1][cols +1] == BOMB)
					bombcounter++;
				if (realBoard[rows + 1][cols] == BOMB)
					bombcounter++;
				if (realBoard[rows + 1][cols - 1] == BOMB)
					bombcounter++;
				if (realBoard[rows][cols - 1] == BOMB)
					bombcounter++;

				realBoard[rows][cols] = bombcounter;
			}

		}
	}
}

/*hiddenGame:
The purpose: The function is responsible for the bombs placement on the board, that by using random fucntion to recive random places on the board.

Parameters:
realBoard - realBoard is a 2D array with the "real borad", which is basically the full board with all the data.
			for each move the user board will recive data from the "real board".
random1 - local variable with random number from 0 to 7. used for row number at bomb placment.
random2 - local variable with random number from 0 to 7. used for column number at bomb placment.
i - local variable for loops and checks on the board.
BOMB - define to the value -1.
*/

void bombPlacement(int realBoard[][COLS], int rowsNum, int colsNum)
{
	int numberOfBombs = sqrt((rowsNum-1) * (colsNum-1)); //calculate the number of bombs

	int random1, random2, i;
	srand(time(NULL));

	for (i = 0; i < numberOfBombs; i++)
	{
		random1 = rand() % (rowsNum-1); //output value of random number from 0 to the nubmber of rows on user board.
		random2 = rand() % (colsNum-1); //output value of random number from 0 to the nubmber of cols on user board.

		if (realBoard[random1 + 1][random2 + 1] == EMPTY)
			realBoard[random1 + 1][random2 + 1] = BOMB; //enter bombs (-1) to random places in the realBorad array.
	}
}


