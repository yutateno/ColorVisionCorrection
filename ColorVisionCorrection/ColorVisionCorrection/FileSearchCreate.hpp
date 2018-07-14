/*
Project Name    : ColorVisionCorrection
File Name		: FileSearchCreate.hpp
Creation Date   : 2018/07/13

Copyright © 2018 yutateno. All rights reserved.

This source code or any portion thereof must not be
reproduced or used in any manner whatsoever.
*/

#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

class FileSearchCreate
{
private:
	char Path[MAX_PATH + 1];	// 実行ファイルの完全パスを取得する変数

	char drive[MAX_PATH + 1]	// ドライブ
		, dir[MAX_PATH + 1]		// ディレクトリパス
		, fname[MAX_PATH + 1]	// ファイル名
		, ext[MAX_PATH + 1];	// ファイル名の拡張子

	std::vector<std::string> imageFileName;		// 画像のパスを拡張子までの情報を持つ者たち
	int *jpgFile;								// JPG
	int *pngFile;								// PNG
	int *bmpFile;								// BMP
	
	std::string exePath;		// 本exeのパス

	void SearchGameFile(std::string gamePath);													// exeと同じ階層に入れたフォルダ名を調べる
	HANDLE hFind;																				// フォルダを確認する
	int fileCount;																				// フォルダの数を得る
	WIN32_FIND_DATA FindFileData;																// 確認したフォルダの名前を得る

	void SearchMediaFile(std::string gamePath);

public:
	FileSearchCreate();
	~FileSearchCreate();

	void Update();

	// ゲッター
	std::vector<std::string> GetImageFileName();
	int *GetJPGFile();
	int *GetPNGFile();
	int *GetBMPFile();
};

/*
このクラスはpngとjpgとbmpを調べて、それの[~.png]までをvectorのstring変数に保存するようにする。
あとついでにそのpngの隣に[画像名+png]というフォルダを作成する。
保存したのをColorCorrectionクラスに渡す。
*/