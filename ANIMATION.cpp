//ANIMATION.cpp
//アニメーションクラス

//************ ヘッダーファイル読み込み **************
#include "ANIMATION.hpp"
#include "FPS.hpp"

//********** クラスの定義 ******************

//コンストラクタ
//引数:const char *:画像のディレクトリ
//引数:const char *:画像の名前
//引数:int:画像の総分割数
//引数:int:画像の横向きの分割数
//引数:int:画像の縦向きの分割数
//引数:int:画像の分割された横の大きさ
//引数:int:画像の分割された縦の大きさ
//引数:double:次の画像に変更する速さ
//引数:bool:アニメーションをループするかどうか
ANIMATION::ANIMATION(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SpritNumY, int SpritWidth, int SpritHeight, double ChangeSpeed, bool IsLoop)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前

	this->Handle.resize(SplitNumALL);			//resize:vectorの要素数を変更する
	this->Handle_itr = this->Handle.begin();	//先頭のポインタを入れる

	this->X = 0;			//X位置
	this->Y = 0;			//Y位置
	this->Width = 0;		//幅
	this->Height = 0;		//高さ
	this->NextChangeSpeed = 0.0;	//画像を変える速さ

	this->ChangeMaxCnt = (int)(ChangeSpeed*fps->Getvalue());	//アニメーションするフレームの最大値
	this->ChangeCnt = 0;										//アニメーションするフレームのカウント

	this->IsAnimeLoop = IsLoop;			//アニメーションはループする?

	this->IsLoad = false;				//読み込めたか？

	this->IsDraw = false;				//描画してはいけない

	//画像を読み込み
	std::string LoadFilePath;			//画像のファイルパスを作成
	LoadFilePath += dir;
	LoadFilePath += name;

	//画像を分割して読み込み
	LoadDivGraph(LoadFilePath.c_str(), SplitNumALL, SpritNumX, SpritNumY, SpritWidth, SpritHeight, &this->Handle[0]);

	if (this->Handle[0] == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//エラーメッセージを作成
		ErrorMsg += TEXT('\n');		//改行
		ErrorMsg += LoadFilePath;	//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),		//char *を返す
			TEXT(ANIMATION_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadFilePath;		//画像のパスを設定
	this->FileName = name;				//画像の名前を設定

	GetGraphSize(
		this->Handle[0],	//このハンドルの画像の大きさを取得
		&this->Width,		//Widthのアドレスを渡す
		&this->Height		//Heightのアドレスを渡す
	);

	this->NextChangeSpeed = ChangeSpeed;		//画像を変える速さ

	this->IsLoad = true;		//読み込めた

	this->IsDraw = true;		//描画してよい

	return;
}

//デストラクタ
ANIMATION::~ANIMATION()
{
	//範囲ベースのforループ
	//vectorなどのコンテナクラスで使用できる
	//auto:型推論:コンパイラが初期力推論して型を決めてくれる
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);
	}

	//vectorのメモリ開放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Handle.swap(v);		//空と中身を入れ替える

	return;
}

//ファイルの名前を取得
std::string ANIMATION::GetFileName(void)
{
	return this->FileName;
}

//X位置を設定
void ANIMATION::SetX(int numX)
{
	this->X = numX;	return;
}

//Y位置を設定
void ANIMATION::SetY(int numY)
{
	this->Y = numY;	return;
}

//X位置を取得
int ANIMATION::GetX(void)
{
	return this->X;
}

//Y位置を取得
int ANIMATION::GetY(void)
{
	return this->Y;
}

//幅を取得
int ANIMATION::GetWidth(void)
{
	return this->Width;
}

//高さを取得
int ANIMATION::GetHeight(void)
{
	return this->Height;
}

//読み込めた？
bool ANIMATION::GetIsLoad(void)
{
	return this->IsLoad;
}

//画像を描画
void ANIMATION::Draw(void)
{
	if (this->IsDraw == true)	//描画してよいなら
	{
		DrawGraph(this->X, this->Y, *this->Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画

		if (this->ChangeCnt == this->ChangeMaxCnt)	//次の画像を表示するときがきたら
		{
			//this->Handle.end()は、最後の要素の1個次のイテレータを返すので、-1している。
			if (this->Handle_itr == this->Handle.end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
			{
				if (this->IsAnimeLoop == false)	//アニメーションループしないなら
				{
					this->IsDraw = false;		//描画をやめる
				}

				//次回の描画に備えて、先頭の画像に戻しておく
				this->Handle_itr = this->Handle.begin();		//イテレータ(ポインタ)を要素の最初に戻す

			}
			else
			{
				this->Handle_itr++;		//次のイテレータ(ポインタ)(次の画像)に移動する
			}

			this->ChangeCnt = 0;		//カウント初期化
		}
		else
		{
			this->ChangeCnt++;			//カウントアップ
		}
	}
	return;
}
