## This is a Readme file for RWA2Group_8_1
` Authored By @Aditya Varadaraj @Akhilrajan Vethirajan @Saurabh Palande `


The project directory comprises Src, Include and Doc directories

The src directory holds all the CPP files used to implement the DFS search algorithm and the move commands
The include directory holds all the header files(.h files) needed to implement the CPP code files
The Doc directory holds the code documents


##SRC Directory

1.api.cpp 

holds various method implementations providded by the simulator API
Note: cout here outputs to simulator. cerr outputs to console.

2.node.cpp

Contains methods to check and set walls in specified directions in maze

3.mouse.cpp

a. Contains the DFS algorithm (search_maze())

     #search_maze()#
	Order of preference North-->East-->South-->West
	The directions are with respect to the maze, i.e. global coordinates

b. Contains the move methods
c. Contains check and display walls in the API and m_maze
i.e. It provides knowledge of walls to the code through m_maze

4.main.cpp

This is the main file of the project 
All initializations are done in the main file
The position of the mouse is initialized
The Goal and the color and text of the goal are set using main()
This acts as the primary loop to recursively search and move the mouse until it reaches goal.
