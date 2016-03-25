#pragma once

#define DLLEXPORT __declspec(dllexport)

#define PI 3.14159265359f

#define B2FACTOR 10.0f

typedef void oB2World;
typedef void oB2Body;
typedef void oB2Joint;

inline int oR2D(float radian)
{
	return (int)(180.0f*radian/PI);
}

inline float oD2R(int degree)
{
	return (float)degree*PI/180.0f;
}

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

struct oBoxInfo
{
	bool bDynamic;
	float fDensity;
	float fFraction;
	float fRestitution;
};

struct oEdge
{
	int X1;
	int Y1;
	int X2;
	int Y2;
};

