#include "SceneResult.h"
#include "DxLib.h"
#include "define.h"
#include "Keyboard.h"
#include "Game.h"

const int DRAW_Depth_X = 650;
const int DRAW_Depth_Y = 155;

const int DRAW_Score_X = 650;
const int DRAW_Score_Y = 285;

const int NUM_WIDTH = 128;
const int NUM_HEIGHT = 128;
const int DRAW_NUM_SIZE_X = 80;
const int DRAW_NUM_SIZE_Y = 80;


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
	//graph->load( Graph::GRAPH_PLEASE_PUSH_SPACE );
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