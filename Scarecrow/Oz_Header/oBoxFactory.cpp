#include "oBoxFactory.h"
using namespace Scarecrow;
#include <Box2D/Box2D.h>

static b2Body* CreateFromShape(oImage* pkImage, int X, int Y, const oBoxInfo& kInfo, b2Shape* pkShape)
{
	b2World* pkWorld = (b2World*)oPhysicWorld::GetInstance()->GetWorld();

	int iWidth = pkImage->GetWidth();
	int iHeight = pkImage->GetHeight();

	b2BodyDef kBodyDef;
	kBodyDef.type = (kInfo.bDynamic ? b2_dynamicBody : b2_staticBody);

	kBodyDef.position.Set(oB2Value(X+iWidth*0.5f),
		oB2Value(Y+iHeight*0.5f));

	b2Body* pkBody = pkWorld->CreateBody(&kBodyDef);

	b2FixtureDef kFixtureDef;
	kFixtureDef.shape = pkShape;
	kFixtureDef.density = kInfo.fDensity;
	kFixtureDef.friction = kInfo.fFraction;
	kFixtureDef.restitution = kInfo.fRestitution;

	pkBody->CreateFixture(&kFixtureDef);

	return pkBody;
}


oBox* oBoxFactory::CreateRectBox( oImage* pkImage, int X, int Y, const oBoxInfo& kInfo )
{
	oBox* pkBox = new oBox(pkImage);
	pkBox->SetPosition(X, Y);

	b2PolygonShape kBoxShape;
	kBoxShape.SetAsBox(
		oB2Value(pkImage->GetWidth()*0.5f),
		oB2Value(pkImage->GetHeight()*0.5f));

	b2Body* pkBody = CreateFromShape(pkImage, X, Y, kInfo, &kBoxShape);

	pkBody->SetUserData((void*)pkBox);
	pkBox->m_pkBody = (oB2Body*)pkBody;

	return pkBox;
}

oBox* oBoxFactory::CreateCircleBox( oImage* pkImage, int X, int Y, const oBoxInfo& kInfo )
{
	oBox* pkBox = new oBox(pkImage);
	pkBox->SetPosition(X, Y);

	b2CircleShape kCircleShape;
	kCircleShape.m_radius = oB2Value((pkImage->GetWidth()+pkImage->GetHeight())*0.25f);

	b2Body* pkBody = CreateFromShape(pkImage, X, Y, kInfo, &kCircleShape);

	pkBody->SetUserData((void*)pkBox);
	pkBox->m_pkBody = (oB2Body*)pkBody;

	return pkBox;
}

void oBoxFactory::DestroyBox( oBox*& pkBox )
{
	delete pkBox;
	pkBox = NULL;
}
