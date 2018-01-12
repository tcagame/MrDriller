#include "SceneTitle.h"
#include "DxLib.h"
#include "define.h"
#include "Keyboard.h"

SceneTitle::SceneTitle( ) {
	_img_handle = LoadGraph( "Resource/title.png", TRUE );
}

SceneTitle::~SceneTitle( ) {
}

Scene::SCENE SceneTitle::update( ) {
	SCENE next = SCENE_TITLE;
	if ( Keyboard::getInstance( )->isPushKey( KEY_INPUT_SPACE ) == TRUE ) {
		next = SCENE_MODE_SELECT;
	}
	return next;
}

void SceneTitle::draw( ) const {
	//BG
	DrawExtendGraph( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _img_handle, FALSE );
	//Please Push
	char *str = "Please Push Space";
	int str_width = GetDrawStringWidth( str, strlen( str ) );
	DrawString( ( SCREEN_WIDTH - str_width ) / 2, 600, str, GetColor( 255, 50, 100 ) );
	//
	DrawString( 10, 700, "製作　山田チーム", GetColor( 255, 0, 13 ) );
}