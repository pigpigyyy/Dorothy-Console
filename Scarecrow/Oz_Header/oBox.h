#pragma once

#include "Dorothy.h"
using namespace Dorothy;
#include "oDataTypes.h"
#include "oPhysicWorld.h"

namespace Scarecrow
{
	class oBoxFactory;

	class DLLEXPORT oBox:public oObject,oIUpdate
	{
		friend class oBoxFactory;
	public:
		oBox(oImage* pkImage);
		~oBox();
		void ApplyForce(int x, int y, int iAngle, int iPower);
		void SetVelocity(int Vx, int Vy);
		void SetAngle(int iAngle);
		int GetAngle() const;
		virtual void SetPosition(int X, int Y);
		virtual oColor GetDisplayColor(int X, int Y) const;
		virtual char GetDisplayChar(int X, int Y) const;
	private:
		virtual void Update();
		virtual void Render();
		void UpdateRenderData();
		bool m_bUpdateRender;
		bool m_bUpdatePos;
		oRect m_kImgRect;
		float m_fCosA;
		float m_fSinA;
		int m_iAngle;
		int m_iRenderWidth;
		int m_iRenderHeight;
		float m_fRotMinWidth;
		float m_fRotMinHeight;
		oB2Body *m_pkBody;
	};
}