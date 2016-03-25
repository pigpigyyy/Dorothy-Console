#include "oConsole.h"
using namespace Dorothy;

static PROCSETCONSOLEFONT SetConsoleFont;

oConsole* oConsole::m_pkInstance = NULL;

const COORD oConsole::m_kOrigin = {0,0};

oConsole::oConsole():
m_hOutput(0),
m_hInput(0),
m_hWindow(0)
{
	HMODULE hKernel32 = GetModuleHandle("kernel32");
	SetConsoleFont = (PROCSETCONSOLEFONT)GetProcAddress(hKernel32,"SetConsoleFont");
	m_kScreenRect.Left = 0;
	m_kScreenRect.Top = 0;
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
}

oConsole::~oConsole()
{
	m_pkInstance = NULL;
	m_hOutput = 0;
	m_hInput = 0;
}

bool oConsole::Initialize(int width, int height, oUInt font)
{
	if ((m_hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE))
		== INVALID_HANDLE_VALUE)
	{
		return false;
	}
	if ((m_hInput = ::GetStdHandle(STD_INPUT_HANDLE))
		== INVALID_HANDLE_VALUE)
	{
		return false;
	}
	if(::GetConsoleCursorInfo(m_hOutput, &m_kCursor)
		== FALSE)
	{
		return false;
	}
	m_hWindow = ::GetConsoleWindow();
	CONSOLE_SCREEN_BUFFER_INFO kInfo;
	::GetConsoleScreenBufferInfo(m_hOutput,&kInfo);
	m_kScreenSize = kInfo.dwSize;
	oConsole::SetFont(font);
	oConsole::SetScreenSize(width, height);
	return true;
}

void oConsole::SetWindowTitle(const char* title )
{
	::SetConsoleTitle(title);
}

void oConsole::SetScreenSize( int width, int height )
{
	m_kScreenSize.X = width;
	m_kScreenSize.Y = height;
	m_kScreenRect.Right = width-1;
	m_kScreenRect.Bottom = height-1;
	::SetConsoleWindowInfo(m_hOutput, TRUE, &m_kScreenRect);
	::SetConsoleScreenBufferSize(m_hOutput, m_kScreenSize);
	/*写两遍才能保证窗口大小设置成功*/
	::SetConsoleWindowInfo(m_hOutput, TRUE, &m_kScreenRect);
}

void oConsole::SetCursorPos( int x, int y )
{
	COORD kPoint = {x,y};
	::SetConsoleCursorPosition(m_hOutput, kPoint);
}

void oConsole::SetCursorWidth( int percentWidth )
{
	m_kCursor.dwSize = percentWidth;
	::SetConsoleCursorInfo(m_hOutput,&m_kCursor);
}

void oConsole::ShowCursor( bool visible )
{
	m_kCursor.bVisible = visible;
	::SetConsoleCursorInfo(m_hOutput,&m_kCursor);
}

oConsole* oConsole::GetInstance()
{
	return m_pkInstance;
}

HANDLE oConsole::GetOutputHandle()
{
	return m_hOutput;
}

HANDLE oConsole::GetInputHandle()
{
	return m_hInput;
}

int oConsole::GetWidth()
{
	return m_kScreenSize.X;
}

int oConsole::GetHeight()
{
	return m_kScreenSize.Y;
}

void oConsole::ShowScreen(const CHAR_INFO* buffer, const COORD& size)
{
	::WriteConsoleOutput(m_hOutput, buffer, size, 
		m_kOrigin, &m_kScreenRect);
}

HWND oConsole::GetWindowHandle()
{
	return m_hWindow;
}

void oConsole::SetFont( oUInt iFONT_WxH )
{
	SetConsoleFont(m_hOutput,iFONT_WxH);
}

void oConsole::MoveWindow( int ScrX,int ScrY )
{
	RECT rc;
	::GetWindowRect(m_hWindow,&rc);
	::MoveWindow(m_hWindow,ScrX,ScrY,rc.right-rc.left,rc.bottom-rc.top,TRUE);
}