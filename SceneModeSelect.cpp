#include "SceneModeSelect.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"


SceneModeSelect::SceneModeSelect( ) {
}


SceneModeSelect::~SceneModeSelect( ) {
}


Scene::SCENE SceneModeSelect::update( ) {
	if ( Keyboard::getInstance( )->isPushKey( KEY_INPUT_SPACE ) == TRUE ) {
		return SCENE_PLAY;
	}
	return SCENE_MODE_SELECT;
}

void SceneModeSelect::draw( ) const {
	DrawString( SCREEN_WIDTH, SCREEN_HEIGHT, "ModeSelect", GetColor( 255, 255, 255 ) );
	
	//Please Push
	char *str = "Please Push Space";
	int str_width = GetDrawStringWidth( str, strlen( str ) );
	DrawString( ( SCREEN_WIDTH - str_width ) / 2, 600, str, GetColor( 255, 50, 100 ) );
}