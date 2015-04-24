#pragma once
#include "DisplayableObject.h"
#include "Image.h"

class EnemyFast :
	public DisplayableObject
{
public:
	EnemyFast(BaseEngine* pEngine);
	~EnemyFast();
	void Draw();
	void DoUpdate(int iCurrentTime);
	unsigned int GetColourPixel(int x, int y);
private:
	Image *enemyFast;
};

