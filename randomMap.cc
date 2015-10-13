#include <iostream>
#include <stdlib.h> 
using namespace std;


#define ROWS 21
#define COLUMNS 21
#define FIXEDWALL 1

int CENTER_ROWS,CENTER_COLUMNS, SQUARE_SIDE_SIZE;

char final_matrix[ROWS][COLUMNS];

int matrix[ROWS][COLUMNS];



void printMatrix(){
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			printf("%c ", final_matrix[j][i]);
		}
		printf("\n");

	}
}

void printPreviousMatrix(){
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			printf("%i  ", matrix[j][i]);
		}
		printf("\n");

	}
}


void generateFinalMatrix(){

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{

			if (matrix[j][i]==FIXEDWALL )
			{
				final_matrix[j][i]='1';
			}else{
				final_matrix[j][i]=' ';
			}
		}
	}
}

void generatePairRows(){

	for (int i = 1; i < ROWS-1; ++i)
	{
		i++;
		for (int j = 0; j < COLUMNS; ++j)
		{
			matrix[j][i]=1;
		}
	}

	for (int i = 1; i < COLUMNS-1; ++i)
	{
		i++;
		for (int j = 0; j < ROWS; ++j)
		{
			matrix[i][j]=1;
		}
	}


}

void printBorder(){

	//left side
	for (int i = 0; i < ROWS; ++i)
	{
		matrix[0][i] =2;
	}
	//right side
	for (int i = 0; i < ROWS; ++i)
	{
		matrix[COLUMNS-1][i] =2;
	}
	//top side
	for (int i = 0; i < COLUMNS; ++i)
	{
		matrix[i][0] =2;
	}
	//bottom side
	for (int i = 0; i < COLUMNS; ++i)
	{
		matrix[i][ROWS-1] =2;
	}
}

void printBorderSpace(){

	//left border side
	for (int i = 1; i < ROWS-1; ++i)
	{
		matrix[1][i] =3;
	}
	//right border side
	for (int i = 1; i < ROWS-1; ++i)
	{
		matrix[COLUMNS-2][i] =3;
	}
	//top border side
	for (int i = 1; i < COLUMNS-1; ++i)
	{
		matrix[i][1] =3;
	}
	//bottom border side
	for (int i = 1; i < COLUMNS-2; ++i)
	{
		matrix[i][ROWS-2] =3;
	}

}

void doWallRight(int x, int y, int size){

	for (int i = 0; i < size; ++i)
	{
		if (matrix[x][i]!=1)
		{
			matrix[x][i]=2;
		}

		if (matrix[x-1][i]!=1)
		{
			matrix[x-1][i]=3;
		}

		if (matrix[x+1][i]!=1)
		{
			matrix[x+1][i]=3;
		}
	}

}

void printEnemyBox(){

	matrix[CENTER_COLUMNS][CENTER_ROWS]=3;
	matrix[CENTER_COLUMNS][CENTER_ROWS-1]=3;
	matrix[CENTER_COLUMNS-1][CENTER_ROWS-1]=3;
	matrix[CENTER_COLUMNS-1][CENTER_ROWS]=3;
	matrix[CENTER_COLUMNS][CENTER_ROWS+1]=3;
	matrix[CENTER_COLUMNS-1][CENTER_ROWS+1]=3;
	matrix[CENTER_COLUMNS][CENTER_ROWS-2]=3;

}

int main(int argc, char* argv[]) {

	SQUARE_SIDE_SIZE = atoi(argv[1]);

	if (SQUARE_SIDE_SIZE%2!=0)
	{
		SQUARE_SIDE_SIZE++;
	}

	//ROWS = SQUARE_SIDE_SIZE;
	//COLUMNS = SQUARE_SIDE_SIZE;


	CENTER_ROWS = (ROWS/2);
	CENTER_COLUMNS =  (ROWS/2);

	printf("ROWS:%i \t COLUMNS: %i \n", ROWS, COLUMNS);

	
	//printBorderSpace();
	//printEnemyBox();

	//generatePairRows();

	printBorder();

	generateFinalMatrix();
	

	printPreviousMatrix();
	printMatrix();

}






