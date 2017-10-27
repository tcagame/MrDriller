#include "Board.h"
#include "DxLib.h"

static int g_img_handle = 0;

void initBoard( ) {
	g_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
}

void updateBoard( ) {
}

void drawBoard( ) {
	DrawGraph( 0, 0, g_img_handle, TRUE);
}

void finalizeBoard( ) {
	DeleteGraph( g_img_handle );
}