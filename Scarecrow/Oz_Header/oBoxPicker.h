#pragma once
#include "Dorothy.h"
#include "oPhysicWorld.h"

namespace Scarecrow
{
	class DLLEXPORT oBoxPicker
	{
	public:
		oBoxPicker();
		~oBoxPicker();
		oBox* Pick(const oPoint& kWorldPoint);
		void Move(const oPoint& kWorldPoint);
		void Drop();
		bool IsPicking() const;
		void GetJointLine(oPoint& kStart, oPoint& kEnd);
	private:
		oB2Joint* m_pkJoint;
	};
}
