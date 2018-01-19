#include "SceneResult.h"
#include "DxLib.h"
#include "define.h"
#include "Keyboard.h"

SceneResult::SceneResult( ) {
	_img_handle = LoadGraph( "Resource/result.png", TRUE );
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
	
}