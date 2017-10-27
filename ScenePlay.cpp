#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"


void initPlay( ) {
	initPlayer( );
	initBoard( );
}

SCENE updatePlay( ) {
	updateBoard( );
	updatePlayer( );
	return SCENE_PLAY;
}

void drawPlay( ) {
	//å„ÇÎÇ©ÇÁèáÇ…ï`âÊ
	drawBoard( );
	drawPlayer( );
}

void finalizePlay( ) {
	finalizePlayer( );
	finalizeBoard( );
}