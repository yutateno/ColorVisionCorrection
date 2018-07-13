/*
Project Name    : ColorVisionCorrection
File Name		: FileSearchCreate.hpp
Creation Date   : 2018/07/13

Copyright © 2018 yutateno. All rights reserved.

This source code or any portion thereof must not be
reproduced or used in any manner whatsoever.
*/

#pragma once
#include <string>
#include <vector>

class FileSearchCreate
{
private:
	//char Path[MAX_PATH + 1];	// 実行ファイルの完全パスを取得する変数

	//char drive[MAX_PATH + 1]	// ドライブ
	//	, dir[MAX_PATH + 1]		// ディレクトリパス
	//	, fname[MAX_PATH + 1]	// ファイル名
	//	, ext[MAX_PATH + 1];	// ファイル名の拡張子

	

	void SearchGameFile(std::string gamePath);
	void SearchMediaFile(std::string gamePath);

public:
	FileSearchCreate();
	~FileSearchCreate();

	void Update();
};

/*
このクラスはpngとjpgとbmpを調べて、それの[~.png]までをvectorのstring変数に保存するようにする。
あとついでにそのpngの隣に[画像名+png]というフォルダを作成する。
保存したのをColorCorrectionクラスに渡す。
*/