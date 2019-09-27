//************ ヘッダーファイル読み込み ************
#include "DxLib.h"
#include "main.hpp"
#include "IMAGE.hpp"
#include"FPS.hpp"

//*********** グローバルオブジェクト ***********
FPS *fps = new(GAME_FPS_SPEED);


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

	while (TRUE)		//無限ループ
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーの時、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		fps->Update();		//FPSの処理[更新]

		//▼▼▼▼▼▼▼ ゲームのシーンここから ▼▼▼▼▼▼▼▼



		//▲▲▲▲▲▲▲　ゲームのシーンここまで ▲▲▲▲▲▲▲▲
	}

	return 0;
}