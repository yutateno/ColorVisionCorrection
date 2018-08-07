/*
透過画像は考慮していません。他プロジェクトとして作る予定です。
*/

#include "DxLib.h"

int XSize = 2048;
int YSize = 2048;

int RGBA[2048][2048][4];			// 元なるRGBをピクセル単位で取得
double XYZ[2048][2048][3];		// RGBからXYZに変換したもの
double PXYZ[2048][2048][3];		// LMSから直接P型異常のXYZに変換
double DXYZ[2048][2048][3];		// LMSから直接D型異常のXYZに変換
double LMS[2048][2048][3];		// XYZからLMSに変換したもの
double PLMS[2048][2048][3];		// LMSからP型異常に変換したもの
double DLMS[2048][2048][3];		// LMSからD型異常に変換したもの
int DRGB[2048][2048][3];			// DXYZからRGBに変換したもの
int PRGB[2048][2048][3];			// PLMSからRGBに変換したもの

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(XSize, YSize, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	SetFontSize(64);

	SetAlwaysRunFlag(true);

	int tmp[3];						// 白黒に生成するためのもので、RGBを一瞬保持するための仮置き

	// ここで保存する画像を決める
	int handle = LoadSoftImage("Media.jpg");

	GetSoftImageSize(handle, &XSize, &YSize);

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			GetPixelSoftImage(handle, x, y, &RGBA[x][y][0], &RGBA[x][y][1], &RGBA[x][y][2], &RGBA[x][y][3]);
		}
	}

	DeleteSoftImage(handle);

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			XYZ[x][y][0] = (0.4124*RGBA[x][y][0] + 0.3576*RGBA[x][y][1] + 0.1805*RGBA[x][y][2]);
			XYZ[x][y][1] = (0.2126*RGBA[x][y][0] + 0.7152*RGBA[x][y][1] + 0.0722*RGBA[x][y][2]);
			XYZ[x][y][2] = (0.0193*RGBA[x][y][0] + 0.1192*RGBA[x][y][1] + 0.9505*RGBA[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			LMS[x][y][0] = (0.15514*XYZ[x][y][0] + 0.54312*XYZ[x][y][1] + (-0.03286)*XYZ[x][y][2]);
			LMS[x][y][1] = (-0.15514*XYZ[x][y][0] + 0.45684*XYZ[x][y][1] + 0.03286*XYZ[x][y][2]);
			LMS[x][y][2] = (0.0*XYZ[x][y][0] + 0.0*XYZ[x][y][1] + 0.01608*XYZ[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			PLMS[x][y][0] = (0.0*LMS[x][y][0] + 2.02344*LMS[x][y][1] + (-2.52581)*LMS[x][y][2]);
			PLMS[x][y][1] = (0.0*LMS[x][y][0] + 1.0*LMS[x][y][1] + 0.0*LMS[x][y][2]);
			PLMS[x][y][2] = (0.0*LMS[x][y][0] + 0.0*LMS[x][y][1] + 1.0*LMS[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			DLMS[x][y][0] = (1.0*LMS[x][y][0] + 0.0*LMS[x][y][1] + 0.0*LMS[x][y][2]);
			DLMS[x][y][1] = (0.494207*LMS[x][y][0] + 0.0*LMS[x][y][1] + 1.24827*LMS[x][y][2]);
			DLMS[x][y][2] = (0.0*LMS[x][y][0] + 0.0*LMS[x][y][1] + 1.0*LMS[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			PXYZ[x][y][0] = (2.9448129066068*PLMS[x][y][0] + (-3.5009779919365)*PLMS[x][y][1] + 13.172182147148*PLMS[x][y][2]);
			PXYZ[x][y][1] = (1.0000400016001*PLMS[x][y][0] + 1.0000400016001*PLMS[x][y][1] + 0 * PLMS[x][y][2]);
			PXYZ[x][y][2] = (0.0*PLMS[x][y][0] + 0.0*PLMS[x][y][1] + 62.189054726368*PLMS[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			DXYZ[x][y][0] = (2.9448129066068*DLMS[x][y][0] + (-3.5009779919365)*DLMS[x][y][1] + 13.172182147148*DLMS[x][y][2]);
			DXYZ[x][y][1] = (1.0000400016001*DLMS[x][y][0] + 1.0000400016001*DLMS[x][y][1] + 0 * DLMS[x][y][2]);
			DXYZ[x][y][2] = (0.0*DLMS[x][y][0] + 0.0*DLMS[x][y][1] + 62.189054726368*DLMS[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			DRGB[x][y][0] = (int)(3.2410*DXYZ[x][y][0] + (-1.5374)*DXYZ[x][y][1] + (-0.4986)*DXYZ[x][y][2]);
			DRGB[x][y][1] = (int)(-0.9692*DXYZ[x][y][0] + 1.8760*DXYZ[x][y][1] + 0.0416*DXYZ[x][y][2]);
			DRGB[x][y][2] = (int)(0.0556*DXYZ[x][y][0] + (-0.2040)*DXYZ[x][y][1] + 1.0570*DXYZ[x][y][2]);
		}
	}

	for (int x = 0; x < XSize; ++x)
	{
		for (int y = 0; y < YSize; ++y)
		{
			PRGB[x][y][0] = (int)(3.2410*PXYZ[x][y][0] + (-1.5374)*PXYZ[x][y][1] + (-0.4986)*PXYZ[x][y][2]);
			PRGB[x][y][1] = (int)(-0.9692*PXYZ[x][y][0] + 1.8760*PXYZ[x][y][1] + 0.0416*PXYZ[x][y][2]);
			PRGB[x][y][2] = (int)(0.0556*PXYZ[x][y][0] + (-0.2040)*PXYZ[x][y][1] + 1.0570*PXYZ[x][y][2]);
		}
	}

	int count = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		count++;
		// 通常
		if (count <= 60)
		{
			for (int x = 0; x < XSize; ++x)
			{
				for (int y = 0; y < YSize; ++y)
				{
					for (int i = 0; i < 3; ++i)
					{
						tmp[i] = RGBA[x][y][i];
					}
					DrawPixel(x, y, GetColor(tmp[0], tmp[1], tmp[2]));
				}
			}
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "通常");
			if (count == 50) 
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\normal.jpg");			// JPG
				// SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\normal.bmp");		// BMP
				// SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\normal.png");		// PNG
			}
		}
		else if (count <= 120)
		{
			for (int x = 0; x < XSize; ++x)
			{
				for (int y = 0; y < YSize; ++y)
				{
					for (int i = 0; i < 3; ++i)
					{
						tmp[i] = DRGB[x][y][i];
					}
					DrawPixel(x, y, GetColor(tmp[0], tmp[1], tmp[2]));
				}
			}
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "D型色覚");
			if (count == 100)
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\D.jpg");			// JPG
				// SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\D.bmp");		// BMP
				// SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\D.png");		// PNG
			}
		}
		else if (count <= 180)
		{
			for (int x = 0; x < XSize; ++x)
			{
				for (int y = 0; y < YSize; ++y)
				{
					for (int i = 0; i < 3; ++i)
					{
						tmp[i] = PRGB[x][y][i];
					}
					DrawPixel(x, y, GetColor(tmp[0], tmp[1], tmp[2]));
				}
			}
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "P型色覚");
			if (count == 150)
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\P.jpg");			// JPG
				// SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\P.bmp");		// BMP
				// SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\P.png");		// PNG
			}
		}
		else if (count <= 240)
		{
			for (int x = 0; x < XSize; ++x)
			{
				for (int y = 0; y < YSize; ++y)
				{
					tmp[0] = (int)(RGBA[x][y][0] * 0.299 + RGBA[x][y][1] * 0.587 + RGBA[x][y][2] * 0.114);
					tmp[1] = tmp[2] = tmp[0];
					DrawPixel(x, y, GetColor(tmp[0], tmp[1], tmp[2]));
				}
			}
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "白黒");
			if (count == 200)
			{
				SaveDrawScreenToJPEG(0, 0, XSize, YSize, "correction\\whiteblack.jpg");			// JPG
				// SaveDrawScreenToBMP(0, 0, XSize, YSize, "correction\\whiteblack.bmp");		// BMP
				// SaveDrawScreenToPNG(0, 0, XSize, YSize, "correction\\whiteblack.png");		// PNG
			}
		}
		else break;
	}

	DxLib_End();
	return 0;
}