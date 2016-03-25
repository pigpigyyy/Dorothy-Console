#pragma once
#include "oAnimation.h"

namespace Dorothy
{
	class DLLEXPORT oMoveAnimation:public oAnimation
	{
	public:
		oMoveAnimation();
		void SetMove(int iMoveXFrom,int iMoveXTo,
			int iMoveYFrom,int iMoveYTo,oUInt iDuration);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		int m_iMoveXFrom;
		int m_iMoveXTo;
		float m_dMoveX;
		int m_iMoveYFrom;
		int m_iMoveYTo;
		float m_dMoveY;
	};
}
