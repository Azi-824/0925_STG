//************ �w�b�_�[�t�@�C���ǂݍ��� ************
#include "DxLib.h"
#include "main.hpp"
#include "IMAGE.hpp"
#include"FPS.hpp"

//*********** �O���[�o���I�u�W�F�N�g ***********
FPS *fps = new(GAME_FPS_SPEED);


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

	while (TRUE)		//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̎��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		fps->Update();		//FPS�̏���[�X�V]

		//�������������� �Q�[���̃V�[���������� ����������������



		//���������������@�Q�[���̃V�[�������܂� ����������������
	}

	return 0;
}