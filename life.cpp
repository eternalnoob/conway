#include "life.h"
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "stdio.h"
#include "string.h"
int life::aliveNext( int x, int y)
{
    int returnVal = 0;
    int count = 0;

    for( int xOffset = -1 ; xOffset < 2 ; xOffset++ )
    {
        for( int yOffset = -1 ; yOffset < 2 ; yOffset++ )
        {
            int xcoord;
            int ycoord;
            if( x + xOffset < 0 ) 
                xcoord = kGridSize - 1;
            else
                xcoord = (x +xOffset) % kGridSize;

            if( y + yOffset < 0 )
                ycoord = kGridSize - 1;
            else
                ycoord = (y + yOffset) % kGridSize;

            if( x == xcoord && y == ycoord )
            {
            } 
            else if ( current[xcoord][ycoord] )
                count++;


        }
    }
    if( count < 2 || count > 3)
    {
        //we die or stay dead
        returnVal = 0;
    }
    else if( (count == 2 && current[x][y]) || count == 3 )
    {
        //we stay alive or are born
        returnVal = 1;
    }

    return returnVal;
};

void life::transfer()
{
    for ( int x = 0; x < kGridSize ; x++ )
    {
        for ( int y = 0; y < kGridSize ; y++ )
        {
            current[x][y] = next_iteration[x][y];
        }
    }
};

void life::update()
{
    //call aliveNext for every value in the grid
    for( int x = 0; x < kGridSize ; x++ )
    {
        for ( int y = 0; y < kGridSize ; y++ )
        {

            next_iteration[x][y] = aliveNext( x, y);
        }
    }

    //transfer the values into the current
    transfer();

}

void life::print()
{
    for( int x = 0; x < kGridSize ; x++ )
    {
        for ( int y = 0; y < kGridSize ; y++ )
        {
            if (current[x][y])
                std::cout << "\u25A0";
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

void life::setup( char * filename)
{

    std::ifstream inFile(filename);
    //fill with an appropriately large input size
    char input[300];

    //read in a blank line that will tell us how large to make our
    //vectors
    inFile.getline( input, 300 );
    //set gridsize appropriately
    kGridSize = strlen(input);

    //resize both current and next_iteration arrays
    current.resize( kGridSize );
    next_iteration.resize( kGridSize );

    for ( int column = 0; column < kGridSize ; column++ )
    {
        current[column].resize(kGridSize);
        next_iteration[column].resize( kGridSize );
    }

    for ( int x = 0 ; x < kGridSize ; x++ )
    {
        //allow for the terminating character
        inFile.getline( input, kGridSize + 1 );
        std::cout << input << std::endl;

        for  ( int y = 0; y <  kGridSize ; y++)
        {
            current[x][y] = int (input[y]) - 48;
        }
    }
    print();

};

void life::infiniteLoop()
{
    while( 1 )
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

