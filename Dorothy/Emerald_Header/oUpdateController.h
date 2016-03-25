#pragma once
#include <vector>
using std::vector;
#pragma once
#include "oIUpdate.h"

namespace Dorothy
{
	class oUpdateController
	{
	public:
		oUpdateController();
		void Update();
		void Register(oIUpdate* pkUpdate);
		void UnRegister(oIUpdate* pkUpdate);
		void SetEnabled(bool enable);
		bool IsEnabled() const;
		static oUpdateController* GetInstance();
	private:
		bool m_bEnabled;
		vector<oIUpdate*> m_kList;
		static oUpdateController* m_pkInstance;
	};
}