#include "Bullet.h"
#include "header.h" 
#include "templates.h"


Bullet::Bullet(BaseEngine* pEngine)
: DisplayableObject(pEngine)
{
	bullet = new ImageSurface();
	bullet->LoadImage("bullet.png");

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	m_iDrawWidth = 11;
	m_iDrawHeight = 22;

	SetVisible(false);
}


Bullet::~Bullet()
{
}


void Bullet::Draw()
{
	if (!IsVisible()) {
		return;
	}

	bullet->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		bullet->GetWidth(), bullet->GetHeight());


	StoreLastScreenPositionAndUpdateRect();
}


void Bullet::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenY -= 5;

	if (m_iCurrentScreenY <= 0)
	{
		SetVisible(false);

	}
}


void Bullet::Shoot(int posX, int posY)
{
	// Make bullet visible on a function call if it's not visible yet
	if (!IsVisible()) {
		m_iCurrentScreenX = posX;
		m_iCurrentScreenY = posY;
		SetVisible(true);
	}
}
