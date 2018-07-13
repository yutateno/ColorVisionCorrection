#pragma once
#include <vector>
#include <string>

class ColorCorrection
{
private:
	std::vector<std::string> drawName;
	std::string createFolderName;

public:
	ColorCorrection();
	ColorCorrection(std::vector<std::string> drawName);
	~ColorCorrection();

	void Update();
};

/*
���̃N���X��FileSearchCreate����n���ꂽ�摜������F��ς����̂��摜��+�g���q�̃t�H���_�ɕۑ�����悤�ɂ���B
*/