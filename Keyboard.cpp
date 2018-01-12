#include "Keyboard.h"
#include "DxLib.h"

static std::shared_ptr< Keyboard > _instance;


std::shared_ptr< Keyboard > Keyboard::getInstance( ) {
	return _instance;
}

void Keyboard::init( ) {
	if ( _instance == std::shared_ptr< Keyboard >( ) ) {
		_instance = std::shared_ptr< Keyboard >( new Keyboard );
	}
}



Keyboard::Keyboard( ) {
	for ( int i = 0; i < KEY_BUF; i++ ) {
		_buf[ i ] = 0;
	}
}


Keyboard::~Keyboard( ) {
}



void Keyboard::update( ) {
	char buf[ KEY_BUF ];
	GetHitKeyStateAll( buf );
	for ( int i = 0; i < KEY_BUF; i++ ) {
		if ( buf[ i ] != 0 ) {
			if ( _buf[ i ] == 0 ) {
				_buf[ i ] = 1;
			} else {
				_buf[ i ] = 2;
			}
		} else {
			_buf[ i ] = 0;
		}
	}
}


bool Keyboard::isPushKey( unsigned char key ) const {
	return _buf[ key ] == 1;
}

bool Keyboard::isHoldKey( unsigned char key ) const {
	return _buf[ key ] > 1;
}