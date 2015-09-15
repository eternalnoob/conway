#include <SDL2/SDL.h>
#include <iostream>
#include "life.h"

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;

const int CELL_SIZE = 15;
int CELL_WIDTH = CELL_SIZE;
int CELL_HEIGHT = CELL_SIZE;

SDL_Window* window;
SDL_Renderer* renderer1;

int delay = 100;

//get everything ready for the game
bool initEverything();
//initialize SDL
bool initSDL();
//create the SDL window
bool createWindow();
//create the SDL renderer1
bool createRenderer();
//setup renderer1
void setupRenderer();
//render current iteration, called every time we update grid
void render(life * gameRef);
//game loop
void runGame(life * gameRef);

void processClick(int x, int y);

struct rectMore
{
	SDL_Rect mRect;
	bool on;
};


int main( int argc, char* args[])
{
	life ourgame = life();
	std::cout << "Do you have an input file? (1 = yes, 0 = no)" << std::endl;
	bool input;
	std::cin >> input;
	if (input)
	{
		std::cout << "Please enter the name of your input file" << std::endl;
		std::string filename;
		std::cin >> filename;
		ourgame = life(filename);
	}
	else
	{
		int col;
		int row;
		std::cout << "Please Enter the number of columns you want your grid to have" << std::endl;
		std::cin >> col;
		std::cout << "Please Enter the number of rows you want your grid to have" << std::endl;
		std::cin >> row;
		ourgame = life(row,col);

	}

	ourgame.setToroidal(0);

	if( !initEverything() )
		return -1;

	runGame(&ourgame);
};



void runGame(life * gameRef)
{
	render(gameRef);
	bool loop = true;
	//small flag to keep track if game is paused
	bool paused = true;

	while ( loop )
	{
		SDL_Event event;
		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
				loop = false;
			else if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_RIGHT:
						delay-=1;
						break;
					case SDLK_LEFT:
						delay+=1;
						break;
						// Remeber 0,0 in SDL is left-top. So when the user pressus down, the y need to increase
					case SDLK_DOWN:
						gameRef->setToroidal( 0 );
						break;
					case SDLK_UP:
						gameRef->setToroidal( 1 );
						break;

					case SDLK_SPACE:
						paused = !paused;

					default :
						break;
				}
			}
			else if ( event.type == SDL_MOUSEBUTTONDOWN )
			{
				if( event.button.button == SDL_BUTTON_LEFT )
				{
					int col = event.button.x / CELL_SIZE;
					int row = event.button.y / CELL_SIZE;
					gameRef->setValAt( row, col , !(gameRef->getValAt( row, col) ));
					render(gameRef);

				}

			}

		}

		if( !paused )
		{
			gameRef->update();
			render(gameRef);
		}

		// Add a 100msec delay to make our game run at a reasonable rate
		SDL_Delay(delay);
	}
}
void render( life * gameRef)
{
	// Clear the window and make it all red
	SDL_RenderClear( renderer1 );

	rectMore r[gameRef->getRows()][gameRef->getColumns()];
	for(int row = 0; row < gameRef->getRows(); row++ )
	{
		for ( int col = 0; col < gameRef->getColumns(); col++ )
		{
			r[row][col].mRect.x = col*CELL_WIDTH;
			r[row][col].mRect.y = row*CELL_HEIGHT;
			r[row][col].mRect.w = CELL_WIDTH;
			r[row][col].mRect.h = CELL_HEIGHT;
			r[row][col].on = gameRef->getValAt( row, col );
			if (r[row][col].on)
			{
				SDL_RenderFillRect(renderer1, &r[row][col].mRect);
			}
			else
			{
				SDL_RenderDrawRect(renderer1, &r[row][col].mRect);
			}
		}
	}


	// Render the changes above
	SDL_RenderPresent( renderer1);
}
bool initEverything()
{
	if ( !initSDL() )
		return false;

	if ( !createWindow() )
		return false;

	if ( !createRenderer() )
		return false;

	setupRenderer();

	return true;
}
bool initSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
bool createWindow()
{
	window = SDL_CreateWindow( "Server", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );

	if ( window == nullptr )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}

	return true;
}
bool createRenderer()
{
	renderer1 = SDL_CreateRenderer( window, -1, 0 );

	if ( renderer1 == nullptr )
	{
		std::cout << "Failed to create renderer1 : " << SDL_GetError();
		return false;
	}

	return true;
}
void setupRenderer()
{
	// Set size of renderer1 to the same as window
	SDL_RenderSetLogicalSize( renderer1, SCREEN_WIDTH, SCREEN_HEIGHT );

	// Set color of renderer1 to black
	SDL_SetRenderDrawColor( renderer1, 0, 0, 0, 0 );

}

