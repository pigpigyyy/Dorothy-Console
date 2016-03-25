#pragma once

#define DLLEXPORT __declspec(dllexport)

typedef   char             oInt8;
typedef   unsigned char    oUInt8;
typedef   short            oInt16;
typedef   unsigned short   oUInt16;
typedef   long             oInt32;
typedef   unsigned long    oUInt32;
typedef   int              oInt;
typedef   unsigned int     oUInt;

typedef   float            oReal32;
typedef   double           oReal64;

struct oPoint
{
	int x;
	int y;
};
