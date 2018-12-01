#include "DxLib.h"

// 画像の対応する最大サイズ
int XSize = 2048;
int YSize = 2048;


// 元なるRGBをピクセル単位で取得
int RGBA[2048][2048][4];

// RGBからXYZに変換したもの
double XYZ[2048][2048][3];

// LMSから直接P型異常のXYZに変換
double PXYZ[2048][2048][3];

// LMSから直接D型異常のXYZに変換
double DXYZ[2048][2048][3];

// XYZからLMSに変換したもの
double LMS[2048][2048][3];

// LMSからP型異常に変換したもの
double PLMS[2048][2048][3];

// LMSからD型異常に変換したもの
double DLMS[2048][2048][3];

// DXYZからRGBに変換したもの
int DRGB[2048][2048][3];

// PLMSからRGBに変換したもの
int PRGB[2048][2048][3];


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);					// ウィンドウにする
	SetGraphMode(XSize, YSize, 32);			// 画面サイズを決める

	DxLib_Init();						// 初期化処理

	SetDrawScreen(DX_SCREEN_BACK);		// 裏描画

	SetAlwaysRunFlag(true);				// 常にアクティブにする

	int monochrome;						// 白黒に生成するためのもので、RGBを一瞬保持するための仮置き

	bool jpgExtension = false;			// jpgでは透過できないのでそれの判断
	
	int handle = -1;
	int normal = -1;


	// 画像のドラッグアンドドロップで起動していないとき
	if (__argc == 1)
	{
		// ここで保存する画像を決める(拡張子探索にしてもいいが楽したいので簡単にする)
		// pngでロードする
		normal = LoadGraph("Media.png");
		handle = LoadSoftImage("Media.png");

		// 失敗したのでjpgでロードする
		if (normal == -1)
		{
			normal = LoadGraph("Media.jpg");
			handle = LoadSoftImage("Media.jpg");
			jpgExtension = true;
		}

		// 失敗したのでbmpでロードする
		if (normal == -1)
		{
			normal = LoadGraph("Media.bmp");
			handle = LoadSoftImage("Media.bmp");
			jpgExtension = true;
		}

		// エラー終了
		if (normal == -1)
		{
			return -1;
		}
	}
	// ドラッグアンドドロップで起動したとき
	else
	{
		// ここで保存する画像を決める(ちゃんとしたものを作りたいが簡単にする)

		const char *mediaFile = NULL;
		const char *dragFile = __argv[1];
		int ch = '\\';
		mediaFile = strrchr(dragFile, ch) + 1;

		const char *Pexe = NULL;

		// pngで探索する
		Pexe = strstr(mediaFile, "png");

		// ロードする
		if (Pexe != NULL)
		{
			normal = LoadGraph(mediaFile);
			handle = LoadSoftImage(mediaFile);
		}
		// 探索して見つからなかった
		else
		{
			// jpgで探索する
			Pexe = strstr(mediaFile, "jpg");

			// ロードする
			if (Pexe != NULL)
			{
				normal = LoadGraph(mediaFile);
				handle = LoadSoftImage(mediaFile);
				jpgExtension = true;
			}
			// 探索して見つからなかった
			else
			{
				// bmpで探索する
				Pexe = strstr(mediaFile, "bmp");
				
				// ロードする
				if (Pexe != NULL)
				{
					normal = LoadGraph(mediaFile);
					handle = LoadSoftImage(mediaFile);
					jpgExtension = true;
				}
			}
		}

		// ロードできなかったのでエラー終了する
		if (normal == -1)
		{
			return -1;
		}
		Pexe = NULL;
		dragFile = NULL;
		mediaFile = NULL;
	}

	

	GetSoftImageSize(handle, &XSize, &YSize);			// 画像のサイズを調べる

	// 空の画像をサイズ指定した状態で作る
	int changeHandle_D = MakeARGB8ColorSoftImage(XSize, YSize);
	int changeHandle_P = MakeARGB8ColorSoftImage(XSize, YSize);
	int changeHandle_Mono = MakeARGB8ColorSoftImage(XSize, YSize);

	int completeHandle_D, completeHandle_P, completeHandle_Mono;		// 空の画像から作った画像を渡すもの


	// ピクセルごとの色を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			GetPixelSoftImage(handle, x, y, &RGBA[x][y][0], &RGBA[x][y][1], &RGBA[x][y][2], &RGBA[x][y][3]);
		}
	}

	DeleteSoftImage(handle);		// 用がないので削除


	// XYZ色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			XYZ[x][y][0] = (0.4124*RGBA[x][y][0] + 0.3576*RGBA[x][y][1] + 0.1805*RGBA[x][y][2]);
			XYZ[x][y][1] = (0.2126*RGBA[x][y][0] + 0.7152*RGBA[x][y][1] + 0.0722*RGBA[x][y][2]);
			XYZ[x][y][2] = (0.0193*RGBA[x][y][0] + 0.1192*RGBA[x][y][1] + 0.9505*RGBA[x][y][2]);
		}
	}


	// LMS色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			LMS[x][y][0] = (0.15514*XYZ[x][y][0] + 0.54312*XYZ[x][y][1] + (-0.03286)*XYZ[x][y][2]);
			LMS[x][y][1] = (-0.15514*XYZ[x][y][0] + 0.45684*XYZ[x][y][1] + 0.03286*XYZ[x][y][2]);
			LMS[x][y][2] = (0.0*XYZ[x][y][0] + 0.0*XYZ[x][y][1] + 0.01608*XYZ[x][y][2]);
		}
	}


	// P型異常のLMS色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			PLMS[x][y][0] = (0.0*LMS[x][y][0] + 2.02344*LMS[x][y][1] + (-2.52581)*LMS[x][y][2]);
			PLMS[x][y][1] = (0.0*LMS[x][y][0] + 1.0*LMS[x][y][1] + 0.0*LMS[x][y][2]);
			PLMS[x][y][2] = (0.0*LMS[x][y][0] + 0.0*LMS[x][y][1] + 1.0*LMS[x][y][2]);
		}
	}


	// D型異常のLMS色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			DLMS[x][y][0] = (1.0*LMS[x][y][0] + 0.0*LMS[x][y][1] + 0.0*LMS[x][y][2]);
			DLMS[x][y][1] = (0.494207*LMS[x][y][0] + 0.0*LMS[x][y][1] + 1.24827*LMS[x][y][2]);
			DLMS[x][y][2] = (0.0*LMS[x][y][0] + 0.0*LMS[x][y][1] + 1.0*LMS[x][y][2]);
		}
	}


	// P型異常のXYZ色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			PXYZ[x][y][0] = (2.9448129066068*PLMS[x][y][0] + (-3.5009779919365)*PLMS[x][y][1] + 13.172182147148*PLMS[x][y][2]);
			PXYZ[x][y][1] = (1.0000400016001*PLMS[x][y][0] + 1.0000400016001*PLMS[x][y][1] + 0 * PLMS[x][y][2]);
			PXYZ[x][y][2] = (0.0*PLMS[x][y][0] + 0.0*PLMS[x][y][1] + 62.189054726368*PLMS[x][y][2]);
		}
	}


	// D型異常のXYZ色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			DXYZ[x][y][0] = (2.9448129066068*DLMS[x][y][0] + (-3.5009779919365)*DLMS[x][y][1] + 13.172182147148*DLMS[x][y][2]);
			DXYZ[x][y][1] = (1.0000400016001*DLMS[x][y][0] + 1.0000400016001*DLMS[x][y][1] + 0 * DLMS[x][y][2]);
			DXYZ[x][y][2] = (0.0*DLMS[x][y][0] + 0.0*DLMS[x][y][1] + 62.189054726368*DLMS[x][y][2]);
		}
	}


	// D型異常のRGB色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			DRGB[x][y][0] = (int)(3.2410*DXYZ[x][y][0] + (-1.5374)*DXYZ[x][y][1] + (-0.4986)*DXYZ[x][y][2]);
			DRGB[x][y][1] = (int)(-0.9692*DXYZ[x][y][0] + 1.8760*DXYZ[x][y][1] + 0.0416*DXYZ[x][y][2]);
			DRGB[x][y][2] = (int)(0.0556*DXYZ[x][y][0] + (-0.2040)*DXYZ[x][y][1] + 1.0570*DXYZ[x][y][2]);

			DrawPixelSoftImage(changeHandle_D, x, y, DRGB[x][y][0], DRGB[x][y][1], DRGB[x][y][2], -(jpgExtension * -255) + RGBA[x][y][3]);			// 空の画像に色をセットする
		}
	}
	completeHandle_D = CreateGraphFromSoftImage(changeHandle_D);			// Softimageからグラフィックハンドルを作成する
	DeleteSoftImage(changeHandle_D);			// いらなくなったので削除


	// P型異常のRGB色空間を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			PRGB[x][y][0] = (int)(3.2410*PXYZ[x][y][0] + (-1.5374)*PXYZ[x][y][1] + (-0.4986)*PXYZ[x][y][2]);
			PRGB[x][y][1] = (int)(-0.9692*PXYZ[x][y][0] + 1.8760*PXYZ[x][y][1] + 0.0416*PXYZ[x][y][2]);
			PRGB[x][y][2] = (int)(0.0556*PXYZ[x][y][0] + (-0.2040)*PXYZ[x][y][1] + 1.0570*PXYZ[x][y][2]);

			DrawPixelSoftImage(changeHandle_P, x, y, PRGB[x][y][0], PRGB[x][y][1], PRGB[x][y][2], -(jpgExtension * -255) + RGBA[x][y][3]);			// 空の画像に色をセットする
		}
	}
	completeHandle_P = CreateGraphFromSoftImage(changeHandle_P);			// Softimageからグラフィックハンドルを作成する
	DeleteSoftImage(changeHandle_P);			// いらなくなったので削除


	// 白黒画像を得る
	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			monochrome = (int)(RGBA[x][y][0] * 0.299 + RGBA[x][y][1] * 0.587 + RGBA[x][y][2] * 0.114);

			DrawPixelSoftImage(changeHandle_Mono, x, y, monochrome, monochrome, monochrome, -(jpgExtension * -255) + RGBA[x][y][3]);			// 空の画像に色をセットする
		}
	}
	completeHandle_Mono = CreateGraphFromSoftImage(changeHandle_Mono);			// Softimageからグラフィックハンドルを作成する
	DeleteSoftImage(changeHandle_Mono);			// いらなくなったので削除


	int count = 0;			// 描画して確認するなどの一連の動作を時間で行うための変数

	// 本編
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		count++;		// 加算する

		// 通常画像
		if (count <= 20)
		{
			DrawGraph(0, 0, normal, true);		// 表示
			// 保存
			if (count == 20) 
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\normal.jpg");			// JPG
				SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\normal.bmp");		// BMP
				SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\normal.png");		// PNG
			}
		}
		// D型色覚画像
		else if (count <= 40)
		{
			DrawGraph(0, 0, completeHandle_D, true);		// 表示
			// 保存
			if (count == 40)
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\D.jpg");		// JPG
				SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\D.bmp");		// BMP
				SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\D.png");		// PNG
			}
		}
		// P型色覚画像
		else if (count <= 60)
		{
			DrawGraph(0, 0, completeHandle_P, true);		// 表示
			// 保存
			if (count == 60)
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\P.jpg");			// JPG
				SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\P.bmp");		// BMP
				SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\P.png");		// PNG
			}
		}
		// 白黒画像
		else if (count <= 80)
		{
			DrawGraph(0, 0, completeHandle_Mono, true);		// 表示
			// 保存
			if (count == 80)
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\whiteblack.jpg");			// JPG
				SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\whiteblack.bmp");		// BMP
				SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\whiteblack.png");		// PNG
			}
		}
		else break;
	}
	DeleteGraph(completeHandle_Mono);
	DeleteGraph(completeHandle_P);
	DeleteGraph(completeHandle_D);
	DeleteGraph(normal);
	
	DxLib_End();
	return 0;
}