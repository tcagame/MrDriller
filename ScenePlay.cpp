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
	//後ろから順に描画
	drawBoard( );
	drawPlayer( );
}

void finalizePlay( ) {
	finalizePlayer( );
	finalizeBoard( );
}