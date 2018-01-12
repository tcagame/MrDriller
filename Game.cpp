#include "DxLib.h"
#include "Game.h"
#include "Keyboard.h"
#include "SceneTitle.h"
#include "SceneModeSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"
#include "FpsController.h"


/*------------------�萔�錾-------------------*/
//�萔�͑啶���Ő錾����

/*-------------�O���[�o���ϐ��錾--------------*/
//static��t���邱�Ƃɂ���ĊO������̕ϐ��ւ̃A�N�Z�X�����S�ɎՒf
//�ϐ��́ug_�v��t���Đ錾������

/*------------------�֐���`-------------------*/

Game::Game( ) :
_now_scene( Scene::SCENE_TITLE ) {
	//�V�[��������
	changeScene( _now_scene );
	_fps_ctrl = std::shared_ptr< FpsController >( new FpsController );
	Keyboard::init( );
	
}

Game::~Game( ) {
}

void Game::run( ) {
	//���[�v
	while ( isLoop( ) ) {
		//�X�V
		Keyboard::getInstance( )->update( );
		Scene::SCENE next = _scene->update( );
		//FPS�`�F�b�N
		_fps_ctrl->update( );
		if ( !_fps_ctrl->isOverFps( ) ) {
			//�`��
			_scene->draw( );
			#if _DEBUG
			DrawFormatString( 1280 - 100, 0, GetColor( 255, 255, 255 ), "FPS:%.2f", _fps_ctrl->getFps( ) );
			#endif
			//�`�攽�f
			ScreenFlip( );
			ClearDrawScreen( );
		}

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
	if ( Keyboard::getInstance( )->isHoldKey( KEY_INPUT_ESCAPE ) != 0 ) {
		result = false;
	}

	return result;
}

void Game::changeScene( Scene::SCENE scene ) {
	//�V�[���I������
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