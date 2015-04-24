#include "header.h" 
#include "templates.h"
#include "EnemyJet.h"


EnemyJet::EnemyJet(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
{

	enemyJet = new Image();
	enemyJet->LoadImage("enemy1.png");

	// Set current coordinates
	m_iCurrentScreenX = m_iPreviousScreenX = 500;
	m_iCurrentScreenY = m_iPreviousScreenY = -100;

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the jet's size as both height and width 
	m_iDrawWidth = 71;
	m_iDrawHeight = 95;

	// And make it visible 
	SetVisible(true);
}


EnemyJet::~EnemyJet()
{
}


void EnemyJet::Draw()
{
	if (!IsVisible())
		return;

	enemyJet->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		enemyJet->GetWidth(), enemyJet->GetHeight());

	StoreLastScreenPositionAndUpdateRect();
}



void EnemyJet::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenY += 3;
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight())
	{
		m_iCurrentScreenX = rand() % 740;
		m_iCurrentScreenY = -(rand() % 500);
		SetVisible(true);

	}
}

unsigned int EnemyJet::GetColourPixel(int x, int y)
{
	// Returns the exact pixels colour as ARGB

	if (x > m_iCurrentScreenX && x < (m_iCurrentScreenX + 71) && y > m_iCurrentScreenY && y < (m_iCurrentScreenY + 95))
	{
		return ((unsigned int *)enemyJet->GetImgSurface()->pixels)[(x - m_iCurrentScreenX) + (y - m_iCurrentScreenY) * enemyJet->GetWidth()];
	}
	else {
		return 0x000000ff;
	}
}