#include "oButton.h"

static RECT g_kCommonBtnRect[3] =
{
	{0,0,51,15},
	{0,15,51,30},
	{0,30,51,45}
};

static RECT g_kReturnBtnRect[3] =
{
	{0,0,27,15},
	{0,15,27,30},
	{0,30,27,45}
};

oButton::oButton(oButtonType type) :
	oSprite(true)
{
	RotateAnimation.OnEnd += std::make_pair(this, &oButton::Reset);

	m_Type = type;
	oImage* pkImage;
	int iAngle = 360;
	switch (type)
	{
	case BT_START:
		pkImage = oDataBase::GetSingleton()->GetImage(IMG_START);
		m_pkRect = g_kCommonBtnRect;
		break;
	case BT_INSTRUCTION:
		pkImage = oDataBase::GetSingleton()->GetImage(IMG_INSTRUCTION);
		m_pkRect = g_kCommonBtnRect;
		break;
	case BT_QUIT:
		pkImage = oDataBase::GetSingleton()->GetImage(IMG_QUIT);
		m_pkRect = g_kCommonBtnRect;
		break;
	case BT_RETURN:
	default:
		iAngle = -360;
		pkImage = oDataBase::GetSingleton()->GetImage(IMG_RETURN);
		m_pkRect = g_kReturnBtnRect;
		break;
	}
	oSprite::SetImage(pkImage);
	oSprite::SetRenderRect(m_pkRect[0]);
	m_kFrame.SetUpFrame(2);
	m_kFrame.SetFrame(0, m_pkRect[1], 300);
	m_kFrame.SetFrame(1, m_pkRect[2], 300);
	m_kFrame.SetLoop(true);
	m_kFrame.SetTarget(this);
	RotateAnimation.SetRotate(0, iAngle, 845);
	RotateAnimation.SetTarget(this);
}

void oButton::Update()
{
	if (!RotateAnimation.IsPlaying())
	{
		oPoint kPoint = { oInput::GetInstance()->GetMouseX(),
			oInput::GetInstance()->GetMouseY() };
		vector<oObject*>& kList = m_pkGroup->GetCollisionList(kPoint);
		bool bHit = false;
		if (kList.size() > 0)
		{
			int iSize = kList.size();
			for (int i = 0; i < iSize; i++)
			{
				if (kList[i] == this)
				{
					bHit = true;
					if (oInput::GetInstance()->IsLeftMouseDown())
					{
						if (!RotateAnimation.IsPlaying())
						{
							RotateAnimation.Start();
							oDataBase::GetSingleton()->GetSound(SND_DIE)->Play(false);
							if (OnClick)
							{
								OnClick(this);
							}
						}
					}
					if (!m_kFrame.IsPlaying())
					{
						oDataBase::GetSingleton()->GetSound(SND_CHOOSE)->Play(false);
						m_kFrame.Start();
					}
					break;
				}
			}
		}
		if (!bHit && m_kFrame.IsPlaying())
		{
			oButton::Reset(NULL);
		}
	}
}

void oButton::Reset(oAnimation* pkTarget)
{
	m_kFrame.Stop();
	oSprite::SetRenderRect(*m_pkRect);
}
