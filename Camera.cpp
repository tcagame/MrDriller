#include "Camera.h"



Camera::Camera( std::shared_ptr< Player > player ) :
_player( player ) {
}


Camera::~Camera( ) {
}

void Camera::update( ) {
	//キャラクターの座標にあわせてy軸を変更
	int a = _player->getY( );
}

int Camera::getY( ) {
	return _y;
}
