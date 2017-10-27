#include "Player.h"
#include "DxLib.h"

static int g_img_handle = 0;

void initPlayer( ) {
	g_img_handle = LoadGraph( "Resource/Character.png", TRUE );
}

void updatePlayer( ) {
}

void drawPlayer( ) {
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y
	DrawRectExtendGraph(0, 0, 100, 100, 0, 0, 25, 25, g_img_handle, TRUE);
}

void finalizePlayer( ) {
	DeleteGraph( g_img_handle );
}