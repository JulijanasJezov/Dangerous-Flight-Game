#include "Image.h"


Image::Image()
{
}


Image::~Image()
{
}

SDL_Surface* Image::GetImgSurface()
{
	// Returns an object's surface

	return m_pSurface;
}