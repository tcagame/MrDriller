#include "SceneResult.h"
#include "DxLib.h"
#include "define.h"
#include "Keyboard.h"
#include "Game.h"

const int DRAW_Depth_X = 650;
const int DRAW_Depth_Y = 155;

const int DRAW_Score_X = 650;
const int DRAW_Score_Y = 285;

const int NUM_WIDTH = 310;
const int NUM_HEIGHT = 310;
const int DRAW_NUM_SIZE_X = 80;
const int DRAW_NUM_SIZE_Y = 80;


SceneResult::SceneResult( int score, int depth ):
_score ( score ),
_depth ( depth ) {
	_img_handle = LoadGraph( "Resource/result.png", TRUE );
	_img_num = LoadGraph( "Resource/DrillerNumber.png" );

	//_se[ 14 ] = LoadSoundMem( "Resource/Sound/effect/effect15.mp3" );
}

SceneResult::~SceneResult( ) {
}

Scene::SCENE SceneResult::update( ) {
	SCENE next = SCENE_RESULT;
	if ( Keyboard::getInstance( )->isPushKey( KEY_INPUT_SPACE ) == TRUE ) {
		//PlaySoundMem( _se[ 14 ], DX_PLAYTYPE_BACK );
		next = SCENE_TITLE;
	}
	return next;
}

void SceneResult::draw( ) const {
	//BG
	DrawExtendGraph( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _img_handle, FALSE );
	//Please Push
	//char *str = "Please Push Space";
	//int str_width = GetDrawStringWidth( str, strlen( str ) );
	//DrawString( ( SCREEN_WIDTH - str_width ) / 2, 600, str, GetColor( 255, 50, 100 ) );
	//
	drawScore( );
	drawDepth( );
}

void SceneResult::drawScore( ) const {
	char buf[ 7 ];
	sprintf_s( buf, "%6d", _score );
	for ( int i = 0; i < 6; i++ ) {
		DrawRectExtendGraph( DRAW_Score_X + i * DRAW_NUM_SIZE_X, DRAW_Score_Y, DRAW_Score_X + ( i + 1 ) * DRAW_NUM_SIZE_X, DRAW_Score_Y + DRAW_NUM_SIZE_Y, ( buf[ i ] - '0' ) % 5 * NUM_WIDTH, ( buf[ i ] - '0' ) / 5 * NUM_HEIGHT, NUM_WIDTH, NUM_HEIGHT, _img_num, TRUE );	
	}
}

void SceneResult::drawDepth( ) const {
	char buf[ 7 ];
	sprintf_s( buf, "%6d", _depth );
	for ( int i = 0; i < 6; i++ ) {
		DrawRectExtendGraph( DRAW_Depth_X + i * DRAW_NUM_SIZE_X, DRAW_Depth_Y, DRAW_Depth_X + ( i + 1 ) * DRAW_NUM_SIZE_X, DRAW_Depth_Y + DRAW_NUM_SIZE_Y, ( buf[ i ] - '0' ) % 5 * NUM_WIDTH, ( buf[ i ] - '0' ) / 5 * NUM_HEIGHT, NUM_WIDTH, NUM_HEIGHT, _img_num, TRUE );
	}
}