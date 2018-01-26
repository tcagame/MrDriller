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
		SOUND_BLOCK_CRUSH,				//ブロック破壊
		SOUND_BLOCK_FALL_CRUSH,		//ブロック落ちて破壊
		SOUND_AIR_CAPSULE,				//エア
		SOUND_SOLID_REDUCE,			//お邪魔ブロックの削り
		SOUND_SOLID_CRUSH,				//お邪魔ブロックの破壊
		SOUND_LEVEL_CRUSH,				//岩盤破壊
		SOUND_AIR_LESS_THAN_THRITY,	//air<30
		SOUND_AIR_LESS_THAN_TEN,		//air<10
		SOUND_DEAD_AIR,				//酸欠死亡
		SOUND_DEAD_CRUSH,				//つぶれて死亡
		SOUND_ANGEL,					//天使
		SOUND_RESURRECTION,			//復活
		SOUND_FALL,
		SOUND_MENU_SELECT,				//メニュー選択
		SOUND_MENU_CLICK,				//メニュー決定
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