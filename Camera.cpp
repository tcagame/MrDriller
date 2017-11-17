#include "Camera.h"



Camera::Camera( std::shared_ptr< Player > player ) :
_player( player ),
_y( 0 ) {
}


Camera::~Camera( ) {
}

void Camera::update( ) {
	//キャラクターの座標にあわせてy軸を変更
	int y = _player->getY( ) - 720 / 2;
	if ( y > _y ) {
		_y = y;
	}
}

int Camera::getY( ) {
	return _y;
}
