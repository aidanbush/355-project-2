Group 6
Names: David Dowie, Aidan Bush, Ben Ha

File Structure:
In the main directory you will be able to compile and run the implementation. From the main directory this is how it is structured:

mini-report: directory that holds a makefile and mini-report.tex file to generate the mini-report.pdf (using "make all")
report: directory that holds a makefile and report.tex file to generate the report.pdf (using "make all")

Given Files: D5.txt, E4.txt, ND.pl, newgame.txt, driver.pl

Source Files:

alphabeta.c: The alpha-beta algorithm called to execute to a specified depth on a given state.

heuristic.c: The file that contains our three heuristic evaluation functions.

input.c: Takes the current state and finds the index of the inputted move from the current states children.

manager.c: Holds the desired heuristic function pointer and handle our thread we use for our timer.

state.c: Handles the model of our state. Adding children, freeing memory, and printing the state representation.

valid_moves.c: Generates all the valid_moves and adds them to the children of a given state.

konane.c: This handles the game being played. Takes in the user input and prints the move decided on in our alpha-beta search.

How to use the makefile:

To compile all the source files:
make all

To remove the .o and executables:
make clean

How to run the agent:
./konane.exe "{text file with the board}" {Player type: "B" or "W"}
