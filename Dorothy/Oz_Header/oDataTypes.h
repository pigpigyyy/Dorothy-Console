#pragma once
#pragma warning(disable:4995)
#include <vector>
#define DLLEXPORT          __declspec(dllexport)

//屏幕的宽高的默认值
#define DEFAULT_WIDTH      80
#define DEFAULT_HEIGHT     25

//颜色类型和可取的值
typedef unsigned short     oColor;

#define FORE_BLACK         0x0000
#define FORE_BLUE          0x0001
#define FORE_GREEN         0x0002
#define FORE_CYAN          0x0003
#define FORE_RED           0x0004
#define FORE_MAGENTA       0x0005
#define FORE_YELLOW        0x0006
#define FORE_WHITE         0x0007
#define FORE_BLACKI        0x0008
#define FORE_BLUEI         0x0009
#define FORE_GREENI        0x000A
#define FORE_CYANI         0x000B
#define FORE_REDI          0x000C
#define FORE_MAGENTAI      0x000D
#define FORE_YELLOWI       0x000E
#define FORE_WHITEI        0x000F

#define BACK_BLACK         0x0000
#define BACK_BLUE          0x0010
#define BACK_GREEN         0x0020
#define BACK_CYAN          0x0030
#define BACK_RED           0x0040
#define BACK_MAGENTA       0x0050
#define BACK_YELLOW        0x0060
#define BACK_WHITE	       0x0070
#define BACK_BLACKI        0x0080
#define BACK_BLUEI         0x0090
#define BACK_GREENI        0x00A0
#define BACK_CYANI         0x00B0
#define BACK_REDI          0x00C0
#define BACK_MAGENTAI      0x00D0
#define BACK_YELLOWI       0x00E0
#define BACK_WHITEI        0x00F0

#define COLOR_NONE         0xFFFF

//oInput类使用的常数
#define MAX_INPUT_READ     10
#define MAX_KEY_TYPE       256

//控制台字体大小
#define FONT_3x5           0
#define FONT_5x8           2
#define FONT_6x12          7
#define FONT_8x16          11
#define FONT_8x18          13
#define FONT_10x20         15

#define MIN_SCREEN_SCALE   0.5f
#define ZOOM_BUFFER_FACTOR 4

#define PI                 3.14159265359f

#define ID_NONE            -1

typedef   char             oInt8;
typedef   unsigned char    oUInt8;
typedef   short            oInt16;
typedef   unsigned short   oUInt16;
typedef   long             oInt32;
typedef   unsigned long    oUInt32;
typedef   int              oInt;
typedef   unsigned int     oUInt;

typedef   float            oReal32;
typedef   double           oReal64;

typedef   void             oSoundBuffer;
typedef   void             oSoundDevice;

//矩形与矩形碰撞
#define RECT_HIT_RECT(lx,ly,rx,ry,lx1,ly1,rx1,ry1) ( (ry)>(ly1) && (ly)<(ry1) \
	&& (rx)>(lx1) && (lx)<(rx1) )

//点与矩形碰撞
#define POINT_IN_RECT(x,y,x1,y1,w,h) ((y)>=(y1) && (y)<(y1)+(h) \
	&& (x)>=(x1) && (x)<(x1)+(w))

struct oRect
{
	int x;
	int y;
	int w;
	int h;
};

struct oPoint
{
	int x;
	int y;
};

//只支持整数角度的sin、cos函数超优化版本
float DLLEXPORT oSin(int iAngle);
float DLLEXPORT oCos(int iAngle);

//把小数四舍五入成整数
inline int oRoundToInt(float fNum)
{
	return (int)(fNum > 0.0f ? (fNum+0.5) : (fNum-0.5));
}
