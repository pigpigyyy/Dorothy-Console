#include "oMaze.h"
using namespace Wizard;

const static int h[4] = {0,-1,1,0};
const static int v[4] = {1,0,0,-1};

oMaze::oMaze():
m_Map(NULL),
m_ppMark(NULL),
m_iLength(10),
m_iDifficulty(100)
{
	srand((oUInt)time(0));
}

oMaze::~oMaze()
{
	oMaze::Release();
}

void oMaze::Generate(int length, int difficulty)
{
	if (1 <= difficulty && difficulty <= 100)
	{
		m_iDifficulty = difficulty;
	}
	oMaze::InitMap(length);
	oMaze::Mapping(length/2,length/2);
	for (int r = 1;r <= length;r++)
	{
		m_Map[r][1] = m_Map[r][0] = WALL;
		m_Map[r][length] = m_Map[r][length+1] = WALL;
	}
	for (int c = 1;c <= length;c++)
	{
		m_Map[1][c] = m_Map[0][c] = WALL;
		m_Map[length][c] = m_Map[length+1][c] = WALL;
	}
	oMaze::SetEntrance(W_BORDER);
	oMaze::SetExit(E_BORDER);
}

void oMaze::InitMap(int length)
{
	if (m_iLength != length)
	{
		oMaze::Release();
	}
	m_iLength = length;
	int iRealLength = length+2;
	if (NULL == m_Map)
	{
		m_Map = new oMapInfo*[iRealLength];
		m_ppMark = new int*[iRealLength];
		for (int i = 0;i < iRealLength;i++)
		{
			m_Map[i] = new oMapInfo[iRealLength];
			m_ppMark[i] = new int[iRealLength];
		}
	}
	for (int i = 0;i < iRealLength;i++)
	{
		if (i == 0 || i == iRealLength-1)
		{
			fill(m_Map[i],m_Map[i]+iRealLength,ROAD);
		}
		else
		{
			fill(m_Map[i]+1,m_Map[i]+iRealLength-1,WALL);
			m_Map[i][0] = m_Map[i][iRealLength-1] = ROAD;
		}
	}
	m_kEntrance.x = m_kEntrance.y = m_kExit.x = m_kExit.y = -1;
}

void oMaze::GetBorderlinePoint(oPoint& point, oBorder whichborder)
{
	switch(whichborder)
	{
	case E_BORDER:
		{
			point.x = m_iLength;
			do point.y = 1+rand()%m_iLength;
			while (m_Map[point.y][m_iLength-1] == WALL);
		}
		break;
	case N_BORDER:
		{
			point.y = 1;
			do point.x = 1+rand()%m_iLength;
			while (m_Map[2][point.x] == WALL);
		}
		break;
	case W_BORDER:
		{
			point.x = 1;
			do point.y = 1+rand()%m_iLength;
			while (m_Map[point.y][2] == WALL);
		}
		break;
	case S_BORDER:
		{
			point.y = m_iLength;
			do point.x = 1+rand()%m_iLength;
			while (m_Map[m_iLength-1][point.x] == WALL);
		}
		break;

	default:
		break;
	}
}

void oMaze::SetEntrance(oBorder whichBorder)
{
	oPoint temp;
	GetBorderlinePoint(temp,whichBorder);
	if (m_kEntrance.x != -1)
	{
		m_Map[m_kEntrance.y][m_kEntrance.x] = WALL;
	}
	m_kEntrance.x = temp.x;
	m_kEntrance.y = temp.y;
	m_Map[m_kEntrance.y][m_kEntrance.x] = ROAD;
}

void oMaze::SetExit(oBorder whichBorder)
{
	oPoint temp;
	GetBorderlinePoint(temp,whichBorder);
	if (m_kExit.x != -1)
	{
		m_Map[m_kExit.y][m_kExit.x] = WALL;
	}
	m_kExit.x = temp.x;
	m_kExit.y = temp.y;
	m_Map[m_kExit.y][m_kExit.x] = ROAD;
}

int oMaze::GetEntranceX()
{
	return m_kEntrance.x-1;
}

int oMaze::GetEntranceY()
{
	return m_kEntrance.y-1;
}

int oMaze::GetExitX()
{
	return m_kExit.x-1;
}

int oMaze::GetExitY()
{
	return m_kExit.y-1;
}

void oMaze::Mapping(int R,int C)
{
	int DirOrder[4] = {0,1,2,3},Dir;
	for (int Face = 0;Face < 4;Face++)
	{
		Dir = rand()%4;
		swap(DirOrder[Face],DirOrder[Dir]);
	}
	m_Map[R][C] = ROAD;//迷宫道路设为ROAD，墙为WALL
	for (int Face = 0;Face < 4;Face++)
	{
		Dir = DirOrder[Face];
		if ( m_Map[R+v[Dir]][C+h[Dir]] == WALL )
		{
			bool bCanGo = true;
			int n = (m_iDifficulty == 100 ? 1 : rand()%m_iDifficulty);//每个点成为分岔路口的几率为1/m_iDifficulty
			for (int FaceToWall = 0;FaceToWall < 4;FaceToWall++)
			{
				if ( FaceToWall == 3-Dir || n == 0 )
				{
					continue;
				}
				if ( m_Map[R+v[Dir]+v[FaceToWall]][C+h[Dir]+h[FaceToWall]] == ROAD )
				{
					bCanGo = false;
				}
			}
			if (bCanGo)
			{
				oMaze::Mapping(R+v[Dir],C+h[Dir]);
			}
		}
	}
}

void oMaze::GetPath(const oPoint& begin, const oPoint& end, vector<oPoint>& ThePath)
{
	int startY = begin.y+1;
	int startX = begin.x+1;
	int endY = end.y+1;
	int endX = end.x+1;
	//如果起始点和终点不是可通行的点就直接退出
	if (m_Map[startY][startX] != ROAD
		|| m_Map[endY][endX] != ROAD)
	{
		return;
	}
	int iRealLength = m_iLength+2;
	for (int i = 0;i < iRealLength;i++)
	{
		fill(m_ppMark[i],m_ppMark[i]+iRealLength,4);
	}
	//从出口起遍历迷宫直到遇到入口，每走一步做下移动方向的标记
	queue<oPoint> PointList;
	oPoint TempPoint,FrontPoint;
	TempPoint.x = endX;
	TempPoint.y = endY;
	PointList.push(TempPoint);
	bool bSearching = true;
	while (bSearching && !PointList.empty())
	{
		FrontPoint = PointList.front();
		PointList.pop();
		for (int i = 0;i < 4;i++)
		{
			int R = FrontPoint.y+v[i];
			int C = FrontPoint.x+h[i];
			if (R < 0 || R >= iRealLength
				|| C < 0 || C >= iRealLength)
			{
				continue;
			}
			if (m_Map[R][C] == ROAD && m_ppMark[R][C] == 4)
			{
				TempPoint.y = R;
				TempPoint.x = C;
				m_ppMark[TempPoint.y][TempPoint.x] = 3-i;
				if (TempPoint.y == startY && TempPoint.x == startX)
				{
					bSearching = false;
				}
				else
				{
					PointList.push(TempPoint);
				}
			}
		}
	}
	//从入口起顺着标记到达出口，并把路径存入ThePath里
	TempPoint.x = m_kEntrance.x;
	TempPoint.y = m_kEntrance.y;
	TempPoint.y--;TempPoint.x--;
	ThePath.push_back(TempPoint);
	TempPoint.y++;TempPoint.x++;
	while (!(TempPoint.x == m_kExit.x && TempPoint.y == m_kExit.y))
	{
		int C = TempPoint.x;
		int R = TempPoint.y;
		TempPoint.x += h[m_ppMark[R][C]];
		TempPoint.y += v[m_ppMark[R][C]];
		TempPoint.y--;TempPoint.x--;
		ThePath.push_back(TempPoint);
		TempPoint.y++;TempPoint.x++;
	}
}

int oMaze::GetLength()
{
	return m_iLength;
}

oMapInfo oMaze::GetMap(int x,int y)
{
	if (x >= m_iLength || y < 0)
	{
		return NONE;
	}
	else
	{
		return m_Map[y+1][x+1];
	}
}

void oMaze::Release()
{
	if (m_Map != NULL)
	{
		int iRealLength = m_iLength+2;
		for (int i = 0;i < iRealLength;i++)
		{
			delete [] m_Map[i];
			m_Map[i] = NULL;
		}
		delete [] m_Map;
		m_Map = NULL;
		for (int i = 0;i < iRealLength;i++)
		{
			delete [] m_ppMark[i];
			m_ppMark[i] = NULL;
		}
		delete [] m_ppMark;
		m_ppMark = NULL;
	}
}
