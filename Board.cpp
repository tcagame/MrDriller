#include "Board.h"
#include "DxLib.h"

static int g_img_handle = 0;

void initBoard( ) {
	g_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
}

void updateBoard( ) {
}

void drawBoard( ) {
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y
	DrawRectExtendGraph( 0, 0, 100, 60, 0, 0, 16, 16, g_img_handle, TRUE);
}

void finalizeBoard( ) {
	DeleteGraph( g_img_handle );
}