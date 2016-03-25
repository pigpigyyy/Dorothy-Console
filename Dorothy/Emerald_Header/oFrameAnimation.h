#pragma once
#include "oAnimation.h"

namespace Dorothy
{
	class DLLEXPORT oFrameAnimation:public oAnimation
	{
	public:
		oFrameAnimation();
		~oFrameAnimation();
		void SetUpFrame(oUInt nFrame);
		void SetFrame(oUInt nSubScript,const RECT& kRenderRect,oUInt nKeepTime);
		void operator=(const oFrameAnimation& kFrame);
	protected:
		virtual void PreStart();
		virtual bool UpdateFrame();
		virtual void PreEnd();
	private:
		RECT* m_pkRenderRectList;
		oUInt* m_pnKeepTime;
		int m_iCurrentFrame;
		oUInt m_nFrameNum;
	};
}
