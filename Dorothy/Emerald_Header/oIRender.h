#pragma once
#include "oZIndexListener.h"

namespace Dorothy
{
	enum oVisibility
	{
		V_VISIBLE,
		V_HIDDEN,
		V_COLLAPSE
	};
		
	class oRenderController;

	class DLLEXPORT oIRender
	{
		friend class oRenderController;
	public:
		oIRender(bool bVisible = true);
		virtual ~oIRender();
		void SetZIndex(int iZ);
		void SetVisible(bool bVisible);
		void SetVisible(oVisibility Visibility);
		int GetZIndex() const;
		bool IsVisible() const;
		static void SetZIndexListener(oZIndexListener* pkListener);
		static void SetAutoManaged(bool autoManaged);
		static bool IsAutoManaged();
	protected:
		virtual void Render() = 0;
	private:
		int m_ID;
		int m_iZ;
		oVisibility m_Visibility;
		static oZIndexListener* m_pkListener;
	};
}
