#pragma once
#include "Scene.h"
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Camera.h"
#include "Game.h"

class ScenePlay : public Scene {
public:
	ScenePlay( Game::MODE mode );
	virtual ~ScenePlay( );
public:
	SCENE update( );
	void draw( ) const;
private:
	void drawDepth( ) const;
	void drawAir( ) const;
	void drawLevel( ) const;
	void drawLife( ) const;
	void drawBg( ) const;
	void drawUIBg( ) const;
	void drawScore( ) const;
	void drawBlind( ) const;
private:
	std::shared_ptr< Player > _player;
	std::shared_ptr< Board > _board;
	std::shared_ptr< Camera > _camera;
	char _brightness;//–¾‚é‚³( MAX 100 )
	int _img_ui;
	int _img_bg;
	int _img_num;
	int _img_life;
	int _img_blind;
	int _bgm;
	Game::MODE _mode;
};