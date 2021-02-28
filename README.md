### AISearchProject

#### Created By: Shadi Helf

#### Date Of Creation: December 21, 2020.

#### VERY IMPORTANT : Read the AI_Project_Summary PDF file in order to understand the inner workings of this project.

#### Summary:
A project which revolves around finding optimal cost path in a grid with a given start and end points using both informed and uninformed search algorithms with some squares in the grid that are a dead end and has a value of -1. The algorithms used in
this project are Iterative Deepining Search (IDS) , Uniform Cost Search (UCS) , A* (ASTAR) , Iterative Deepining A* (IDASTAR) , Bidirectional A* (BIASTAR).
Tests files and their results are in the 'Tests' folder.

Example Test :

	ASTAR // Algorithm name
	17    // Dimensions of grid. Here we have 17 x 17 grid.
	0,0   // Starting point
	16,16 // Ending Point
 	1, 1, 6, 2, 8, 2, 9, 4, 8, 7, 5, 9, 8, 2, 1, 3, 6 // Prices of vertices in grid first line
 	4, 1, 2, 9,12, 2, 7, 9, 2, 1, 2, 8, 9, 3,12, 6, 7
 	1, 7, 8, 9, 1, 2, 1,12,12, 2,12, 1, 2,12, 3, 7, 5
 	2, 7, 6, 9,12, 5,12, 6, 3, 8, 2, 7, 9, 7, 1, 7, 1
 	9, 1, 3, 5, 6, 2,12, 4, 1, 7, 4, 6, 6, 2, 8,12, 5
 	2, 2, 1, 1, 6, 2, 6, 4, 9, 5, 6,12, 7, 3, 3,12, 5
 	3, 2, 3,12, 1, 8,12, 4, 9, 4, 9, 2, 3, 1, 2, 3, 8
 	4, 1, 4, 8, 9, 1, 9, 3, 7, 8, 5, 2, 5, 1, 4, 4, 2
	-1, 3, 9, 5, 5,12, 2, 3, 2, 8,12, 3, 5, 8, 6, 3, 2
 	1, 4, 8,12, 9, 6, 2, 4, 2, 2, 5, 2,12, 3, 6, 8, 4
 	2, 6, 2, 7, 1, 6, 4, 3, 4, 7, 6, 2, 7, 2, 5,12, 1
 	9, 3, 2, 8, 8, 6, 7, 8, 2, 2, 1, 6, 3, 6, 4, 6, 9
 	9, 6, 3, 6, 7, 3, 9, 5,12, 6, 7, 1, 3, 6, 9,12, 2
 	7, 4, 3, 5, 4, 3, 6, 6, 6, 7, 2, 8, 4, 1, 6, 8, 2
 	1, 2, 1, 2, 5, 2, 7, 2, 9, 3, 3, 4,12, 2, 1, 7, 9 // Prices of vertices in grid last line
 	6, 5, 2, 3, 4,12, 3, 3, 2, 2, 5, 8, 2, 1, 9, 2, 9
 	3, 2, 2, 3, 2, 4, 9, 3, 5, 3, 6, 5, 8, 4, 7, 6, 7


In order to run the program download the AISearchProject.exe file and follow these steps :

1. Open the AISearchProject executable file.

2. Paste the absolute address of txt input file from your your PC ( Example input files exist in the Tests folder ).

3. Enter a positive number in order to determine the time limit for the search algorithm to run under.

4. Results will be displayed on screen.

5. Press 0 to exit the program.

Peace !!!
