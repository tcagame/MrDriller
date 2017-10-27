#include "DxLib.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


/*------------プロトタイプ関数宣言-------------*/
bool initialize( );				  //初期化
bool isLoop( );					  //ループチェック
void update( );					  //更新
void draw( );					  //描画
void finalize( );				  //終了処理
void changeScene( SCENE scene );  //シーン遷移

/*------------------定数宣言-------------------*/
//定数は大文字で宣言する
const char* TITLE_NAME = "Mr.Driller";

/*-------------グローバル変数宣言--------------*/
//staticを付けることによって外部からの変数へのアクセスを完全に遮断
//変数は「g_」を付けて宣言をする
static SCENE g_scene = SCENE_PLAY;

/*------------------関数定義-------------------*/

void run( ) {
	//初期化
	if ( !initialize( ) ) {
		//初期化に失敗したら抜ける
		return;
	}
	//ループ
	while ( isLoop( ) ) {
		//更新
		update( );
		//描画
		draw( );
	}

	//終了処理
	finalize( );
}

bool initialize( ) {
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
		return false;
	}

	//描画対象を指定
	SetDrawScreen( DX_SCREEN_BACK );

	//シーン初期化
	switch ( g_scene ) {
	case SCENE_TITLE:
		initTitle();
		break;
	case SCENE_PLAY:
		initPlay();
		break;
	case SCENE_RESULT:
		initResult();
		break;
	};

	return result;
}

bool isLoop( ) {
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

void update( ) {
	SCENE next = g_scene;

	switch ( g_scene ) {
	case SCENE_TITLE:
		next = updateTitle( );
		break;
	case SCENE_PLAY:
		next = updatePlay( );
		break;
	case SCENE_RESULT:
		next = updateResult( );
		break;
	}

	//シーン変更
	if ( next != g_scene ) {
		changeScene( next );
	}
}

void draw( ) {
	switch ( g_scene ) {
	case SCENE_TITLE:
		drawTitle( );
		break;
	case SCENE_PLAY:
		drawPlay( );
		break;
	case SCENE_RESULT:
		drawResult( );
		break;
	}
	ScreenFlip();
	ClearDrawScreen();
}

void finalize( ) {
	//シーン終了処理
	switch ( g_scene ) {
	case SCENE_TITLE:
		finalizeTitle( );
		break;
	case SCENE_PLAY:
		finalizePlay( );
		break;
	case SCENE_RESULT:
		finalizeResult( );
		break;
	}

	//DxLib終了処理
	DxLib_End( );
}

void changeScene( SCENE scene ) {
	//シーン終了処理
	switch ( g_scene ) {
	case SCENE_TITLE:
		finalizeTitle( );
		break;
	case SCENE_PLAY:
		finalizePlay( );
		break;
	case SCENE_RESULT:
		finalizeResult( );
		break;
	}

	//シーン初期化処理
	switch ( scene ) {
	case SCENE_TITLE:
		initTitle( );
		break;
	case SCENE_PLAY:
		initPlay( );
		break;
	case SCENE_RESULT:
		initResult( );
		break;
	};

	g_scene = scene;
}