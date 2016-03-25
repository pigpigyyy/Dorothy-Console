#pragma once
#include "Dorothy.h"
using namespace Dorothy;

enum ImageID
{
	IMG_DOROTHY = 0,
	IMG_DOROTHYTXT,
	IMG_BUNNYS,
	IMG_START,
	IMG_INSTRUCTION,
	IMG_QUIT,
	IMG_RETURN,
	IMG_README,
	IMG_FLOWER,
	IMG_GAMEBK,
	IMG_NUMBERS,
	IMG_LEVEL,
	IMG_SCORE,
	IMG_FLAG
};

enum SoundID
{
	SND_CHOOSE = 0,
	SND_CAT,
	SND_DIE,
	SND_MEOMEO
};

class oDataBase
{
public:
	oDataBase();
	~oDataBase();
	bool Load();
	void Unload();
	oImage* GetImage(ImageID ID);
	oSound* GetSound(SoundID ID);
	static oDataBase* GetSingleton();
protected:
	oImage** m_ppkImage;
	oSound** m_ppkSound;
	static oDataBase* m_pkSingleton;
};