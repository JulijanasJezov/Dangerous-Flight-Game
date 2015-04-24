#pragma once
#include "JPGImage.h"

class Image :
	public ImageSurface
{
public:
	Image();
	~Image();

	SDL_Surface* GetImgSurface();
};

