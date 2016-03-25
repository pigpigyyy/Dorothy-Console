#pragma once
#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <algorithm>
using std::fill;
using std::swap;
#include <cstdlib>
#include <ctime>
#include "oDataTypes.h"

namespace Wizard
{
	enum oBorder{N_BORDER,S_BORDER,W_BORDER,E_BORDER};
	enum oMapInfo{WALL,ROAD,NONE};
	class DLLEXPORT oMaze
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