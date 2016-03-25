#pragma once
#include "oDataTypes.h"
#include "oIUpdate.h"
#include "AcfDelegate.h"
using Acf::Delegate;

namespace Dorothy
{
	template class DLLEXPORT Delegate<void ()>;
	typedef Delegate<void ()> oTimerHandler;
	class DLLEXPORT oTimer:public oIUpdate
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
}