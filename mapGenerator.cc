
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.cc"

#define COLUMNS 51
#define ROWS 51
#define WIDTH 300
#define HEIGHT 300
#define SATURATION 0.50

//-----------------------------------------------

void randomlyGenerate(char map[][COLUMNS], int mapNumbersCells[][COLUMNS]);
void printMap(char map[][COLUMNS]);
void printNumberMap(int map[][COLUMNS]);
bool isBorder(int j);
bool isCage(int i, int j);

bool valid_point(int i, int j);
bool isLateral(int i);
bool isInsideCage(int i,int j);
bool isMidLane(int j);

bool isMapConnex(char map[][COLUMNS], int mapNumbersCells[][COLUMNS]);
int getNumOfVertex(char map[][COLUMNS]);
void fillMatrixNumbersCells(int map[ROWS][COLUMNS]);
bool isEdge(int i, int j, int x, int y, char map[][COLUMNS]);

void display();
void keyboard(unsigned char c,int x,int y);

//-----------------------------------------------

int keyflag=0;

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[])
{

    printf("Pacman map randomly generated:\n\n");
    
    char map[ROWS][COLUMNS];
    int mapNumbersCells[ROWS][COLUMNS];

    fillMatrixNumbersCells(mapNumbersCells);
    printNumberMap(mapNumbersCells);

    randomlyGenerate(map, mapNumbersCells);
    printMap(map); 

    isMapConnex(map, mapNumbersCells);

    exit(0);
}

void fillMatrixNumbersCells(int map[ROWS][COLUMNS]){


  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLUMNS; ++j)
    {
        map[i][j]=0;
    }
  }


  for (int i = 0; i < ROWS; ++i)
  {
      map[0][i]=0;
      map[ROWS][i]=0;
  }

  for (int i = 0; i < COLUMNS; ++i)
  {
      map[i][COLUMNS]=0;
      map[i][0]=0;
  }

  int number=0;

  for (int i = 1; i < ROWS-1; ++i)
  {
    for (int j = 1; j < COLUMNS-1; ++j)
    {
      number=number+1;
      map[i][j]= number;
    }
  }

}

bool isMapConnex(char map[ROWS][COLUMNS], int mapNumbersCells[ROWS][COLUMNS]){

    int vertex = getNumOfVertex(map);

    Graph g(ROWS*COLUMNS);

    for (int i = 1; i < ROWS; ++i)
    {
      for (int j = 1; j < COLUMNS; ++j)
      {
          if (isEdge(i,j,i+1,j,map))
          {
              g.addEdge(mapNumbersCells[i][j],mapNumbersCells[i+1][j]);
          }

          if (isEdge(i,j,i,j+1,map))
          {
              g.addEdge(mapNumbersCells[i][j],mapNumbersCells[i][j+1]);
          }

          if (isEdge(i,j,i-1,j,map))
          {
              g.addEdge(mapNumbersCells[i][j],mapNumbersCells[i-1][j]);
          }

          if (isEdge(i,j,i,j-1,map))
          {
              g.addEdge(mapNumbersCells[i][j],mapNumbersCells[i][j-1]);
          }
      }
    }
    int connexVertex = g.BFS(mapNumbersCells[ROWS/2][COLUMNS/2]);

    printf("connexVertex: %i  vertex: %i \n",connexVertex,vertex );


    if (connexVertex==vertex)
    {
      return true;
    }else{
      return false;
    }
}


int getNumOfVertex(char map[ROWS][COLUMNS]){

  int vertex = 0;

    for (int i = 1; i < ROWS; ++i)
    {
      for (int j = 1; j < COLUMNS; ++j)
      {
          if (map[i][j]==' ')
          {
            vertex= vertex + 1;   
          }
      }
    }
    return vertex;
}

bool isEdge(int i, int j, int x, int y, char map[][COLUMNS]) {

  if (i > ROWS || j > COLUMNS || x> ROWS || y > COLUMNS)
  {
     return false;
  }

  if (map[i][j]==' ' && map[x][y]==' ')
  {
      return true;
  }else{
      return false;
  }

}

void randomlyGenerate(char map[][COLUMNS], int mapNumbersCells[ROWS][COLUMNS]){
    int i,j;
    for(i=0;i<1;i++)
        for(j=0;j<COLUMNS;j++){
            map[i][j]='0';
        }
    
    for(i=1;i<ROWS-1;i++)
        for(j=0;j<COLUMNS;j++){
            if(isBorder(j) || isCage(i,j))
                map[i][j]='0';
            else
                map[i][j]=' ';
        }
    
    for(i=ROWS-1;i<ROWS;i++)
        for(j=0;j<COLUMNS;j++){
            map[i][j]='0';
        }

    int rand_row=0;
    int rand_col=0;
    float corridors=0.0;
    float walls=0.0;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            if(map[i][j]=='0')
                walls=walls+1;
            else
                corridors=corridors+1;
        }
    }
    srand(time(NULL));
    while(walls/corridors<SATURATION){
//  cout << rand_row << " " << rand_col << "\n";
        rand_row = rand()%ROWS+1;
        rand_col = rand()%COLUMNS/2;
        if(valid_point(rand_row,rand_col)){
            map[rand_row][rand_col]='0';
            map[rand_row][COLUMNS-rand_col-1]='0';
            if(isMapConnex(map,mapNumbersCells)){
              printf("Connex\n");
              walls=walls+1;
            }else{
              printf("No Connex\n");
              map[rand_row][rand_col]=' ';
              map[rand_row][COLUMNS-rand_col-1]=' ';
            }  
        }
        else{
//    cout << "NO VALID\n" ;
  }
    }
}

bool valid_point(int i, int j){
    return !isLateral(i) && !isBorder(j) && !isCage(i,j) && !isInsideCage(i,j) && !isMidLane(j);
}

bool isBorder(int j){
    return j==0 || j==(COLUMNS-1);
}

bool isLateral(int i){
    return i==0 || i==ROWS-1;
}

bool isMidLane(int j){
    return j==COLUMNS/2;
}

bool isCage(int i, int j){
    if(i==ROWS/2 && j>COLUMNS/2-3 && j<COLUMNS/2+3 && j!=COLUMNS/2)
        return true;
    if(i==ROWS/2+4 && j>COLUMNS/2-3 && j<COLUMNS/2+3)
        return true;
    if(j==COLUMNS/2-3 && i>ROWS/2-1 && i<ROWS/2+5)
        return true;
    if(j==COLUMNS/2+3 && i>ROWS/2-1 && i<ROWS/2+5)
        return true;
    return false;
}

bool isInsideCage(int i, int j){
    return i>ROWS/2-5 && i<ROWS/2+5 && j>COLUMNS/2-3 && j<COLUMNS/2+3;
}

void printMap(char map[ROWS][COLUMNS]){
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printNumberMap(int map[ROWS][COLUMNS]){
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            printf("%i\t",map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
int main(int argc,char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Chess board");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

  glutMainLoop();
  return 0;
}
*/

//------------------------------------------------------------
//------------------------------------------------------------


