#pragma once
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

	

	void SearchGameFile(std::string gamePath);
	void SearchMediaFile(std::string gamePath);

public:
	FileSearchCreate();
	~FileSearchCreate();

	void Update();
};

