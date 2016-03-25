#include "oBoxPicker.h"
using namespace Scarecrow;
#include <Box2D/Box2D.h>

//矩形区域相交查询用的类
class QueryCallback: public b2QueryCallback
{
public:
	QueryCallback(const b2Vec2& point)
	{
		m_kPoint = point;
		m_pkFixture = NULL;
	}
	bool ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(m_kPoint);
			if (inside)
			{
				m_pkFixture = fixture;
				return false;
			}
		}
		return true;
	}
	b2Vec2 m_kPoint;
	b2Fixture* m_pkFixture;//用来存储查询结果
};

oBoxPicker::oBoxPicker():m_pkJoint(NULL){}

oBoxPicker::~oBoxPicker()
{
	oBoxPicker::Drop();
}

oBox* oBoxPicker::Pick( const oPoint& kWorldPoint )
{
	if (m_pkJoint != NULL)
	{
		return NULL;
	}
	b2World* pkWorld = (b2World*)(oPhysicWorld::GetInstance()->GetWorld());
	b2Body* pkGround = (b2Body*)(oPhysicWorld::GetInstance()->GetGround());
	b2Vec2 kPickPoint;
	kPickPoint.Set(oB2Value(kWorldPoint.x),oB2Value(kWorldPoint.y));
	//创建一个小矩形
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = kPickPoint - d;
	aabb.upperBound = kPickPoint + d;
	//查询与该AABB相交的物体
	QueryCallback callback(kPickPoint);
	pkWorld->QueryAABB(&callback, aabb);
	if (callback.m_pkFixture)
	{
		b2Body* body = callback.m_pkFixture->GetBody();
		b2MouseJointDef md;
		md.collideConnected = true;
		md.bodyA = pkGround;
		md.bodyB = body;
		md.target = kPickPoint;
		md.maxForce = 1000.0f * body->GetMass();
		m_pkJoint = (b2MouseJoint*)pkWorld->CreateJoint(&md);
		body->SetAwake(true);
		return (oBox*)(body->GetUserData());
	}
	return NULL;
}

void oBoxPicker::Move( const oPoint& kWorldPoint )
{
	if (m_pkJoint)
	{
		((b2MouseJoint*)m_pkJoint)->SetTarget(b2Vec2(oB2Value(kWorldPoint.x), oB2Value(kWorldPoint.y)));
	}
}

void oBoxPicker::Drop()
{
	if (m_pkJoint)
	{
		b2World* pkWorld = (b2World*)(oPhysicWorld::GetInstance()->GetWorld());
		pkWorld->DestroyJoint((b2MouseJoint*)m_pkJoint);
		m_pkJoint = NULL;
	}
}

void Scarecrow::oBoxPicker::GetJointLine( oPoint& kPointA, oPoint& kPointB )
{
	if (m_pkJoint)
	{
		b2MouseJoint* pkMouseJoint = (b2MouseJoint*)m_pkJoint;
		kPointA.x = oDoroValue(pkMouseJoint->GetAnchorA().x);
		kPointA.y = oDoroValue(pkMouseJoint->GetAnchorA().y);
		kPointB.x = oDoroValue(pkMouseJoint->GetAnchorB().x);
		kPointB.y = oDoroValue(pkMouseJoint->GetAnchorB().y);
	}
}

bool oBoxPicker::IsPicking() const
{
	return (m_pkJoint != NULL);
}