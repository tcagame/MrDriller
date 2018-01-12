#include "DxLib.h"
#include "Game.h"
#include "Keyboard.h"
#include "SceneTitle.h"
#include "SceneModeSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"
#include "FpsController.h"


/*------------------定数宣言-------------------*/
//定数は大文字で宣言する

/*-------------グローバル変数宣言--------------*/
//staticを付けることによって外部からの変数へのアクセスを完全に遮断
//変数は「g_」を付けて宣言をする

/*------------------関数定義-------------------*/

Game::Game( ) :
_now_scene( Scene::SCENE_TITLE ) {
	//シーン初期化
	changeScene( _now_scene );
	_fps_ctrl = std::shared_ptr< FpsController >( new FpsController );
	Keyboard::init( );
	
}

Game::~Game( ) {
}

void Game::run( ) {
	//ループ
	while ( isLoop( ) ) {
		//更新
		Keyboard::getInstance( )->update( );
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
	if ( Keyboard::getInstance( )->isHoldKey( KEY_INPUT_ESCAPE ) != 0 ) {
		result = false;
	}

	return result;
}

void Game::changeScene( Scene::SCENE scene ) {
	//シーン終了処理
	_scene.reset( );
	switch ( scene ) {
	case Scene::SCENE_TITLE:
		_scene = std::shared_ptr< Scene >( new SceneTitle );
		break;
	case Scene::SCENE_MODE_SELECT:
		_scene = std::shared_ptr< Scene >( new SceneModeSelect );
		break;
	case Scene::SCENE_PLAY:
		_scene = std::shared_ptr< Scene >( new ScenePlay );
		break;	
	case Scene::SCENE_RESULT:
		_scene = std::shared_ptr< Scene >( new SceneResult );
		break;	
	}

	_now_scene = scene;
}