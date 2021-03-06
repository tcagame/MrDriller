#include "DxLib.h"
#include "Game.h"
#include "Keyboard.h"
#include "SceneTitle.h"
#include "SceneModeSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"
#include "FpsController.h"
#include "Sound.h"
#include "Graph.h"


/*------------------定数宣言-------------------*/
//定数は大文字で宣言する

/*-------------グローバル変数宣言--------------*/
//staticを付けることによって外部からの変数へのアクセスを完全に遮断
//変数は「g_」を付けて宣言をする

/*------------------関数定義-------------------*/

Game::Game( ) :
_now_scene( Scene::SCENE_TITLE ),
_mode( MODE_NORMAL ) {
	//シーン初期化
	changeScene( _now_scene );
	_fps_ctrl = std::shared_ptr< FpsController >( new FpsController );
}

Game::~Game( ) {
}

void Game::run( ) {
	//ループ
	while ( isLoop( ) ) {
		//更新
		Keyboard::get( )->update( );
		Scene::SCENE next = _scene->update( );
		//FPSチェック
		_fps_ctrl->update( );
		if ( !_fps_ctrl->isOverFps( ) ) {
			//描画
			_scene->draw( );
			#if _DEBUG
			DrawFormatString( 1280 - 100, 0, GetColor( 255, 255, 255 ), "FPS:%.2f", _fps_ctrl->getFps( ) );
			#endif
			//描画反映
			ScreenFlip( );
			ClearDrawScreen( );
		}

		//シーン遷移
		if ( next != _now_scene ) {
			changeScene( next );
		}
	}


}

bool Game::isLoop( ) const {
	bool result = true;
	//ウィンドウメッセージ処理
	if ( ProcessMessage( ) != 0 ) {
		result = false;
	}

	//Escで終了
	if ( Keyboard::get( )->isHoldKey( KEY_INPUT_ESCAPE ) != 0 ) {
		result = false;
	}

	return result;
}

void Game::changeScene( Scene::SCENE scene ) {
	//シーン終了処理
	_scene.reset( );
	Sound::get( )->unLoadAll( );
	Graph::get( )->unLoadAll( );

	switch ( scene ) {
	case Scene::SCENE_TITLE:
		_scene = std::shared_ptr< Scene >( new SceneTitle );
		break;
	case Scene::SCENE_MODE_SELECT:
		_scene = std::shared_ptr< Scene >( new SceneModeSelect( &_mode ) );
		break;
	case Scene::SCENE_PLAY:
		_scene = std::shared_ptr< Scene >( new ScenePlay( _mode, &_score, &_depth, &_level ) );
		break;	
	case Scene::SCENE_RESULT:
		_scene = std::shared_ptr< Scene >( new SceneResult( _score, _depth, _level ) );
		break;	
	}
	_scene->loadGraph( );
	_scene->loadSound( );
	_now_scene = scene;
}