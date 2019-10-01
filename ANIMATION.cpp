//ANIMATION.cpp
//�A�j���[�V�����N���X

//************ �w�b�_�[�t�@�C���ǂݍ��� **************
#include "ANIMATION.hpp"
#include "FPS.hpp"

//********** �N���X�̒�` ******************

//�R���X�g���N�^
//����:const char *:�摜�̃f�B���N�g��
//����:const char *:�摜�̖��O
//����:int:�摜�̑�������
//����:int:�摜�̉������̕�����
//����:int:�摜�̏c�����̕�����
//����:int:�摜�̕������ꂽ���̑傫��
//����:int:�摜�̕������ꂽ�c�̑傫��
//����:double:���̉摜�ɕύX���鑬��
//����:bool:�A�j���[�V���������[�v���邩�ǂ���
ANIMATION::ANIMATION(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SpritNumY, int SpritWidth, int SpritHeight, double ChangeSpeed, bool IsLoop)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O

	this->Handle.resize(SplitNumALL);			//resize:vector�̗v�f����ύX����
	this->Handle_itr = this->Handle.begin();	//�擪�̃|�C���^������

	this->X = 0;			//X�ʒu
	this->Y = 0;			//Y�ʒu
	this->Width = 0;		//��
	this->Height = 0;		//����
	this->NextChangeSpeed = 0.0;	//�摜��ς��鑬��

	this->ChangeMaxCnt = (int)(ChangeSpeed*fps->Getvalue());	//�A�j���[�V��������t���[���̍ő�l
	this->ChangeCnt = 0;										//�A�j���[�V��������t���[���̃J�E���g

	this->IsAnimeLoop = IsLoop;			//�A�j���[�V�����̓��[�v����?

	this->IsLoad = false;				//�ǂݍ��߂����H

	this->IsDraw = false;				//�`�悵�Ă͂����Ȃ�

	//�摜��ǂݍ���
	std::string LoadFilePath;			//�摜�̃t�@�C���p�X���쐬
	LoadFilePath += dir;
	LoadFilePath += name;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadFilePath.c_str(), SplitNumALL, SpritNumX, SpritNumY, SpritWidth, SpritHeight, &this->Handle[0]);

	if (this->Handle[0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//�G���[���b�Z�[�W���쐬
		ErrorMsg += TEXT('\n');		//���s
		ErrorMsg += LoadFilePath;	//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),		//char *��Ԃ�
			TEXT(ANIMATION_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadFilePath;		//�摜�̃p�X��ݒ�
	this->FileName = name;				//�摜�̖��O��ݒ�

	GetGraphSize(
		this->Handle[0],	//���̃n���h���̉摜�̑傫�����擾
		&this->Width,		//Width�̃A�h���X��n��
		&this->Height		//Height�̃A�h���X��n��
	);

	this->NextChangeSpeed = ChangeSpeed;		//�摜��ς��鑬��

	this->IsLoad = true;		//�ǂݍ��߂�

	this->IsDraw = true;		//�`�悵�Ă悢

	return;
}

//�f�X�g���N�^
ANIMATION::~ANIMATION()
{
	//�͈̓x�[�X��for���[�v
	//vector�Ȃǂ̃R���e�i�N���X�Ŏg�p�ł���
	//auto:�^���_:�R���p�C���������͐��_���Č^�����߂Ă����
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);
	}

	//vector�̃������J�����s��
	std::vector<int> v;			//���vector���쐬����
	this->Handle.swap(v);		//��ƒ��g�����ւ���

	return;
}

//�t�@�C���̖��O���擾
std::string ANIMATION::GetFileName(void)
{
	return this->FileName;
}

//X�ʒu��ݒ�
void ANIMATION::SetX(int numX)
{
	this->X = numX;	return;
}

//Y�ʒu��ݒ�
void ANIMATION::SetY(int numY)
{
	this->Y = numY;	return;
}

//X�ʒu���擾
int ANIMATION::GetX(void)
{
	return this->X;
}

//Y�ʒu���擾
int ANIMATION::GetY(void)
{
	return this->Y;
}

//�����擾
int ANIMATION::GetWidth(void)
{
	return this->Width;
}

//�������擾
int ANIMATION::GetHeight(void)
{
	return this->Height;
}

//�ǂݍ��߂��H
bool ANIMATION::GetIsLoad(void)
{
	return this->IsLoad;
}

//�摜��`��
void ANIMATION::Draw(void)
{
	if (this->IsDraw == true)	//�`�悵�Ă悢�Ȃ�
	{
		DrawGraph(this->X, this->Y, *this->Handle_itr, TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��

		if (this->ChangeCnt == this->ChangeMaxCnt)	//���̉摜��\������Ƃ���������
		{
			//this->Handle.end()�́A�Ō�̗v�f��1���̃C�e���[�^��Ԃ��̂ŁA-1���Ă���B
			if (this->Handle_itr == this->Handle.end() - 1)	//�C�e���[�^(�|�C���^)���Ō�̗v�f�̂Ƃ���
			{
				if (this->IsAnimeLoop == false)	//�A�j���[�V�������[�v���Ȃ��Ȃ�
				{
					this->IsDraw = false;		//�`�����߂�
				}

				//����̕`��ɔ����āA�擪�̉摜�ɖ߂��Ă���
				this->Handle_itr = this->Handle.begin();		//�C�e���[�^(�|�C���^)��v�f�̍ŏ��ɖ߂�

			}
			else
			{
				this->Handle_itr++;		//���̃C�e���[�^(�|�C���^)(���̉摜)�Ɉړ�����
			}

			this->ChangeCnt = 0;		//�J�E���g������
		}
		else
		{
			this->ChangeCnt++;			//�J�E���g�A�b�v
		}
	}
	return;
}
