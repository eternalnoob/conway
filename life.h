#include <string>
#ifndef LIFE_H
#define LIFE_H
class life
{
	static const int kGridSize = 5;
	static const int kGameMax = kGridSize -1;
	static const int kGameSize = kGridSize - 2;

	
	private:
		//arrays to hold the current and next iteration of grids
		int current [kGridSize][kGridSize];
		int next_iteration [kGridSize][kGridSize];

		//called within update to see if cell will be "alive" in the next iteration
		int aliveNext(int x, int y);

		//called after every iteration to print the grid of the game
		void print();
		//called to transfer the next_iteration into current
		void transfer();
		//called every iteration to update the grid
		void update();
		
	public:
		//runs the loop of the game a give number of iterations, printing after each
		void gameLoop(int iterations);
		//populate the initial array according to user supplied text file
		void setup( char * filename);
		life();
};
#include "life.cpp"
#endif
