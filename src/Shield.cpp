#include "Shield.h"
#include "header.h" 
#include "templates.h"

Shield::Shield(BaseEngine* pEngine)
: DisplayableObject(pEngine)
{
	shieldImg = new Image();
	shieldImg->LoadImage("shield.png");

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Size of a shield
	m_iDrawWidth = 104;
	m_iDrawHeight = 145;

	SetVisible(false);
}


Shield::~Shield()
{
}


void Shield::Draw()
{
	if (!IsVisible())
		return;

	shieldImg->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		shieldImg->GetWidth(), shieldImg->GetHeight());

	StoreLastScreenPositionAndUpdateRect();
}

void Shield::DoUpdate(int iCurrentTime)
{
	RedrawObjects();
}

void Shield::ShieldUp(int posX, int posY)
{
	// Make shield appear when function is called in the passed location as parameters

	SetVisible(true);
	m_iCurrentScreenX = posX - 52;
	m_iCurrentScreenY = posY - 70;
}