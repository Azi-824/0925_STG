//ANIMATION.hpp
//アニメーションクラス

#pragma once


//************ ヘッダーファイル読み込み ************
#include "DxLib.h"
#include <string>
#include <vector>

//********* マクロ定義:画像のファイルパスと名前 ************
#define MY_ANIME_DIT_BAKU				R"(.\MY_ANIME\bakuhatsu\)"		//爆発の画像ファイルの場所

#define MY_ANIME_NAME_BAKU_1			R"(bakuhatsu_01_png)"			//爆発の画像の名前
#define BAKU_1_WIDTH	70		//分割する幅の大きさ
#define BAKU_1_HEIGHT	64		//分割する高さの大きさ

//*********** マクロ定義:エラーメッセージ **************
#define ANIMATION_ERROR_TITLE	"ANIMATION_ERROR"			//エラータイトル
#define ANIMATION_ERROR_MSG		"アニメーションが読み込めませんでした"//エラーメッセージ

//*********** クラスの定義 *******************
class ANIMATION
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	std::vector<int> Handle;		//ハンドル

	std::vector<int>::iterator Handle_itr;	//ハンドルのイテレータ(ポインタ)

	int X;						//X位置
	int Y;						//Y位置
	int Width;					//幅
	int Height;					//高さ

	double NextChangeSpeed;		//アニメーションを変更する速さ(秒)
	int ChangeMaxCnt;			//アニメーションするフレームの最大値
	int ChangeCnt;				//アニメーションするフレームのカウント

	bool IsAnimeLoop;			//アニメーションはループする？

	bool IsLoad;				//読み込めたか？

	bool IsDraw;				//描画しても良い？

public:
	ANIMATION(const char *, const char *, int, int, int, int, int, double, bool);	//コンストラクタ
	virtual ~ANIMATION();	//デストラクタ

	std::string GetFileName(void);	//名前を取得

	void SetX(int);					//X位置を設定
	void SetY(int);					//Y位置を設定
	int GetX(void);					//X位置を取得
	int GetY(void);					//Y位置を取得
	int GetWidth(void);				//幅を取得
	int GetHeight(void);			//高さを取得

	bool GetIsLoad(void);			//読み込めた？

	void Draw(void);				//画像を描画
};
