#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class EnemyBullet :
	public DisplayableObject
{
public:
	EnemyBullet(BaseEngine* pEngine);
	~EnemyBullet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void Shoot(int posX, int posY);

private:
	ImageSurface *enBullet;
};

