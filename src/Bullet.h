#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class Bullet :
	public DisplayableObject
{
public:
	Bullet(BaseEngine* pEngine);
	~Bullet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void Shoot(int posX, int posY);

private:
	ImageSurface *bullet;
};

