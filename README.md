## FUNCTION:
  This program takes in an input containing the size of a nxn
  chess board along with an amount of preplaced queens and then
  attempts to place the remaining (n-inputted amount) queens in spots 
  where none of them can attack eachother.

## FILES:
  nqueens.cpp
    -contains the main function, the BoardState class, does 
     input/output and has the code for solving the nxn queens problem.
  queen.cpp
    -contains the queen class which is used to store the coords
     of a given queen as well as a function to check if the queen
     can attack another queen of given coords.
  queen.h
    -declares the queen class

## USAGE:
  To compile the program simply type "make" into the terminal.
  The program uses files for input/output. Each line of the
  input file is a new test and should be formatted like below.
  
  <size of board> <col of queen> <row of queen>
  ex.
    5 1 4 2 2
    The above example would create a 5x5 chessboard with
    preplaced queens at (1,4) and (2,2).
  
  If there is no solution to the given input, "No solution"
  is outputted, otherwise the coords to all the queens positions
  is outputted. The command to run the program is below.
  
  ./nqueens <input file> <output file>

## CITATIONS:
  How to split the input into seperate ints using stringstream
  from here:
  https://stackoverflow.com/questions/3421817/splitting-int-from-a-string/29326185
   
