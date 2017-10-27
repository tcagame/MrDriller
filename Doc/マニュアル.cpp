//C++の書き方(実際に書いて覚える)

//C  の場合のupdateは「updateSample」になるが
//C++の場合のupdateは「Sample::update」のような形になる

Sample::Sample( ) {
	//コンストラクター( クラス生成時に呼ばれる )
	//Cの場合initialize( )関数とかにする
}

Sample::~Sample( ) {
	//デストラクター( クラス破棄時に呼ばれる )
	//Cの場合finalize( )関数とか
}

void Sample::update( ) {
	//更新処理
}
void Sample::draw( ) {
	//描画処理
}
 
int Sample::getNum( ) {
	return _num;
}