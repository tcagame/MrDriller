#include "Camera.h"

const int CAMERA_MOVE_SPEED = 8;

Camera::Camera( ) :
_y( 0 ) {
}


Camera::~Camera( ) {
}

void Camera::update( int player_y ) {
	//キャラクターの座標にあわせてy軸を変更
	if( player_y > CAMERA_PLAYER_Y ) {
		int target_y = player_y - CAMERA_PLAYER_Y;
		if( _y != target_y ) {
			int vec = target_y - _y;
			if( abs( vec ) > CAMERA_MOVE_SPEED ) {
				if( vec > 0 ) {
					vec = CAMERA_MOVE_SPEED;
				} else {
					vec = CAMERA_MOVE_SPEED * -1;
				}
			}
			_y += vec;
		}
	}
}

int Camera::getY( ) {
	return _y;
}
