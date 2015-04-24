#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class missile :
	public DisplayableObject
{
public:
	missile(BaseEngine* pEngine);
	~missile();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void Shoot(int posX, int posY);
	enum {left, right, front, back, topRight, topLeft, bottomRight, bottomLeft};
	void FindPlayer(int pX, int pY);
private:
	ImageSurface *missileImg;
	int playerX;
	int playerY;
	int rotState;
};

