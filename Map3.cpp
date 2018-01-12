#include "Map3.h"



Map3::Map3(){
	_map[ 0 ] = {
		"         "
		"         "
		"         "
		"****B****"
		"BBBBBBBBB"
		"****BG***"
		"BBBBB*GG*"
		"****B****"
		"GGGABBBBB"
		"BBGGGBGGB"
		"GGBGBBGBG"
		"GBBGB*GGB"
		"GGBBBBGBB"
		"BGBGBGBGB"
		"**BBG*GA*"
		"BGGG*B*GB"
		"GG*BG*B*G"
		"B*B*GB*GB"
		"GGGGGGGGG"
		"**B*A*B*G"
		"**GGGGGGG"
		"BGBGBGGG*"
		"***GGG*G*"
		"A***GGGB*"
		"GGGGGGG*B"
		"******GBG"
		"BG**BGGAB"
		"GGBG**GBG"
		"BG*BGB**B"
		"GBGGGGBG*"
		"BG*BGG***"
		"GBBGAGGGG"
		"**B**GGGG"
		"GB**B***B"
		"GGGGB****"
		"BGBGGBABG"
		"GGGGBGGGB"
		"B**BGGBGB"
		"GBGBG**GB"
		"B*BGGGGGB"
		"GB**BGGGG"
		"GABG**BG*"
		"GGB**BGG*"
		"GGGBG*BGG"
		"BGGGBGG*G"
		"**G***B**"
		"BGB*B*GGG"
		"GB*GGB*B*"
		"BA**B**GB"
		"GGBGGGB**"
		"BGGB**BGG"
		"GGBGG**BG"
		"GBGGGGB**"
		"BGGBGBAGG"
		"GGG*B***B"
		"G*GBG**BB"
		"G*BGBBG**"
		"B*GBGGBBG"
		"G*BGGBGGB"
		"*A**BGGBG"
		"**GGG**BG"
		"GGGGBBG**"
		"GBB**GBB*"
		"G**GGG*GB"
		"GB***GBGB"
		"G*B*GG***"
		"BGGBGG*GB"
		"GB**BG***"
		"BG**GBGG*"
		"GB**GGBG*"
		"BG*GB*GGG"
		"*GGB*GG*G"
		"GBGGBGGGB"
		"BG*GGBGBG"
		"***BGGGGB"
		"AA*AAA*AA"
		"G*GBGG*G*"
		"GBGG*BGGG"
		"GGGBG**GG"
		"GBGGBGG**"
		"GGGBGG*GG"
		"BGG***BBG"
		"**GG*GGGG"
		"B**GGG*GB"
		"GB*GGB**G"
		"BGBGGGBGB"
		"GGGGGGGGG"
		"GGBGBGGBG"
		"BG*GG*BGG"
		"BGBGGGBGG"
		"GGGGBBG*B"
		"BBGBGGGB*"
		"GGBG***GG"
		"GGGBGGGGB"
		"BBB***BBB"
		"BGGBGGGBB"
		"GGBB**BBB"
		"BBBGGG***"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
	};
}


Map3::~Map3( ) {
}

std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > Map3::getMap( int pattern ) {
	if ( pattern < 0 ) {
		pattern = 0;
	}
	if ( pattern >= MAX_PATTERN ){
		pattern = MAX_PATTERN - 1;
	}
	return _map[ pattern ];
}
