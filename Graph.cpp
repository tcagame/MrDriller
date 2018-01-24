#include "Graph.h"
#include "DxLib.h"

std::shared_ptr< Graph > instance;

std::shared_ptr< Graph > Graph::get( ) {
	return instance;
}

void Graph::initialize( ) {
	if ( instance == std::shared_ptr< Graph >( ) ) {
		instance = std::shared_ptr< Graph >( new Graph );
	}
}


Graph::Graph( ) {
	_filenames[ GRAPH_NUMBER		    ] = "Resource/Graph/Common/Number.png";
	_filenames[ GRAPH_PLEASE_PUSH_SPACE ] = "Resource/Graph/Common/PleasePushSpace.png";
	_filenames[ GRAPH_TITLE_BG			] = "Resource/Graph/Title/Bg.jpg";
	_filenames[ GRAPH_MODESELECT_TEXT	] = "Resource/Graph/ModeSelect/Text.png";
	_filenames[ GRAPH_PLAY_BG			] = "Resource/Graph/Play/Bg.jpg";
	_filenames[ GRAPH_PLAY_UI			] = "Resource/Graph/Play/UI.png";
	_filenames[ GRAPH_PLAY_BLIND		] = "Resource/Graph/Play/Blind.png";
	_filenames[ GRAPH_PLAY_BLOCK		] = "Resource/Graph/Play/Block.png";
	_filenames[ GRAPH_PLAY_CHARACTER	] = "Resource/Graph/Play/Character.png";
	_filenames[ GRAPH_PLAY_AIRGAUGE     ] = "Resource/Graph/Play/AirGauge.png";
	_filenames[ GRAPH_RESULT_BG			] = "Resource/Graph/Result/Bg.png";


	for ( int i = 0; i < MAX_GRAPH; i++ ) {
		_graphs[ i ] = -1;
	}
}


Graph::~Graph( ) {
}


void Graph::load( GRAPH Graph ) {
	_graphs[ Graph ] = LoadGraph( _filenames[ Graph ].c_str( ), TRUE );
}

void Graph::unLoad( GRAPH Graph ) {
	if ( _graphs[ Graph ] == -1 ) {
		return;
	}
	DeleteGraph( _graphs[ Graph ] );
	_graphs[ Graph ] = -1;
}

void Graph::unLoadAll( ) {
	for ( int i = 0; i < MAX_GRAPH; i++ ) {
		if ( _graphs[ i ] == -1 ) {
			continue;
		}
		DeleteGraph( _graphs[ i ] );
		_graphs[ i ] = -1;
	}
}

void Graph::draw( GRAPH graph, int trans, int x1, int y1, int x2, int y2, int tx, int ty, int tw, int th ) {
	if ( x2 < 0 ) {
		//‚»‚Ì‚Ü‚Ü
		DrawGraph( x1, y1, _graphs[ graph ], trans );
	} else if ( tx < 0 ) {
		//Šg‘åEk¬
		DrawExtendGraph( x1, y1, x2, y2, _graphs[ graph ], trans );
	} else {
		//‰æ‘œØ‚èŽæ‚è
		DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, tw, th, _graphs[ graph ], trans );
	}
}
