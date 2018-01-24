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
	//�E�B���h�E���[�h
#if _DEBUG
	ChangeWindowMode( TRUE );
#endif

	//�𑜓x���w��
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, FPS );

	//�A�N�e�B�u�ł͂Ȃ��Ƃ��͏������邩�ǂ���
	SetAlwaysRunFlag( TRUE );

	//�^�C�g����ݒ�
	SetWindowText( TITLE_NAME );

	//DxLib������
	if ( DxLib_Init( ) == -1 ) {
		return -1;
	}

	//�`��Ώۂ��w��
	SetDrawScreen( DX_SCREEN_BACK );
	
	//initialize
	Keyboard::initalize( );
	Sound::initialize( );
	Graph::initialize( );

	{//�Q�[�����[�v
		std::shared_ptr< Game >( new Game )->run( );
	}
	Sound::get( )->unLoadAll( );
	Graph::get( )->unLoadAll( );

	//DxLib�I������
	DxLib_End( );
	return 0;
}