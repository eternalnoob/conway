#include "life.h"
#include <fstream>
int life::toroidalAliveNext( int row, int col)
{
	int returnVal = 0;
	int count = 0;

	for( int rowOffset = -1; rowOffset < 2; rowOffset++ )
	{
		for( int colOffset = -1; colOffset < 2; colOffset++ )
		{
			int rowCoord = ( row + rowOffset + rowGridSize ) % rowGridSize;
			int colCoord = ( col + colOffset + colGridSize ) % colGridSize;

			if( row == rowCoord && col == colCoord)
			{

			}
			else if( current[rowCoord][colCoord] )
				count++;

		}
	}
	if( count < 2 || count > 3 )
	{
		//we die or stay dead
		returnVal = 0;
	}
	else if ( ( count == 2 && current[row][col] ) || count == 3) 
	{
		//we stay alive or are born
		returnVal = 1;
	}
	return returnVal;

};

int life::nonToroidalAliveNext( int row, int col )
{
	int returnVal = 0;
	int count = 0;
	
	for( int rowOffset = -1; rowOffset < 2 ; rowOffset++ )
	{
		for( int colOffset = -1; colOffset < 2 ; colOffset++ )
		{
			int rowCoord = row + rowOffset;
			int colCoord = col + colOffset;

			if( (rowCoord == row && colCoord == col)  )
			{
			}
			else if( rowCoord >= rowGridSize || rowCoord < 0
					|| colCoord >= colGridSize || colCoord < 0)
			{
			}
			else if( current[rowCoord][colCoord])
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
    else if( ( count == 2 && current[row][col] ) || count == 3 )
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
    for ( int row = 0; row < rowGridSize ; row++ )
    {
        for ( int col = 0; col < colGridSize ; col++ )
        {
            current[row][col] = next_iteration[row][col];
        }
    }
};

void life::update()
{
    //call aliveNext for every value in the grid
    for( int row = 0; row < rowGridSize ; row++ )
    {
        for ( int col = 0; col < colGridSize ; col++ )
        {

            //call the correct AliveNext Function
            next_iteration[row][col] = ( toroidal ?
            toroidalAliveNext(row, col) : nonToroidalAliveNext(row, col) );
        }
    }

    //transfer the values into the current
    transfer();

}

void life::setup( std::string filename)
{

    std::fstream inFile(filename);
    //create a string to read input
    std::string input;
    //read in a blank line that will tell us how many rows
    inFile >> input;
    //set rowgridsize appropriately
    rowGridSize = input.length();

    //read in a blank line that will tell us how many columns
    inFile >> input;
    //set yGridSize appropriately
    colGridSize = input.length();

    //resize both current and next_iteration arrays
    //with the correct amount of columns
    current.resize( rowGridSize );
    next_iteration.resize( rowGridSize );

    //resize all of the sub arrays
    for ( int row = 0; row < rowGridSize ; row++ )
    {
        current[row].resize(colGridSize);
        next_iteration[row].resize( colGridSize );
    }

    for ( int row = 0 ; row < rowGridSize ; row++ )
    {
        //allow for the terminating character
        inFile >> input;

        for  ( int col = 0; col <  colGridSize ; col++)
        {
            //this is important, convert the input into an integer
            //then subtract the ascii value of 0
            current[row][col] = int (input[col]) - 48;
        }
    }

};

life::life(std::string filename)
{
	setup(filename);
};

life::life()
{
};

life::life( int row, int col)
{
	rowGridSize = row;
	colGridSize = col;
    current.resize( rowGridSize );
    next_iteration.resize( rowGridSize );

    for ( int row = 0; row < rowGridSize ; row++ )
    {
        current[row].resize(colGridSize);
        next_iteration[row].resize( colGridSize );
    }
    for ( int row = 0 ; row < rowGridSize ; row++ )
    {

        for  ( int col = 0; col <  colGridSize ; col++)
        {
            //this is important, convert the input into an integer
            //then subtract the ascii value of 0
            current[row][col] = 0;
        }
    }
}

void life::setToroidal( bool toroid )
{
    toroidal = toroid;
};

bool life::getToroidal()
{
    return toroidal;
};

int life::getValAt( int row, int col)
{
	if( row < rowGridSize && col < colGridSize )
		return current[row][col];
	else
		return -1;
};

int life::setValAt( int row, int col, int on)
{
	if( row < rowGridSize && col < colGridSize )
	{
		current[row][col] = on;
		return 0;
	}
	else
		return 1;
}

				

int life::getColumns()
{
	return colGridSize;
};

int life::getRows()
{
	return rowGridSize;
};
