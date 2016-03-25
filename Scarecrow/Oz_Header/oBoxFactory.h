#pragma once

#include "oDataTypes.h"
#include "oPhysicWorld.h"
#include "oBox.h"

namespace Scarecrow
{
	class DLLEXPORT oBoxFactory
	{
	public:
		static oBox* CreateRectBox(oImage* pkImage, int X, int Y, const oBoxInfo& kInfo);
		static oBox* CreateCircleBox(oImage* pkImage, int X, int Y, const oBoxInfo& kInfo);
		static void DestroyBox(oBox*& pkBox);
	};
}
