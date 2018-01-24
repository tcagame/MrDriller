#pragma once
#include <memory>

class Keyboard {
public:
	static std::shared_ptr< Keyboard > get( );
	static void initalize( );
public:
	Keyboard( );
	virtual ~Keyboard( );
public:
	void update( );
	bool isPushKey( unsigned char key ) const;
	bool isHoldKey( unsigned char key ) const;
private:
	static const int KEY_BUF = 256;
private:
	char _buf[ KEY_BUF ];
};

