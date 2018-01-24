#include <Windows.h>
#include <memory>
#include "Game.h"
#include "DxLib.h"
#include "define.h"
#include "FpsController.h"
#include "Keyboard.h"
#include "Sound.h"
#include "Graph.h"

const char* TITLE_NAME = "Mr.Driller";

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow ) {
	//ウィンドウモード
#if _DEBUG
	ChangeWindowMode( TRUE );
#endif

	//解像度を指定
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, FPS );

	//アクティブではないときは処理するかどうか
	SetAlwaysRunFlag( TRUE );

	//タイトルを設定
	SetWindowText( TITLE_NAME );

	//DxLib初期化
	if ( DxLib_Init( ) == -1 ) {
		return -1;
	}

	//描画対象を指定
	SetDrawScreen( DX_SCREEN_BACK );
	
	//initialize
	Keyboard::initalize( );
	Sound::initialize( );
	Graph::initialize( );

	{//ゲームループ
		std::shared_ptr< Game >( new Game )->run( );
	}
	Sound::get( )->unLoadAll( );
	Graph::get( )->unLoadAll( );

	//DxLib終了処理
	DxLib_End( );
	return 0;
}