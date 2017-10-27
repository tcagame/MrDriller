#include "Player.h"
#include "DxLib.h"

//�萔�錾
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x

//�O���[�o���ϐ��錾
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
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y
	DrawRectExtendGraph(0, 0, 100, 100, 0, 0, 25, 25, g_img_handle, TRUE);
}


int Player::getAir( ) {
	return g_air;
}