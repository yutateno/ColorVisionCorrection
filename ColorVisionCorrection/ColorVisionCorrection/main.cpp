/*
Project Name    : ColorVisionCorrection
File Name		: main.cpp
Creation Date   : 2018/07/13

Copyright © 2018 yutateno. All rights reserved.

This source code or any portion thereof must not be
reproduced or used in any manner whatsoever.
*/

#include "DxLib.h"
#include "ColorCorrection.hpp"
#include "FileSearchCreate.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 16);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);


	FileSearchCreate* fileSearchCreate = new FileSearchCreate();
	// ColorCorrection* colorCorrection = new ColorCorrection();


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		fileSearchCreate->Update();
	}

	delete fileSearchCreate;
	// delete colorCorrection;

	DxLib_End();
	return 0;
}