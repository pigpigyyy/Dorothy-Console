#include "oPhysicWorld.h"
using namespace Scarecrow;
#include <Box2D/Box2D.h>
#include <list>
using std::list;
#include <unordered_map>
using std::unordered_map;
using std::pair;

/************************************************************************/
/* 以下是碰撞检测用的                                                   */
/************************************************************************/

struct oContactInfo
{
	oBox* pkBox;
	oPoint kPoint;
};

typedef unordered_map<intptr_t,oContactInfo> oContactTable;
static const int MAX_CONTACT = 1024;
static oContactTable g_kContactTable;
static intptr_t g_pkContactKeyList[MAX_CONTACT];
static int g_iContactCount = 0;

/*碰撞事件监听类*/
class oContactListener: public b2ContactListener
{
public:
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		const b2Manifold* manifold = contact->GetManifold();
		if (manifold->pointCount == 0 || g_iContactCount >= MAX_CONTACT)
		{
			return;
		}
		b2WorldManifold kWorldManifold;
		contact->GetWorldManifold(&kWorldManifold);
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		oBox* pkBox = (oBox*)(fixtureB->GetBody()->GetUserData());
		if (pkBox != NULL)
		{
			intptr_t key = (intptr_t)(fixtureA->GetBody()->GetUserData());
			g_pkContactKeyList[g_iContactCount] = key;
			g_iContactCount++;
			oContactInfo& kInfo = g_kContactTable[key];
			kInfo.pkBox = pkBox;
			kInfo.kPoint.x = oDoroValue(kWorldManifold.points[0].x);
			kInfo.kPoint.y = oDoroValue(kWorldManifold.points[0].y);
		}
		pkBox = (oBox*)(fixtureA->GetBody()->GetUserData());
		if (pkBox != NULL)
		{
			intptr_t key = (intptr_t)(fixtureB->GetBody()->GetUserData());
			g_pkContactKeyList[g_iContactCount] = key;
			g_iContactCount++;
			oContactInfo& kInfo = g_kContactTable[key];
			kInfo.pkBox = pkBox;
			kInfo.kPoint.x = oDoroValue(kWorldManifold.points[0].x);
			kInfo.kPoint.y = oDoroValue(kWorldManifold.points[0].y);
		}
	}
};

class oContactFilter : public b2ContactFilter
{
public:
	virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
	{
		return true;
	}
};

static list<oEdge> g_kEdgeList;
static b2World* g_pkWorld;
static b2Body* g_pkGround;
static oContactListener g_kContactListener;
static oContactFilter g_kContactFilter;

oPhysicWorld* oPhysicWorld::m_pkInstance = NULL;

oPhysicWorld::oPhysicWorld( float fGravityX, float fGravityY, int iFPS, int iVelocityIterations, int iPositionIterations )
{
	b2Vec2 gravity(fGravityX, fGravityY);
	g_pkWorld = new b2World(gravity);
	g_pkWorld->SetContactListener(&g_kContactListener);
	g_pkWorld->SetContactFilter(&g_kContactFilter);
	oPhysicWorld::SetStepParams(iFPS, iVelocityIterations, iPositionIterations);
	g_pkGround = NULL;
	oPhysicWorld::SetUpGround();
	oIUpdate::Register();
	m_pkInstance = this;
}

oPhysicWorld::~oPhysicWorld()
{
	oIUpdate::UnRegister();
	delete g_pkWorld;
	g_pkWorld = NULL;
}

void oPhysicWorld::SetStepParams( int iFPS, int iVelocityIterations, int iPositionIterations )
{
	m_fTimeStep = 1.0f/iFPS;
	m_iVelocityIterations = iVelocityIterations;
	m_iPositionIterations = iPositionIterations;
}

void oPhysicWorld::Update()
{
	for (int i = 0;i < g_iContactCount;i++)
	{
		g_kContactTable[(intptr_t)g_pkContactKeyList[i]].pkBox = NULL;
	}
	g_iContactCount = 0;
	g_pkWorld->Step(m_fTimeStep, m_iVelocityIterations, m_iPositionIterations);
	g_pkWorld->ClearForces();
}

oPhysicWorld* oPhysicWorld::GetInstance()
{
	return m_pkInstance;
}

oB2World* oPhysicWorld::GetWorld()
{
	return (oB2World*)g_pkWorld;
}

void oPhysicWorld::AttachEdge( int X1, int Y1, int X2, int Y2, float fFraction, float fRestitution )
{
	oEdge kEdge = {X1,Y1,X2,Y2};
	g_kEdgeList.push_back(kEdge);
	b2ChainShape kShape;
	b2Vec2 vs[] = {
		b2Vec2(oB2Value(X1), oB2Value(Y1)),
		b2Vec2(oB2Value(X2), oB2Value(Y2))
	};
	kShape.CreateChain(vs, 2);
	b2FixtureDef kFixtureDef;
	kFixtureDef.shape = &kShape;
	kFixtureDef.density = 0.0f;
	kFixtureDef.friction = fFraction;
	kFixtureDef.restitution = fRestitution;
	g_pkGround->CreateFixture(&kFixtureDef);
}

int oPhysicWorld::GetEdgeAmount()
{
	return g_kEdgeList.size();
}

const oEdge& oPhysicWorld::GetEdge( int iSubscript )
{
	list<oEdge>::iterator it = g_kEdgeList.begin();
	for (int i = 0;i < iSubscript;i++,it++);
	return (*it);
}

void oPhysicWorld::RemoveEdge( int iSubscript )
{
	b2Fixture* pkFixture = g_pkGround->GetFixtureList();
	for (int i = 0;i < iSubscript;i++,pkFixture = pkFixture->GetNext());
	g_pkGround->DestroyFixture(pkFixture);
	list<oEdge>::iterator it = g_kEdgeList.begin();
	for (int i = 0;i < iSubscript;i++,it++);
	g_kEdgeList.erase(it);
}

void oPhysicWorld::ClearEdges()
{
	g_kEdgeList.clear();
	oPhysicWorld::SetUpGround();
}

void oPhysicWorld::SetUpGround()
{
	if (g_pkGround != NULL)
	{
		g_pkWorld->DestroyBody(g_pkGround);
	}
	b2BodyDef kBodyDef;
	kBodyDef.type = b2_staticBody;
	kBodyDef.position.Set(0.0f, 0.0f);
	g_pkGround = g_pkWorld->CreateBody(&kBodyDef);
	g_pkGround->SetUserData(NULL);
}

oBox* oPhysicWorld::GetCollision( const oBox* pkBox, oPoint& kContactPoint )
{
	oContactTable::iterator it = g_kContactTable.find((intptr_t)pkBox);
	if (it != g_kContactTable.end())
	{
		kContactPoint.x = it->second.kPoint.x;
		kContactPoint.y = it->second.kPoint.y;
		return it->second.pkBox;
	}
	return NULL;
}

oB2Body* oPhysicWorld::GetGround()
{
	return (oB2Body*)g_pkGround;
}
