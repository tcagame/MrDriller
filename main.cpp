#include <Windows.h>
#include <memory>
#include "Game.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow ) {
	std::shared_ptr< Game > game( new Game );
	game->run( );
	return 0;
}