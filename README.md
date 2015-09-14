#This is an implementation of Conway's Game of Life in C++ for linux
##By: Ethan Seither

1. Getting Started
  0. This requires the SDL2 graphics library for the GUI to work
    a. apt-get install libsdl2-dev if you have that apt magic
    b. otherwise you can install it however you want
    c. If you do not want these or cannot get these, you can still use the old console interface
    d. To do so, run g++ driver.cpp -std=c++11
  1. Compile by running make in the cloned directory
  2. Provide a properly formatted input file
    a. First line should supply the number of rows in the input file
    b. Second line should supply the number of columns in the input file
    c. Next line begins the pattern. Live cells are represented by 1, dead are 0
  3. A window will open, running your simulation
    a. press left to slow the simulation down
    b. press right to speed it up
    c. press down to set the grid to toroidal off(default);
    d. press up to st the grid to toroidal on
    e. press space to pause
    f. press left mouse button on any cell to switch it on or off
2. Behavior
  1. This implementation uses a multidimensional array to store a grid of cells
  2. The grid can be toroidal, meaning when a shape goes off one edge, it will continue onto the other
    a. Your glider guns will all die eventually, don't take it to heart.
  3. You can decide whether the array will be toroidal or not in the driver program
3. What's Next
  1. Translate the graphics side of this into a class to avoid passing so many references
  2. Get this working on windows using equivalent of linux-exclusive functions
  
