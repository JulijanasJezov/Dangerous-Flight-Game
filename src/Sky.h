#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"

class Sky :
	public DisplayableObject
{
public:
	Sky(BaseEngine* pEngine, int startPosY);
	~Sky();
	void Draw();
	void DoUpdate(int iCurrentTime);

private:
	ImageData *skyBg;
};

