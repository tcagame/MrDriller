#pragma once
#include "Scene.h"

class SceneResult : public Scene {
public:
	SceneResult( int score, int depth );
	virtual ~SceneResult( );
public://åpè≥
	SCENE update( );
	void draw( ) const;
	void loadSound( );
	void loadGraph( );
private:
	void drawDepth( ) const;
	void drawScore( ) const;
private:
	int _score;
	int _depth;
	//int _se[ 18 ];
};