#pragma once
#include <Windows.h>
#include "oDataTypes.h"

namespace Dorothy
{
	class DLLEXPORT oAccurateTimer
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
}