#include "FpsController.h"
#include "DxLib.h"

const int UPDATE_INTERVAL = 20;
const int FRAME_TIME = 1000 / FPS;//  àÍïb/àÍïbä‘ÇÃçXêVâÒêî

FpsController::FpsController( ) :
_count( UPDATE_INTERVAL ) {
	_fps = FPS;
	init( );
}


FpsController::~FpsController( ) {
}

void FpsController::init( ) {
	_before_time = GetNowCount( );
	_count = 0;
}

void FpsController::update( ) {
	_count++;
	int now = GetNowCount( );
	int diff_time = now - _before_time;
	if ( diff_time < FRAME_TIME ) {
		_wait_time = FRAME_TIME - diff_time;
		Sleep( _fps );
		return;
	}
	int frame_time = diff_time / _count;
	
	_wait_time = FRAME_TIME - frame_time;
	_fps = 1000.0 / frame_time;
	if ( _wait_time > 0 ) {
		Sleep( _wait_time );
	}

	if ( _count >= UPDATE_INTERVAL ) {
		init( );
	}
}

bool FpsController::isOverFps( ) const {
	return _wait_time < -FRAME_TIME;
}

double FpsController::getFps( ) const {
	return _fps;
}
