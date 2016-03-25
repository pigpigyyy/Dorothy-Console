#include "Dorothy.h"
using namespace Dorothy;
#include "oDataTypes.h"

typedef int oImageID;
typedef int oSoundID;
typedef long oObjectID;
#define ID_NONE 0

namespace ToTo
{
	DLLEXPORT void oCaptureDorothy(int iFPS);
	DLLEXPORT void oPlayDorothy();
	DLLEXPORT void oGoodByeDorothy();
	DLLEXPORT void oReleaseDorothy();

	DLLEXPORT void oSetUpdateFunc(void (*UpdateFunc)());
	DLLEXPORT void oSetRenderFunc(void (*RenderFunc)());

	DLLEXPORT void oSetWindowTitle(const char* title);
	DLLEXPORT void oSetScreenSize(int width, int height);
	DLLEXPORT void oMoveWindow(int ScrX, int ScrY);
	DLLEXPORT void oSetFont(oUInt iFONT_WxH);
	DLLEXPORT void oSetCursorPos(int x, int y);
	DLLEXPORT void oSetCursorWidth(int percentWidth);
	DLLEXPORT void oShowCursor(bool visible);

	DLLEXPORT void oCameraMove(int X, int Y);
	DLLEXPORT int oGetCameraX();
	DLLEXPORT int oGetCameraY();
	DLLEXPORT void oCameraZoom(float fZoom);
	DLLEXPORT float oGetCameraZoom();
	DLLEXPORT void oBeginPaint(WORD fillColor = BACK_BLACK);
	DLLEXPORT void oEndPaint();
	DLLEXPORT oImageID oLoadFromBMP(const char* filename);
	DLLEXPORT void oDrawImage(oImageID imageID, int X, int Y);
	DLLEXPORT void oDrawLine(const oPoint& start, const oPoint& end, WORD color, char ch = ' ');
	DLLEXPORT void oDrawCircle(const oPoint& center, int radius, WORD color, char ch = ' ');
	DLLEXPORT void oDrawRectangle(const RECT& rect, WORD color, char ch = ' ');
	DLLEXPORT void oDrawPoint(const oPoint* pointList, oUInt number, WORD color, char ch = ' ');

	DLLEXPORT bool oGetKeyState(oUInt8 iVK_KEY);
	DLLEXPORT bool oIsKeyDown(oUInt8 iVK_KEY);
	DLLEXPORT bool oGetLeftButtonState();
	DLLEXPORT bool oIsLeftButtonUp();
	DLLEXPORT bool oIsLeftButtonDown();
	DLLEXPORT bool oGetRightButtonState();
	DLLEXPORT bool oIsRightButtonUp();
	DLLEXPORT bool oIsRightButtonDown();
	DLLEXPORT bool oIsWheelUp();
	DLLEXPORT bool oIsWheelDown();
	DLLEXPORT int oGetMouseX();
	DLLEXPORT int oGetMouseY();

	DLLEXPORT oSoundID oLoadFromWAV(const char* filename );
	DLLEXPORT void oPlaySound(oSoundID soundID, bool loop = false);
	DLLEXPORT void oStopSound(oSoundID soundID );
	DLLEXPORT void oPlayMusic(const char* mp3file );
	DLLEXPORT void oStopMusic();
	DLLEXPORT bool oIsMusicEnd();

	DLLEXPORT oObjectID oCreateObject(oImageID imageID, int X, int Y, int Z);
	DLLEXPORT void oSetObjVisible(oObjectID objID, bool bVisible);
	DLLEXPORT void oSetObjDetective(oObjectID objID, bool bDetective);
	DLLEXPORT int oGetObjX(oObjectID objID);
	DLLEXPORT int oGetObjY(oObjectID objID);
	DLLEXPORT int oGetObjWidth(oObjectID objID);
	DLLEXPORT int oGetObjHeight(oObjectID objID);
	DLLEXPORT bool oIsObjVisible(oObjectID objID);
	DLLEXPORT bool oIsObjDetective(oObjectID objID);
	DLLEXPORT void oSetObjPosition(oObjectID objID, int X, int Y);
	DLLEXPORT void oSetObjZIndex(oObjectID objID, int Z);
	DLLEXPORT void oDrawObject(oObjectID objID);
	DLLEXPORT void oDrawAllObject();
	DLLEXPORT void oDestroyObject(oObjectID objID);
	DLLEXPORT oObjectID oGetCollision(oObjectID objID, bool checkImage = false);

	class oToToGame:public oGame
	{
	public:
		oToToGame()
		{
			UpdateFunc = NULL;
			RenderFunc = NULL;
		}
		void Update()
		{
			if (UpdateFunc != NULL)
			{
				UpdateFunc();
			}
		}
		void Render()
		{
			if (RenderFunc != NULL)
			{
				RenderFunc();
			}
		}
		void (*UpdateFunc)();
		void (*RenderFunc)();
		oCamera m_kCamera;
	};

	static oToToGame g_kGame;
	static vector<oImage*> g_kImageList;
	static vector<oSound*> g_kSoundList;
	static vector<oObject*> g_kCollisionList;
	static oGroup g_kGroup;

	void oCaptureDorothy(int iFPS)
	{
		g_kGame.Initialize("ToTo Game",iFPS);
	}

	void oPlayDorothy()
	{
		g_kGame.Run();
	}

	void oGoodByeDorothy()
	{
		g_kGame.Stop();
	}

	void oReleaseDorothy()
	{
		if (g_kImageList.size() != 0)
		{
			for (oUInt n = 0;n < g_kImageList.size();n++)
			{
				delete g_kImageList[n];
				g_kImageList[n] = NULL;
			}
		}
		if (g_kSoundList.size() != 0)
		{
			for (oUInt n = 0;n < g_kSoundList.size();n++)
			{
				delete g_kSoundList[n];
				g_kSoundList[n] = NULL;
			}
		}
	}

	void oSetUpdateFunc(void (*UpdateFunc)())
	{
		g_kGame.UpdateFunc = UpdateFunc;
	}

	void oSetRenderFunc(void (*RenderFunc)())
	{
		g_kGame.RenderFunc = RenderFunc;
	}

	void oSetWindowTitle(const char* title)
	{
		oConsole::GetInstance()->SetWindowTitle(title);
	}

	void oSetScreenSize(int width, int height)
	{
		oConsole::GetInstance()->SetScreenSize(width, height);
	}

	void oMoveWindow(int ScrX,int ScrY)
	{
		oConsole::GetInstance()->MoveWindow(ScrX, ScrY);
	}

	void oSetFont(oUInt iFONT_WxH)
	{
		oConsole::GetInstance()->SetFont(iFONT_WxH);
	}

	void oSetCursorPos(int x, int y)
	{
		oConsole::GetInstance()->SetCursorPos(x, y);
	}

	void oSetCursorWidth(int percentWidth)
	{
		oConsole::GetInstance()->SetCursorWidth(percentWidth);
	}

	void oShowCursor(bool visible)
	{
		oConsole::GetInstance()->ShowCursor(visible);
	}

	void oCameraMove(int X, int Y)
	{
		g_kGame.m_kCamera.Move(X,Y);
	}

	int oGetCameraX()
	{
		return g_kGame.m_kCamera.GetX();
	}

	int oGetCameraY()
	{
		return g_kGame.m_kCamera.GetY();
	}

	void oCameraZoom( float fZoom )
	{
		g_kGame.m_kCamera.Zoom(fZoom);
	}

	float oGetoCameraZoom()
	{
		return g_kGame.m_kCamera.GetZoom();
	}

	void oBeginPaint(WORD fillColor)
	{
		oScreen::GetInstance()->Begin(fillColor);
	}

	void oEndPaint()
	{
		oScreen::GetInstance()->End();
	}

	oImageID oLoadFromBMP( const char* filename )
	{
		oImage* pkImage = Dorothy::oCreateImageFromBMP24(filename);
		if (pkImage == NULL)
		{
			return ID_NONE;
		}
		g_kImageList.push_back(pkImage);
		return g_kImageList.size();
	}

	void oDrawImage( oImageID imageID, int X, int Y )
	{
		imageID--;
		if (0 <= imageID && (oUInt)imageID < g_kImageList.size())
		{
			oObject kObj;
			kObj.SetImage(g_kImageList[imageID]);
			kObj.SetPosition(X,Y);
			kObj.Render();
		}
	}

	void oDrawLine( const oPoint& start, const oPoint& end, WORD color, char ch )
	{
		oScreen::GetInstance()->DrawLine(start, end, color, ch);
	}

	void oDrawCircle( const oPoint& center, int radius, WORD color, char ch )
	{
		oScreen::GetInstance()->DrawCircle(center, radius, color, ch);
	}

	void oDrawRectangle( const RECT& rect, WORD color, char ch )
	{
		oScreen::GetInstance()->DrawRectangle(rect, color, ch);
	}

	void oDrawPoint( const oPoint* pointList, oUInt number, WORD color, char ch )
	{
		oScreen::GetInstance()->DrawPoint(pointList, number, color, ch);
	}

	bool oGetKeyState( oUInt8 iVK_KEY )
	{
		return oInput::GetInstance()->GetKeyState(iVK_KEY);
	}

	bool oGetLeftButtonState()
	{
		return oInput::GetInstance()->GetLeftMouseState();
	}

	bool oIsLeftButtonUp()
	{
		return oInput::GetInstance()->IsLeftMouseUp();
	}

	bool oGetRightButtonState()
	{
		return oInput::GetInstance()->GetRightMouseState();
	}

	bool oIsRightButtonUp()
	{
		return oInput::GetInstance()->IsRightMouseUp();
	}

	bool oIsKeyDown(oUInt8 iVK_KEY)
	{
		return oInput::GetInstance()->IsKeyDown(iVK_KEY);
	}

	bool oIsLeftButtonDown()
	{
		return oInput::GetInstance()->GetLeftMouseState();
	}

	bool oIsRightButtonDown()
	{
		return oInput::GetInstance()->GetRightMouseState();
	}

	bool oIsWheelUp()
	{
		return oInput::GetInstance()->IsWheelUp();
	}

	bool oIsWheelDown()
	{
		return oInput::GetInstance()->IsWheelDown();
	}

	int oGetMouseX()
	{
		return oInput::GetInstance()->GetMouseX();
	}

	int oGetMouseY()
	{
		return oInput::GetInstance()->GetMouseY();
	}

	oSoundID oLoadFromWAV( const char* filename )
	{
		oSound* pkSound = new oSound();
		if (pkSound->LoadFromFile(filename))
		{
			g_kSoundList.push_back(pkSound);
			return g_kSoundList.size();
		}
		return ID_NONE;
	}

	void oPlaySound( oSoundID soundID, bool loop )
	{
		soundID--;
		if (0 <= soundID && (oUInt)soundID < g_kSoundList.size())
		{
			g_kSoundList[soundID]->Play(loop);
		}
	}

	void oStopSound( oSoundID soundID )
	{
		soundID--;
		if (0 <= soundID && (oUInt)soundID < g_kSoundList.size())
		{
			g_kSoundList[soundID]->Stop();
		}
	}

	void oPlayMusic( const char* mp3file )
	{
		oMusicPlayer::GetInstance()->Open(mp3file);
		oMusicPlayer::GetInstance()->Play();
	}

	void oStopMusic()
	{
		oMusicPlayer::GetInstance()->Close();
	}

	bool oIsMusicEnd()
	{
		return (oMusicPlayer::GetInstance()->GetState() == PS_STOP);
	}

	oObjectID oCreateObject(oImageID imageID, int X, int Y, int Z)
	{
		imageID--;
		if (0 <= imageID && (oUInt)imageID < g_kImageList.size())
		{
			oObject* pkObj = new oObject();
			oImage* pkImage = g_kImageList[imageID];
			pkObj->SetImage(pkImage);
			pkObj->SetSize(pkImage->GetWidth(), pkImage->GetHeight());
			pkObj->SetPosition(X,Y);
			pkObj->SetZIndex(Z);
			pkObj->SetGroup(&g_kGroup);
			return (oObjectID)pkObj;
		}
		return ID_NONE;
	}

	void oSetObjVisible(oObjectID objID, bool bVisible)
	{
		oObject* pkObj = (oObject*)objID;
		pkObj->SetVisible(bVisible);
	}

	void oSetObjDetective(oObjectID objID, bool bDetective)
	{
		oObject* pkObj = (oObject*)objID;
		pkObj->SetDetective(bDetective);
	}

	int oGetObjX(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		return pkObj->GetX();
	}

	int oGetObjY(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		return pkObj->GetY();
	}

	int oGetObjWidth(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		return pkObj->GetWidth();
	}

	int oGetObjHeight(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		return pkObj->GetHeight();
	}

	bool oIsObjVisible(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		return pkObj->IsVisible();
	}

	bool oIsObjDetective(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		return pkObj->IsDetective();
	}

	void oSetObjPosition(oObjectID objID, int X, int Y)
	{
		oObject* pkObj = (oObject*)objID;
		pkObj->SetPosition(X,Y);
	}

	void oSetObjZIndex(oObjectID objID, int Z)
	{
		oObject* pkObj = (oObject*)objID;
		pkObj->SetZIndex(Z);
		g_kGroup.Update();
	}

	void oDrawAllObject()
	{
		g_kGroup.Render();
	}

	oObjectID oGetCollision(oObjectID objID, bool checkImage)
	{
		oObject* pkObj = (oObject*)objID;
		vector<oObject*>& collisionList = g_kGroup.GetCollisionList(pkObj,checkImage);
		if (collisionList.size() != 0)
		{
			return (oObjectID)collisionList[0];
		}
		return ID_NONE;
	}

	void oDrawObject(oObjectID objID)
	{
		oObject* pkObj = (oObject*)objID;
		pkObj->Render();
	}

	void oDestroyObject( oObjectID objID )
	{
		delete (oObject*)objID;
	}
}
