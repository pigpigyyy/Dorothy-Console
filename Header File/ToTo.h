//Dorothy 1.50
#pragma once
#include <Windows.h>
#pragma comment(lib, "ToTo.lib")

#define DLLIMPORT __declspec(dllimport)

//所有可用的颜色FORECOLOR，BACKCOLOR可以分别和FORE_INTENSITY，BACK_INTENSITY组合
#define COLOR_NONE        0xFFFF

#define FORE_BLACK        0x0000
#define FORE_BLUE         0x0001
#define FORE_GREEN        0x0002
#define FORE_CYAN         0x0003
#define FORE_RED          0x0004
#define FORE_MAGENTA      0x0005
#define FORE_YELLOW       0x0006
#define FORE_WHITE        0x0007

#define FORE_INTENSITY    0x0008

#define BACK_BLACK        0x0000
#define BACK_BLUE         0x0010
#define BACK_GREEN        0x0020
#define BACK_CYAN         0x0030
#define BACK_RED          0x0040
#define BACK_MAGENTA      0x0050
#define BACK_YELLOW       0x0060
#define BACK_WHITE        0x0070

#define BACK_INTENSITY    0x0080

//控制台字体大小
#define FONT_3x5          0
#define FONT_5x8          2
#define FONT_6x12         7
#define FONT_8x16         11
#define FONT_8x18         13
#define FONT_10x20        15

#define ID_NONE           0

typedef   char            oInt8;
typedef   unsigned char   oUInt8;
typedef   short           oInt16;
typedef   unsigned short  oUInt16;
typedef   long            oInt32;
typedef   unsigned long   oUInt32;
typedef   int             oInt;
typedef   unsigned int    oUInt;
typedef   float           oReal32;
typedef   double          oReal64;

typedef   int             oImageID;
typedef   int             oSoundID;
typedef   long            oObjectID;

#ifndef OPOINT_DEFINED
#define OPOINT_DEFINED
struct oPoint
{
	int x;
	int y;
};
#endif

namespace ToTo
{
	DLLIMPORT void oCaptureDorothy(int iFPS);
	DLLIMPORT void oPlayDorothy();
	DLLIMPORT void oGoodByeDorothy();
	DLLIMPORT void oReleaseDorothy();

	DLLIMPORT void oSetUpdateFunc(void (*UpdateFunc)());
	DLLIMPORT void oSetRenderFunc(void (*RenderFunc)());

	DLLIMPORT void oSetWindowTitle(const char* title);
	DLLIMPORT void oSetScreenSize(int width, int height);
	DLLIMPORT void oMoveWindow(int ScrX,int ScrY);
	DLLIMPORT void oSetFont(oUInt iFONT_WxH);
	DLLIMPORT void oSetCursorPos(int x, int y);
	DLLIMPORT void oSetCursorWidth(int percentWidth);
	DLLIMPORT void oShowCursor(bool visible);

	DLLIMPORT void oCameraMove(int X, int Y);
	DLLIMPORT int oGetCameraX();
	DLLIMPORT int oGetCameraY();
	DLLIMPORT void oCameraZoom(float fZoom);
	DLLIMPORT float oGetCameraZoom();
	DLLIMPORT void oBeginPaint(oColor fillColor = BACK_BLACK);
	DLLIMPORT void oEndPaint();
	DLLIMPORT oImageID oLoadFromBMP(const char* filename);
	DLLIMPORT void oDrawImage(oImageID imageID, int X, int Y);
	DLLIMPORT void oDrawLine(const oPoint& start, const oPoint& end, oColor color, char ch = ' ');
	DLLIMPORT void oDrawCircle(const oPoint& center, int radius, oColor color, char ch = ' ');
	DLLIMPORT void oDrawRectangle(const RECT& rect, oColor color, char ch = ' ');
	DLLIMPORT void oDrawPoint(const oPoint* pointList, oUInt number, oColor color, char ch = ' ');

	DLLIMPORT bool oGetKeyState(oUInt8 iVK_KEY);
	DLLIMPORT bool oIsKeyDown(oUInt8 iVK_KEY);
	DLLIMPORT bool oGetLeftButtonState();
	DLLIMPORT bool oIsLeftButtonUp();
	DLLIMPORT bool oIsLeftButtonDown();
	DLLIMPORT bool oGetRightButtonState();
	DLLIMPORT bool oIsRightButtonUp();
	DLLIMPORT bool oIsRightButtonDown();
	DLLIMPORT bool oIsWheelUp();
	DLLIMPORT bool oIsWheelDown();
	DLLIMPORT int oGetMouseX();
	DLLIMPORT int oGetMouseY();

	DLLIMPORT oSoundID oLoadFromWAV(const char* filename);
	DLLIMPORT void oPlaySound(oSoundID soundID, bool loop = false);
	DLLIMPORT void oStopSound(oSoundID soundID);
	DLLIMPORT void oPlayMusic(const char* mp3file);
	DLLIMPORT void oStopMusic();
	DLLIMPORT bool oIsMusicEnd();

	DLLIMPORT oObjectID oCreateObject(oImageID imageID, int X, int Y, int Z);
	DLLIMPORT void oSetObjVisible(oObjectID objID, bool bVisible);
	DLLIMPORT void oSetObjDetective(oObjectID objID, bool bDetective);
	DLLIMPORT int oGetObjX(oObjectID objID);
	DLLIMPORT int oGetObjY(oObjectID objID);
	DLLIMPORT int oGetObjWidth(oObjectID objID);
	DLLIMPORT int oGetObjHeight(oObjectID objID);
	DLLIMPORT bool oIsObjVisible(oObjectID objID);
	DLLIMPORT bool oIsObjDetective(oObjectID objID);
	DLLIMPORT void oSetObjPosition(oObjectID objID, int X, int Y);
	DLLIMPORT void oSetObjZIndex(oObjectID objID, int Z);
	DLLIMPORT void oDrawObject(oObjectID objID);
	DLLIMPORT void oDrawAllObject();
	DLLIMPORT void oDestroyObject(oObjectID objID);
	DLLIMPORT oObjectID oGetCollision(oObjectID objID, bool checkImage = false);
}