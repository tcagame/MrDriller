#pragma once
#include <memory>
#include <array>
#include <string>

class Graph {
public:
	static std::shared_ptr< class Graph > get( );
	static void initialize( );
public:
	enum GRAPH {
		//Common
		GRAPH_NUMBER,
		GRAPH_PLEASE_PUSH_SPACE,
		//Title
		GRAPH_TITLE_BG,
		//ModeSelect
		GRAPH_MODESELECT_TEXT,
		//Play
		GRAPH_PLAY_BG,
		GRAPH_PLAY_UI,
		GRAPH_PLAY_BLIND,
		GRAPH_PLAY_BLOCK,
		GRAPH_PLAY_CHARACTER,
		GRAPH_PLAY_AIRGAUGE,
		//Result
		GRAPH_RESULT_BG,
		GRAPH_RESULT_COMMENT,
		MAX_GRAPH
	};
public:
	Graph( );
	virtual ~Graph( );
public:
	void draw( GRAPH graph, int trans, int x1, int y1, int x2 = -1, int y2 = -1, int tx = -1, int ty = -1, int tw = -1, int th = -1 );
	void load  ( GRAPH graph );
	void unLoad( GRAPH graph );
	void unLoadAll( );
private:
	std::array< std::string, MAX_GRAPH > _filenames;
	std::array< int        , MAX_GRAPH > _graphs;
};