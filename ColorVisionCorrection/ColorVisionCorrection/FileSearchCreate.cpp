/*
Project Name    : ColorVisionCorrection
File Name		: FileSearchCreate.cpp
Creation Date   : 2018/07/13

Copyright © 2018 yutateno. All rights reserved.

This source code or any portion thereof must not be
reproduced or used in any manner whatsoever.
*/

#include "FileSearchCreate.hpp"



void FileSearchCreate::SearchGameFile(std::string gamePath)
{
}

void FileSearchCreate::SearchMediaFile(std::string gamePath)
{
}

FileSearchCreate::FileSearchCreate()
{
	jpgFile = new int[50];
	pngFile = new int[50];
	bmpFile = new int[50];

	GetModuleFileName(NULL, Path, MAX_PATH);	// 実行ファイルの完全パスを取得

	_splitpath(Path, drive, dir, fname, ext);	// パス名を構成要素に分解する

	exePath = "";

	exePath.operator+=(drive);
	exePath.operator+=(dir);
}


FileSearchCreate::~FileSearchCreate()
{
	delete[] jpgFile;
	delete[] pngFile;
	delete[] bmpFile;
}

void FileSearchCreate::Update()
{
	DrawFormatString(0, 0, 255, "%s", exePath.c_str());
}

std::vector<std::string> FileSearchCreate::GetImageFileName()
{
	return imageFileName;
}

int *FileSearchCreate::GetJPGFile()
{
	return jpgFile;
}

int *FileSearchCreate::GetPNGFile()
{
	return pngFile;
}

int *FileSearchCreate::GetBMPFile()
{
	return bmpFile;
}
