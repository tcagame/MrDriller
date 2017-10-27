#include "Player.h"
#include "DxLib.h"

static int g_img_handle = 0;

void initPlayer( ) {
	g_img_handle = LoadGraph( "Resource/Character.png", TRUE );
}

void updatePlayer( ) {
}

void drawPlayer( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	DrawRectExtendGraph(0, 0, 100, 100, 0, 0, 25, 25, g_img_handle, TRUE);
}

void finalizePlayer( ) {
	DeleteGraph( g_img_handle );
}