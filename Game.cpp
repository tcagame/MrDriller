#include "DxLib.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"


/*------------�v���g�^�C�v�֐��錾-------------*/
bool initialize( );				  //������
bool isLoop( );					  //���[�v�`�F�b�N
void update( );					  //�X�V
void draw( );					  //�`��
void finalize( );				  //�I������
void changeScene( SCENE scene );  //�V�[���J��

/*------------------�萔�錾-------------------*/
//�萔�͑啶���Ő錾����
const char* TITLE_NAME = "Mr.Driller";

/*-------------�O���[�o���ϐ��錾--------------*/
//static��t���邱�Ƃɂ���ĊO������̕ϐ��ւ̃A�N�Z�X�����S�ɎՒf
//�ϐ��́ug_�v��t���Đ錾������
static SCENE g_scene = SCENE_PLAY;

/*------------------�֐���`-------------------*/

void run( ) {
	//������
	if ( !initialize( ) ) {
		//�������Ɏ��s�����甲����
		return;
	}
	//���[�v
	while ( isLoop( ) ) {
		//�X�V
		update( );
		//�`��
		draw( );
	}

	//�I������
	finalize( );
}

bool initialize( ) {
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
		return false;
	}

	//�`��Ώۂ��w��
	SetDrawScreen( DX_SCREEN_BACK );

	//�V�[��������
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

	//�V�[���ύX
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
	//�V�[���I������
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

	//DxLib�I������
	DxLib_End( );
}

void changeScene( SCENE scene ) {
	//�V�[���I������
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

	//�V�[������������
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