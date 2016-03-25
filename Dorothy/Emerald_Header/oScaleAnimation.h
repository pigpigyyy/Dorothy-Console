#pragma once
#include "oAnimation.h"

namespace Dorothy
{
	class DLLEXPORT oScaleAnimation:public oAnimation
	{
	public:
		oScaleAnimation();
		void SetScale(float fScaleXFrom,float fScaleXTo,
			float fScaleYFrom,float fScaleYTo,oUInt iDuration);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		float m_fScaleXFrom;
		float m_fScaleXTo;
		float m_dScaleX;
		float m_fScaleYFrom;
		float m_fScaleYTo;
		float m_dScaleY;
	};
}
