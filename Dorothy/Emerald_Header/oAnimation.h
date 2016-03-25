#pragma once
#include "oSprite.h"
#include "oGame.h"
#include "oIUpdate.h"
#include "AcfDelegate.h"
using Acf::Delegate;

namespace Dorothy
{
	class oAnimation;
	template class DLLEXPORT Delegate<void (oAnimation*)>;
	typedef Delegate<void (oAnimation*)> oAnimationHandler;
	class DLLEXPORT oAnimation:public oIUpdate
	{
	public:
		oAnimation();
		void SetTarget(oSprite* pkSprite);
		void SetSpeed(float fSpeed);
		void SetLoop(bool bLoop);
		void SetReverse(bool bReverse);
		oSprite* GetTarget();
		bool IsPlaying() const;
		void Start();
		void End();
		void Stop();
		oAnimationHandler OnEnd;
	protected:
		virtual void PreStart() = 0;
		virtual bool UpdateFrame() = 0;
		virtual void PreEnd() = 0;
		bool m_bPlay;
		bool m_bLoop;
		bool m_bReverse;
		bool m_bIsReversing;
		oUInt m_nCount;
		float m_fAdd;
		float m_fCurrent;
		oSprite* m_pkTarget;
	private:
		virtual void Update();
	};
}