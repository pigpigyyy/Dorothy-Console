#pragma once
#include "oScreen.h"
#include "oObject.h"
#include "oIUpdate.h"

namespace Dorothy
{
	class DLLEXPORT oCamera:public oIUpdate
	{
	public:
		oCamera();
		~oCamera();
		void LockAt(const oObject* pkTarget, float fOriginX = 0.5f, float fOriginY = 0.5f);
		void Zoom(float fZoom);
		void Move(int X, int Y);
		float GetZoom() const;
		int GetX() const;
		int GetY() const;
		const oObject* GetTarget() const;
	private:
		virtual void Update();
		int m_iX;
		int m_iY;
		float m_fZoom;
		float m_fOriginX;
		float m_fOriginY;
		const oObject* m_pkTarget;
	};
}