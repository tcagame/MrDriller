#include "Map1.h"



Map1::Map1( ) {
	_map[ 0 ] = {
		"         "
		"         "
		"         "
		"         "
		"  GGGGG  "
		" YYBGBYY "
		"***GGG***"
		"YYYRARYYY"
		"R***A***B"
		"**YYL*YBG"
		"BBBRRYGGB"
		"YYYBRBGRG"
		"R*YBBGAA*"
		"**BRGG***"
		"AABBGARB*"
		"GYYGBRAYY"
		"YARY*YYB"
		"GGRY*ABAA"
		"BYGBBRRYY"
		"RR*GGAYBB"
		"RABBYAYYR"
		"YY**BRARB"
		"BBGARGYBY"
		"RRYAYYAAA"
		"B*RRARGBB"
		"YYAY*BBYA"
		"BAGGY*RYY"
		"RRBARYYAB"
		"YYABBYRRB"
		"BGGYGB*Y*"
		"*BBGYRBAB"
		"BY*BGGTTB"
		"BYRYYBGGA"
		"BBRRGGRRB"
		"YYBYABBRR"
		"BYY*BGGBA"
		"GGYBYY*RB"
		"***BBBABG"
		"YYABGGGRR"
		"BBBGRRRYY"
		"YRRBBAYBB"
		"GGG*RRYYA"
		"BYRBYGGAA"
		"YYBBARYRR"
		"*BAYRYGRY"
		"BBGRRYYBB"
		"RRYYGG*AR"
		"GG*RGARBB"
		"YRBBGYYRY"
		"GGRRRA*Y*"
		"*YRGA*BRR"
		"RRGYYYRBY"
		"GARRBBGGG"
		"BBBRYRRBY"
		"YYYARYRBB"
		"B*BYYBGGG"
		"GGGBBYYRR"
		"***YYB*YR"
		"Y*BBGGBBY"
		"GGAYBBYRR"
		"RYRBGGYGG"
		"YY*BBB*YY"
		"RBRYYBBAG"
		"GYGGRRYYB"
		"Y*YBBBYGB"
		"YRBGAG*BY"
		"GYYYBBRRR"
		"YGG*YYRBR"
		"BBBA*BBYY"
		"YYRYBYRRR"
		"RRBA*YYY*"
		"YYY*BRGBB"
		"ABBBYRRRG"
		"GYGGA*BBB"
		"BGGGAYRRY"
		"YBYBBAGYR"
		"GBYYAYBGG"
		"BYYBRRRAR"
		"*YYRAYR*B"
		"BBRBRRARY"
		"GBYYYGYYB"
		"RRYBBAYRR"
		"GGY**GYBB"
		"BBBYYARRR"
		"RYYRRBA**"
		"YBGGGYBRR"
		"RBBBRRYYG"
		"G*YBABBRR"
		"YYARB*YBA"
		"GRRBRRYYY"
		"**YYBGGGR"
		"YYBAGB*RA"
		"BBYABYGGY"
		"YYRRB*BBB"
		"BBYRGGARY"
		"Y*YYARYRR"
		"GRYRYRRBB"
		"YYRAYYYRB"
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