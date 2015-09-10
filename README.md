#This is an implementation of Conway's Game of Life in C++ for linux
##By: Ethan Seither

1. Getting Started
  1. Compile using g++ driver.cpp -std = c++11 -o (output file name)
  2. Provide a properly formatted input file
    a. First line should supply the number of rows in the input file
    b. Second line should supply the number of columns in the input file
    c. Next line begins the pattern. Live cells are represented by 1, dead are 0
  3. Provide your Preferred time step for the loops( integer or float )
  4. Hit enter and watch!
  5. Press a key to exit at any time
2. Behavior
  1. This implementation uses a multidimensional array to store a grid of cells
  2. The grid is toroidal, meaning when a shape goes off one edge, it will continue onto the other
    a. Your glider guns will all die eventually, don't take it to heart.
3. What's Next
  1. Get this working on windows using equivalent of linux-exclusive functions
  2. Possibly tie in with a very simple graphics library such that user can create their own grids more easily
