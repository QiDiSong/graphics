#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <iostream>

//TO-DO:
//- randomize grid
//- insert certain "creatures"
//- 

// grid is a 2d array, 102x102, of ints
//(only 100x100 will be displayed, the extra 2 is so that we don't
//have to worry about ArrayIndexOutOfBounds errors)
// 0 = dead, 1 = alive

//randomizes grid
void randomWorld(int world[][52]){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			///to-do
		}
	}
}
//empties grid
void emptyWorld(int world[][52]){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			world[i][j]=0;
		}
	}
}

//grid copier so that we can put results into the copied grid without affecting
//the calculations based off of the original grid
void copyWorld(int original[][52], int copy[][52]){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			copy[i][j] = original[i][j];
		}
	}
}

//checks whether a cell should live or die
void life(int world[][52]){
	int temp[52][52];
	copyWorld(world, temp);
	for (int i = 1; i < 52; i++){
		for (int j = 1; j < 52; j++){
			int n = 0; //neighbour counter
			n = world[i-1][j] + world[i+1][j] + world[i][j+1] + world[i][j-1] + world[i-1][j+1] + world[i+1][j+1] + world[i-1][j+1] + world[i+1][j-1];
			if (n==3 || (world[i][j]==1 && n==2)){
				temp[i][j]==1;
			}
			else{
				temp[i][j]==0;
			}
		}
	}
	copyWorld(temp, world);
}

void print(int array[][52])
{	
	for(int j = 1; j < 52; j++)
 	{
 		for(int i = 1; i < 52; i++) 			
		{	
			if(array[j][i] == 1){
				printf("*");
			}
			else{
				printf("-");
			}
		}
		printf("\n");
 	}
}

int main(int argc, char **argv) {

	int wholeNewWorld[52][52];
	emptyWorld(wholeNewWorld);
	wholeNewWorld[5][5] = 1;
	wholeNewWorld[5][4] = 1;
	wholeNewWorld[4][5] = 1;
	wholeNewWorld[4][4] = 1;
	print(wholeNewWorld);
	printf("life! \n");
	life(wholeNewWorld);
	print(wholeNewWorld);
	// life(wholeNewWorld);
	// print(wholeNewWorld);
	// life(wholeNewWorld);

	return 0;
}