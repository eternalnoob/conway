#include "life.h"
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
			if( xOffset == 0  && yOffset == 0 )
			{
			}
			else if ( current[ x + xOffset ][y + yOffset] == 1 )
			{
				count++;
			}
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
	//clear out the border, this is really inefficient, fix it later
	//weoo technical debt
	for( int x = 0; x < kGridSize; x++)
	{
		for ( int y = 0; y < kGridSize; y++)
		{
			if( x == 0 || y == 0  || y == kGridSize-1 || x == kGridSize - 1 )
				current[x][y] = 0;
		}
	}
	for( int x = 1; x <= kGameSize ; x++ )
	{
		for ( int y = 1; y <= kGameSize ; y++ )
		{

			next_iteration[x][y] = aliveNext( x, y);
		}
	}

	//transfer the values into the current
	transfer();

}

void life::print()
{
	for( int x = 1; x <= kGameSize ; x++ )
	{
		for ( int y = 1; y <= kGameSize ; y++ )
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
	char input[kGameSize];
	for ( int y = 1; y <= kGameSize ; y++ )
	{
		inFile.getline( input, kGameSize +1 );
		for  ( int x = 1; x <= kGameSize ; x++)
		{
			current[y][x] = int (input[x-1]) - 48;
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

