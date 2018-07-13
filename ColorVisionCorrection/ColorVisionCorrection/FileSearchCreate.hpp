#pragma once
#include <string>
#include <vector>

class FileSearchCreate
{
private:
	char Path[MAX_PATH + 1];	// ���s�t�@�C���̊��S�p�X���擾����ϐ�

	char drive[MAX_PATH + 1]	// �h���C�u
		, dir[MAX_PATH + 1]		// �f�B���N�g���p�X
		, fname[MAX_PATH + 1]	// �t�@�C����
		, ext[MAX_PATH + 1];	// �t�@�C�����̊g���q

	

	void SearchGameFile(std::string gamePath);
	void SearchMediaFile(std::string gamePath);

public:
	FileSearchCreate();
	~FileSearchCreate();

	void Update();
};

/*
���̃N���X��png��jpg��bmp�𒲂ׂāA�����[~.png]�܂ł�vector��string�ϐ��ɕۑ�����悤�ɂ���B
���Ƃ��łɂ���png�ׂ̗�[�摜��+png]�Ƃ����t�H���_���쐬����B
�ۑ������̂�ColorCorrection�N���X�ɓn���B
*/