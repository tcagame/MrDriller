#include "Sound.h"
#include "DxLib.h"

std::shared_ptr< Sound > instance;

std::shared_ptr< Sound > Sound::get( ) {
	return instance;
}

void Sound::initialize( ) {
	if ( instance == std::shared_ptr< Sound >( ) ) {
		instance = std::shared_ptr< Sound >( new Sound );
	}
}


Sound::Sound( ) {
	SetCreateSoundDataType( DX_SOUNDDATATYPE_FILE );

	_filenames[ SOUND_BLOCK_CRUSH 		   ] = "Resource/Sound/effect/effect01.mp3";
	_filenames[ SOUND_BLOCK_FALL_CRUSH 	   ] = "Resource/Sound/effect/effect02.mp3";
	_filenames[ SOUND_AIR_CAPSULE 		   ] = "Resource/Sound/effect/effect03.mp3";
	_filenames[ SOUND_SOLID_REDUCE 		   ] = "Resource/Sound/effect/effect04.mp3";
	_filenames[ SOUND_SOLID_CRUSH 		   ] = "Resource/Sound/effect/effect05.mp3";
	_filenames[ SOUND_LEVEL_CRUSH 		   ] = "Resource/Sound/effect/effect06.mp3";
	_filenames[ SOUND_AIR_LESS_THAN_THRITY ] = "Resource/Sound/effect/effect07.mp3";
	_filenames[ SOUND_AIR_LESS_THAN_TEN    ] = "Resource/Sound/effect/effect08.mp3";
	_filenames[ SOUND_DEAD_AIR 			   ] = "Resource/Sound/effect/effect09.mp3";
	_filenames[ SOUND_DEAD_CRUSH 		   ] = "Resource/Sound/effect/effect10.mp3";
	_filenames[ SOUND_ANGEL 			   ] = "Resource/Sound/effect/effect11.mp3";
	_filenames[ SOUND_RESURRECTION 		   ] = "Resource/Sound/effect/effect12.mp3";
	_filenames[ SOUND_FALL 				   ] = "Resource/Sound/effect/effect13.mp3";
	_filenames[ SOUND_MENU_SELECT 		   ] = "Resource/Sound/effect/effect14.mp3";
	_filenames[ SOUND_MENU_CLICK 		   ] = "Resource/Sound/effect/effect15.mp3";
	_filenames[ SOUND_BGM_AIRMAN 		   ] = "Resource/Sound/bgm/Airman.mp3";
	for ( int i = 0; i < MAX_SOUND; i++ ) {
		_sounds[ i ] = -1;
	}
}


Sound::~Sound( ) {
}


void Sound::load( SOUND sound ) {
	_sounds[ sound ] = LoadSoundMem( _filenames[ sound ].c_str( ) );
}

void Sound::unLoad( SOUND sound ) {
	if ( _sounds[ sound ] == -1 ) {
		return;
	}
	DeleteSoundMem( _sounds[ sound ] );
	_sounds[ sound ] = -1;
}

void Sound::play( SOUND sound, bool loop, bool top, int volume ) {
	if ( volume > 0 ) {
		ChangeVolumeSoundMem( volume, _sounds[ sound ] );
	}
	int top_flag = FALSE;
	if ( top ) {
		top_flag = TRUE;
	}
	if ( !loop ) {
		PlaySoundMem( _sounds[ sound ], DX_PLAYTYPE_BACK, top_flag );
	} else {
		PlaySoundMem( _sounds[ sound ], DX_PLAYTYPE_LOOP, top_flag );
	}
}

void Sound::stop( SOUND sound ) {
	StopSoundMem( _sounds[ sound ] );
}

void Sound::unLoadAll( ) {
	for ( int i = 0; i < MAX_SOUND; i++ ) {
		if ( _sounds[ i ] == -1 ) {
			continue;
		}
		DeleteSoundMem( _sounds[ i ] );
		_sounds[ i ] = -1;
	}
}
