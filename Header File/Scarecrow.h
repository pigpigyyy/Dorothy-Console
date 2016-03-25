//Dorothy 1.50
#pragma once
#include "Dorothy.h"
using namespace Dorothy;
#pragma comment(lib, "Scarecrow.lib")

#define B2FACTOR 10.0f

typedef void oB2World;
typedef void oB2Body;
typedef void oB2Joint;

inline float oB2Value(int value)
{
	return (float)value/B2FACTOR;
}

inline float oB2Value(float value)
{
	return value/B2FACTOR;
}

inline int oDoroValue(float value)
{
	return (int)(value*B2FACTOR);
}

struct oEdge
{
	int X1;
	int Y1;
	int X2;
	int Y2;
};

struct oBoxInfo
{
	bool bDynamic;
	float fDensity;
	float fFraction;
	float fRestitution;
};

namespace Scarecrow
{
	class DLLIMPORT oBox:public oObject,oIUpdate
	{
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

	class DLLIMPORT oPhysicWorld:public oIUpdate
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

	class DLLIMPORT oBoxFactory
	{
	public:
		static oBox* CreateRectBox(oImage* pkImage, int X, int Y, const oBoxInfo& kInfo);
		static oBox* CreateCircleBox(oImage* pkImage, int X, int Y, const oBoxInfo& kInfo);
		static void DestroyBox(oBox*& pkBox);
	};

	class DLLIMPORT oBoxPicker
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