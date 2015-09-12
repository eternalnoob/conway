#include <string>
#include <vector>
#ifndef LIFE_H
#define LIFE_H
class life
{
    private:
        int xGridSize;
        int yGridSize;
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
        //called every iteration to update the grid
        void update();

        //populate the initial array according to user supplied text file
        void setup( std::string filename);
    public:
        //runs the loop of the game a give number of iterations, printing after each
        void gameLoop(int iterations);
        //loops constantly at the given Time Step
        void infiniteLoop();
        //constructor initiates our grids
        life( std::string filename);
        //allows us to retrieve the time step
        double getStep();
        //sets the time step
        void setStep( double nStep );
        //used to set whether or not the grid is toroidal
        bool getToroidal();
        void setToroidal( bool toroidal );
};
#include "life.cpp"
#endif
