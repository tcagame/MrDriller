#pragma once
#include "Scene.h"

class SceneResult : public Scene {
public:
	SceneResult( int score, int depth, int level );
	virtual ~SceneResult( );
public://�p��
	SCENE update( );
	void draw( ) const;
	void loadSound( );
	void loadGraph( );
private:
	void drawComment( ) const;
	void drawDepth( ) const;
	void drawScore( ) const;
	void drawPleasePush( ) const;
private:
	int _score;
	int _depth;
	int _level;
	int _rand;
	int _count;
	//int _se[ 18 ];
};