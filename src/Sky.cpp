#include "Sky.h"
#include "header.h" 
#include "templates.h"


Sky::Sky(BaseEngine* pEngine, int startPosY)
	:DisplayableObject(pEngine)
{
	skyBg = new ImageData();
	skyBg->LoadImage("cloud2.png");

	// The object coordinate will be the top left of the object 
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Current object's coordinates, Y is passed from main game class
	m_iCurrentScreenX = 0;
	m_iCurrentScreenY = startPosY;

	// Size of a background
	m_iDrawWidth = 794;
	m_iDrawHeight = 600;

	// And make it visible 
	SetVisible(true);
}


Sky::~Sky()
{
}


void Sky::Draw()
{
	skyBg->RenderImage(GetEngine()->GetBackground(),
		0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		skyBg->GetWidth(), skyBg->GetHeight());


	StoreLastScreenPositionAndUpdateRect();
}


void Sky::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenY++;

	// Respawn the background at the top when Y reaches the bottom
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight())
	{
		m_iCurrentScreenX = 0;
		m_iCurrentScreenY = -610;

	}
}
