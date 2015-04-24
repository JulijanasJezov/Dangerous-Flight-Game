#pragma once
#include "DisplayableObject.h"
#include "Image.h"

class Shield :
	public DisplayableObject
{
public:
	Shield(BaseEngine* pEngine);
	~Shield();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void ShieldUp(int posX, int posY);

private:
	Image *shieldImg;
};

