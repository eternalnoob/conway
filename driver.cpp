#include "life.h"
int main() {
 life ourgame;
 char inputFile [256];
 std::cout << "Please input your file name";
 std::cin.getline( inputFile, 256 );
 ourgame.setup( inputFile);
 ourgame.gameLoop( 5 );
};
