#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


/*------------------定数宣言-------------------*/
//定数は大文字で宣言する

/*-------------グローバル変数宣言--------------*/
//staticを付けることによって外部からの変数へのアクセスを完全に遮断
//変数は「g_」を付けて宣言をする

/*------------------関数定義-------------------*/

Game::Game( ) :
_now_scene( Scene::SCENE_PLAY ) {
	//シーン初期化
	changeScene( _now_scene );
}

Game::~Game( ) {
}

void Game::run( ) {
	//ループ
	while ( isLoop( ) ) {
		//更新
		Scene::SCENE next = _scene->update( );
		//描画
		_scene->draw( );
		//描画反映
		ScreenFlip( );
		ClearDrawScreen( );

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
	if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
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
	case Scene::SCENE_PLAY:
		_scene = std::shared_ptr< Scene >( new ScenePlay );
		break;	
	case Scene::SCENE_RESULT:
		_scene = std::shared_ptr< Scene >( new SceneResult );
		break;	
	}

	_now_scene = scene;
}