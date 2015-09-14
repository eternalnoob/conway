#include "life.h"
//kbhit replicates the functionality of the windows function by the same name
#include "kbhit.cpp"
//unistd gives us the sleep function, have not added the appropriate windows function yet
#include <unistd.h>
#include <fstream>
#include <iostream>
int life::toroidalAliveNext( int x, int y)
{
    int returnVal = 0;
    int count = 0;

    for( int xOffset = -1 ; xOffset < 2 ; xOffset++ )
    {
        for( int yOffset = -1 ; yOffset < 2 ; yOffset++ )
        {
            //avoid negative index and overflow index by using combo
            //of modulus and adding xGridSize
            int xcoord = ( x + xOffset + xGridSize) % xGridSize;
            int ycoord = ( y + yOffset + yGridSize) % yGridSize;

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
}
int life::nonToroidAliveNext( int x, int y)
{
    int returnVal = 0;
    int count = 0;

    for( int xOffset = -1 ; xOffset < 2 ; xOffset++ )
    {
        for( int yOffset = -1 ; yOffset < 2 ; yOffset++ )
        {
            //avoid negative index and overflow index by using combo
            //of modulus and adding xGridSize
            int xcoord = ( x + xOffset );
            int ycoord = ( y + yOffset );

            //do not count self
            if( ( x == xcoord && y == ycoord ) )
            {
            } 
            //ignore cells past border
            else if( xcoord >= xGridSize || xcoord < 0 
                   || ycoord >= yGridSize || ycoord < 0 )
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
    for ( int x = 0; x < xGridSize ; x++ )
    {
        for ( int y = 0; y < yGridSize ; y++ )
        {
            current[x][y] = next_iteration[x][y];
        }
    }
};

void life::update()
{
    //call aliveNext for every value in the grid
    for( int x = 0; x < xGridSize ; x++ )
    {
        for ( int y = 0; y < yGridSize ; y++ )
        {

            //call the correct AliveNext Function
            next_iteration[x][y] = ( toroidal ?
            toroidalAliveNext(x, y) : nonToroidAliveNext(x, y) );
        }
    }

    //transfer the values into the current
    transfer();

}

void life::print()
{

    std:: cout << std::endl;
    for( int x = 0; x < xGridSize ; x++ )
    {
        for ( int y = 0; y < yGridSize ; y++ )
        {
            //print a "black" square
            if (current[x][y])
                std::cout << "\u25A0" << " ";
            //print a hollow square
            else
                std::cout << "\u25A1" << " ";
        }
        std::cout << std::endl;
    }
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

life::life( std::string filename )
{
    setup( filename );
};

void life::setup( std::string filename)
{

    std::fstream inFile(filename);
    //create a string to read input
    std::string input;
    //read in a blank line that will tell us how many columns
    inFile >> input;
    //set xgridsize appropriately
    xGridSize = input.length();

    //read in a blank line that will tell us how many rows
    inFile >> input;
    //set yGridSize appropriately
    yGridSize = input.length();

    //resize both current and next_iteration arrays
    //with the correct amount of columns
    current.resize( xGridSize );
    next_iteration.resize( xGridSize );

    //resize all of the sub arrays
    for ( int column = 0; column < xGridSize ; column++ )
    {
        current[column].resize(yGridSize);
        next_iteration[column].resize( yGridSize );
    }

    for ( int x = 0 ; x < xGridSize ; x++ )
    {
        //allow for the terminating character
        inFile >> input;

        for  ( int y = 0; y <  yGridSize ; y++)
        {
            //this is important, convert the input into an integer
            //then subtract the ASCII value of 0
            current[x][y] = int (input[y]) - 48;
        }
    }
   
    //print our initial array

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

void life::setToroidal( bool toroid )
{
    toroidal = toroid;
};

bool life::getToroidal()
{
    return toroidal;
};


void life::increaseStep( double seconds )
{
	step += seconds;
};

void life::decreaseStep( double seconds )
{
	step -= seconds;
};

int life::getValAt( int x, int y)
{
	if( x < xGridSize && y < yGridSize )
		return current[x][y];
	else
		return -1;
};

int life::getXColumns()
{
	return xGridSize;
};

int life::getYRows()
{
	return yGridSize;
};
