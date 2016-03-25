#pragma once

#include "oDataTypes.h"
#include "oObject.h"
#include "oScreen.h"

namespace Dorothy
{
	class DLLEXPORT oSprite:public oObject
	{
	public:
		oSprite(bool bImageBased = false);
		void SetRenderRect(const RECT& rect);
		float GetScaleX() const;
		float GetScaleY() const;
		int GetAngle() const;
		virtual void SetScale(float fScaleX, float fScaleY);
		virtual void SetAngle(int iAngle);
		virtual void SetPosition(int X, int Y);
		virtual void SetSize(int width, int height);
		virtual const oRect* GetRect() const;
		virtual oColor GetDisplayColor(int X, int Y) const;
		virtual char GetDisplayChar(int X, int Y) const;
		virtual void Render();
	protected:
		const bool m_bImageBased;
	private:
		void UpdateRenderData();
		bool m_bUpdateRender;
		bool m_bUpdatePos;
		bool m_bFlipX;
		bool m_bFlipY;
		float m_fCosA;
		float m_fSinA;
		float m_fScaleX;
		float m_fScaleY;
		int m_iAngle;
		int m_iRenderWidth;
		int m_iRenderHeight;
		oRect m_kImgRect;
		RECT m_kRenderRect;
		float m_fRotMinWidth;
		float m_fRotMinHeight;
	};
}