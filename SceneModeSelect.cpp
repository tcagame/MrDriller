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
}


SceneModeSelect::~SceneModeSelect( ) {
}

//--------------Load---------------//
void SceneModeSelect::loadSound( ) {
	std::shared_ptr< Sound > sound = Sound::get( );
	sound->load( Sound::SOUND_MENU_SELECT ); //メニュー選択
	sound->load( Sound::SOUND_MENU_CLICK  ); //メニュー決定
}

void SceneModeSelect::loadGraph( ) {
	std::shared_ptr< Graph > graph = Graph::get( );
	graph->load( Graph::GRAPH_MODESELECT_TEXT   );
	graph->load( Graph::GRAPH_PLEASE_PUSH_SPACE );
}

//-----------Update Draw-----------//
Scene::SCENE SceneModeSelect::update( ) {
	_count++;

	std::shared_ptr< Keyboard > key = Keyboard::get( );
	//選択
	if ( key->isPushKey( KEY_INPUT_UP ) ) {
		//上
		if ( *_select != 0 ) {
			*_select = ( Game::MODE )( *_select - 1 );
			Sound::get( )->play( Sound::SOUND_MENU_SELECT );
		}
	}
	
	if ( key->isPushKey( KEY_INPUT_DOWN ) ) {
		//下
		if ( *_select != ( Game::MODE )( Game::MAX_MODE - 1 ) ) {
			*_select = ( Game::MODE )( *_select + 1 );
			Sound::get( )->play( Sound::SOUND_MENU_SELECT );
		}
	}

	//シーン遷移
	if ( key->isPushKey( KEY_INPUT_SPACE ) ) {
		Sound::get( )->play( Sound::SOUND_MENU_CLICK );
		return SCENE_PLAY;
	}
	return SCENE_MODE_SELECT;
}

void SceneModeSelect::draw( ) const {
	std::shared_ptr< Graph > graph = Graph::get( );
	{//ModeSelect
		int x1 = ( SCREEN_WIDTH - MODE_LOGO_DRAW_WIDTH ) / 2;
		int y1 = 50;
		int x2 = x1 + MODE_LOGO_DRAW_WIDTH;
		int y2 = y1 + MODE_LOGO_DRAW_HEIGHT;
		graph->draw( Graph::GRAPH_MODESELECT_TEXT, TRUE, x1, y1, x2, y2, MODE_SPRITE_WIDTH, 128, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT );
	}
	
	{//Please Push
		int x1 = ( SCREEN_WIDTH - PLEASE_PUSH_DRAW_WIDTH ) / 2;
		int y1 = 550;
		int x2 = x1 + PLEASE_PUSH_DRAW_WIDTH;
		int y2 = y1 + PLEASE_PUSH_DRAW_HEIGHT;
		SetDrawBlendMode( DX_BLENDMODE_ADD, ( int )( ( sin( _count * 0.03 ) + 1 ) * 64 + 64 ) );//明るくする
		graph->draw( Graph::GRAPH_PLEASE_PUSH_SPACE, TRUE, x1, y1, x2, y2 );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
	}
	{//Arrow
		int x1 = ( SCREEN_WIDTH - MODE_SPRITE_WIDTH - MODE_SPRITE_ARROW_SIZE ) / 2 + ( int )( ( sin( _count * 0.06 ) - 1 ) * 6 );
		int y1 = SCREEN_HEIGHT / 2 - MODE_SPRITE_HEIGHT + (*_select) * MODE_SPRITE_HEIGHT;
		int x2 = x1 + MODE_SPRITE_ARROW_SIZE;
		int y2 = y1 + MODE_SPRITE_ARROW_SIZE;
		graph->draw( Graph::GRAPH_MODESELECT_TEXT, TRUE, x1, y1, x2, y2, MODE_SPRITE_WIDTH, 0, MODE_SPRITE_ARROW_SIZE, MODE_SPRITE_ARROW_SIZE );
	}

	{//Mode
		//ModeNormal
		int x1 = SCREEN_WIDTH  / 2 - MODE_SPRITE_WIDTH / 2;
		int y1 = SCREEN_HEIGHT / 2 - MODE_SPRITE_HEIGHT;
		int x2 = x1 + MODE_SPRITE_WIDTH;
		int y2 = y1 + MODE_SPRITE_HEIGHT;
		graph->draw( Graph::GRAPH_MODESELECT_TEXT, TRUE, x1, y1, x2, y2, 0,   0, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT );
		//ModeBlind
		y1 += MODE_SPRITE_HEIGHT;
		y2 += MODE_SPRITE_HEIGHT;
		graph->draw( Graph::GRAPH_MODESELECT_TEXT, TRUE, x1, y1, x2, y2, 0, 128, MODE_SPRITE_WIDTH, MODE_SPRITE_HEIGHT );
	}
}