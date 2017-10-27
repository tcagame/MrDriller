#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include <stdio.h>

//プロトタイプ関数宣言
void drawAir( );
void drawDepth( );
void drawLevel( );

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度
const int DRAW_AIR_X = 1000;
const int DRAW_AIR_Y = 350;
const int DRAW_Depth_X = 1000;
const int DRAW_Depth_Y = 100;
const int DRAW_Level_X = 1000;
const int DRAW_Level_Y = 600;
const int DRAW_STRING_COLOR = RGB( 255, 255, 255 );

//グローバル変数宣言
static int g_air = 100;
static int g_depth = 0;
static int g_level = 1;
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
	drawDepth( );
	drawLevel( );

}

void finalizePlay( ) {
	finalizePlayer( );
	finalizeBoard( );
}

void drawDepth( ) {
	char buf[ 20 ];
	sprintf_s( buf, "Depth:%d", g_depth );
	DrawString( DRAW_Depth_X, DRAW_Depth_Y, buf, DRAW_STRING_COLOR );
}

void drawAir( ) {
	char buf[ 20 ];
	sprintf_s( buf, "Air:%d%%", g_air );
	DrawString( DRAW_AIR_X, DRAW_AIR_Y, buf, DRAW_STRING_COLOR );
}

void drawLevel( ) {
	char buf[ 20 ];
	sprintf_s( buf, "Level:%d", g_level );
	DrawString( DRAW_Level_X, DRAW_Level_Y, buf, DRAW_STRING_COLOR );
}