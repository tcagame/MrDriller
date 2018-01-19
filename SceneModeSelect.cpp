#include "SceneModeSelect.h"
#include "define.h"
#include "Keyboard.h"
#include "DxLib.h"

const int MODE_LOGO_DRAW_WIDTH = 800;
const int MODE_LOGO_DRAW_HEIGHT = 200;

const int PLEASE_PUSH_DRAW_WIDTH = 700;
const int PLEASE_PUSH_DRAW_HEIGHT = 100;

const int MODE_SPRITE_ARROW_SIZE = 128;

const int MODE_SPRITE_WIDTH  = 512;
const int MODE_SPRITE_HEIGHT = 128;

SceneModeSelect::SceneModeSelect( Game::MODE* mode ) :
_select( mode ),
_count( 0 ) {
	_image_mode = LoadGraph( "Resource/Mode.png" );
	_se[ 13 ] = LoadSoundMem( "Resource/Sound/effect/effect14.mp3" ); //メニュー選択
	_se[ 14 ] = LoadSoundMem( "Resource/Sound/effect/effect15.mp3" ); //メニュー決定
}


SceneModeSelect::~SceneModeSelect( ) {
	DeleteGraph( _image_mode );
}


Scene::SCENE SceneModeSelect::update( ) {
	_count++;

	std::shared_ptr< Keyboard > key = Keyboard::getInstance( );
	//選択
	if ( key->isPushKey( KEY_INPUT_UP ) ) {
		//上
		if ( *_select != 0 ) {
			*_select = ( Game::MODE )( *_select - 1 );
			PlaySoundMem( _se[ 13 ], DX_PLAYTYPE_BACK );
		}
	}
	
	if ( key->isPushKey( KEY_INPUT_DOWN ) ) {
		//下
		if ( *_select != ( Game::MODE )( Game::MAX_MODE - 1 ) ) {
			*_select = ( Game::MODE )( *_select + 1 );
			PlaySoundMem( _se[ 13 ], DX_PLAYTYPE_BACK );
		}
	}

	//シーン遷移
	if ( key->isPushKey( KEY_INPUT_SPACE ) ) {
		PlaySoundMem( _se[ 14 ], DX_PLAYTYPE_BACK );
		return SCENE_PLAY;
	}
	return SCENE_MODE_SELECT;
}

void SceneModeSelect::draw( ) const {
	{//ModeSelect
		int x = ( SCREEN_WIDTH - MODE_LOGO_DRAW_WIDTH ) / 2;
		int y = 50;
		int x2 = x + MODE_LOGO_DRAW_WIDTH;
		int y2 = y + MODE_LOGO_DRAW_HEIGHT;
		DrawRectExtendGraph( x, y, x2, y2, MODE_SPRITE_WIDTH, 128, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT, _image_mode, TRUE );
	}
	
	{//Please Push
		int x = ( SCREEN_WIDTH - PLEASE_PUSH_DRAW_WIDTH ) / 2;
		int y = 600;
		int x2 = x + PLEASE_PUSH_DRAW_WIDTH;
		int y2 = y + PLEASE_PUSH_DRAW_HEIGHT;
		SetDrawBlendMode( DX_BLENDMODE_ADD, ( int )( ( sin( _count * 0.03 ) + 1 ) * 64 + 64 ) );
		DrawRectExtendGraph( x, y, x2, y2, MODE_SPRITE_WIDTH, 256, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT, _image_mode, TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
	}
	{//Arrow
		int x = SCREEN_WIDTH  / 2 - MODE_SPRITE_WIDTH / 2 - MODE_SPRITE_ARROW_SIZE / 2;
		x += ( int )( ( sin( _count * 0.06 ) - 1 ) * 6 );
		int y = SCREEN_HEIGHT / 2 - MODE_SPRITE_HEIGHT;
		y += *_select * MODE_SPRITE_HEIGHT;
		DrawRectGraph( x, y, MODE_SPRITE_WIDTH, 0, MODE_SPRITE_ARROW_SIZE, MODE_SPRITE_ARROW_SIZE, _image_mode, TRUE, FALSE );
	}

	{//Mode
		//ModeNormal
		int x = SCREEN_WIDTH  / 2 - MODE_SPRITE_WIDTH / 2;
		int y = SCREEN_HEIGHT / 2 - MODE_SPRITE_HEIGHT;
		DrawRectGraph( x, y, 0,   0, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT, _image_mode, TRUE, FALSE );
		//ModeBlind
		y += MODE_SPRITE_HEIGHT;
		DrawRectGraph( x, y, 0, 128, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT, _image_mode, TRUE, FALSE );
	}
}