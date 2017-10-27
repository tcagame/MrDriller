#include "Player.h"
#include "DxLib.h"

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度

//グローバル変数宣言
static int g_img_handle = 0;
static int g_air = 100;
static int g_count = 0;

Player::Player( int x, int y ) {
	g_img_handle = LoadGraph( "Resource/Character.png", TRUE );
}

Player::~Player( ) {
	DeleteGraph( g_img_handle );
}

void Player::update( ) {
	g_count++;
	if ( g_count % ( 60 * TIME_AIR_DECREASE ) == 0 ) {
		g_air--;
	}
}

void Player::draw( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	DrawRectExtendGraph(0, 0, 100, 100, 0, 0, 25, 25, g_img_handle, TRUE);
}


int Player::getAir( ) {
	return g_air;
}