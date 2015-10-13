#include <iostream>
#include <stdlib.h> 
using namespace std;


#define ROWS 31
#define COLUMNS 31
#define FIXEDWALL 1
#define CARRIER 0

int matrix[ROWS][COLUMNS];
int CENTER_ROWS,CENTER_COLUMNS;


void generatePairRows(){

	for (int i = 1; i < ROWS-1; ++i)
	{
		i++;
		for (int j = 0; j < COLUMNS; ++j)
		{
			matrix[j][i]=FIXEDWALL;
		}
	}

	for (int i = 1; i < COLUMNS-1; ++i)
	{
		i++;
		for (int j = 0; j < ROWS; ++j)
		{
			matrix[i][j]=FIXEDWALL;
		}
	}


}


void printFinalMap(){
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			if (matrix[j][i]==1)
			{
				printf("1 ");
			}else{
				printf("  ");
			}
		}
		printf("\n");

	}
}

void printEnemyBox(){
	CENTER_ROWS= ROWS/2;
	CENTER_COLUMNS=COLUMNS/2;

	int size = 4/2;

	matrix[CENTER_COLUMNS][CENTER_ROWS]=CARRIER;

	int init_row = CENTER_ROWS - size;
	int finish_row = CENTER_ROWS + size;
	int init_column = CENTER_COLUMNS - size;
	int finish_column = CENTER_COLUMNS + size;

for (int j = 0; j < size; ++j)
	{
	for (int i = 0; i < size; ++i)
	{
		matrix[CENTER_COLUMNS+j][CENTER_ROWS+i]=CARRIER;
		matrix[CENTER_COLUMNS][CENTER_ROWS+i]=CARRIER;
		matrix[CENTER_COLUMNS+j][CENTER_ROWS]=CARRIER;

		matrix[CENTER_COLUMNS-j][CENTER_ROWS-i]=CARRIER;
		matrix[CENTER_COLUMNS][CENTER_ROWS-i]=CARRIER;
		matrix[CENTER_COLUMNS-j][CENTER_ROWS]=CARRIER;
	}
}
/*

	CENTER_ROWS= ROWS/2;
	CENTER_COLUMNS=COLUMNS/2;

	
	matrix[CENTER_COLUMNS][CENTER_ROWS-1]=CARRIER;
	matrix[CENTER_COLUMNS+1][CENTER_ROWS]=CARRIER;
	matrix[CENTER_COLUMNS-1][CENTER_ROWS]=CARRIER;

	matrix[CENTER_COLUMNS][CENTER_ROWS+1]=CARRIER;
	matrix[CENTER_COLUMNS-1][CENTER_ROWS+1]=CARRIER;
	//Exit
	matrix[CENTER_COLUMNS][CENTER_ROWS-2]=CARRIER;

	*/

}

void printMatrix(){
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			printf("%i  ", matrix[j][i]);
		}
		printf("\n");

	}
}

void putBorder(){

	//left side
	for (int i = 0; i < ROWS; ++i)
	{
		matrix[0][i] =FIXEDWALL;
	}
	//right side
	for (int i = 0; i < ROWS; ++i)
	{
		matrix[COLUMNS-1][i] =FIXEDWALL;
	}
	//top side
	for (int i = 0; i < COLUMNS; ++i)
	{
		matrix[i][0] =FIXEDWALL;
	}
	//bottom side
	for (int i = 0; i < COLUMNS; ++i)
	{
		matrix[i][ROWS-1] =FIXEDWALL;
	}
}

int main(int argc, char* argv[]) {

	//SQUARE_SIDE_SIZE = atoi(argv[1]);

	printf("ROWS:%i \t COLUMNS: %i \n", ROWS, COLUMNS);
	
	//printBorderSpace();
	//printEnemyBox();

	//generatePairRows();

	generatePairRows();

	putBorder();
	printEnemyBox();

	printMatrix();

	printFinalMap();

}