#include "Map1.h"



Map1::Map1( ) {
	_map[ 0 ] = {
		"         "
		"         "
		"         "
		"         "
		"**GGGGG**"
		"RRRBGBYYY"
		"***GGG***"
		"BBBBABBBB"
		"R***A***B"
		"**YYB*YBG"
		"BBBRRYGGB"
		"YYYBRBGRG"
		"R*YBBGRG*"
		"**BRGG***"
		"YRBBGBRB*"
		"GYYGBRGYY"
		"YRRY*YYBR"
		"GGRY*GBGG"
		"BYGBBRRYY"
		"RR*GGAYBB"
		"RGBBYRYYR"
		"YY**BRYRB"
		"BBGGRGYBY"
		"RRYBYYGG*"
		"B*RRARGBB"
		"YY*Y*BBYA"
		"BBGGY*RYY"
		"RRBRRYY*B"
		"YYABBYRRB"
		"BGGYGB*Y*"
		"*BBGYRBAB"
		"BY*BGGYYB"
		"YYRYYBGGA"
		"BBRRGGRRB"
		"YYBYYBBRR"
		"BYY*BGGBR"
		"GGYBYY*RB"
		"***BBBABG"
		"YYRBGGGRR"
		"BBBGRRRYY"
		"YRRBB*YBB"
		"GGG*RRYYA"
		"BYRBYGG**"
		"YYBB*RYRR"
		"*BYYRYGRY"
		"BBGRRYYBB"
		"RRYYGG*AR"
		"GG*RGYRBB"
		"YRBBGYYRY"
		"GGRRRG*Y*"
		"*YRGG*BRR"
		"RRGYYYRBY"
		"G*RRBBGGG"
		"BBBRYRRBY"
		"YYY*RYRBB"
		"B*BYYBGGG"
		"GGGBBYYRR"
		"***YYB*YR"
		"Y*BBGGBBY"
		"GGAYBBYRR"
		"RYRBGGYGG"
		"YY*BBB*YY"
		"RBRYYBBGG"
		"GYGGRRYYB"
		"Y*YBBBYGB"
		"YRBGYG*BY"
		"GYYYBBRRR"
		"YGGAYYRBR"
		"BBBR*BBYY"
		"YYRYBYRRR"
		"RRBB*YYY*"
		"YYY*BRGBB"
		"ABBBYRRRG"
		"GYGGB*BBB"
		"BGGG*ARRY"
		"YBYBB**YR"
		"GBYYRYBGG"
		"BYYBRRR*R"
		"*YYRYYR*B"
		"BBRBRRRY*"
		"GBYYRRYYB"
		"RRBBBYYRR"
		"GGYA*GYBB"
		"BBBYYBRRR"
		"RYYRRBY**"
		"YBGGGYBRR"
		"RBBBRRYYG"
		"G*YBYBBRR"
		"YYRRB*YBG"
		"RRRBRRYYY"
		"**YYBGGGR"
		"YYB*GB*RA"
		"BBYBBYGGY"
		"YYRRB*BBB"
		"BBYRGGYRY"
		"Y*YYYRYRR"
		"GRYRYRRBB"
		"YYRRRYGGB"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
		"LLLLLLLLL"
	};
}


Map1::~Map1( ) {
}

std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > Map1::getMap( int pattern ) {
	if ( pattern < 0 ) {
		pattern = 0;
	}
	if ( pattern >= MAX_PATTERN ) {
		pattern = MAX_PATTERN - 1;
	}
	return _map[ pattern ];
}