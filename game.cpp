/* for now we're just going to store everything as an array of bools for simplicity's sake
 * fill the starting array with the values supplied by user
 * then iterate over the array to see what the updated state of the array will be
 * update array, then copy the updated array into the current array and repeat 
 */
#include <iostream>
#define SIZE 5
using namespace std;
int main() {

	bool current [SIZE][SIZE];
	bool updated [SIZE][SIZE];
	
	//store the count of live adjacent cells to current cell
	int count = 0;

	//zero the array
	for( int x = 0; x < SIZE ; x++ )
	{
		for ( int y = 0; y < SIZE ; y++ )
		{
			current[x][y]=0;
		}
	}

	//initialize basic array
	current [1][1] = 1;
	current [1][2] = 1;
	current [2][1] = 1;

	for( int x = 1; x < SIZE -1 ; x++ )
	{
		for( int y = 1; y < SIZE -1 ; y++ )
		{
			cout << current[x][y];
		}
		cout << endl;

	}

	//iterate over every cell within the array
	for( int x = 1 ; x < SIZE - 1 ; x++ )
	{
		for ( int y = 1 ; y < SIZE - 1  ; y++)
		{
			//inner loop to check all adjacents
			for ( int xOffSet = -1 ; xOffSet < 2; xOffSet++ )
			{
				for( int yOffSet = -1; yOffSet < 2; yOffSet++ )
				{
					//check if value at each adjacency is present
					if ( xOffSet == 0 && yOffSet == 0 )
					{
						//this means it's checking it's own value, do nothing
					}
					else if ( current[ x + xOffSet ][ y + yOffSet]  )
						count++;
				}

			}
			cout << endl << "Count at " << x <<" " << y << " is " << count << endl;
			if( count < 2 || count > 3)
			{
				//we die or stay dead
				updated[x][y] = 0;
			}
			else if( (count == 2 && current[x][y]) || count == 3 )
			{
				//we stay alive or are born
				updated[x][y] = 1;
			}


			//reset count
			count = 0;
		}
	}

	//print updated array
	for( int x = 1; x < SIZE -1 ; x++ )
	{
		for( int y = 1; y < SIZE -1 ; y++ )
		{
			if( updated[x][y] )
			{
				cout << "\u25A0";
			}
			else
			{
				cout << "\u25A1";
			};
		}
		cout << endl;

	}

};
