#include <string>
#include <vector>
#ifndef LIFE_H
#define LIFE_H
class life
{
	 int kGridSize;

	
	private:
		double step = 1;
		//arrays to hold the current and next iteration of grids
        std::vector < std::vector<int> > current;
        std::vector < std::vector<int> > next_iteration;

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
		void infiniteLoop();
		life();
		double getStep();
		void setStep( double nStep );
};
#include "life.cpp"
#endif
