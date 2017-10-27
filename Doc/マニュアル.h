//C++の書き方(実際に書いて覚える)
//



//[クラスの構造]
class Sample {
public:
	Sample( ); //コンストラクター( クラス生成時に呼ばれる )
	~Sample( ); //デストラクター( クラス破棄時に呼ばれる )
public:
//ここにupdateやdrawを書く
	void update( ); //更新処理
	void draw( ); //描画処理
public:
//get系関数を書く( メンバ変数などを取得したいとき )
 int getNum( );
private:
//ここにメンバ変数( C言語の場合はグローバル変数 )
//ここでは初期化しない
	int _num;
}


//クラス生成の仕方
//できればstd::sheard_ptrを使う( 自動的に破棄してくれるポインタ )

#include <memory>//shared_ptrのためにinclude

void func( ) {
	//サンプルクラスのポインタを生成
	std::shared_ptr< Sample > sample( new Sample );

	//関数を呼び出すときは->を使う
	sample->update( );
	sample->draw( );

	//sampleからの値の取得
	int num = sample->getNum( );
}