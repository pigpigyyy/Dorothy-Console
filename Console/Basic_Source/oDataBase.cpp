#include "oDataBase.h"

#define IMAGE_NUM 14
static char* g_szImageName[IMAGE_NUM] = 
{
	"Image/Dorothy.bmp",//0
	"Image/DorothyTxt.bmp",//1
	"Image/Bunnys.bmp",//2
	"Image/Start.bmp",//3
	"Image/Instruction.bmp",//4
	"Image/Quit.bmp",//5
	"Image/Return.bmp",//6
	"Image/Readme.bmp",//7
	"Image/Flower.bmp",//8
	"Image/GameBk.bmp",//9
	"Image/Numbers.bmp",//10
	"Image/Level.bmp",//11
	"Image/Score.bmp",//12
	"Image/Flag.bmp"//13
};

#define SOUND_NUM 4
static char* g_szSoundName[SOUND_NUM] = 
{
	"Sound/Choose.wav",//0
	"Sound/Cat.wav",//1
	"Sound/Die.wav",//2
	"Sound/MeoMeo.wav"//3
};

oDataBase::oDataBase():
m_ppkImage(NULL),
m_ppkSound(NULL)
{
	m_pkSingleton = this;
}

oDataBase::~oDataBase()
{
	m_pkSingleton = NULL;
}

oDataBase* oDataBase::m_pkSingleton = NULL;

oDataBase* oDataBase::GetSingleton()
{
	return m_pkSingleton;
}

bool oDataBase::Load()
{
	m_ppkImage = new oImage*[IMAGE_NUM];
	for (int i = 0;i < IMAGE_NUM;i++)
	{
		m_ppkImage[i] = oCreateImageFromBMP24(g_szImageName[i]);
		if (m_ppkImage[i] == NULL)
		{
			return false;
		}
	}
	m_ppkSound = new oSound*[SOUND_NUM];
	for (int i = 0;i < SOUND_NUM;i++)
	{
		m_ppkSound[i] = new oSound();
		if (!m_ppkSound[i]->LoadFromFile(g_szSoundName[i]))
		{
			return false;
		}
	}
	m_ppkSound[0]->SetVolume(50);
	return true;
}

void oDataBase::Unload()
{
	if (m_ppkImage != NULL)
	{
		for (int i = 0;i < IMAGE_NUM;i++)
		{
			delete m_ppkImage[i];
			m_ppkImage[i] = NULL;
		}
		delete [] m_ppkImage;
		m_ppkImage = NULL;
	}
	if (m_ppkSound != NULL)
	{
		for (int i = 0;i < SOUND_NUM;i++)
		{
			delete m_ppkSound[i];
			m_ppkSound[i] = NULL;
		}
		delete [] m_ppkSound;
		m_ppkSound = NULL;
	}
}

oImage* oDataBase::GetImage( ImageID ID )
{
	return m_ppkImage[(int)ID];
}

oSound* oDataBase::GetSound( SoundID ID )
{
	return m_ppkSound[(int)ID];
}