#pragma once
#include <memory>
#include <array>
#include <string>

class Sound : std::enable_shared_from_this< Sound > {
public:
	static std::shared_ptr< class Sound > get( );
	static void initialize( );
public:
	enum SOUND {
		SOUND_BLOCK_CRUSH,				//�u���b�N�j��
		SOUND_BLOCK_FALL_CRUSH,		//�u���b�N�����Ĕj��
		SOUND_AIR_CAPSULE,				//�G�A
		SOUND_SOLID_REDUCE,			//���ז��u���b�N�̍��
		SOUND_SOLID_CRUSH,				//���ז��u���b�N�̔j��
		SOUND_LEVEL_CRUSH,				//��Քj��
		SOUND_AIR_LESS_THAN_THRITY,	//air<30
		SOUND_AIR_LESS_THAN_TEN,		//air<10
		SOUND_DEAD_AIR,				//�_�����S
		SOUND_DEAD_CRUSH,				//�Ԃ�Ď��S
		SOUND_ANGEL,					//�V�g
		SOUND_RESURRECTION,			//����
		SOUND_FALL,
		SOUND_MENU_SELECT,				//���j���[�I��
		SOUND_MENU_CLICK,				//���j���[����
		SOUND_BGM_AIRMAN,
		MAX_SOUND
	};
public:
	Sound( );
	virtual ~Sound( );
public:
	bool isPlaying( SOUND sound ) const;
	void load     ( SOUND sound );
	void unLoad   ( SOUND sound );
	void play     ( SOUND sound, bool loop = false, bool top = false, int volume = -1 );
	void stop     ( SOUND sound );
	void unLoadAll( );
private:
	std::array< std::string, MAX_SOUND > _filenames;
	std::array< int        , MAX_SOUND > _sounds;
};