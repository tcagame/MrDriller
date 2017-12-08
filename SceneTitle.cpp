#include "SceneTitle.h"
#include "DxLib.h"

SceneTitle::SceneTitle( ) {
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
	DrawString( 600, 100, "ƒ^ƒCƒgƒ‹‰æ–Ê", GetColor( 255, 255, 255 ) );
	DrawString( 550, 600, "Please Push Space", GetColor( 255, 255, 255 ) );
}