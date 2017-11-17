#pragma once
#include "Scene.h"
#include <memory>
#include "Player.h"
#include "Board.h"

class ScenePlay : public Scene {
public:
	ScenePlay( );
	virtual ~ScenePlay( );
public:
	SCENE update( );
	void draw( ) const;
private:
	void drawDepth( ) const;
	void drawAir( ) const;
	void drawLevel( ) const;
	void drawUIBack( ) const;
	void drawLife( ) const;
	void drawBack( ) const;
	void drawScore( ) const;
private:
	std::shared_ptr< Player > _player;
	std::shared_ptr< Board > _board;
	int _img_ui;
	int _img_back;
	int _img_num;
	int _level;
};