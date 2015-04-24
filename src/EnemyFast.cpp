#include "header.h" 
#include "templates.h"
#include "EnemyFast.h"


EnemyFast::EnemyFast(BaseEngine* pEngine)
:DisplayableObject(pEngine)
{
	enemyFast = new Image();
	enemyFast->LoadImage("enemyF.png");

	// Place it randomly off the screen at the top
	m_iCurrentScreenX = rand() % 740;
	m_iCurrentScreenY = -200;

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Set size as width and height
	m_iDrawWidth = 60;
	m_iDrawHeight = 79;

	// And make it visible 
	SetVisible(true);
}


EnemyFast::~EnemyFast()
{
}


void EnemyFast::Draw()
{
	if (!IsVisible())
		return;

	enemyFast->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		enemyFast->GetWidth(), enemyFast->GetHeight());

	StoreLastScreenPositionAndUpdateRect();
}



void EnemyFast::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenY += 6;
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight())
	{
		m_iCurrentScreenX = rand() % 740;
		m_iCurrentScreenY = -(rand() % 500);
		SetVisible(true);

	}
}

unsigned int EnemyFast::GetColourPixel(int x, int y)
{
	// Returns the exact pixels colour as ARGB

	if (x > m_iCurrentScreenX && x < (m_iCurrentScreenX + 60) && y > m_iCurrentScreenY && y < (m_iCurrentScreenY + 79))
	{
		return ((unsigned int *)enemyFast->GetImgSurface()->pixels)[(x - m_iCurrentScreenX) + (y - m_iCurrentScreenY) * enemyFast->GetWidth()];
	}
	else {
		return 0x000000ff;
	}
}