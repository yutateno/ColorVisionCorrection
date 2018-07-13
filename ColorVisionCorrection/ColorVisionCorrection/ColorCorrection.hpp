/*
Project Name    : ColorVisionCorrection
File Name		: ColorCorrection.hpp
Creation Date   : 2018/07/13

Copyright © 2018 yutateno. All rights reserved.

This source code or any portion thereof must not be
reproduced or used in any manner whatsoever.
*/

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
このクラスはFileSearchCreateから渡された画像名から色を変えたのを画像名+拡張子のフォルダに保存するようにする。
*/