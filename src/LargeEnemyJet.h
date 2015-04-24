#pragma once
#include "DisplayableObject.h"
#include "Image.h"

class LargeEnemyJet :
	public DisplayableObject
{
public:
	LargeEnemyJet(BaseEngine* pEngine);
	~LargeEnemyJet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	unsigned int GetColourPixel(int x, int y);
private:
	Image *largeEnemy;
};

