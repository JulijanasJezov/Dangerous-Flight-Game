#include "header.h" 
#include "templates.h"
#include "Jet.h"

Jet::Jet(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
	, m_dX(330)
	, m_dY(400)
	, m_dSX(0)
	, m_dSY(0)
{
	jet = new Image();

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the jet's size as both height and width 
	m_iDrawWidth = 80;
	m_iDrawHeight = 120;

	// And make it visible 
	SetVisible(true);
}


Jet::~Jet()
{
}


void Jet::Draw()
{
	if (!IsVisible())
		return;

	jet->RenderImage(GetEngine()->GetForeground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		jet->GetWidth(), jet->GetHeight());

	StoreLastScreenPositionAndUpdateRect();
}


void Jet::DoUpdate(int iCurrentTime)
{
	// Jet's movement using accelaration
	if (GetEngine()->IsKeyPressed(SDLK_UP))
		m_dSY -= 0.2;
	else if (GetEngine()->IsKeyPressed(SDLK_DOWN))
		m_dSY += 0.2;
	else if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_dSX -= 0.2;
	else if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_dSX += 0.2;
	else // Stop when movement keys are not pressed
		m_dSX = m_dSY = 0;

	m_dX += m_dSX;
	m_dY += m_dSY;

	// Don't go out of the screen
	if ((m_dX + m_iStartDrawPosX) < 0)
	{
		m_dX = -m_iStartDrawPosX;
		m_dSX = 0;
	}

	if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) >(GetEngine()->GetScreenWidth() - 1))
	{
		m_dX = GetEngine()->GetScreenWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
		m_dSX = 0;
	}

	if ((m_dY + m_iStartDrawPosY) < 0)
	{
		m_dY = -m_iStartDrawPosY;
		m_dSY = 0;
	}

	if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) >(GetEngine()->GetScreenHeight() - 1))
	{
		m_dY = GetEngine()->GetScreenHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
		m_dSY = 0;
	}

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX + 0.5);
	m_iCurrentScreenY = (int)(m_dY + 0.5);
}

void Jet::ChangeJet(int posX, int posY, int jetNo, bool bg)
{
	m_iCurrentScreenX = posX;
	m_iCurrentScreenY = posY;

	// Checks which jet is chosen and loads an image depending on it

	switch (jetNo)
	{
	case 0:
		jet->LoadImage("su37kt.png");
		
		if (bg)
			jet->RenderImage(GetEngine()->GetBackground(),
				0, 0,
				m_iCurrentScreenX, m_iCurrentScreenY,
				jet->GetWidth(), jet->GetHeight());
		break;
	case 1:
		jet->LoadImage("mig51.png");
		if (bg)
			jet->RenderImage(GetEngine()->GetBackground(),
			0, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			jet->GetWidth(), jet->GetHeight());
		break;
	case 2:
		jet->LoadImage("su51.png");
		if (bg)
			jet->RenderImage(GetEngine()->GetBackground(),
			0, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			jet->GetWidth(), jet->GetHeight());
		break;
	}
	
}

unsigned int Jet::GetColourPixel(int x, int y)
{
	// Returns the exact pixels colour as ARGB

	if (x > m_iCurrentScreenX && x < (m_iCurrentScreenX + 80) && y > m_iCurrentScreenY && y < (m_iCurrentScreenY + 120))
	{
		return ((unsigned int *)jet->GetImgSurface()->pixels)[(x - m_iCurrentScreenX) + (y - m_iCurrentScreenY) * jet->GetWidth()];
	}
	else {
		return 0x000000ff;
	}
}