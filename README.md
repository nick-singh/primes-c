
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

		You may use the same prime more than once in the grid. 
		You must output all possible solutions.



	Solution:

	Given that all 5 digit prime numbers lay between 10000 and 99999, a function is used 
	to generate all the 5 digit numbers which adds up to some given prime number m. 
	While each valid prime (primes which digits adds up to the given prime) is 
	generated a table of indexes keeps track of the positions of all unique leading 
	digits as well as a matrix to store the digits of each prime, 
	e.g. 13331, primeArray{1, 3, 3, 3, 1}.

	We will fill and check the square systematically in twelve steps. 
	Each step concerns a sequence of five digits. Filling each row, column, 
	and diagonal.During this process some positions in the square have been filled 
	with a digit and others not yet. Whenever a new row/column/diagonal is 
	considered, we fill it with all possible candidate primes from the 
	table (one by one). Of course, such a prime has to match the digits that 
	are already in the square. When all rows/ columns and diagonals have been 
	filled with primes we have a solution. 

	
	The digits are filled in the following order:

	1  2  3  4  5
	6 13 14 12 15
	7 16 11 18 19
	8 10 20 22 23
	9 17 21 24 25

