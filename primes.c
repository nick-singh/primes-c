/*

	Problem : Primes

	Problem Statement:

		Write a program to fill a 5 x 5 grid such that each row (from left to right), 
		each column (from top to bottom) and each diagonal (from left to right) form 
		a 5-digit prime number. The sum of the digits of each prime is the same. 
		For example:

		1 1 3 5 1
		3 3 2 0 3
		3 0 3 2 3
		1 4 0 3 3
		3 3 3 1 1

		Here, the digits of each prime add up to 11. The diagonal primes are 13331 and 34301.

		Data consists of two numbers, m and n. The digits of each prime must add up to m and 
		n must be placed in the top-left position. In the example, m = 11 and n = 1.

		You may use the same prime more than once in the grid. You must output all possible solutions.



	Solution:

	Given that all 5 digit prime numbers lay between 10000 and 99999, a function is used to generate all 
	the 5 digit numbers which adds up to some given prime number m. While each valid prime (primes which digits adds up to
	the given prime) is generated a table of indexes keeps track of the positions of all unique leading digits as well as 
	a matrix to store the digits of each prime, e.g. 13331, primeArray{1, 3, 3, 3, 1}.

	We will fill and check the square systematically in twelve steps. 
	Each step concerns a sequence of five digits. Filling each row, column, and diagonal.During this process some 
	positions in the square have been filled with a digit and others not yet. Whenever a new row/column/diagonal 
	is considered, we fill it with all possible candidate primes from the table (one by one). Of course, such a prime has 
	to match the digits that are already in the square. When all rows/ columns and diagonals 
	have been filled with primes we have a solution. 

	
	The digits are filled in the following order:

	1  2  3  4  5
	6 13 14 12 15
	7 16 11 18 19
	8 10 20 22 23
	9 17 21 24 25



*/

#include <stdio.h>
#include <stdlib.h>

#define maxPrimes 10000
#define gSize 5

int isPrime(int); //determines if a number is prime
int genetatePrimes(int[][gSize+1], int[], int); // generates list of prime numbers that add up to m

void initGrid(int[][gSize+1], int); // initializes the 5 x 5 grid
void printGrid(int[][gSize+1], int); // prints the 5 x 5 grid

void primes(int[][gSize+1], int[], int[][gSize+1], int, int, int); // filles the grid

FILE *in;
FILE *out;
int count = 0;

int main()
{


	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");

	int primeArray[maxPrimes][gSize+1], m, n, grid[gSize+1][gSize+1];
	int indexes[11];	
	initGrid(grid, gSize);	

	if(in == NULL || out == NULL){
		printf("error reading files\n");
		return 0;
	}
	fscanf(in,"%d %d", &m, &n);
	
	int numPrimes = genetatePrimes(primeArray, indexes, m);			
	indexes[10] = numPrimes-1;
	primes(primeArray, indexes, grid, numPrimes, m, n);	

	printf("%d \n", count);

	return 0;
}


void primes(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void row1(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	
	int i, j;
	grid[1][1] = n; // sets the first position in the grid to the privided number n

	row1(primeArray, indexes, grid, numPrimes, m, n);	// populates the first row
}


void row1(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){

	void col1(int[][gSize+1], int[], int[][gSize+1], int, int, int);

	int i, j, gridRow= 1, flag;

	for (i = indexes[n]; i < indexes[n+1]; i++)
	{	
		flag = 1;
		// ensure that none of the numbers in the first row contains a 0
		for(j =2; j < gSize; j++){
			if(primeArray[i][j] == 0)flag = 0;
		}
		if(flag){
			//	copy the valid digits into the gird
			for(j =2; j <= gSize; j++){
				grid[gridRow][j] = primeArray[i][j];												
			}						
			// now, populate the first column
			col1(primeArray, indexes, grid, numPrimes, m, n);	
		}
	}

}

void col1(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){

	void dia2(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	
	int i, j, gridCol = 1, flag;

	for (i = indexes[n]; i < indexes[n+1]; i++)
	{
		flag = 1;
		// ensure that the first column does not contain any 0
		for(j =2; j < gSize; j++){
			if(primeArray[i][j] == 0)flag = 0;
		}
		if(flag){					
			for(j = 2; j <= gSize; j++){
				grid[j][gridCol] = primeArray[i][j];																
			}							
			dia2(primeArray, indexes, grid, numPrimes, m, grid[5][1]);
		}
	}

}

void dia2(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void row2(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j, gridCol = 1;

	for (i = indexes[n]; i < indexes[n+1]; i++)
	{	// comparing what we already have stored in the grid
		if(grid[1][gSize] == primeArray[i][gSize]){

			// if we have a match, copy the remaining digits to hte grid
			grid[4][2]	= primeArray[i][2];
			grid[3][3]	= primeArray[i][3];
			grid[2][4]	= primeArray[i][4];

			// now to populate the second row
			row2(primeArray, indexes, grid, numPrimes, m, grid[2][1]);	
		}
	}

}


void row2(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void col2(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j, sum;
	for (i = indexes[n]; i < indexes[n+1]; i++)
	{
		if( grid[2][4] == primeArray[i][4]){
		
			grid[2][2]	= primeArray[i][2];
			grid[2][3]	= primeArray[i][3];
			grid[2][5]	= primeArray[i][5];	
			col2(primeArray, indexes, grid, numPrimes, m, grid[1][2]);		
		}
	}
}

void col2(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void row3(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if(grid[2][2] == primeArray[i][2] && grid[4][2] == primeArray[i][4]){
				
			grid[3][2]	= primeArray[i][3];
			grid[5][2]	= primeArray[i][5];	
			row3(primeArray, indexes, grid, numPrimes, m, grid[3][1]);			
		}
	}	

}


void row3(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void col3(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j, sum;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if(grid[3][2] == primeArray[i][2] && grid[3][3] == primeArray[i][3]){
		
			grid[3][4]	= primeArray[i][4];
			grid[3][5]	= primeArray[i][5];			
			col3(primeArray, indexes, grid, numPrimes, m, grid[1][3]);		
		}
	}
}

void col3(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void row4(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if(grid[2][3] == primeArray[i][2] && grid[3][3] == primeArray[i][3]){
				
			grid[4][3]	= primeArray[i][4];
			grid[5][3]	= primeArray[i][5];	
			row4(primeArray, indexes, grid, numPrimes, m, grid[4][1]);			
		}
	}	

}

void row4(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void col4(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j, sum;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if(grid[4][2] == primeArray[i][2] && 
			grid[4][3] == primeArray[i][3]){

			grid[4][4]	= primeArray[i][4];
			grid[4][5]	= primeArray[i][5];			
			col4(primeArray, indexes, grid, numPrimes, m, grid[1][4]);		
		}
	}
}

void col4(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void row5(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if(grid[2][4] == primeArray[i][2] && 
			grid[3][4] == primeArray[i][3] && 
			grid[4][4] == primeArray[i][4]){
				
			grid[5][4]	= primeArray[i][5];	
			row5(primeArray, indexes, grid, numPrimes, m, grid[5][1]);			
		}
	}	
}


void row5(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void col5(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j, sum;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if(grid[5][2] == primeArray[i][2] &&
			grid[5][3] == primeArray[i][3] && 
			grid[5][4] == primeArray[i][4]){
					
			grid[5][5]	= primeArray[i][5];			
			col5(primeArray, indexes, grid, numPrimes, m, grid[1][5]);		
		}
	}
}

void col5(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	void dia1(int[][gSize+1], int[], int[][gSize+1], int, int, int);
	int i, j;
	for (i = indexes[n]; i < indexes[n+1]; i++){

		if ((primeArray[i][2]==grid[2][5])&&
			(primeArray[i][3]==grid[3][5])&&
			(primeArray[i][4]==grid[4][5])&&
			(primeArray[i][5]==grid[5][5])){
			dia1(primeArray, indexes, grid, numPrimes, m, grid[1][1]);
		}
		
	}	
}


void dia1(int primeArray[][gSize+1], int indexes[], int grid[][gSize+1], int numPrimes, int m, int n){
	
	int i, j;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if ((primeArray[i][1]==grid[1][1])&&
			(primeArray[i][2]==grid[2][2])&&
			(primeArray[i][3]==grid[3][3])&&
			(primeArray[i][4]==grid[4][4])&&
			(primeArray[i][5]==grid[5][5])){
			printGrid(grid, gSize);
		count++;
		}		
	}
	
}

int genetatePrimes(int primeArray[][gSize+1], int indexes[], int m){
	int evaluatePrimes(int, int);
	int i, count = 1, temp, col, indexPos = 1;

	indexes[indexPos] = count; // position 1 has the index of all primes starting with 1

	for(i = 10001; i < 99999; i+=2){

		if(isPrime(i)){

			if(evaluatePrimes(i, m)){
				
				temp = i;
				col = gSize;			
				while(temp > 0){

					if(temp < 10){ // if we are on the first digit						
						if(indexPos != temp%10) {
							indexes[++indexPos] = count;												
						}						
					}
					primeArray[count][col] = temp%10;	
					temp/=10;
					col--;					
				}						
				count++;					
			}			
		}		
	}			
	return count;
}


int evaluatePrimes(int prime, int m){
	int sum = 0;
	while(prime > 0){
		sum += prime % 10;
		prime/=10;
	}
	return sum == m;	
}



void initGrid(int grid[][gSize+1], int len){
	int i, j;

	for(i = 1; i <= len; i++){
		for(j = 1; j <= len; j++){
			grid[i][j] = 0;		
		}		
	}
}

void printGrid(int grid[][gSize+1], int len){
	int i, j;

	for(i = 1; i <= len; i++){
		for(j = 1; j <= len; j++){
			fprintf(out,"%d ",grid[i][j]);
		}		
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
}

int isPrime(int n){
   int i;
   if(n<=1)return 0;
   if(n==2)return 1;
   if(n%2 == 0)return 0;
   for(i = 3; i*i<=n;i+=2){
	   if(n%i == 0)return 0;
   }
   return 1;
}
