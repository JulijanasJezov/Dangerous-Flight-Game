#include "missile.h"
#include "header.h" 
#include "templates.h"

missile::missile(BaseEngine* pEngine)
: DisplayableObject(pEngine)
{
	missileImg = new ImageSurface();
	missileImg->LoadImage("missile.png");

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Missile's size
	m_iDrawWidth = 42;
	m_iDrawHeight = 40;

	SetVisible(false);
}


missile::~missile()
{
}

void missile::Draw()
{
	if (!IsVisible()) {
		return;
	}

	// Cuts the loaded image into parts to achieve rotation of a missile
	switch (rotState)
	{
	case right:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case left:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			45, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case back:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			90, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case front:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			135, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case bottomLeft:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			180, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case bottomRight:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			225, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case topRight:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			270, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	case topLeft:
		missileImg->RenderImage(GetEngine()->GetForeground(),
			315, 0,
			m_iCurrentScreenX, m_iCurrentScreenY,
			45, missileImg->GetHeight());
		break;
	}

	StoreLastScreenPositionAndUpdateRect();
}


void missile::DoUpdate(int iCurrentTime)
{
	// Movement and setting the rotation state depending on where it's heading

	if (playerX > m_iCurrentScreenX && playerY > m_iCurrentScreenY)
	{
		rotState = bottomRight;
		m_iCurrentScreenY += 2;
		m_iCurrentScreenX += 2;
	}
	else if (playerX < m_iCurrentScreenX && playerY < m_iCurrentScreenY)
	{
		rotState = topLeft;
		m_iCurrentScreenY -= 2;
		m_iCurrentScreenX -= 2;
	}
	else if (playerX > m_iCurrentScreenX && playerY < m_iCurrentScreenY)
	{
		rotState = topRight;
		m_iCurrentScreenY -= 2;
		m_iCurrentScreenX += 2;
	}
	else if (playerX < m_iCurrentScreenX && playerY > m_iCurrentScreenY)
	{
		rotState = bottomLeft;
		m_iCurrentScreenY += 2;
		m_iCurrentScreenX -= 2;
	} 
	else if (playerX == m_iCurrentScreenX && playerY > m_iCurrentScreenY)
	{
		rotState = front;
		m_iCurrentScreenY += 2;
	}
	else if (playerX == m_iCurrentScreenX && playerY < m_iCurrentScreenY)
	{
		rotState = back;
		m_iCurrentScreenY -= 2;
	}
	else if (playerY == m_iCurrentScreenY && playerX > m_iCurrentScreenX)
	{
		rotState = right;
		m_iCurrentScreenX += 2;
	}
	else if (playerY == m_iCurrentScreenY && playerX < m_iCurrentScreenX)
	{
		rotState = left;
		m_iCurrentScreenX -= 2;
	}

	if (m_iCurrentScreenY >= 600)
	{
		SetVisible(false);

	}
}


void missile::Shoot(int posX, int posY)
{
	// Make missile vissible when the function is called and set the right location

	if (!IsVisible()) {
		m_iCurrentScreenX = posX;
		m_iCurrentScreenY = posY;
		SetVisible(true);
	}


}

void missile::FindPlayer(int pX, int pY)
{
	// Gets the player jet's location

	playerX = pX;
	playerY = pY;
}
