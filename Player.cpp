#include "Player.h"
#include "DxLib.h"

static int g_img_handle = 0;

void initPlayer( ) {
	g_img_handle = LoadGraph( "Resource/Character.png", TRUE );
}

void updatePlayer( ) {
}

void drawPlayer( ) {
	//DrawGraph( 0, 0, g_img_handle, TRUE);
}

void finalizePlayer( ) {
	DeleteGraph( g_img_handle );
}