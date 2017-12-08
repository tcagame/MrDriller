#include "SceneTitle.h"
#include "DxLib.h"
#include "define.h"

SceneTitle::SceneTitle( ) {
	_img_handle = LoadGraph( "Resource/title.jpg", TRUE );
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
	DrawExtendGraph( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _img_handle, FALSE );
	DrawString( 550, 600, "Please Push Space", GetColor( 255, 255, 255 ) );
}