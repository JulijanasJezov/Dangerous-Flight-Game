#include "LargeEnemyJet.h"
#include "header.h" 
#include "templates.h"

LargeEnemyJet::LargeEnemyJet(BaseEngine* pEngine)
: DisplayableObject(pEngine)
{
	largeEnemy = new Image();
	largeEnemy->LoadImage("largeEnemy.png");

	// Place object randomly out of the screen at the top
	m_iCurrentScreenX = rand() % 700;
	m_iCurrentScreenY = -500;

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the jet's size as both height and width 
	m_iDrawWidth = 108;
	m_iDrawHeight = 190;

	// And make it visible 
	SetVisible(true);
}


LargeEnemyJet::~LargeEnemyJet()
{
}

void LargeEnemyJet::Draw()
{
	if (!IsVisible())
		return;

	largeEnemy->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		largeEnemy->GetWidth(), largeEnemy->GetHeight());

	StoreLastScreenPositionAndUpdateRect();
}



void LargeEnemyJet::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenY += 2;

	// Respawn enemy at random place out of the screen at the top
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight())
	{
		m_iCurrentScreenX = rand() % 700;
		m_iCurrentScreenY = -(rand() % 1000);
		SetVisible(true);

	}

}

unsigned int LargeEnemyJet::GetColourPixel(int x, int y)
{
	// Returns the exact pixels colour as ARGB

	if (x > m_iCurrentScreenX && x < (m_iCurrentScreenX + 108) && y > m_iCurrentScreenY && y < (m_iCurrentScreenY + 190))
	{
		return ((unsigned int *)largeEnemy->GetImgSurface()->pixels)[(x - m_iCurrentScreenX) + (y - m_iCurrentScreenY) * largeEnemy->GetWidth()];
	}
	else {
		return 0x000000ff;
	}
}