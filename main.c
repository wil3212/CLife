#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <unistd.h>
#include <time.h>


// Matrix of int
                      // Returns pointer to beggining of array of len..
int* func1(int len) {
    int* arr = (int*) malloc(sizeof(int)*len); 
    if (arr == NULL) printf("failled to alloc mem to arrray");
    return arr; 
}
// Hardcode approach for making a matrix
int** func2(int rows,int columns) {
    int** matrix = (int**) malloc(sizeof(int*)*rows);
    if (matrix == NULL) {
        printf("failled to alloc mem for matrix");
        return NULL;
    }
    for (int i=0;i<rows;i++) {
        matrix[i] = func1(columns);
    }
    return matrix;
}
// Free matrix...
void freeMatrix(int** matrix,int rows) {
    for (int i=0;i<rows;i++) {
        free(matrix[i]);
    }
    free(matrix);
    printf("matrix freed!\n");
}                     


// Matrix of Vector2

                      // Returns pointer to beggining of array of len..
Vector2* func1V(int len) {
    Vector2* arr = (Vector2*) malloc(sizeof(Vector2)*len); 
    if (arr == NULL) printf("failled to alloc mem to arrray");
    return arr; 
}
// Hardcode approach for making a matrix
Vector2** func2V(int rows,int columns) {
    Vector2** matrix = (Vector2**) malloc(sizeof(Vector2*)*rows);
    if (matrix == NULL) {
        printf("failled to alloc mem for matrix");
        return NULL;
    }
    for (int i=0;i<rows;i++) {
        matrix[i] = func1V(columns);
    }
    return matrix;
}
// Free V matrix...
void freeVMatrix(Vector2** matrix,int rows) {
    for (int i=0;i<rows;i++) {
        free(matrix[i]);
    }
    free(matrix);
    printf("matrix freed!\n");
}                     
// --------------------------------------------------------------------------------------
void gridInit(int cellSize, Vector2 cellNumber, Vector2** gridToInitialize) {                    // Function will assing the right xreen coord for each cell
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
			gridToInitialize[i][j].x = i*cellSize;
			gridToInitialize[i][j].y = j*cellSize;
        }
	}
}
void gridCellsInit(Vector2 cellNumber,int** gridCells) {
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
        		gridCells[i][j] = 0;	
		}
	}
}
void drawGrid(int cellSize,Vector2 cellNumber, int** gridCells, Vector2** gridPoss) {
	Vector2 cellSizeV = {cellSize,cellSize};
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
			if (gridCells[i][j] == 1) {
				DrawRectangleV(gridPoss[i][j],cellSizeV, BLUE);
			}
		}
	}
}
void drawGridUpdate(int cellSize,Vector2 cellNumber, int** gridCells, Vector2** gridPoss,Vector2* cellsToUpdate,int* countUpdates) {
	Vector2 cellSizeV = {cellSize,cellSize};
    if (*countUpdates > -1) {
        for (int i=0;i<=*countUpdates;i++) {
            if (gridCells[(int)cellsToUpdate[i].x][(int)cellsToUpdate[i].y] == 1) 
                DrawRectangleV(gridPoss[(int)cellsToUpdate[i].x][(int)cellsToUpdate[i].y],cellSizeV, BLUE);
        }
    }
}
int countN(Vector2 cellNumber, Vector2 cellInQuestion,int** gridCells) {
	int matrix[3][3];
    for (int i=0;i<3;i++) { //initializes with 3, so that later one is easy to tell if it fell in the excession cases
        for (int j=0;j<3;j++) {
            matrix[i][j] = 3;
        }
    }
	if (cellInQuestion.x - 1 < 0) {
        if (cellInQuestion.y == 0)
            matrix[0][0] = gridCells[(int)cellNumber.x-1][(int)cellNumber.y-1];                                    // cellNumber -1
        else 
            matrix[0][0] = gridCells[(int)cellNumber.x-1][(int)cellInQuestion.y-1];                               // cellNumber..
		matrix[0][1] = gridCells[(int)cellNumber.x-1][(int)cellInQuestion.y];     //talvez tenha que subtrair 1 de cellNumber.x
        if (cellInQuestion.y == cellNumber.y-1)
            matrix[0][2] = gridCells[(int)cellNumber.x-1][0];
        else 
            matrix[0][2] = gridCells[(int)cellNumber.x-1][(int)cellInQuestion.y+1];
	}
	if (cellInQuestion.x + 1 == cellNumber.x) {
        if (cellInQuestion.y == 0)
            matrix[2][0] = gridCells[0][(int)cellNumber.y-1];
        else
            matrix[2][0] = gridCells[0][(int)cellInQuestion.y-1];
		matrix[2][1] = gridCells[0][(int)cellInQuestion.y];
        if (cellInQuestion.y == cellNumber.y-1)
            matrix[2][2] = gridCells[0][0];
        else
            matrix[2][2] = gridCells[0][(int)cellInQuestion.y+1];
	}
	if (cellInQuestion.y - 1 < 0) {
        if (cellInQuestion.x == 0)
            matrix[0][0] = gridCells[(int)cellNumber.x-1][(int)cellNumber.y-1];
        else 
            matrix[0][0] = gridCells[(int)cellInQuestion.x-1][(int)cellNumber.y-1];
		matrix[1][0] = gridCells[(int)cellInQuestion.x][(int)cellNumber.y-1]; // talvez tenha que subrair 1 de cellNumber.y
        if (cellInQuestion.x == cellNumber.x-1)
            matrix[2][0] = gridCells[0][(int)cellNumber.y-1];
        else
            matrix[2][0] = gridCells[(int)cellInQuestion.x+1][(int)cellNumber.y-1];
	}
	if (cellInQuestion.y + 1 == cellNumber.y) {
        if (cellInQuestion.x == 0)
            matrix[0][2] = gridCells[(int)cellNumber.x-1][0];
        else
            matrix[0][2] = gridCells[(int)cellInQuestion.x-1][0];
		matrix[1][2] = gridCells[(int)cellInQuestion.x][0];
        if (cellInQuestion.x == cellNumber.x-1)
            matrix[2][2] = gridCells[0][0];
        else
            matrix[2][2] = gridCells[(int)cellInQuestion.x+1][0];
	}
    if (matrix[0][0] == 3)
	matrix[0][0] = gridCells[(int)cellInQuestion.x - 1][(int)cellInQuestion.y -1];
    if (matrix[0][1] == 3)
	matrix[0][1] = gridCells[(int)cellInQuestion.x - 1][(int)cellInQuestion.y];
    if (matrix[0][2] == 3)
	matrix[0][2] = gridCells[(int)cellInQuestion.x - 1][(int)cellInQuestion.y +1];
    if (matrix[1][0] == 3)
	matrix[1][0] = gridCells[(int)cellInQuestion.x][(int)cellInQuestion.y -1];
	matrix[1][1] = 0;
    if (matrix[1][2] == 3)
	matrix[1][2] = gridCells[(int)cellInQuestion.x][(int)cellInQuestion.y +1];
    if (matrix[2][0] == 3)
	matrix[2][0] = gridCells[(int)cellInQuestion.x + 1][(int)cellInQuestion.y -1];
    if (matrix[2][1] == 3)
	matrix[2][1] = gridCells[(int)cellInQuestion.x + 1][(int)cellInQuestion.y];
    if (matrix[2][2] == 3)
	matrix[2][2] = gridCells[(int)cellInQuestion.x + 1][(int)cellInQuestion.y +1];
	int sum = 0;

    for (int i=0;i<3;i++) {
		for (int j=0;j<3;j++) {
            sum = sum + matrix[i][j];
		}
	}
	return sum;
}

void updateGrid(Vector2 cellNumber, int** gridCells, Vector2* cellsToUpdate,int* countUpdates) {
	Vector2 cellInQuestion;
	int current;
    *countUpdates = -1; //set to -1, as 0 indicates that cellsToUpdate[0] needs to change.
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
            cellInQuestion.x = i;
            cellInQuestion.y = j;
			current = countN(cellNumber, cellInQuestion,gridCells);
            if (gridCells[i][j] == 1) {
                if (current < 2 || current > 3) { 
                    //gridCells2[i][j] = 0;
                    (*countUpdates)++;
                    cellsToUpdate[*countUpdates].x = i;
                    cellsToUpdate[*countUpdates].y = j;
                    //printf("cell[%d][%d]: cuurent: %d\n",(int)cellInQuestion.x,(int)cellInQuestion.y,current);
                }
            }
            else {                             // that is, if (gridCells[i][j] == 0) {
                if (current == 3) {
                    //gridCells2[i][j] = 1;
                    (*countUpdates)++;
                    cellsToUpdate[*countUpdates].x = i;
                    cellsToUpdate[*countUpdates].y = j;
                }
			}
		}
    }
    if (*countUpdates > -1) {
        for (int i=0;i<=*countUpdates;i++)           // now, instead of checking every cell, just check the changed ones, in cellsToUpdate, from 0 to countUpdates.
            gridCells[(int)cellsToUpdate[i].x][(int)cellsToUpdate[i].y] = !gridCells[(int)cellsToUpdate[i].x][(int)cellsToUpdate[i].y];
    }
	
}
void Ones(Vector2 cellNumber, int** gridCells) {
	/*
	gridCells[03][03] = 1;
	gridCells[03][04] = 1;
	gridCells[04][03] = 1;
	gridCells[04][04] = 1;

	gridCells[05][05] = 1;
	gridCells[05][06] = 1;
	gridCells[06][05] = 1;
	gridCells[06][06] = 1;
         
	gridCells[0][0] = 1;
	gridCells[0][1] = 1;
	gridCells[1][0] = 1;
	gridCells[1][1] = 1;

	gridCells[4][4] = 1;
	gridCells[4][5] = 1;
	gridCells[5][4] = 1;
	gridCells[5][5] = 1;
          */
	gridCells[10][3] = 1;
	gridCells[10][4] = 1;
	gridCells[10][5] = 1;
	gridCells[9][5] = 1;
	gridCells[8][4] = 1;
}
void Test(Vector2 cellNumber, int** gridCells) {
	gridCells[1][49] = 1;
	gridCells[1][49] = 1;
	gridCells[99][50] = 1;
	gridCells[99][50] = 1;

}

void randomCells(int number,Vector2 cellNumber, int** gridCells) {
	for (int i=0;i<number;i++) {
		int randx = rand() % ((int)cellNumber.x );
		int randy = rand() % ((int)cellNumber.y );
		gridCells[randx][randy] = 1;
	}
}
void printCell(Vector2 cellNumber, int** gridCells) {
	printf("\n\n");
	Vector2 cellInQuestion;
	
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
			printf("%d",gridCells[i][j]);
		}
		printf("      ");
		for (int j=0;j<cellNumber.y;j++) {
			cellInQuestion.x = i;
			cellInQuestion.y = j;
			printf("%d",countN(cellNumber,cellInQuestion,gridCells));
		}
		printf("\n");
	}
}

struct quadrado {
	Vector2 screenPos;
	int status;
};
void quadraInit() {};

int main() {
	clock_t start,end;

    Vector2 cellNumber = {1000,1000};  // Cell grid dimentions, e.g 50,100 would be a 50 by 100 cell grid
	int cellSize = 1;
	int width = cellSize*(int)cellNumber.x;
	int height = cellSize*(int)cellNumber.y;
	char *title = "sdhfjhsdafjh";

    // ---------------For updateGrid() & drawGrid()---------------
    int countUpdates = 0; 
    int* toCountUpdates = &countUpdates;
    Vector2* toUpdate = func1V((int)cellNumber.x*(int)cellNumber.y);        // array that will hold coordinates of cells to update, has capacity to store (in the worst case) all cells in grid;
                                                                            //
    int countAlive = 0; 
    int* toCountAlive = &countUpdates;
    Vector2* toDraw = func1V((int)cellNumber.x*(int)cellNumber.y);        


    // Matrix instead of Vector2
    Vector2** grid = func2V((int)cellNumber.x,(int)cellNumber.y);
	gridInit(cellSize,cellNumber,grid);   //Initialize the poss grid
                                        
    printf("1 ok\n");
	//int gridCells[(int)cellNumber.x][(int)cellNumber.y];  //grid containing alive dead status for each cell
    int** gridCells = func2((int)cellNumber.x,(int)cellNumber.y);
    //int** gridCells2 = func2((int)cellNumber.x,(int)cellNumber.y);
	gridCellsInit(cellNumber, gridCells); // Initialize with all dead cells
                                          
    
    
    printf("2 ok\n");
	Vector2 pos = {0,0};
	//Vector2 size = {10,10};
	Ones(cellNumber, gridCells);
	//Test(cellNumber, gridCells);
    randomCells(14032,cellNumber,gridCells);


    printf("3 ok\n");
	InitWindow(width, height, title);
    while (!WindowShouldClose()) {
	//for (int i=0;i<4;i++) {
		start = clock();
	       // printCell(cellNumber, gridCells);
		BeginDrawing();
        ClearBackground(BLACK);
		//drawGridUpdate(cellSize,cellNumber,gridCells,grid,toUpdate,toCountUpdates);
	    drawGrid(cellSize,cellNumber,gridCells,grid);  //draw all squares
		EndDrawing();
		updateGrid(cellNumber,gridCells,toUpdate,toCountUpdates);
		end = clock();
        //printf("time %f\n", 1000*((double) (end - start)/CLOCKS_PER_SEC));
        printf("FPS %.0f\n", 1000 / (1000*((double) (end - start)/CLOCKS_PER_SEC)));
	}
    printf("program ended\n");
    free(toUpdate);
    freeMatrix(gridCells,(int)cellNumber.x);
    //freeMatrix(gridCells2,(int)cellNumber.x);
    freeVMatrix(grid,(int)cellNumber.x);
return 1;
}
