#pragma once
#include "oDataTypes.h"
#include "Dorothy.h"
using namespace Dorothy;

namespace Scarecrow
{
	class oBox;

	class DLLEXPORT oPhysicWorld:public oIUpdate
	{
	public:
		oPhysicWorld(float fGravityX, float fGravityY, int iFPS = 30,
			int iVelocityIterations = 8, int iPositionIterations = 3);
		~oPhysicWorld();
		void SetStepParams(int iFPS, int iVelocityIterations,
			int iPositionIterations);
		oB2World* GetWorld();
		oB2Body* GetGround();
		void AttachEdge(int X1, int Y1, int X2, int Y2, float fFraction = 0.2f, float fRestitution = 0.0f);
		int GetEdgeAmount();
		const oEdge& GetEdge(int iSubscript);
		void RemoveEdge(int iSubscript);
		void ClearEdges();
		oBox* GetCollision(const oBox* pkBox, oPoint& kContactPoint);
		static oPhysicWorld* GetInstance();
	private:
		virtual void Update();
		void SetUpGround();
		int m_iVelocityIterations;
		int m_iPositionIterations;
		float m_fTimeStep;
		static oPhysicWorld* m_pkInstance;
	};
}