//************ ヘッダーファイル読み込み ************
#include "DxLib.h"
#include "main.hpp"
#include "IMAGE.hpp"
#include"FPS.hpp"
//#include "KEYDOWN.hpp"
#include "ANIMATION.hpp"
//#include "CHARACTOR.hpp"

//*********** グローバルオブジェクト ***********
FPS *fps = new FPS(GAME_FPS_SPEED);
//KEYDOWN *keydown = new KEYDOWN();


//*********** プログラムで最初に実行される関数 ***************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));

	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	IMAGE *jiki = new IMAGE(MY_IMG_DIR_JIKI, MY_IMG_NAME_JIKI_1);
	if (jiki->GetIsLoad() == FALSE) { return -1; };	//画像読み込みチェック

	ANIMATION *baku = new ANIMATION(MY_ANIME_DIR_BAKU,MY_ANIME_NAME_BAKU_1,16,16,1, BAKU_1_HEIGHT,BAKU_1_HEIGHT,0.05,true);
	if (baku->GetIsLoad() == false) {return -1; };//画像読み込みチェック


	while (TRUE)		//無限ループ
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーの時、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		fps->Update();		//FPSの処理[更新]

		//▼▼▼▼▼▼▼ ゲームのシーンここから ▼▼▼▼▼▼▼▼

		jiki->Draw();
		baku->Draw();
		

		//▲▲▲▲▲▲▲　ゲームのシーンここまで ▲▲▲▲▲▲▲▲

		fps->Draw(0, 0);				//FPSの処理(描画)

		ScreenFlip();					//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();					//FPSの処理(待つ)

	}

	delete jiki;			//jikiを破棄
	delete baku;			//bakuを破棄

	delete fps;				//fpsを破棄

	DxLib_End();			//DXライブラリ使用の終了処理

	return 0;
}