#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include <stdio.h>
#include <memory>

//íËêîêÈåæ
const int UI_X = 900;
const int DRAW_AIR_X = 922;
const int DRAW_AIR_Y = 365;
const int GAGE_WIDTH = 330;
const int GAGE_HEIGHT = 45;
const int DRAW_Depth_X = 1000;
const int DRAW_Depth_Y = 100;
const int DRAW_Level_X = 1000;
const int DRAW_Level_Y = 600;
const int DRAW_Life_X = 1000;
const int DRAW_Life_Y = 700;
const int DRAW_Score_X = 1000;
const int DRAW_Score_Y = 300;
const int DRAW_STRING_COLOR = RGB( 255, 255, 255 );
const int GAGE_COLOR = RGB( 0, 0, 255);


ScenePlay::ScenePlay( ) :
_level( 1 ) {
	_img_ui = LoadGraph( "Resource/DrillerUI.png" );
	_img_back = LoadGraph( "Resource/back.jpg" );

	_board = std::shared_ptr< Board >( new Board( ) );
	_player = std::shared_ptr< Player >( new Player( 300, 0, _board ) );
}

ScenePlay::~ScenePlay( ) {
}

Scene::SCENE ScenePlay::update( ) {
	_board->update( );
	_player->update( );
	return SCENE_PLAY;
}

void ScenePlay::draw( ) const {
	//å„ÇÎÇ©ÇÁèáÇ…ï`âÊ
	drawBack( );
	drawUIBack( );
	_board->draw( );
	_player->draw( );
	drawAir( );
	drawDepth( );
	drawLevel( );
	drawLife( );
	drawScore( );
}

void ScenePlay::drawDepth( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Depth:%d", _player->getDepth( ) );
	DrawString( DRAW_Depth_X, DRAW_Depth_Y, buf, DRAW_STRING_COLOR );
}

void ScenePlay::drawAir( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Air:%d%%", _player->getAir( ) );
	DrawString( DRAW_AIR_X, DRAW_AIR_Y + 50, buf, DRAW_STRING_COLOR );
	DrawBox( DRAW_AIR_X, DRAW_AIR_Y, DRAW_AIR_X +( int )( GAGE_WIDTH * _player->getAir( ) / 100 ), DRAW_AIR_Y+GAGE_HEIGHT, GAGE_COLOR, TRUE );
}

void ScenePlay::drawLevel( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Level:%d", _level );
	DrawString( DRAW_Level_X, DRAW_Level_Y, buf, DRAW_STRING_COLOR );
}

void ScenePlay::drawScore( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "SCORE:%d", _player->getScore( ) );
	DrawString( DRAW_Score_X, DRAW_Score_Y, buf, DRAW_STRING_COLOR );
}

void ScenePlay::drawUIBack( ) const {
	DrawGraph( UI_X, 0, _img_ui, FALSE );
}

void ScenePlay::drawLife( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Lives:%d", _player->getLife( ) );
	DrawString( DRAW_Life_X, DRAW_Life_Y, buf, DRAW_STRING_COLOR );
}

void ScenePlay::drawBack( ) const {
	DrawExtendGraph( 0, 0, UI_X, 720, _img_back, FALSE );
}
