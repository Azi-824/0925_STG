//************ �w�b�_�[�t�@�C���ǂݍ��� ************
#include "DxLib.h"
#include "main.hpp"
#include "IMAGE.hpp"
#include"FPS.hpp"
//#include "KEYDOWN.hpp"
#include "ANIMATION.hpp"
//#include "CHARACTOR.hpp"

//*********** �O���[�o���I�u�W�F�N�g ***********
FPS *fps = new FPS(GAME_FPS_SPEED);
//KEYDOWN *keydown = new KEYDOWN();


//*********** �v���O�����ōŏ��Ɏ��s�����֐� ***************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));

	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	IMAGE *jiki = new IMAGE(MY_IMG_DIR_JIKI, MY_IMG_NAME_JIKI_1);
	if (jiki->GetIsLoad() == FALSE) { return -1; };	//�摜�ǂݍ��݃`�F�b�N

	ANIMATION *baku = new ANIMATION(MY_ANIME_DIR_BAKU,MY_ANIME_NAME_BAKU_1,16,16,1, BAKU_1_HEIGHT,BAKU_1_HEIGHT,0.05,true);
	if (baku->GetIsLoad() == false) {return -1; };//�摜�ǂݍ��݃`�F�b�N


	while (TRUE)		//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̎��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		fps->Update();		//FPS�̏���[�X�V]

		//�������������� �Q�[���̃V�[���������� ����������������

		jiki->Draw();
		baku->Draw();
		

		//���������������@�Q�[���̃V�[�������܂� ����������������

		fps->Draw(0, 0);				//FPS�̏���(�`��)

		ScreenFlip();					//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();					//FPS�̏���(�҂�)

	}

	delete jiki;			//jiki��j��
	delete baku;			//baku��j��

	delete fps;				//fps��j��

	DxLib_End();			//DX���C�u�����g�p�̏I������

	return 0;
}