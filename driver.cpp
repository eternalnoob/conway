#include "life.h"
int main() {
 life ourgame;
 char inputFile [256];
 std::cout << "Please input your file name" << std::endl;
 std::cin.getline( inputFile, 256 );
 ourgame.setup( inputFile);
 std::cout << std::endl << "Please select the time step, in seconds (floats allowed)"
	 << std::endl;
 double timeStep;
 std::cin >> timeStep;
 std::cin.clear();
 ourgame.setStep( timeStep );
 ourgame.infiniteLoop();
};
