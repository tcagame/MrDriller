#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


/*------------------定数宣言-------------------*/
//定数は大文字で宣言する
const char* TITLE_NAME = "Mr.Driller";

/*-------------グローバル変数宣言--------------*/
//staticを付けることによって外部からの変数へのアクセスを完全に遮断
//変数は「g_」を付けて宣言をする

/*------------------関数定義-------------------*/

Game::Game( ) :
_now_scene( Scene::SCENE_PLAY ) {
	bool result = true;
	//ウィンドウモード
	ChangeWindowMode( TRUE );

	//解像度を指定
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32 );

	//アクティブではないときは処理しない
	SetAlwaysRunFlag( FALSE );

	//タイトルを設定
	SetWindowText( TITLE_NAME );

	//DxLib初期化
	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	//描画対象を指定
	SetDrawScreen( DX_SCREEN_BACK );

	//シーン初期化
	changeScene( _now_scene );
}

Game::~Game( ) {
	//DxLib終了処理
	DxLib_End( );
}

void Game::run( ) {
	//ループ
	while ( isLoop( ) ) {
		//更新
		Scene::SCENE next = update( );
		//描画
		draw( );

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

Scene::SCENE Game::update( ) {
	return _scene->update( );
}

void Game::draw( ) {
	_scene->draw( );
	ScreenFlip();
	ClearDrawScreen();
}

void Game::changeScene( Scene::SCENE scene ) {
	//シーン終了処理
	//_scene.reset( new Scene );
	_now_scene = scene;
}