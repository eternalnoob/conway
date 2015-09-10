#include "life.h"
//kbhit replicates the functionality of the windows function by the same name
#include "kbhit.cpp"
//unistd gives us the sleep function, have not added the appropriate windows function yet
#include <unistd.h>
#include <fstream>
#include <iostream>
int life::aliveNext( int x, int y)
{
    int returnVal = 0;
    int count = 0;

    for( int xOffset = -1 ; xOffset < 2 ; xOffset++ )
    {
        for( int yOffset = -1 ; yOffset < 2 ; yOffset++ )
        {
            //avoid negative index and overflow index by using combo
            //of modulus and adding gridSize
            int xcoord = ( x + xOffset + gridSize) % gridSize;
            int ycoord = ( y + yOffset + gridSize) % gridSize;

            //do not count self
            if( x == xcoord && y == ycoord )
            {
            } 
            //if there is a "truthy" value at current, increment count
            else if ( current[xcoord][ycoord] )
                count++;
        }
    }
    if( count < 2 || count > 3)
    {
        //we die or stay dead
        returnVal = 0;
    }
    else if( ( count == 2 && current[x][y] ) || count == 3 )
    {
        //we stay alive or are born
        returnVal = 1;
    }

    return returnVal;
};

void life::transfer()
{
    //go through the entire vector, copying to current from the
    //next_iteration 
    for ( int x = 0; x < gridSize ; x++ )
    {
        for ( int y = 0; y < gridSize ; y++ )
        {
            current[x][y] = next_iteration[x][y];
        }
    }
};

void life::update()
{
    //call aliveNext for every value in the grid
    for( int x = 0; x < gridSize ; x++ )
    {
        for ( int y = 0; y < gridSize ; y++ )
        {

            next_iteration[x][y] = aliveNext( x, y);
        }
    }

    //transfer the values into the current
    transfer();

}

void life::print()
{
    for( int x = 0; x < gridSize ; x++ )
    {
        for ( int y = 0; y < gridSize ; y++ )
        {
            //print a "black" square
            if (current[x][y])
                std::cout << "\u25A0";
            //print a hollow square
            else
                std::cout << "\u25A1";
        }
        std::cout << std::endl;
    }
    std:: cout << std::endl;
}

//controls how many iterations we print
void life::gameLoop( int iterations )
{
    for( int n = 0; n < iterations ; n++ )
    {
        update();
        print();
    }
}

life::life()
{
};

void life::setup( std::string filename)
{

    std::fstream inFile(filename);
    //create a string to read input
    std::string input;
    //read in a blank line that will tell us how large to make our
    //vectors
    inFile >> input;
    //set gridsize appropriately
    gridSize = input.length();

    //resize both current and next_iteration arrays
    current.resize( gridSize );
    next_iteration.resize( gridSize );

    //resize all of the sub arrays
    for ( int column = 0; column < gridSize ; column++ )
    {
        current[column].resize(gridSize);
        next_iteration[column].resize( gridSize );
    }

    for ( int x = 0 ; x < gridSize ; x++ )
    {
        //allow for the terminating character
        inFile >> input;
        std::cout << input << std::endl;

        for  ( int y = 0; y <  gridSize ; y++)
        {
            //this is important, convert the input into an integer
            //then subtract the ASCII value of 0
            current[x][y] = int (input[y]) - 48;
        }
    }
   
    //print our initial array
    print();

};

void life::infiniteLoop()
{
    //while the user does not press a key
    while( kbhit() == 0)
    {
        update();
        print();
        //usleep takes microseconds, so convert seconds to microseconds
        usleep(step * 1000000);
    }
};

void life::setStep( double nStep )
{
    step = nStep;
};


double life::getStep()
{
    return step;
};

