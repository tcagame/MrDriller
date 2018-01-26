#include "SceneResult.h"
#include "DxLib.h"
#include "define.h"
#include "Keyboard.h"
#include "Game.h"

const int DRAW_COMMENT_X = 400;
const int DRAW_COMMENT_Y = 400;
const int DRAW_COMMENT_SIZE_X = 600;
const int DRAW_COMMENT_SIZE_Y = 250;

const int DRAW_Depth_X = 650;
const int DRAW_Depth_Y = 155;

const int DRAW_Score_X = 650;
const int DRAW_Score_Y = 285;

const int NUM_WIDTH = 128;
const int NUM_HEIGHT = 128;
const int DRAW_NUM_SIZE_X = 80;
const int DRAW_NUM_SIZE_Y = 80;

const int PLEASH_PUSH_DRAW_Y = 625;
const int PLEASE_PUSH_DRAW_WIDTH = 700;
const int PLEASE_PUSH_DRAW_HEIGHT = 100;


SceneResult::SceneResult( int score, int depth ):
_score ( score ),
_depth ( depth ) {
}

SceneResult::~SceneResult( ) {
}


//--------------Load---------------//
void SceneResult::loadSound( ) {
	//Sound::get( )->load( Sound::SOUND_MENU_CLICK );
}

void SceneResult::loadGraph( ) {
	std::shared_ptr< Graph > graph = Graph::get( );
	graph->load( Graph::GRAPH_NUMBER );
	graph->load( Graph::GRAPH_RESULT_BG );
	graph->load( Graph::GRAPH_RESULT_COMMENT );
	graph->load( Graph::GRAPH_PLEASE_PUSH_SPACE );
}

//-----------Update Draw-----------//
Scene::SCENE SceneResult::update( ) {
	SCENE next = SCENE_RESULT;
	if ( Keyboard::get( )->isPushKey( KEY_INPUT_SPACE ) == TRUE ) {
		//Sound::get( )->play( Sound::SOUND_MENU_CLICK );
		next = SCENE_TITLE;
	}
	return next;
}

void SceneResult::draw( ) const {
	//BG
	Graph::get( )->draw( Graph::GRAPH_RESULT_BG, FALSE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	//Please Push
	//Graph::get( )->draw( Graph::GRAPH_PLEASE_PUSH_SPACE, FALSE, x1, y1, x2, y2 );
	drawScore( );
	drawDepth( );
	drawPleasePush( );
	drawComment( );
}

void SceneResult::drawComment( ) const {
	std::shared_ptr< Graph > graph = Graph::get( );
	int x1 = DRAW_COMMENT_X;
	int y1 = DRAW_COMMENT_Y;
	int x2 = DRAW_COMMENT_X + DRAW_COMMENT_SIZE_X;
	int y2 = DRAW_COMMENT_Y + DRAW_COMMENT_SIZE_Y;
	int tx = 0;
	int ty = 0;
	graph->draw( Graph::GRAPH_RESULT_COMMENT, TRUE, x1, y1, x2, y2, tx, ty, 850, 300 );
}

void SceneResult::drawScore( ) const {
	std::shared_ptr< Graph > graph = Graph::get( );
	char buf[ 7 ];
	sprintf_s( buf, "%6d", _score );
	int x1 = DRAW_Score_X;
	int y1 = DRAW_Score_Y;
	int x2 = DRAW_Score_X + DRAW_NUM_SIZE_X;
	int y2 = DRAW_Score_Y + DRAW_NUM_SIZE_Y;
	int ty = 0;

	for ( int i = 0; i < 6; i++ ) {
		if ( buf[ i ] != ' ' ) {
			int tx = ( buf[ i ] - '0' ) * NUM_WIDTH;
			graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, tx, ty, NUM_WIDTH, NUM_HEIGHT );
		}
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}
}

void SceneResult::drawDepth( ) const {
	std::shared_ptr< Graph > graph = Graph::get( );
	char buf[ 7 ];
	sprintf_s( buf, "%6d", _depth );
	int x1 = DRAW_Depth_X;
	int y1 = DRAW_Depth_Y;
	int x2 = DRAW_Depth_X + DRAW_NUM_SIZE_X;
	int y2 = DRAW_Depth_Y + DRAW_NUM_SIZE_Y;
	int ty = 0;

	for ( int i = 0; i < 6; i++ ) {
		if ( buf[ i ] != ' ' ) {
			int tx = ( buf[ i ] - '0' ) * NUM_WIDTH;
			graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, tx, ty, NUM_WIDTH, NUM_HEIGHT );
		}
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}
}

void SceneResult::drawPleasePush( ) const{
	std::shared_ptr<Graph>graph=Graph::get( );
	int x1 = ( SCREEN_WIDTH - PLEASE_PUSH_DRAW_WIDTH ) / 2;
	int y1 = PLEASH_PUSH_DRAW_Y;
	int x2 = x1 + PLEASE_PUSH_DRAW_WIDTH;
	int y2 = y1 + PLEASE_PUSH_DRAW_HEIGHT;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( ( sin( _count * 0.06 ) + 1 ) * 64 + 156 ) );//“§–¾‰»
	Graph::get( )->draw( Graph::GRAPH_PLEASE_PUSH_SPACE, TRUE, x1, y1, x2, y2 );
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}