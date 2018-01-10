#include "SceneTitle.h"
#include "DxLib.h"
#include "define.h"

SceneTitle::SceneTitle( ) {
	_img_handle = LoadGraph( "Resource/title.png", TRUE );
}

SceneTitle::~SceneTitle( ) {
}

Scene::SCENE SceneTitle::update( ) {
	SCENE next = SCENE_TITLE;
	if ( CheckHitKey( KEY_INPUT_SPACE ) == TRUE ) {
		next = SCENE_PLAY;
	}
	return next;
}

void SceneTitle::draw( ) const {
	char *str = "Please Push Space";
	int str_width = GetDrawStringWidth( str, strlen( str ) );
	DrawExtendGraph( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _img_handle, FALSE );
	DrawString( ( SCREEN_WIDTH - str_width ) / 2, 600, str, GetColor( 255, 50, 100 ) );
	DrawString( 10, 700, "製作　山田チーム", GetColor( 255, 0, 13 ) );
}