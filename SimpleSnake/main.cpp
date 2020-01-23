#include "GameWindow.h"

using namespace std;
int main(int argc, char* args[])
{
	GameWindow *game = new GameWindow("Snake Window", 640, 480);
	game->InitWindow();
	game->UpdateWindow();
	delete game;

	return 0;
}