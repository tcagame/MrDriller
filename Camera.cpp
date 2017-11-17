#include "Camera.h"

const int CAMERA_MOVE_SPEED = 4;

Camera::Camera( std::shared_ptr< Player > player ) :
_player( player ),
_y( 0 ) {
}


Camera::~Camera( ) {
}

void Camera::update( ) {
	//�L�����N�^�[�̍��W�ɂ��킹��y����ύX
	int target_y = _player->getY( ) - 720 / 2;
	if ( _y != target_y ) {
		int vec = target_y - _y;
		if ( abs( vec ) > CAMERA_MOVE_SPEED ) {
			if ( vec > 0 ) {
				vec = CAMERA_MOVE_SPEED;
			} else {
				vec = CAMERA_MOVE_SPEED * -1;
			}
		}
		_y += vec;
	}
}

int Camera::getY( ) {
	return _y;
}
