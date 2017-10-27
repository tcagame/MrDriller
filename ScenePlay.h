#pragma once
#include "Scene.h"
#include <memory>
#include "Player.h"
#include "Board.h"

class ScenePlay : public Scene {
public:
	ScenePlay( );
	~ScenePlay( );
public:
	SCENE update( );
	void draw( ) const;
private:
	void drawDepth( ) const;
	void drawAir( ) const;
	void drawLevel( ) const;
private:
	std::shared_ptr< Player > _player;
	std::shared_ptr< Board > _board;
};