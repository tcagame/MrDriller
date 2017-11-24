#include "Camera.h"

const int CAMERA_MOVE_SPEED = 8;

Camera::Camera( ) :
_y( 0 ) {
}


Camera::~Camera( ) {
}

void Camera::update( int player_y ) {
	//�L�����N�^�[�̍��W�ɂ��킹��y����ύX
	if(player_y>360){
	int target_y = player_y - 720 /2;
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
	}}
}

int Camera::getY( ) {
	return _y;
}
