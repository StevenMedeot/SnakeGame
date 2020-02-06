#include "GameWindow.h"
#include <thread>
using namespace std;
int main(int argc, char* args[])
{
	GameWindow *game = new GameWindow("Snake Window", 640, 640);
	game->InitWindow();

	delete game;

	return 0;
}