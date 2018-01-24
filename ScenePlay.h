#pragma once
#include "Scene.h"
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Camera.h"
#include "Game.h"

class ScenePlay : public Scene {
public:
	ScenePlay( Game::MODE mode, int *score, int *depth );
	virtual ~ScenePlay( );
public://åpè≥
	SCENE update( );
	void draw( ) const;
	void loadSound( );
	void loadGraph( );
public://get
	int getScore( );
	int getDepth( );
private:
	void drawDepth( ) const;
	void drawAir( ) const;
	void drawAirGauge( ) const;
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
	char _brightness;//ñæÇÈÇ≥( MAX 100 )
	int *_score;
	int *_depth;
	Game::MODE _mode;
};