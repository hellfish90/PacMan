
#include <stdio.h>
#include "graph.cc"

#define COLUMNS 25
#define ROWS 25
#define WIDTH 300
#define HEIGHT 300

//-----------------------------------------------

void randomlyGenerate(char map[][COLUMNS]);
void printMap(char map[][COLUMNS]);
bool isBorder(int j);
bool isCage(int i, int j);

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
    randomlyGenerate(map);
    printMap(map); 
}

void randomlyGenerate(char map[][COLUMNS]){
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
    
    
}

bool isBorder(int j){
    return j==0 || j==COLUMNS-1;
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

void printMap(char map[][COLUMNS]){
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            printf("%c",map[i][j]);
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


