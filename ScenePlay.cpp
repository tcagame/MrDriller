#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include <stdio.h>

//プロトタイプ関数宣言
void drawAir( );

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度
const int DRAW_STRING_X = 1000;
const int DRAW_STRING_Y = 600;
const int DRAW_STRING_COLOR = RGB( 255, 255, 255 );

//グローバル変数宣言
static int g_air = 100;
static int g_time = 0;

void initPlay( ) {
	initPlayer( );
	initBoard( );
}

SCENE updatePlay( ) {
	g_time++;
	if ( g_time % ( 60 * TIME_AIR_DECREASE ) == 0 ) {
		g_air--;
	}
	updateBoard( );
	updatePlayer( );
	return SCENE_PLAY;
}

void drawPlay( ) {
	//後ろから順に描画
	drawBoard( );
	drawPlayer( );
	drawAir( );

}

void finalizePlay( ) {
	finalizePlayer( );
	finalizeBoard( );
}

void drawAir( ) {
	char buf[ 20 ];
	sprintf_s( buf, "Air:%d%%", g_air );
	DrawString( DRAW_STRING_X, DRAW_STRING_Y, buf, DRAW_STRING_COLOR );
}