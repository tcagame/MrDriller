#include "Camera.h"



Camera::Camera( std::shared_ptr< Player > player ) :
_player( player ) {
}


Camera::~Camera( ) {
}

void Camera::update( ) {
	//�L�����N�^�[�̍��W�ɂ��킹��y����ύX
	int a = _player->getY( );
}

int Camera::getY( ) {
	return _y;
}
