#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include <math.h>
#include <memory>

//íËêîêÈåæ
const int UI_X = 900;
const int DRAW_AIR_GAGE_X = 922;
const int DRAW_AIR_GAGE_Y = 365;
const int DRAW_AIR_NUM_X = 1105;
const int DRAW_AIR_NUM_Y = 440;
const int GAGE_WIDTH = 330;
const int GAGE_HEIGHT = 45;
const int DRAW_Depth_X = 1002;
const int DRAW_Depth_Y = 77;
const int DRAW_Level_X = 1145;
const int DRAW_Level_Y = 560;
const int DRAW_Life_X = 1000;
const int DRAW_Life_Y = 700;
const int DRAW_Score_X = 1001;
const int DRAW_Score_Y = 191;
const int NUM_WIDTH = 310;
const int NUM_HEIGHT = 310;
const int DRAW_NUM_SIZE_X = 37;
const int DRAW_NUM_SIZE_Y = 37;
const int DRAW_STRING_COLOR = RGB( 255, 255, 255 );
const int GAGE_COLOR = RGB( 0, 0, 255 );


ScenePlay::ScenePlay( ) :
	_level( 1 ) {
	_img_ui = LoadGraph( "Resource/DrillerUI.png" );
	_img_bg = LoadGraph( "Resource/bg.jpg" );
	_img_num = LoadGraph( "Resource/DrillerNumber.png" );
	_img_life = LoadGraph( "Resource/NewCharacter.png" );

	_board = std::shared_ptr< Board >( new Board( ) );
	_camera = std::shared_ptr< Camera >( new Camera( ) );
	_player = std::shared_ptr< Player >( new Player( 400, -50, _board ) );
}

ScenePlay::~ScenePlay( ) {
}

Scene::SCENE ScenePlay::update( ) {
	_player->update( );
	_board->update( _camera->getY( ) );
	_camera->update( _player->getY( ) );
	return SCENE_PLAY;
}

void ScenePlay::draw( ) const {
	//å„ÇÎÇ©ÇÁèáÇ…ï`âÊ
	drawBack( );
	drawUIBack( );
	_board->draw( _camera->getY( ) );
	_player->draw( _camera->getY( ) );
	drawAir( );
	drawDepth( );
	drawLevel( );
	drawLife( );
	drawScore( );
}

void ScenePlay::drawDepth( ) const {
	char buf[ 7 ];
	if ( _player->getDepth( ) >= 0 ) {
		sprintf_s( buf, "%6d", _player->getDepth( ) );
		DrawBox( 1220 - ( ( int )log10( _player->getDepth( ) + 1 ) + 1 ) * DRAW_NUM_SIZE_X, 77, 1220, 105, RGB( 0, 0, 0 ), TRUE );
		for ( int i = 0; i < 6; i++ ) {
			DrawRectExtendGraph( DRAW_Depth_X + i * DRAW_NUM_SIZE_X, DRAW_Depth_Y, DRAW_Depth_X + ( i + 1 ) * DRAW_NUM_SIZE_X, DRAW_Depth_Y + DRAW_NUM_SIZE_Y, ( buf[ i ] - '0' ) % 5 * NUM_WIDTH, ( buf[ i ] - '0' ) / 5 * NUM_HEIGHT, NUM_WIDTH, NUM_HEIGHT, _img_num, TRUE );
		}
	}
}

void ScenePlay::drawAir( ) const {
	char buf[ 4 ];
	if ( _player->getDepth( ) >= 0 ) {
		sprintf_s( buf, "%3d", _player->getAir( ) );
		for ( int i = 0; i < 3; i++ ) {
			DrawRectExtendGraph( DRAW_AIR_NUM_X + i * DRAW_NUM_SIZE_X, DRAW_AIR_NUM_Y, DRAW_AIR_NUM_X + ( i + 1 ) * DRAW_NUM_SIZE_X, DRAW_AIR_NUM_Y + DRAW_NUM_SIZE_Y, ( buf[ i ] - '0' ) % 5 * NUM_WIDTH, ( buf[ i ] - '0' ) / 5 * NUM_HEIGHT, NUM_WIDTH, NUM_HEIGHT, _img_num, TRUE );
		}
		DrawBox( DRAW_AIR_GAGE_X, DRAW_AIR_GAGE_Y, DRAW_AIR_GAGE_X + ( int )( GAGE_WIDTH * _player->getAir( ) / 100 ), DRAW_AIR_GAGE_Y + GAGE_HEIGHT, GAGE_COLOR, TRUE );
	}
}

void ScenePlay::drawLevel( ) const {
	char buf[ 4 ];
	if ( _player->getDepth( ) >= 0 ) {
		sprintf_s( buf, "%3d", _level );
		DrawBox( 1260 - ( ( int )log10( _level ) + 1 ) * DRAW_NUM_SIZE_X, 530, 1260, 600, RGB( 0, 0, 0 ), TRUE );
		for ( int i = 0; i < 3; i++ ) {
			DrawRectExtendGraph( DRAW_Level_X + i * DRAW_NUM_SIZE_X, DRAW_Level_Y, DRAW_Level_X + ( i + 1 ) * DRAW_NUM_SIZE_X, DRAW_Level_Y + DRAW_NUM_SIZE_Y, ( buf[ i ] - '0' ) % 5 * NUM_WIDTH, ( buf[ i ] - '0' ) / 5 * NUM_HEIGHT, NUM_WIDTH, NUM_HEIGHT, _img_num, TRUE );
		}
	}
}

void ScenePlay::drawScore( ) const {
	char buf[ 7 ];
	if ( _player->getDepth( ) >= 0 ) {
		sprintf_s( buf, "%6d", _player->getScore( ) );
		DrawBox( 1220 - ( ( int )log10( _player->getScore( ) + 1 ) + 1 ) * DRAW_NUM_SIZE_X, 180, 1220, 235, RGB( 0, 0, 0 ), TRUE );
		for ( int i = 0; i < 6; i++ ) {
			DrawRectExtendGraph( DRAW_Score_X + i * DRAW_NUM_SIZE_X, DRAW_Score_Y, DRAW_Score_X + ( i + 1 ) * DRAW_NUM_SIZE_X, DRAW_Score_Y + DRAW_NUM_SIZE_Y, ( buf[ i ] - '0' ) % 5 * NUM_WIDTH, ( buf[ i ] - '0' ) / 5 * NUM_HEIGHT, NUM_WIDTH, NUM_HEIGHT, _img_num, TRUE );
		}
	}
}

void ScenePlay::drawUIBack( ) const {
	DrawGraph( UI_X, 0, _img_ui, FALSE );
}

void ScenePlay::drawLife( ) const {
	char buf[ 20 ];
	if ( _player->getDepth( ) >= 0 ) {
		sprintf_s( buf, "Lives:%d", _player->getLife( ) );
		for ( int i = 0; i < _player->getLife( ); i++ ) {
			DrawBox( 1180, 670, 1260, 720, RGB( 0, 0, 0 ), TRUE );
		}
		for ( int i = 0; i < _player->getLife( ); i++ ) {
			DrawRectExtendGraph( 1222 - i * 37, 670, 1259 - i * 37, 707, 0, 0, 64, 64, _img_life, TRUE );
		}
	}
}

void ScenePlay::drawBack( ) const {
	int y1 = ( ( _camera->getY( ) + 720 ) % 720 ) * -1;
	if ( y1 > 0 || y1 < -720 ) {
		int check = 0;
	}
	int y2 = y1 + 720;
	int y3 = y2 + 720;
	DrawExtendGraph( 0, y1, UI_X, y2, _img_bg, FALSE );
	DrawExtendGraph( 0, y2, UI_X, y3, _img_bg, FALSE );
}
