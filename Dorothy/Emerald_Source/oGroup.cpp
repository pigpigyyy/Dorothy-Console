#include "oGroup.h"
using namespace Dorothy;

static vector<oObject*> g_kCollisionList;

oGroup::oGroup() :
	m_pkFirst(NULL),
	m_pkLast(NULL)
{ }

oObject* oGroup::First()
{
	return m_pkFirst;
}

oObject* oGroup::Last()
{
	return m_pkLast;
}

void oGroup::Update()
{
	for (oObject* pkObj = m_pkFirst; pkObj != NULL; pkObj = pkObj->Next())
	{
		oIUpdate* item = dynamic_cast<oIUpdate*>(pkObj);
		if (item)
		{
			item->Update();
		}
	}
}

void oGroup::Render()
{
	for (oObject* pkObj = m_pkFirst; pkObj != NULL; pkObj = pkObj->Next())
	{
		if (pkObj->IsVisible())
		{
			pkObj->Render();
		}
	}
}

void oGroup::Clear()
{
	vector<oObject*>& items = oGroup::GetItems();
	for (size_t i = 0; i < items.size(); i++)
	{
		delete items[i];
	}
}

vector<oObject*>& oGroup::GetItems() const
{
	g_kCollisionList.clear();
	for (oObject* pkObj = m_pkFirst; pkObj != NULL; pkObj = pkObj->Next())
	{
		g_kCollisionList.push_back(pkObj);
	}
	return g_kCollisionList;
}

vector<oObject*>& oGroup::GetCollisionList(oObject* pkObject, bool bCheckImage) const
{
	g_kCollisionList.clear();
	if (!pkObject->IsDetective())
	{
		return g_kCollisionList;
	}
	for (oObject* pkObj = m_pkFirst; pkObj != NULL; pkObj = pkObj->Next())
	{
		if (pkObject == pkObj || !pkObj->IsDetective())
		{
			continue;
		}
		const oRect* pkRect1 = pkObject->GetRect();
		const oRect* pkRect2 = pkObj->GetRect();
		int lx1 = pkRect1->x,
			ly1 = pkRect1->y;
		int rx1 = lx1 + pkRect1->w,
			ry1 = ly1 + pkRect1->h;
		int lx2 = pkRect2->x,
			ly2 = pkRect2->y;
		int rx2 = lx2 + pkRect2->w,
			ry2 = ly2 + pkRect2->h;
		if (RECT_HIT_RECT(lx1, ly1, rx1, ry1, lx2, ly2, rx2, ry2))
		{
			if (bCheckImage)
			{
				if (pkObj->GetImage() != NULL && pkObj->GetImage() != NULL)
				{
					bool bCollision = false;
					int sX = (lx1 > lx2 ? lx1 : lx2),
						sY = (ly1 > ly2 ? ly1 : ly2),
						eX = (rx1 < rx2 ? rx1 : rx2),
						eY = (ry1 < ry2 ? ry1 : ry2);
					for (int i = sY; i < eY; i++)
					{
						for (int o = sX; o < eX; o++)
						{
							int iCondition =
								int(pkObj->GetDisplayColor(o, i) == COLOR_NONE)
								+ int(pkObj->GetDisplayColor(o, i) == COLOR_NONE)
								+ int(!(pkObj->GetDisplayChar(o, i)))
								+ int(!(pkObj->GetDisplayChar(o, i)));
							if (iCondition <= 2)
							{
								bCollision = true;
								o = eX; i = eY;
							}
						}
					}
					if (bCollision)
					{
						g_kCollisionList.push_back(pkObj);
					}
				}
			}
			else
			{
				g_kCollisionList.push_back(pkObj);
			}
		}
	}
	return g_kCollisionList;
}

vector<oObject*>& oGroup::GetCollisionList(const oPoint& kPoint, bool bCheckImage) const
{
	g_kCollisionList.clear();
	for (oObject* pkObj = m_pkFirst; pkObj != NULL; pkObj = pkObj->Next())
	{
		if (!pkObj->IsDetective())
		{
			continue;
		}
		const oRect* pkRect = pkObj->GetRect();
		if (POINT_IN_RECT(kPoint.x, kPoint.y, pkRect->x, pkRect->y, pkRect->w, pkRect->h))
		{
			if (bCheckImage)
			{
				if (!(pkObj->GetDisplayColor(kPoint.x, kPoint.y) == COLOR_NONE
					&& pkObj->GetDisplayChar(kPoint.x, kPoint.y) == 0))
				{
					g_kCollisionList.push_back(pkObj);
				}
			}
			else
			{
				g_kCollisionList.push_back(pkObj);
			}
		}
	}
	return g_kCollisionList;
}

