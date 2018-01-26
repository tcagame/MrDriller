#include "SceneTitle.h"
#include "DxLib.h"
#include "define.h"
#include "Keyboard.h"

const int PLEASE_PUSH_DRAW_Y = 550;
const int PLEASE_PUSH_DRAW_WIDTH = 700;
const int PLEASE_PUSH_DRAW_HEIGHT = 100;

SceneTitle::SceneTitle( ) :
_count( 0 ),
_next( false ) {
}

SceneTitle::~SceneTitle( ) {
}

//--------------Load---------------//
void SceneTitle::loadSound( ) {
	Sound::get( )->load( Sound::SOUND_MENU_CLICK ); //メニュー決定
}

void SceneTitle::loadGraph( ) {
	std::shared_ptr< Graph > graph = Graph::get( );
	graph->load( Graph::GRAPH_TITLE_BG          );
	graph->load( Graph::GRAPH_PLEASE_PUSH_SPACE );
}

//-----------Update Draw-----------//
Scene::SCENE SceneTitle::update( ) {
	SCENE next = SCENE_TITLE;
	if ( Keyboard::get( )->isPushKey( KEY_INPUT_SPACE ) ) {
		Sound::get( )->play( Sound::SOUND_MENU_CLICK );
		_next = true;
	}
	if ( _next && !Sound::get( )->isPlaying( Sound::SOUND_MENU_CLICK ) ) {
		next = SCENE_MODE_SELECT;
	}
	_count++;
	return next;
}

void SceneTitle::draw( ) const {
	drawBg( );
	drawPleasePush( );
	//DrawString( 10, 700, "製作　山田チーム", GetColor( 255, 0, 13 ) );
}

void SceneTitle::drawBg( ) const {
	Graph::get( )->draw( Graph::GRAPH_TITLE_BG, FALSE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
}

void SceneTitle::drawPleasePush( ) const {
	std::shared_ptr< Graph > graph = Graph::get( );
	int x1 = ( SCREEN_WIDTH - PLEASE_PUSH_DRAW_WIDTH ) / 2;
	int y1 = PLEASE_PUSH_DRAW_Y;
	int x2 = x1 + PLEASE_PUSH_DRAW_WIDTH;
	int y2 = y1 + PLEASE_PUSH_DRAW_HEIGHT;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( ( sin( _count * 0.06 ) + 1 ) * 64 + 156 ) );//透明化
	Graph::get( )->draw( Graph::GRAPH_PLEASE_PUSH_SPACE, TRUE, x1, y1, x2, y2 );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}