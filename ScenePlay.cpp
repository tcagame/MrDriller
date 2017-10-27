#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include <stdio.h>

//�v���g�^�C�v�֐��錾
void drawAir( );

//�萔�錾
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x
const int DRAW_STRING_X = 1000;
const int DRAW_STRING_Y = 600;
const int DRAW_STRING_COLOR = RGB( 255, 255, 255 );

//�O���[�o���ϐ��錾
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
	//��납�珇�ɕ`��
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