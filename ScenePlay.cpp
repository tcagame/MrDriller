#include "ScenePlay.h"
#include "Player.h"
#include "Board.h"
#include "dxlib.h"
#include "Keyboard.h"
#include <math.h>
#include <memory>
#include "Sound.h"

//定数宣言
const int UI_X = 900;
const int DRAW_AIR_GAGE_X = 917;
const int DRAW_AIR_GAGE_Y = 362;

const int DRAW_AIR_NUM_X = 1105;
const int DRAW_AIR_NUM_Y = 440;

const int GAGE_WIDTH = 340;
const int GAGE_HEIGHT = 51;

const int DRAW_Depth_X = 1002;
const int DRAW_Depth_Y = 77;

const int DRAW_Level_X = 1182;
const int DRAW_Level_Y = 560;

const int DRAW_Life_X = 1182;
const int DRAW_Life_Y = 670;

const int DRAW_Score_X = 1001;
const int DRAW_Score_Y = 191;

const int NUM_WIDTH  = 128;
const int NUM_HEIGHT = 128;
const int DRAW_NUM_SIZE_X = 37;
const int DRAW_NUM_SIZE_Y = 37;

const int GAGE_COLOR = GetColor( 255, 0, 0 );

const int MAX_BRIGHTNESS = 100;

const int SPRITE_SIZE = 64;

ScenePlay::ScenePlay( Game::MODE mode, int *score, int *depth, int *level ) :
_mode( mode ),
_score( score ),
_depth( depth ),
_level( level ),
_brightness( MAX_BRIGHTNESS ) {
	_board  = std::shared_ptr< Board  >( new Board( ) );
	_board->loadBlock( );
	_camera = std::shared_ptr< Camera >( new Camera( ) );
	_player = std::shared_ptr< Player >( new Player( 400, -50, _board ) );
}

ScenePlay::~ScenePlay( ) {
}

//--------------Load---------------//
void ScenePlay::loadSound( ) {
	std::shared_ptr< Sound > sound = Sound::get( );
	sound->load( Sound::SOUND_BLOCK_CRUSH  		   );//ブロック破壊
	sound->load( Sound::SOUND_BLOCK_FALL_CRUSH     );//ブロック落ちて破壊
	sound->load( Sound::SOUND_AIR_CAPSULE  		   );//エア
	sound->load( Sound::SOUND_SOLID_REDUCE  	   );//お邪魔ブロックの削り
	sound->load( Sound::SOUND_SOLID_CRUSH  		   );//お邪魔ブロックの破壊
	sound->load( Sound::SOUND_LEVEL_CRUSH  		   );//岩盤破壊
	sound->load( Sound::SOUND_AIR_LESS_THAN_THRITY );//air < 30
	sound->load( Sound::SOUND_AIR_LESS_THAN_TEN    );//air < 10
	sound->load( Sound::SOUND_DEAD_AIR  		   );//酸欠死亡
	sound->load( Sound::SOUND_DEAD_CRUSH  		   );//つぶれて死亡
	sound->load( Sound::SOUND_ANGEL  			   );//天使
	sound->load( Sound::SOUND_RESURRECTION  	   );//復活
	sound->load( Sound::SOUND_FALL  			   );//落下
	sound->load( Sound::SOUND_MENU_SELECT  		   );//メニュー選択
	sound->load( Sound::SOUND_MENU_CLICK  		   );//メニュー決定
	sound->load( Sound::SOUND_BGM_AIRMAN           );//BGM
	sound->play( Sound::SOUND_BGM_AIRMAN, true, true, 128 );
}

void ScenePlay::loadGraph( ) {
	std::shared_ptr< Graph > graph = Graph::get( );
	graph->load( Graph::GRAPH_NUMBER         );
	graph->load( Graph::GRAPH_PLAY_BG        );
	graph->load( Graph::GRAPH_PLAY_UI        );
	graph->load( Graph::GRAPH_PLAY_BLIND     );
	graph->load( Graph::GRAPH_PLAY_BLOCK     );
	graph->load( Graph::GRAPH_PLAY_CHARACTER );
	graph->load( Graph::GRAPH_PLAY_AIRGAUGE  );
}

//-----------Update Draw-----------//
Scene::SCENE ScenePlay::update( ) {
	_player->update( );
	_board->update( );
	_camera->update( _player->getY( ) );
	_brightness = 25 + ( int )( _player->getAir( ) * 0.75 );

	SCENE next = SCENE_PLAY;
	if ( _player->isFinished( ) ||
		 _board->isFinished( ) ) {
		//if ( _player->getAct( ) == Player::ACT_GOAL ) {
			*_score = _player->getScore( );
			*_depth = _player->getDepth( );
		//}
		next = SCENE_RESULT;
	}
	if ( _player->isGoal( ) ) {
		Sound::get( )->stop( Sound::SOUND_BGM_AIRMAN );
	}
	if ( Keyboard::get( )->isPushKey( KEY_INPUT_Q ) ) {
		next = SCENE_MODE_SELECT;
	}
	return next;
}

void ScenePlay::draw( ) const {
	//後ろから順に描画
	//BG
	drawBg( );
	//Play
	_board->draw( _camera->getY( ) );
	_player->draw( _camera->getY( ) );
	drawBlind( );
	//UI
	drawUIBg( );
	drawAir( );
	drawAirGauge( );
	drawDepth( );
	drawLevel( );
	drawLife( );
	drawScore( );
}

void ScenePlay::drawDepth( ) const {
	if ( _player->getDepth( ) < 0 ) {
		return;
	}
	std::shared_ptr< Graph > graph = Graph::get( );
	char buf[ 7 ];
	sprintf_s( buf, "%6d", _player->getDepth( ) );

	int x1 = DRAW_Depth_X;
	int y1 = DRAW_Depth_Y;
	int x2 = x1 + DRAW_NUM_SIZE_X;
	int y2 = y1 + DRAW_NUM_SIZE_Y;
	int ty = 0;

	for ( int i = 0; i < 6; i++ ) {
		int tx = ( buf[ i ] - '0' ) * NUM_WIDTH;
		if ( buf[ i ] == ' ' ) {
			tx = 10 * NUM_WIDTH;//「・」
		}
		graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, tx, ty, NUM_WIDTH, NUM_HEIGHT );
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}	
}

void ScenePlay::drawAir( ) const {
	//数字
	if ( _player->getDepth( ) < 0 ) {
		return;
	}
	std::shared_ptr< Graph > graph = Graph::get( );
	char buf[ 4 ];
	sprintf_s( buf, "%3d", _player->getAir( ) );

	int x1 = DRAW_AIR_NUM_X;
	int y1 = DRAW_AIR_NUM_Y;
	int x2 = x1 + DRAW_NUM_SIZE_X;
	int y2 = y1 + DRAW_NUM_SIZE_Y;
	int ty = 0;

	for ( int i = 0; i < 3; i++ ) {
		int tx = ( buf[ i ] - '0' ) * NUM_WIDTH;
		if ( buf[ i ] == ' ' ) {
			tx = 10 * NUM_WIDTH;//「・」
		}
		graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, tx, ty, NUM_WIDTH, NUM_HEIGHT );
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}
}

void ScenePlay::drawAirGauge( ) const {
	//ゲージ
	std::shared_ptr< Graph > graph = Graph::get( );
	if ( _player->getDepth( ) < 0 ) {
		{//cover描画
			int x1 = DRAW_AIR_GAGE_X;
			int y1 = DRAW_AIR_GAGE_Y;
			int x2 = x1 + GAGE_WIDTH;
			int y2 = y1 + GAGE_HEIGHT;
			graph->draw( Graph::GRAPH_PLAY_AIRGAUGE, TRUE,x1, y1, x2, y2, 0, 0, 256, 64 );
		}
		return;
	}
	{//gauge描画
		int width = ( int )( GAGE_WIDTH * _player->getAir( ) / 100 );
		int x1 = DRAW_AIR_GAGE_X;
		int y1 = DRAW_AIR_GAGE_Y;
		int x2 = x1 + width;
		int y2 = y1 + GAGE_HEIGHT;
		graph->draw( Graph::GRAPH_PLAY_AIRGAUGE, TRUE, x1, y1, x2, y2, 0, 64, 256, 64 );
	}
	{//cover描画
		int x1 = DRAW_AIR_GAGE_X;
		int y1 = DRAW_AIR_GAGE_Y;
		int x2 = x1 + GAGE_WIDTH;
		int y2 = y1 + GAGE_HEIGHT;
		graph->draw( Graph::GRAPH_PLAY_AIRGAUGE, TRUE,x1, y1, x2, y2, 0, 0, 256, 64 );
	}
}


void ScenePlay::drawLevel( ) const {
	if ( _player->getDepth( ) < 0 ) {
		return;
	}
	std::shared_ptr< Graph > graph = Graph::get( );
	char buf[ 3 ];
	sprintf_s( buf, "%2d", _board->getLevel( ) + 1 );
	
	int x1 = DRAW_Level_X;
	int y1 = DRAW_Level_Y;
	int x2 = x1 + DRAW_NUM_SIZE_X;
	int y2 = y1 + DRAW_NUM_SIZE_Y;
	int ty = 0;

	for ( int i = 0; i < 2; i++ ) {
		int tx = ( buf[ i ] - '0' ) * NUM_WIDTH;
		if ( buf[ i ] == ' ' ) {
			tx = 10 * NUM_WIDTH;//「・」
		}
		graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, tx, ty, NUM_WIDTH, NUM_HEIGHT );
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}
}

void ScenePlay::drawScore( ) const {
	if ( _player->getDepth( ) < 0 ) {
		return;
	}
	std::shared_ptr< Graph > graph = Graph::get( );
	char buf[ 7 ];
	sprintf_s( buf, "%6d", _player->getScore( ) );
	
	int x1 = DRAW_Score_X;
	int y1 = DRAW_Score_Y;
	int x2 = x1 + DRAW_NUM_SIZE_X;
	int y2 = y1 + DRAW_NUM_SIZE_Y;
	int ty = 0;

	for ( int i = 0; i < 6; i++ ) {
		int tx = ( buf[ i ] - '0' ) * NUM_WIDTH;
		if ( buf[ i ] == ' ' ) {
			tx = 10 * NUM_WIDTH;//「・」
		}
		graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, tx, ty, NUM_WIDTH, NUM_HEIGHT );
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}
}

void ScenePlay::drawUIBg( ) const {
	int x1 = UI_X;
	int y1 = 0;
	int x2 = SCREEN_WIDTH;
	int y2 = SCREEN_HEIGHT;
	Graph::get( )->draw( Graph::GRAPH_PLAY_UI, FALSE, x1, y1, x2, y2 );
}

void ScenePlay::drawLife( ) const {
	if ( _player->getDepth( ) < 0 ) {
		return;
	}
	std::shared_ptr< Graph > graph = Graph::get( );
	int life = _player->getLife( );

	int x1 = DRAW_Life_X;
	int y1 = DRAW_Life_Y;
	int x2 = x1 + DRAW_NUM_SIZE_X;
	int y2 = y1 + DRAW_NUM_SIZE_Y;
	for ( int i = 0; i < PLAYER_MAX_LIFE; i++ ) {
		int check_life = PLAYER_MAX_LIFE - i - 1;
		if ( life > check_life ) {
			//顔描画
			graph->draw( Graph::GRAPH_PLAY_CHARACTER, TRUE, x1, y1, x2, y2, 0, 0, 64, 64 );
		} else {
			//点描画
			graph->draw( Graph::GRAPH_NUMBER, TRUE, x1, y1, x2, y2, NUM_WIDTH * 10, 0, NUM_WIDTH, NUM_HEIGHT );
		}
		x1 += DRAW_NUM_SIZE_X;
		x2 += DRAW_NUM_SIZE_X;
	}
	
}

void ScenePlay::drawBg( ) const {
	int y1 = ( ( _camera->getY( ) + SCREEN_HEIGHT ) % SCREEN_HEIGHT ) * -1;
	int y2 = y1 + SCREEN_HEIGHT;
	int y3 = y2 + SCREEN_HEIGHT;

	std::shared_ptr< Graph > graph = Graph::get( );
	graph->draw( Graph::GRAPH_PLAY_BG, FALSE, 0, y1, UI_X, y2 );
	graph->draw( Graph::GRAPH_PLAY_BG, FALSE, 0, y2, UI_X, y3 );
}

void ScenePlay::drawBlind( ) const {
	if ( _mode != Game::MODE_BLIND ) {
		return;
	}

	int width  = ( int )( UI_X          * _brightness * 0.08 );
	int height = ( int )( SCREEN_HEIGHT * _brightness * 0.08 );

	int base_x = _player->getX( ) + SPRITE_SIZE / 2;
	int base_y = _player->getY( ) - _camera->getY( );//SCREEN_HEIGHT / 2;

	int x1 = base_x - width  / 2;
	int y1 = base_y - height / 2;
	int x2 = base_x + width  / 2;
	int y2 = base_y + height / 2;
	Graph::get( )->draw( Graph::GRAPH_PLAY_BLIND, TRUE, x1, y1, x2, y2 );
}

int ScenePlay::getScore( ) {
	return _player->getScore( );
}

int ScenePlay::getDepth( ) {
	return _player->getDepth( );
}

int ScenePlay::getLevel( ) {
	return _board->getLevel( );
}