# AISearchProject

## Created By: Shadi Helf

## Date Of Creation: December 21, 2020.

# VERY IMPORTANT : Read the AI_Project_Summary PDF file in order to understand the inner workings of this project.

## Summary:
A project which revolves around finding optimal cost path in a grid with a given start and end points using both informed and uninformed search algorithms with some squares in the grid that are a dead end and has a value of -1. The algorithms used in
this project are Iterative Deepining Search (IDS) , Uniform Cost Search (UCS) , A* (ASTAR) , Iterative Deepining A* (IDASTAR) , Bidirectional A* (BIASTAR) 

## Example Input :

IDASTAR // Algorithm name and it could be IDS, UCS, ASTAR, IDASTAR, BIASTAR

30  // Indicates a maze with 30x30 dimensions

0,0  // Starting point

29,29  // Ending point

 7, 9, 4, 3, 7, 1, 4, 2, 7, 8, 2, 3, 1, 3, 6, 8, 6, 5, 4,-1, 5, 8, 2, 9, 6, 9, 5, 6, 6, 7 // the contents of the grid beginning
 
 6, 6, 4,-1, 3, 6, 6, 7, 6, 9, 6, 1, 3, 1, 3, 1, 5,-1, 2,-1, 5, 6, 1, 9,16, 7, 4, 8, 2,-1
 
 9, 6, 6, 5, 9, 6, 5, 1, 9, 6,16,-1,16, 2, 2, 3, 5, 6,-1, 8, 4, 4, 4, 4, 8, 8,-1,16, 2, 6
 
 1, 7, 4, 2, 9, 5, 8, 2, 1, 9, 1, 8, 8, 6, 2,-1,-1, 5, 5, 7, 8, 4, 8, 8, 9, 5,16, 1, 6,-1
 
 6, 6, 3, 6, 7, 6, 3,16, 8, 7, 5, 6, 2, 3, 8, 8, 3, 1,-1, 7,16, 1, 5,-1,-1, 3,-1, 5, 1, 7
 
 9, 6, 4, 6, 4,16, 1, 5, 3, 8,-1,-1,-1,16,-1, 8,-1, 4, 7, 3, 4, 1, 6, 3, 7, 6, 6, 1, 4, 6
 
 4, 6, 9, 6, 7, 5, 6, 3, 6,16, 2, 9, 4, 6,-1, 3, 6, 6, 6, 3,-1, 1,16, 7,16, 8,-1,16, 6,-1
 
 6, 3, 5, 5, 9, 2, 7, 6, 5, 4, 2, 2, 8,16, 2, 6, 6, 6, 7, 4, 4, 3,-1, 9, 1,-1,16, 6,-1, 4
 
 9, 6,16, 1, 1, 8, 4, 9, 6,-1, 6, 1, 4,-1, 5, 5, 1, 3, 1, 4, 6, 5, 6, 7, 4,-1, 6, 5, 5, 4
 
 8, 4,16, 1, 2,16, 6, 1, 5, 1,-1, 6, 4, 8, 2, 3, 6, 8, 7, 7, 3, 7, 2, 6, 8, 9, 1, 6, 2, 1
 
 4, 7, 7, 6, 9, 1, 5,16, 2, 9, 9, 6, 6, 3, 6, 6, 5, 6, 8, 3, 7, 3, 5, 6, 6, 3, 6, 3, 6, 8
 
 4, 8, 9, 1, 9, 4, 6, 1, 5, 6, 7, 7, 1, 5, 9, 8, 7, 6, 6, 6, 5, 4, 8, 2, 8,-1, 2, 3, 2, 2
 
 6, 1, 7, 7, 1, 5, 2, 5, 4,16, 4, 9, 2, 4, 5, 1, 6, 7, 2, 3, 4, 4,16, 6, 5, 3, 6, 7, 6,16
 
 5, 5, 7, 5, 8, 7, 4, 6, 9, 6, 3, 9, 4, 6, 3,16, 5, 6, 2,16, 6, 4, 4, 1, 3, 6, 4,16, 1, 6
 
 8, 4, 8, 6, 2, 3, 5, 9, 5, 9, 5, 2, 8, 1, 4, 8, 4, 6, 6, 5, 9, 2, 6, 7, 7, 1,16, 8,16, 1
 
 6, 9, 5, 3, 6, 3, 6,16, 3, 8, 2, 6, 8,16, 1, 5, 5, 7, 6, 4, 7, 6, 2,16, 6, 6, 5, 1, 1, 5
 
 7, 6, 8, 3, 2, 6, 9, 9, 6, 8, 7,16, 1, 1, 5, 1, 9, 7, 7, 5, 5,16, 1, 2, 2, 3, 4, 7, 8, 2
 
16, 6, 8, 9, 2, 9, 6,16, 2, 9, 6, 3, 1, 9,16, 6,16, 7, 9, 1, 5, 9,16, 5, 6, 5, 8, 1, 1, 1

 1, 2, 8, 9, 9, 6,16, 7,16, 3, 2, 6, 9, 2, 8, 5, 7, 2, 6, 1, 8, 5, 1, 3, 8, 6, 2, 8, 8,16
 
 9, 8, 1,16, 2, 9,16, 2, 6, 2, 9, 8, 1, 9, 1, 8, 3, 6, 4, 1,16, 5, 8, 2, 9, 6, 2, 9, 3, 9
 
 2, 1,16, 1,16, 6, 5, 6,16, 5, 3, 7, 2,16, 6, 4,16, 6, 8, 1, 5,16, 8, 4, 6, 2, 4, 6, 9, 7
 
 2, 5, 5, 1, 9, 7, 6, 9, 4, 5, 6, 7, 1, 6, 4, 5,16, 8, 7, 1, 8, 3, 7, 7, 3, 4, 6, 2, 3, 5
 
 9, 5, 7, 5, 6, 4, 2, 8, 7, 7, 3, 2, 8, 6, 4, 3, 7, 8, 6, 4, 9, 6, 6, 1, 7, 6,16, 1,16,16
 
 9, 6, 3,16, 3, 9, 7, 5, 6, 6, 1, 2, 3, 5, 4, 8, 6, 1, 9, 5, 7, 7, 9, 6,-1, 1, 6, 4, 3,16
 
 7, 1, 1, 6, 6, 5, 6, 6, 9, 8, 3, 4,16, 5, 4, 1,16, 8, 9, 6, 5, 3, 5, 7,-1, 1, 6, 1,16,16
 
 3, 1, 6, 2, 8, 3, 5, 3, 4, 6, 9, 1, 6, 5, 3, 6, 1, 6, 6, 2,16, 9, 1, 9, 6, 6, 6, 9, 6, 4
 
 1, 7, 7, 6,16, 3, 3, 6, 3, 1, 6,16, 5, 6,16, 1, 9, 6, 6, 6, 7, 2, 9,16, 2, 6, 1, 5,16, 1
 
 6, 6, 5, 6, 6, 3, 4,16, 2, 9, 1,16, 2, 4, 9, 3, 8, 6, 6,16, 4, 2, 2, 6, 7, 4, 4, 6, 5, 3
 
 6,16, 8, 2, 9, 6, 4, 2, 4, 7, 6, 8, 9, 8, 1, 1, 5, 6, 9, 9, 7,16, 5, 1, 7, 1, 6,16, 7, 1
 
 2,-1, 9, 4, 2, 8, 1, 1, 6, 4, 1,16, 6, 1, 9,16, 4, 6, 6, 5, 9, 9, 6, 6, 6, 7, 1, 8, 6, 3 // the contents of the grid end
 
 

## Example Output ( All explanation for the output is provided in the AI_Project_Summary PDF file ) :

Enter a time limit factor for the algorithm (dimension is 30): 0.2

Time limit = dimension * factor = 6.000000 seconds

SOLUTION DETAILS (IDASTAR) :

***************************************************************************************

Path : RD-RD-RD-RD-R-RD-RD-RD-R-R-RD-RD-RD-RU-R-RD-RD-RD-R-RD-RD-RD-RD-R-RD-RD-D-D-RD-D-RD-LD-RD-RD-D-D-D

Cost : 119.000000

Number Of Expanded Vertices : 812

***************************************************************************************

Solution Length : 38

Execution Time : 3.642000 seconds

Penetrance : 0.046798

Heursistic Average : 19.381773

Effective Branching Factor Is Approximately : 1.192799

Minimum Search Tree Depth : 1

Maximum Search Tree Depth : 40

Average Of Search Tree Depths : 21.911535

UPDATE: Code is tested and working 100% In order to run the code download and open the AISearchProject.exe file and follow the instructions in the PDF summary file in order to run the program properly. Also VERY important to check the pictures uploaded in order to see g=ho the exe file works.

Peace !!!
