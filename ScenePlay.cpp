#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include <stdio.h>
#include <memory>

//�萔�錾
const int DRAW_AIR_X = 1000;
const int DRAW_AIR_Y = 350;
const int DRAW_Depth_X = 1000;
const int DRAW_Depth_Y = 100;
const int DRAW_Level_X = 1000;
const int DRAW_Level_Y = 600;
const int DRAW_STRING_COLOR = RGB( 255, 255, 255 );


ScenePlay::ScenePlay( ) :
_depth( 0 ),
_level( 1 ) {
	_player = std::shared_ptr< Player >( new Player( 100, 100 ) );
	_board = std::shared_ptr< Board >( new Board( ) );
}

ScenePlay::~ScenePlay( ) {
}

Scene::SCENE ScenePlay::update( ) {
	_board->update( );
	_player->update( );
	return SCENE_PLAY;
}

void ScenePlay::draw( ) const {
	//��납�珇�ɕ`��
	_board->draw( );
	_player->draw( );
	drawAir( );
	drawDepth( );
	drawLevel( );

}

void ScenePlay::drawDepth( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Depth:%d", _depth );
	DrawString( DRAW_Depth_X, DRAW_Depth_Y, buf, DRAW_STRING_COLOR );
}

void ScenePlay::drawAir( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Air:%d%%", _player->getAir( ) );
	DrawString( DRAW_AIR_X, DRAW_AIR_Y, buf, DRAW_STRING_COLOR );
}

void ScenePlay::drawLevel( ) const {
	char buf[ 20 ];
	sprintf_s( buf, "Level:%d", _level );
	DrawString( DRAW_Level_X, DRAW_Level_Y, buf, DRAW_STRING_COLOR );
}