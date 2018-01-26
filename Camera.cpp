#include "Camera.h"

Camera::Camera( ) :
_y( 0 ) {
}


Camera::~Camera( ) {
}

void Camera::update( int player_y ) {
	//キャラクターの座標にあわせてy軸を変更
	if( player_y > CAMERA_PLAYER_Y ) {
		_y = player_y - CAMERA_PLAYER_Y;
	}
}

int Camera::getY( ) {
	return _y;
}
