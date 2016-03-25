#pragma once
#include "oDataTypes.h"

namespace Dorothy
{
	class DLLEXPORT oZIndexListener
	{
	public:
		oZIndexListener();
		void NotifyZChange();
	protected:
		bool m_bZChanged;
	};
}