#include "oInput.h"
using namespace Dorothy;

oInput* oInput::m_pkInstance = NULL;

oInput::oInput():
m_hInput(0),
m_iReadInput(0),
m_bLeftDown(false),
m_bRightDown(false),
m_bDoubleClick(false),
m_WheelState(WH_NONE),
m_iPosX(0),
m_iPosY(0),
m_iLastKeyCount(0)
{
	ZeroMemory(m_bKeyDown,sizeof(bool)*MAX_KEY_TYPE);
	ZeroMemory(m_bKeyPrev,sizeof(bool)*MAX_KEY_TYPE);
	assert(m_pkInstance == NULL);
	m_pkInstance = this;
}

bool oInput::Initialize( HANDLE hInputHandle )
{
	m_hInput = hInputHandle;
	if (SetConsoleMode(hInputHandle, ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT) == FALSE)
	{
		return false;
	}
	oIUpdate::Register();
	return true;
}

void oInput::Update()
{
	m_bLeftPrev = m_bLeftDown;
	m_bRightPrev = m_bRightDown;
	m_WheelState = WH_NONE;
	for (int i = 0;i < m_iLastKeyCount;i++)
	{
		m_bKeyPrev[m_iLastKey[i]] = m_bKeyDown[m_iLastKey[i]];
	}
	m_iLastKeyCount = 0;
	GetNumberOfConsoleInputEvents(m_hInput, &m_iEvent);
	if (m_iEvent == 0)
	{
		return;
	}
	ReadConsoleInput(m_hInput,m_kInputBuffer,MAX_INPUT_READ,&m_iReadInput);
	for (DWORD i = 0;i < m_iReadInput;i++)
	{
		if (m_kInputBuffer[i].EventType == KEY_EVENT)
		{
			oColor iKeyCode = m_kInputBuffer[i].Event.KeyEvent.wVirtualKeyCode;
			m_bKeyPrev[iKeyCode] = m_bKeyDown[iKeyCode];
			m_iLastKey[m_iLastKeyCount] = iKeyCode;
			m_iLastKeyCount++;
			if (m_kInputBuffer[i].Event.KeyEvent.bKeyDown)
			{
				m_bKeyDown[iKeyCode] = true;
			}
			else
			{
				m_bKeyDown[iKeyCode] = false;
			}
		}
		else if (m_kInputBuffer[i].EventType == MOUSE_EVENT)
		{
			m_bDoubleClick = false;
			switch (m_kInputBuffer[i].Event.MouseEvent.dwEventFlags)
			{
			case MOUSE_MOVED:
				m_iPosX = m_kInputBuffer[i].Event.MouseEvent.dwMousePosition.X;
				m_iPosY = m_kInputBuffer[i].Event.MouseEvent.dwMousePosition.Y; 
				break;
			case 0:
				m_bLeftDown = ((m_kInputBuffer[i].Event.MouseEvent.dwButtonState&FROM_LEFT_1ST_BUTTON_PRESSED) == 1);
				m_bRightDown = ((m_kInputBuffer[i].Event.MouseEvent.dwButtonState&RIGHTMOST_BUTTON_PRESSED) == 2);
				break;
			case DOUBLE_CLICK:
				m_bDoubleClick = true;
				break;
			case MOUSE_WHEELED:
				m_WheelState = ((m_kInputBuffer[i].Event.MouseEvent.dwButtonState&0xFF000000) ? WH_DOWN : WH_UP);
				break;
			default:
				break;
			}
		}
	}
}

bool oInput::GetKeyState( oUInt8 iVK_KEY )
{
	return m_bKeyDown[iVK_KEY];
}

bool oInput::IsKeyUp( oUInt8 iVK_KEY )
{
	return (m_bKeyPrev[iVK_KEY] == true && m_bKeyDown[iVK_KEY] == false);
}

bool oInput::IsKeyDown( oUInt8 iVK_KEY )
{
	return (m_bKeyPrev[iVK_KEY] == false && m_bKeyDown[iVK_KEY] == true);
}

bool oInput::GetLeftMouseState()
{
	return m_bLeftDown;
}

bool oInput::GetRightMouseState()
{
	return m_bRightDown;
}

bool oInput::IsDoubleClicked()
{
	return m_bDoubleClick;
}

oInput* Dorothy::oInput::GetInstance()
{
	return m_pkInstance;
}

bool Dorothy::oInput::IsLeftMouseDown()
{
	return (m_bLeftPrev == false && m_bLeftDown == true);
}

bool Dorothy::oInput::IsRightMouseDown()
{
	return (m_bRightPrev == false && m_bRightDown == true);
}

bool Dorothy::oInput::IsLeftMouseUp()
{
	return (m_bLeftPrev == true && m_bLeftDown == false);
}

bool Dorothy::oInput::IsRightMouseUp()
{
	return (m_bRightPrev == true && m_bRightDown == false);
}

int oInput::GetMouseX()
{
	return (oScreen::GetInstance()->GetViewX()+(int)((float)m_iPosX/oScreen::GetInstance()->GetScaleX()));
}

int oInput::GetMouseY()
{
	return (oScreen::GetInstance()->GetViewY()+(int)((float)m_iPosY/oScreen::GetInstance()->GetScaleY()));
}

int oInput::GetMouseScreenX()
{
	return m_iPosX;
}

int oInput::GetMouseScreenY()
{
	return m_iPosY;
}

bool oInput::IsWheelUp()
{
	return (m_WheelState == WH_UP);
}

bool oInput::IsWheelDown()
{
	return (m_WheelState == WH_DOWN);
}