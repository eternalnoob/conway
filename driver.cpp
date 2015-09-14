#include "life.h.old"
#include <fstream>
#include <iostream>
int main() {
 char inputFile [256];
 std::cout << "Please input your file name" << std::endl;
 std::cin.getline( inputFile, 256 );
 life ourgame(inputFile);
 std::cout << std::endl << "Please select the time step, in seconds (floats allowed)"
	 << std::endl;
 double timeStep;
 std::cin >> timeStep;
 std::cin.clear();
 ourgame.setStep( timeStep );

 bool toroid;
 std::cout << "Please select whether the game should be toroidal (overlap at  edges)"
     << std::endl;
 std::cin >> toroid;
 std::cin.clear();
 ourgame.setToroidal( toroid );

 ourgame.infiniteLoop();
};
