#pragma once
#include "DisplayableObject.h"
#include "Image.h"

class EnemyJet :
	public DisplayableObject
{
public:
	EnemyJet(BaseEngine* pEngine);
	~EnemyJet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	unsigned int GetColourPixel(int x, int y);

private:
	Image *enemyJet;
};

