#pragma once
#include <time.h>
#include "oDataTypes.h"

namespace Dorothy
{
	class DLLEXPORT oDateTime
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
}