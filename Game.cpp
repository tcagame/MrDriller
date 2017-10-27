#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


/*------------------�萔�錾-------------------*/
//�萔�͑啶���Ő錾����
const char* TITLE_NAME = "Mr.Driller";

/*-------------�O���[�o���ϐ��錾--------------*/
//static��t���邱�Ƃɂ���ĊO������̕ϐ��ւ̃A�N�Z�X�����S�ɎՒf
//�ϐ��́ug_�v��t���Đ錾������

/*------------------�֐���`-------------------*/

Game::Game( ) :
_now_scene( Scene::SCENE_PLAY ) {
	bool result = true;
	//�E�B���h�E���[�h
	ChangeWindowMode( TRUE );

	//�𑜓x���w��
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32 );

	//�A�N�e�B�u�ł͂Ȃ��Ƃ��͏������Ȃ�
	SetAlwaysRunFlag( FALSE );

	//�^�C�g����ݒ�
	SetWindowText( TITLE_NAME );

	//DxLib������
	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	//�`��Ώۂ��w��
	SetDrawScreen( DX_SCREEN_BACK );

	//�V�[��������
	changeScene( _now_scene );
}

Game::~Game( ) {
	//DxLib�I������
	DxLib_End( );
}

void Game::run( ) {
	//���[�v
	while ( isLoop( ) ) {
		//�X�V
		Scene::SCENE next = update( );
		//�`��
		draw( );

		//�V�[���J��
		if ( next != _now_scene ) {
			changeScene( next );
		}
	}
}

bool Game::isLoop( ) const {
	bool result = true;
	//�E�B���h�E���b�Z�[�W����
	if ( ProcessMessage( ) != 0 ) {
		result = false;
	}

	//Esc�ŏI��
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
	//�V�[���I������
	//_scene.reset( new Scene );
	_now_scene = scene;
}