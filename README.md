Problem Description:


	Write a program to fill a 5 x 5 grid such that each row (from left to right), 
	each column (from top to bottom) and each diagonal (from left to right) form a
	5-digit prime number. The sum of the digits of each prime is the same. For example:

		1	1	3	5	1

		3	3	2	0	3

		3	0	3	2	3

		1	4	0	3	3

		3	3	3	1	1

	Here, the digits of each prime add up to 11. The diagonal primes are 13331 and 34301.

	Data consists of two numbers, m and n. The digits of each prime must 
	add up to m and n must be placed in the top-left position. 
	In the example, m = 11 and n = 1.

	You may use the same prime more than once in the grid. 
	You must output all possible solutions.

	In addition to the above, there are two other 
	solutions for m = 11 and n = 1. They are:

		1 1 3 5 1		1 3 3 1 3 
		1 4 0 3 3		1 3 0 4 3 
		3 0 3 2 3 	and	3 2 3 0 3
		5 3 2 0 1		5 0 2 3 1
		1 3 3 1 3 		1 3 3 3 1
	
