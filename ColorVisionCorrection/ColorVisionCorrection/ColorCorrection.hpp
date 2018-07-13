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

