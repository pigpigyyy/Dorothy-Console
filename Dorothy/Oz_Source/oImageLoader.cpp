#pragma once
#include <Windows.h>
#include <fstream>
using std::ios;
using std::fstream;
#include "oImage.h"
using Dorothy::oImage;

namespace Dorothy
{
	DLLEXPORT oImage* oCreateImageFromBMP24( const char* filename )
	{
		const static DWORD ColorList[] ={0x00000000,0x00000080,0x00008000,0x00008080,
			0x00800000,0x00800080,0x00808000,0x00C0C0C0,0x00808080,0x000000FF,0x0000FF00,
			0x0000FFFF,0x00FF0000,0x00FF00FF,0x00FFFF00,0x00FFFFFF};
		HBITMAP hBitmap = (HBITMAP)LoadImage(0,filename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		if (hBitmap == NULL)
		{
			return NULL;
		}
		BITMAP kBmpInfo;
		GetObject(hBitmap, sizeof(BITMAP), &kBmpInfo);
		HDC hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, hBitmap);
		oUInt32 iWidth = kBmpInfo.bmWidth;
		oUInt32 iHeight = kBmpInfo.bmHeight;
		oImage* pkImage = new oImage();
		pkImage->Create(iWidth,iHeight);
		for (oUInt32 iY = 0;iY < iHeight;iY++)
		{
			for (oUInt32 iX = 0;iX < iWidth;iX++)
			{
				oColor iColor = COLOR_NONE;
				DWORD iCheck = GetPixel(hdcMem,iX,iY);
				iCheck = ((iCheck&0x000000FF)<<16) | (iCheck&0x0000FF00) | (iCheck>>16);
				if (iCheck == 0x00808080)
				{
					iColor = 0x0080;
				}
				else
				{
					int low = 0,high = 8,mid;
					while (low <= high)
					{
						mid = (high+low)/2;
						if (iCheck == ColorList[mid])
							iColor = (0|mid<<4);
						if (iCheck > ColorList[mid])
							low = mid+1;
						else
							high = mid-1;
					}
					if (iColor == COLOR_NONE)
					{
						low = 9;high = 16;
						while (low <= high)
						{
							mid = (high+low)/2;
							if (iCheck == ColorList[mid])
								iColor = (0|mid<<4);
							if (iCheck > ColorList[mid])
								low = mid+1;
							else
								high = mid-1;
						}
					}
				}
				pkImage->SetColor(iX,iY,iColor);
			}
		}
		DeleteDC(hdcMem);
		DeleteObject((HBITMAP)hBitmap);
		return pkImage;
	}

	DLLEXPORT void oReleaseImage( oImage*& pkImage )
	{
		delete pkImage;
		pkImage = NULL;
	}
}
/*
Black      0x00000000  0x0000
Blue       0x00000080  0x0010
Green      0x00008000  0x0020
Cyan       0x00008080  0x0030
Red        0x00800000  0x0040
Magenta    0x00800080  0x0050
Yellow     0x00808000  0x0060
White      0x00C0C0C0  0x0070
Black   I  0x00808080  0x0080
Blue    I  0x000000FF  0x0090
Green   I  0x0000FF00  0x00A0
Cyan    I  0x0000FFFF  0x00B0
Red     I  0x00FF0000  0x00C0
Magenta I  0x00FF00FF  0x00D0
Yellow  I  0x00FFFF00  0x00E0
White   I  0x00FFFFFF  0x00F0
*/