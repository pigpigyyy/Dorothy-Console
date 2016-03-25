//Dorothy 1.50
#pragma once
#pragma warning(disable:4995)
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <Windows.h>
#include <time.h>
#include <vector>
using std::vector;
#include "Other/AcfDelegate.h"
using Acf::Delegate;

#define DLLIMPORT          __declspec(dllimport)

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

#ifndef OPOINT_DEFINED
#define OPOINT_DEFINED
struct oPoint
{
	int x;
	int y;
};
#endif

//只支持整数角度的sin、cos函数超优化版本
float DLLIMPORT oSin(int iAngle);
float DLLIMPORT oCos(int iAngle);

//把小数四舍五入成整数
inline int oRoundToInt(float fNum)
{
	return (int)(fNum > 0.0f ? (fNum+0.5) : (fNum-0.5));
}

//命名空间:桃乐兹
namespace Dorothy
{
	/*Console类*/
	class DLLIMPORT oConsole
	{
	public:
		oConsole();
		~oConsole();
		bool Initialize(
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT,
			oUInt font = FONT_6x12);
		void SetWindowTitle(const char* title);
		void SetScreenSize(int width, int height);
		void MoveWindow(int ScrX,int ScrY);
		void SetFont(oUInt iFONT_WxH);
		void SetCursorPos(int x, int y);
		void SetCursorWidth(int percentWidth);
		void ShowCursor(bool visible);
		void ShowScreen(const CHAR_INFO* buffer, const COORD& size);
		int GetWidth();
		int GetHeight();
		HANDLE GetOutputHandle();
		HANDLE GetInputHandle();
		HWND GetWindowHandle();
		static oConsole* GetInstance();
	protected:
		HANDLE m_hOutput;
		HANDLE m_hInput;
		HWND m_hWindow;
		const static COORD m_kOrigin;
		COORD m_kScreenSize;
		SMALL_RECT m_kScreenRect;
		CONSOLE_CURSOR_INFO m_kCursor;
		static oConsole* m_pkInstance;
	};

	/*Image类*/
	class DLLIMPORT oImage
	{
	public:
		oImage();
		~oImage();
		void Create(int width, int height);
		//下面是以自己左上角为(0,0)的坐标
		void SetChar(int x, int y, char ch);
		void SetColor(int x, int y, oColor color);
		char GetChar(int x, int y) const;
		oColor GetColor(int x, int y) const;
		int GetWidth() const;
		int GetHeight() const;
		void Release();
		CHAR_INFO** GetData();
	protected:
		int m_iWidth;
		int m_iHeight;
		CHAR_INFO** m_ppData;
	};

	//由下面函数获得的图片请直接delete或用oReleaseImage函数释放
	DLLIMPORT oImage* oCreateImageFromBMP24( const char* filename );
	DLLIMPORT void oReleaseImage( oImage*& pkImage );

	/*Graphic类*/
	class DLLIMPORT oScreen
	{
	public:
		oScreen();
		~oScreen();
		bool Initialize(HANDLE hOutputHandle);
		void Begin(oColor fillColor = BACK_BLACK);
		void End();
		void DrawPoint(const oPoint* pointList, oUInt number, oColor color, char ch = ' ');
		void DrawLine(const oPoint& start, const oPoint& end, oColor color, char ch = ' ');
		void DrawRectangle(const RECT& rect, oColor color, char ch = ' ');
		void DrawCircle(const oPoint& center, int radius, oColor color, char ch = ' ');
		bool SetVSync(bool VSync);
		//设置在Game World坐标系中自己左上角的位置
		void SetView(int X, int Y);
		void SetScale(float fScaleX, float fScaleY);
		int GetViewX();
		int GetViewY();
		float GetScaleX();
		float GetScaleY();
		int GetWidth();
		int GetHeight();
		bool IsVSync();
		oImage* CaptureScreen();
		CHAR_INFO* GetBuffer();
		const RECT* GetRect();
		static oScreen* GetInstance();
	protected:
		inline void Put_Pixel(int X, int Y, oColor color, char ch);
		void SetUpBuffer();
		void SetUpUsingBuffer();
		bool m_bVSync;
		bool m_bZoomScreen;
		float m_fScaleX;
		float m_fScaleY;
		int m_iWidth;
		int m_iHeight;
		int m_iScreenWidth;
		int m_iScreenHeight;
		int m_iScaleWidth;
		int m_iScaleHeight;
		int m_iBufferSize;
		RECT m_kRect;
		CHAR_INFO* m_pkScreenBuffer;
		CHAR_INFO* m_pkScaleBuffer;
		CHAR_INFO* m_pkBuffer;
		static oScreen* m_pkInstance;
	};

	/*音效播放器类*/
	class DLLIMPORT oSoundPlayer
	{
	public:
		oSoundPlayer();
		~oSoundPlayer();
		bool Initialize(HWND hWindow);
		oSoundDevice* GetDevice();
		static oSoundPlayer *GetInstance();
	protected:
		oSoundDevice* m_lpkDSound;
		static oSoundPlayer *m_pkInstance;
	};

	/*音乐播放器类*/
	enum oPlayerState{PS_PLAY,PS_PAUSE,PS_STOP};
	class DLLIMPORT oMusicPlayer
	{
	public:
		oMusicPlayer();
		~oMusicPlayer();
		bool Open(const char* filename);
		void Close();
		void Play();
		void Pause();
		void Stop();
		void SetVolume(oUInt iVolume);
		oPlayerState GetState();
		static oMusicPlayer* GetInstance();
	protected:
		oPlayerState m_State;
		static oMusicPlayer* m_pkInstance;
	};

	class DLLIMPORT oIUpdate
	{
	public:
		oIUpdate();
		virtual ~oIUpdate();
		static void SetAutoManaged(bool autoManaged);
		static bool IsAutoManaged();
		virtual void Update() = 0;
		void Register();
		void UnRegister();
		bool IsRegistered() const;
	private:
		int m_ID;
	};

	/*输入类*/
	enum oWheelState{WH_UP,WH_DOWN,WH_NONE};
	class DLLIMPORT oInput:public oIUpdate
	{
	public:
		oInput();
		bool Initialize(HANDLE hInputHandle);
		bool GetKeyState(oUInt8 iVK_KEY);
		bool IsKeyUp(oUInt8 iVK_KEY);
		bool IsKeyDown(oUInt8 iVK_KEY);
		bool IsLeftMouseDown();
		bool IsRightMouseDown();
		bool IsLeftMouseUp();
		bool IsRightMouseUp();
		bool GetLeftMouseState();
		bool GetRightMouseState();
		bool IsDoubleClicked();
		bool IsWheelUp();
		bool IsWheelDown();
		int GetMouseX();
		int GetMouseY();
		int GetMouseScreenX();
		int GetMouseScreenY();
		static oInput* GetInstance();
	private:
		virtual void Update();
		bool m_bLeftPrev;
		bool m_bLeftDown;
		bool m_bRightPrev;
		bool m_bRightDown;
		bool m_bDoubleClick;
		bool m_bKeyPrev[MAX_KEY_TYPE];
		bool m_bKeyDown[MAX_KEY_TYPE];
		int m_iPosX;
		int m_iPosY;
		int m_iLastKey[MAX_INPUT_READ];
		int m_iLastKeyCount;
		HANDLE m_hInput;
		DWORD m_iEvent;
		DWORD m_iReadInput;
		oWheelState m_WheelState;
		INPUT_RECORD m_kInputBuffer[MAX_INPUT_READ];
		static oInput* m_pkInstance;
	};

	/*精准计时器类*/
	class DLLIMPORT oAccurateTimer
	{
	public:
		oAccurateTimer();
		void Start();
		void Stop();
		bool IsRunning();
		void ZeroCount();
		//获得时间差(s)
		float GetCount();
	protected:
		bool m_bRun;
		/*硬件定时器变量*/
		LARGE_INTEGER m_iFrequency;
		LARGE_INTEGER m_iCurrentQuery;
		LARGE_INTEGER m_iLastQuery;
		LARGE_INTEGER m_iCount;
	};

	/*日期和时间类*/
	class DLLIMPORT oDateTime
	{
	public:
		oDateTime();
		void Update();
		oUInt32 GetSeconds() const;
		oUInt32 GetMinutes() const;
		oUInt32 GetHours() const;
		oUInt32 GetDay() const;
		oUInt32 GetMonth() const;
		oUInt32 GetYear() const;
	protected:
		tm m_kTime;
	};

	/*声效类*/
	class DLLIMPORT oSound
	{
	public:
		oSound();
		~oSound();
		bool LoadFromFile(const char* filename);
		void SetVolume(oUInt32 iVolume);
		void Play(bool bLoop);
		void Stop();
		void Release();
	protected:
		oSoundBuffer* m_lpkSound;
	};

	//监听物体Z坐标变化的类
	class DLLIMPORT oZIndexListener
	{
	public:
		oZIndexListener();
		void NotifyZChange();
	protected:
		bool m_bZChanged;
	};

	enum oVisibility{V_VISIBLE,V_HIDDEN,V_COLLAPSE};
	class DLLIMPORT oIRender
	{
	public:
		oIRender(bool bVisible = true);
		virtual ~oIRender();
		void SetZIndex(int iZ);
		void SetVisible(bool bVisible);
		void SetVisible(oVisibility Visibility);
		int GetZIndex() const;
		bool IsVisible() const;
		static void SetZIndexListener(oZIndexListener* pkListener);
		static void SetAutoManaged(bool autoManaged);
		static bool IsAutoManaged();
	protected:
		virtual void Render() = 0;
	private:
		int m_ID;
		int m_iZ;
		oVisibility m_Visibility;
		static oZIndexListener* m_pkListener;
	};

	class DLLIMPORT oCirclePaint:public oIRender
	{
	public:
		oCirclePaint();
		void Set(const oPoint& kCenter, int iRadius, oColor color, char ch = ' ');
		void SetCenter(const oPoint& kCenter);
		void SetRadius(int iRadius);
		void SetColor(oColor color);
		void SetChar(char ch);
	private:
		virtual void Render();
		oPoint m_kCenter;
		int m_iRadius;
		oColor m_Color;
		char m_Ch;
	};

	class DLLIMPORT oDotPaint:public oIRender
	{
	public:
		oDotPaint();
		void Set(const oPoint* pointList, oUInt number, oColor color, char ch = ' ');
		void SetPoint(const oPoint* pointList, oUInt number);
		void SetColor(oColor color);
		void SetChar(char ch);
	private:
		virtual void Render();
		const oPoint* m_pkPointList;
		int m_iNumber;
		oColor m_Color;
		char m_Ch;
	};

	class DLLIMPORT oLinePaint:public oIRender
	{
	public:
		oLinePaint();
		void Set(const oPoint& start,const oPoint& end, oColor color, char ch = ' ');
		void SetLine(const oPoint& start,const oPoint& end);
		void SetColor(oColor color);
		void SetChar(char ch);
	private:
		virtual void Render();
		oPoint m_kStart;
		oPoint m_kEnd;
		oColor m_Color;
		char m_Ch;
	};

	class DLLIMPORT oRectPaint:public oIRender
	{
	public:
		oRectPaint();
		void Set(const RECT& rect, oColor color, char ch = ' ');
		void SetColor(oColor color);
		void SetRect(const RECT& rect);
		void SetChar(char ch);
	private:
		virtual void Render();
		RECT m_kRect;
		oColor m_Color;
		char m_Ch;
	};

	class oGroup;

	class DLLIMPORT oObject:public oIRender
	{
	public:
		oObject();
		virtual ~oObject();
		//下面使用的oImage没有被拷贝
		void SetImage(oImage* image);
		void SetDetective(bool bDetective);
		void SetGroup(oGroup* group);
		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		bool IsDetective() const;
		oImage* GetImage() const;
		oGroup* GetGroup() const;
		oObject* Prev() const;
		oObject* Next() const;
		//设置在Game World坐标系中自己左上角的位置
		virtual void SetPosition(int X, int Y);
		virtual void SetSize(int width, int height);
		virtual const oRect* GetRect() const;
		virtual oColor GetDisplayColor(int X, int Y) const;
		virtual char GetDisplayChar(int X, int Y) const;
		virtual void Render();
	protected:
		void RemoveGroup();
		bool m_bDetective;
		oRect m_kRect;
		oImage* m_pkImage;
		oObject* m_pkPrev;
		oObject* m_pkNext;
		oGroup* m_pkGroup;
	};

	class DLLIMPORT oGroup
	{
	public:
		oGroup();
		oObject* First();
		oObject* Last();
		void Clear();
		void Update();
		void Render();
		vector<oObject*>& GetItems() const;
		vector<oObject*>& GetCollisionList(oObject* pkObject, bool bCheckImage = false) const;
		vector<oObject*>& GetCollisionList(const oPoint& kPoint, bool bCheckImage = false) const;
	private:
		oObject* m_pkFirst;
		oObject* m_pkLast;
	};

	class DLLIMPORT oSprite:public oObject
	{
	public:
		oSprite(bool bImageBased = false);
		void SetRenderRect(const RECT& rect);
		float GetScaleX() const;
		float GetScaleY() const;
		int GetAngle() const;
		virtual void SetScale(float fScaleX, float fScaleY);
		virtual void SetAngle(int iAngle);
		virtual void SetPosition(int X, int Y);
		virtual void SetSize(int width, int height);
		virtual const oRect* GetRect() const;
		virtual oColor GetDisplayColor(int X, int Y) const;
		virtual char GetDisplayChar(int X, int Y) const;
		virtual void Render();
	protected:
		const bool m_bImageBased;
	private:
		void UpdateRenderData();
		bool m_bUpdateRender;
		bool m_bUpdatePos;
		bool m_bFlipX;
		bool m_bFlipY;
		float m_fCosA;
		float m_fSinA;
		float m_fScaleX;
		float m_fScaleY;
		int m_iAngle;
		int m_iRenderWidth;
		int m_iRenderHeight;
		oRect m_kImgRect;
		RECT m_kRenderRect;
		float m_fRotMinWidth;
		float m_fRotMinHeight;
	};

	template class DLLIMPORT Delegate<void ()>;
	typedef Delegate<void ()> oTimerHandler;
	class DLLIMPORT oTimer:public oIUpdate
	{
	public:
		oTimer(oUInt nDelay,oUInt nLoop = 1);
		void SetDelay(oUInt nDelay);
		void SetLoop(oUInt nLoop);
		void Start();
		void Stop();
		bool IsRunning() const;
		oUInt GetCurrentLoop() const;
		oUInt GetLoop() const;
		oTimerHandler OnTimer;
	private:
		virtual void Update();
		bool m_bRun;
		oUInt m_nLoop;
		oUInt m_nCurrentCount;
		oUInt m_nCurrentLoop;
		oUInt m_nCount;
	};

	class oAnimation;
	template class DLLIMPORT Delegate<void (oAnimation*)>;
	typedef Delegate<void (oAnimation*)> oAnimationHandler;
	class DLLIMPORT oAnimation:public oIUpdate
	{
	public:
		oAnimation();
		void SetTarget(oSprite* pkSprite);
		void SetSpeed(float fSpeed);
		void SetLoop(bool bLoop);
		void SetReverse(bool bReverse);
		oSprite* GetTarget();
		bool IsPlaying() const;
		void Start();
		void End();
		void Stop();
		oAnimationHandler OnEnd;
	protected:
		virtual void PreStart() = 0;
		virtual bool UpdateFrame() = 0;
		virtual void PreEnd() = 0;
		bool m_bPlay;
		bool m_bLoop;
		bool m_bReverse;
		bool m_bIsReversing;
		oUInt m_nCount;
		float m_fAdd;
		float m_fCurrent;
		oSprite* m_pkTarget;
	private:
		virtual void Update();
	};

	class DLLIMPORT oFrameAnimation:public oAnimation
	{
	public:
		oFrameAnimation();
		~oFrameAnimation();
		void SetUpFrame(oUInt nFrame);
		void SetFrame(oUInt nSubScript,const RECT& kRenderRect,oUInt nKeepTime);
		void operator=(const oFrameAnimation& kFrame);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		RECT* m_pkRenderRectList;
		oUInt* m_pnKeepTime;
		int m_iCurrentFrame;
		oUInt m_nFrameNum;
	};

	class DLLIMPORT oMoveAnimation:public oAnimation
	{
	public:
		oMoveAnimation();
		void SetMove(int iMoveXFrom,int iMoveXTo,
			int iMoveYFrom,int iMoveYTo,oUInt iDuration);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		int m_iMoveXFrom;
		int m_iMoveXTo;
		float m_dMoveX;
		int m_iMoveYFrom;
		int m_iMoveYTo;
		float m_dMoveY;
	};

	class DLLIMPORT oRotateAnimation:public oAnimation
	{
	public:
		oRotateAnimation();
		void SetRotate(int iAngleFrom,int iAngleTo,oUInt iDuration);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		int m_iAngleFrom;
		int m_iAngleTo;
		float m_dAngle;
	};

	class DLLIMPORT oScaleAnimation:public oAnimation
	{
	public:
		oScaleAnimation();
		void SetScale(float fScaleXFrom,float fScaleXTo,
			float fScaleYFrom,float fScaleYTo,oUInt iDuration);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		float m_fScaleXFrom;
		float m_fScaleXTo;
		float m_dScaleX;
		float m_fScaleYFrom;
		float m_fScaleYTo;
		float m_dScaleY;
	};

	class DLLIMPORT oCamera:public oIUpdate
	{
	public:
		oCamera();
		~oCamera();
		void LockAt(const oObject* pkTarget, float fOriginX = 0.5f, float fOriginY = 0.5f);
		void Zoom(float fZoom);
		void Move(int X, int Y);
		float GetZoom() const;
		int GetX() const;
		int GetY() const;
		const oObject* GetTarget() const;
	private:
		virtual void Update();
		int m_iX;
		int m_iY;
		float m_fZoom;
		float m_fOriginX;
		float m_fOriginY;
		const oObject* m_pkTarget;
	};

	class DLLIMPORT oGame : public oIRender, public oIUpdate
	{
	public:
		oGame();
		~oGame();
		bool Initialize(
			const char* title,
			int iFPS,
			bool bUseSound = false,
			bool bUseMusic = false,
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT,
			oUInt iFONT_WxH = FONT_8x16);
		void Run();
		void Stop();
		int GetFPS();
		int GetCurrentFPS();
		void SetBackColor(oColor color);
		static oGame* GetInstance();
	private:
		bool m_bRun;
		int m_iFPS;
		int m_iCurrentFPS;
		oConsole* m_pkConsole;
		oScreen* m_pkScreen;
		oInput* m_pkInput;
		oSoundPlayer* m_pkSoundPlayer;
		oMusicPlayer* m_pkMusicPlayer;
		oAccurateTimer m_kTimer;
		static oGame* m_pkInstance;
	};
}
