#include "EnemyBullet.h"
#include "header.h" 
#include "templates.h"

EnemyBullet::EnemyBullet(BaseEngine* pEngine)
: DisplayableObject(pEngine)
{
	enBullet = new ImageSurface();
	enBullet->LoadImage("enbullet.png");
	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Size
	m_iDrawWidth = 7;
	m_iDrawHeight = 14;

	SetVisible(false);
}


EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Draw()
{
	if (!IsVisible()) {
		return;
	}

	enBullet->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		enBullet->GetWidth(), enBullet->GetHeight());


	StoreLastScreenPositionAndUpdateRect();
}


void EnemyBullet::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenY += 5;

	if (m_iCurrentScreenY >= 600)
	{
		SetVisible(false);

	}
}


void EnemyBullet::Shoot(int posX, int posY)
{
	// Make bullet visible on a function call if it's not visible yet
	if (!IsVisible()) {
		m_iCurrentScreenX = posX;
		m_iCurrentScreenY = posY;
		SetVisible(true);
	}
}
