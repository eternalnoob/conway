#include <string>
#include <vector>
#ifndef LIFE_H
#define LIFE_H
class life
{
    private:
		//number of columns
        int xGridSize;
		//number of rows
        int yGridSize;
		//whether the grid overlaps
        bool toroidal;
        double step = 1;
        //arrays to hold the current and next iteration of grids
        std::vector < std::vector<int> > current;
        std::vector < std::vector<int> > next_iteration;

        //called within update to see if cell will be "alive" in the next iteration
        int toroidalAliveNext(int x, int y);

        //called depending whether or not we are using a toroidal array or not
        int nonToroidAliveNext(int x, int y);

        //called after every iteration to print the grid of the game
        void print();
        //called to transfer the next_iteration into current
        void transfer();
        //populate the initial array according to user supplied text file
        void setup( std::string filename);

    public:
        //runs the loop of the game a give number of iterations, printing after each
        void gameLoop(int iterations);
        //loops constantly at the given Time Step
        void infiniteLoop();
        //constructor initiates our grids
        life( std::string filename);
		//constructor initiates empty grid;
		life( int x, int y);
		//default constructor populates an nonexistant grid;
		life();
        //allows us to retrieve the time step
        double getStep();
        //sets the time step
        void setStep( double nStep );
        //used to set whether or not the grid is toroidal
        void setToroidal( bool toroidal );
		//let us now if the grid is toroidal or not
        bool getToroidal();

		int getXColumns();
		int getYRows();
		//get value at x and y coord given such that it is in range
		int getValAt( int x, int y);

		//set value at x and y coord given such that it is in range
		//return 0 on success, 1 on failure
		int setValAt( int x, int y, int on);

        //called every iteration to update the grid
        void update();
};
#include "life.cpp"
#endif
