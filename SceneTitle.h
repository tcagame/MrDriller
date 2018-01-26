#pragma once
#include "Scene.h"

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );
public://åpè≥
	SCENE update( );
	void draw( ) const;
	void loadSound( );
	void loadGraph( );
private:
	void drawBg( ) const;
	void drawPleasePush( ) const;
private:
	int _count;
	bool _next;
	bool _click;
};