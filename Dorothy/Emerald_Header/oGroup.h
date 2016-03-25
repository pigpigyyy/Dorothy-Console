#pragma once

#include "oObject.h"
#include <vector>
using std::vector;

namespace Dorothy
{
	class DLLEXPORT oGroup
	{
		friend class oObject;
	public:
		oGroup();
		oObject* First();
		oObject* Last();
		void Clear();
		void Update();
		void Render();
		vector<oObject*>& GetItems() const;
		vector<oObject*>& GetCollisionList(oObject* pkObject, bool bCheckImage = false) const;
		vector<oObject*>& GetCollisionList(const oPoint& kPoint, bool bCheckImage = false) const;
	private:
		oObject* m_pkFirst;
		oObject* m_pkLast;
	};
}