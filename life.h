#include <string>
#include <vector>
#ifndef LIFE_H
#define LIFE_H
class life
{
    private:
		//number of columns
        int colGridSize;
		//number of rows
        int rowGridSize;
		//whether the grid overlaps
        bool toroidal = 1;
        //arrays to hold the current and next iteration of grids
        std::vector < std::vector<int> > current;
        std::vector < std::vector<int> > next_iteration;

        //called within update to see if cell will be "alive" in the next iteration
        int toroidalAliveNext(int row, int col);

        //called depending whether or not we are using a toroidal array or not
        int nonToroidalAliveNext(int row, int col);

        //called to transfer the next_iteration into current
        void transfer();
        //populate the initial array according to user supplied text file
        void setup( std::string filename);

    public:
        //constructor initiates our grids
        life( std::string filename);
		//constructor initiates empty grid;
		life( int row, int col);
		//default constructor populates an nonexistant grid;
		life();
		//Lets us set the whether the grid performs like a torus
        void setToroidal( bool toroidal );
		//let us now if the grid is toroidal or not
        bool getToroidal();

		int getColumns();
		int getRows();
		//get value at x and y coord given such that it is in range
		int getValAt( int row, int col);

		//set value at x and y coord given such that it is in range
		//return 0 on success, 1 on failure
		int setValAt( int row, int col, int on);

        //called every iteration to update the grid
        void update();
};
#include "life.cpp"
#endif
