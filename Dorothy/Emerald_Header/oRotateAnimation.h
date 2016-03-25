#pragma once
#include "oAnimation.h"

namespace Dorothy
{
	class DLLEXPORT oRotateAnimation:public oAnimation
	{
	public:
		oRotateAnimation();
		void SetRotate(int iAngleFrom,int iAngleTo,oUInt iDuration);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		int m_iAngleFrom;
		int m_iAngleTo;
		float m_dAngle;
	};
}
