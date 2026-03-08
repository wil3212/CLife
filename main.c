#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <unistd.h>

void gridInit(int cellSize, Vector2 cellNumber, Vector2 gridToInitialize[(int)cellNumber.x][(int)cellNumber.y]) {                    // Function will assing the right xreen coord for each cell
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
			gridToInitialize[i][j].x = i*cellSize;
			gridToInitialize[i][j].y = j*cellSize;
        	}
	}
}
void gridCellsInit(Vector2 cellNumber,int gridCells[(int)cellNumber.x][(int)cellNumber.y]) {
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
        		gridCells[i][j] = 0;	
		}
	}
}
void drawGrid(int cellSize,Vector2 cellNumber, int gridCells[(int)cellNumber.x][(int)cellNumber.y], Vector2 gridPoss[(int)cellNumber.x][(int)cellNumber.y]) {
	Vector2 cellSizeV = {cellSize,cellSize};
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
			if (gridCells[i][j] == 1) {
				DrawRectangleV(gridPoss[i][j],cellSizeV, BLUE);
			}

			else {
				DrawRectangleV(gridPoss[i][j],cellSizeV, BLACK);
			}
		}
	}
}
int countN(Vector2 cellNumber, Vector2 cellInQuestion,int gridCells[][(int)cellNumber.y]) {
	int matrix[3][3];
	matrix[0][0] = gridCells[(int)cellInQuestion.x - 1][(int)cellInQuestion.y -1];
	matrix[0][1] = gridCells[(int)cellInQuestion.x - 1][(int)cellInQuestion.y];
	matrix[0][2] = gridCells[(int)cellInQuestion.x - 1][(int)cellInQuestion.y +1];
	matrix[1][0] = gridCells[(int)cellInQuestion.x][(int)cellInQuestion.y -1];
	matrix[1][1] = 0;
	matrix[1][2] = gridCells[(int)cellInQuestion.x][(int)cellInQuestion.y +1];
	matrix[2][0] = gridCells[(int)cellInQuestion.x + 1][(int)cellInQuestion.y -1];
	matrix[2][1] = gridCells[(int)cellInQuestion.x + 1][(int)cellInQuestion.y];
	matrix[2][2] = gridCells[(int)cellInQuestion.x + 1][(int)cellInQuestion.y +1];

	if (cellInQuestion.x - 1 < 0) {
		matrix[0][0] = 0;
		matrix[0][1] = 0;
		matrix[0][2] = 0;
	}
	if (cellInQuestion.x + 1 > cellNumber.x) {
		matrix[2][0] = 0;
		matrix[2][1] = 0;
		matrix[2][2] = 0;
	}
	if (cellInQuestion.y - 1 < 0) {
		matrix[0][0] = 0;
		matrix[1][0] = 0;
		matrix[2][0] = 0;
	}
	if (cellInQuestion.y + 1 > cellNumber.y) {
		matrix[0][2] = 0;
		matrix[1][2] = 0;
		matrix[2][2] = 0;
	}
	int sum = 0;

        for (int i=0;i<3;i++) {
		for (int j=0;j<3;j++) {
                	sum = sum + matrix[i][j];
		}
	}
	return sum;
}
void updateGrid(Vector2 cellNumber, int gridCells[][(int)cellNumber.y]) {
	Vector2 cellInQuestion;
	int gridCells2[(int)cellNumber.x][(int)cellNumber.y];
	int current;
	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
                        cellInQuestion.x = i;
                        cellInQuestion.y = j;

			current = countN(cellNumber, cellInQuestion,gridCells);
                        if (gridCells[i][j] == 1) {
                        	if (current == 1 | current > 3) {
                                     	gridCells2[i][j] = 0;
				}
				else {
                                	gridCells2[i][j] = 1;
				}
			}
			if (gridCells[i][j] == 0) {
                       		if (current == 3) {
                                	gridCells2[i][j] = 1;
				}
				
				else {
					gridCells2[i][j] = 0;
				}

			}
		}
	}

	for (int i=0;i<cellNumber.x;i++) {
		for (int j=0;j<cellNumber.y;j++) {
	    		gridCells[i][j] = gridCells2[i][j];
		}
	}
}
void Ones(Vector2 cellNumber, int gridCells[][(int)cellNumber.y]) {
	/*
	gridCells[03][03] = 1;
	gridCells[03][04] = 1;
	gridCells[04][03] = 1;
	gridCells[04][04] = 1;

	gridCells[05][05] = 1;
	gridCells[05][06] = 1;
	gridCells[06][05] = 1;
	gridCells[06][06] = 1;
         */
	gridCells[0][0] = 1;
	gridCells[0][1] = 1;
	gridCells[1][0] = 1;
	gridCells[1][1] = 1;

	gridCells[4][4] = 1;
	gridCells[4][5] = 1;
	gridCells[5][4] = 1;
	gridCells[5][5] = 1;

	gridCells[10][3] = 1;
	gridCells[10][4] = 1;
	gridCells[10][5] = 1;
	gridCells[9][5] = 1;
	gridCells[8][4] = 1;
}

void randomCells(int number,Vector2 cellNumber, int gridCells[][(int)cellNumber.y]) {

	for (int i=0;i<number;i++) {
		int randx = rand() % ((int)cellNumber.x + 1);
		int randy = rand() % ((int)cellNumber.y + 1);
		gridCells[randx][randy] = 1;

	}

}
void printCell(Vector2 cellNumber, int gridCells[][(int)cellNumber.y]) {
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
int main() {
        Vector2 cellNumber = {500,500};  // Cell grid dimentions, e.g 50,100 would be a 50 by 100 cell grid
	int cellSize = 1;
	int width = cellSize*(int)cellNumber.x;
	int height = cellSize*(int)cellNumber.y;
	char *title = "sdhfjhsdafjh";
	Vector2 grid[(int)cellNumber.x][(int)cellNumber.y];  // 2d array holding the coordinates of every cell in the window
	gridInit(cellSize,cellNumber,grid);   //Initialize the poss grid
	int gridCells[(int)cellNumber.x][(int)cellNumber.y];  //grid containing alive dead status for each cell
	gridCellsInit(cellNumber, gridCells); // Initialize with all dead cells
	Vector2 pos = {0,0};
	Vector2 size = {10,10};
	//Ones(cellNumber, gridCells);
        randomCells(14000,cellNumber,gridCells);

	InitWindow(width, height, title);
        while (!WindowShouldClose()) {
	//for (int i=0;i<4;i++) {
	       // printCell(cellNumber, gridCells);
		BeginDrawing();
		drawGrid(cellSize,cellNumber,gridCells,grid);
		EndDrawing();
		updateGrid(cellNumber,gridCells);
	}
return 1;
}
