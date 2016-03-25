#pragma once
#include "oDataTypes.h"

namespace Dorothy
{
	class oUpdateController;

	class DLLEXPORT oIUpdate
	{
		friend class oUpdateController;
	public:
		oIUpdate();
		virtual ~oIUpdate();
		static void SetAutoManaged(bool autoManaged);
		static bool IsAutoManaged();
		virtual void Update() = 0;
		void Register();
		void UnRegister();
		bool IsRegistered() const;
	private:
		int m_ID;
	};
}
