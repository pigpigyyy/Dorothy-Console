#include "oDataTypes.h"
#include <math.h>

static float sin_value[360];
static float cos_value[360];

class oMathInitializer
{
public:
	oMathInitializer()
	{
		for (int i = 0;i < 360;i++)
		{
			sin_value[i] = sin(((float)i/180)*PI);
			cos_value[i] = cos(((float)i/180)*PI);
		}
	}
};

static oMathInitializer Init;

float oSin(int iAngle)
{
	iAngle %= 360;
	iAngle += (iAngle < 0 ? 360 : 0);
	return sin_value[iAngle];
}

float oCos(int iAngle)
{
	iAngle %= 360;
	iAngle += (iAngle < 0 ? 360 : 0);
	return cos_value[iAngle];
}

