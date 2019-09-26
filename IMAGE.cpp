// IMAGE.cpp


//********** �w�b�_�[�t�@�C���̓ǂݍ��� ************
#include"IMAGE.hpp"

//********** �N���X�̒�` *************

//�R���X�g���N�^
//����: const char* :�摜�̃f�B���N�g��
//����: const char* :�摜�̖��O
IMAGE::IMAGE(const char *dir, const char *name)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O

	this->Handle = -1;		//�n���h��

	this->X = 0;			//X�ʒu
	this->Y = 0;			//Y�ʒu
	this->Width = 0;		//��
	this->Height = 0;		//����

	this->IsLoad = false;	//�ǂݍ��߂����H

	//�摜��ǂݍ���
	std::string LoadfilePath;	//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle = LoadGraph(LoadfilePath.c_str());	//�摜��ǂݍ���

	if (this->Handle == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(IMAGE_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');					//���s
		ErrorMsg += LoadfilePath;				//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char *��Ԃ�
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//�摜�̃p�X��ݒ�
	this->FileName = name;				//�摜�̖��O��ݒ�

	GetGraphSize(
		this->Handle,		//���̃n���h���̉摜�̑傫�����擾
		&this->Width,		//Width�̃A�h���X��n��
		&this->Height		//Height�̃A�h���X��n��
	);

	this->IsLoad = true;	//�ǂݍ��߂�

	return;
}

//�f�X�g���N�^
IMAGE::IMAGE()
{
	DeleteGraph(this->Handle);		//�ǂݍ��񂾉摜���폜
	return;
}

//�t�@�C���̖��O���擾
std::string IMAGE::GetFileName(void)
{
	return this->FileName;
}

//X�ʒu��ݒ�
void IMAGE::SetX(int numX)
{
	this->X = numX;	return;
}

//Y�ʒu��ݒ�
void IMAGE::SetY(int numY)
{
	this->Y = numY;	return;
}

//X�ʒu���擾
int IMAGE::GetX(void)
{
	return this->X;
}

//Y�ʒu���擾
int IMAGE::GetY(void)
{
	return this->Y;
}

//�����擾
int IMAGE::GetWidth(void)
{
	return this->Width;
}

//�������擾
int IMAGE::GetHeight(void)
{
	return this->Height;
}

//�ǂݍ��߂��H
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//�摜��`��
void IMAGE::Draw(void)
{
	DrawGraph(this->X, this->Y, this->Handle, TRUE);
	return;
}