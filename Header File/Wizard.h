//Dorothy 1.10
#pragma once
#include <vector>
using std::vector;
#pragma comment(lib, "Wizard.lib")

#define DLLIMPORT __declspec(dllimport)

#ifndef OPOINT_DEFINED
#define OPOINT_DEFINED
struct oPoint
{
	int x;
	int y;
};
#endif

namespace Wizard
{
	enum oBorder{N_BORDER,S_BORDER,W_BORDER,E_BORDER};
	enum oMapInfo{WALL,ROAD,NONE};
	class DLLIMPORT oMaze
	{
	public:
		oMaze();
		~oMaze();
		void Generate(int length = 10, int difficulty = 100);
		void SetEntrance(oBorder whichBorder);
		void SetExit(oBorder whichBorder);
		int GetEntranceX();
		int GetEntranceY();
		int GetExitX();
		int GetExitY();
		int GetLength();
		oMapInfo GetMap(int x, int y);
		void GetPath(const oPoint& begin, const oPoint& end,
			vector<oPoint>& ThePath);
	private:
		void Release();
		void InitMap(int length);
		void Mapping(int R,int C);
		void GetBorderlinePoint(oPoint& point, oBorder whichborder);
		oMapInfo **m_Map;
		int** m_ppMark;
		int m_iLength;
		int m_iDifficulty;
		oPoint m_kEntrance;
		oPoint m_kExit;
	};
}