#include "header.h"
#include "JPGImage.h"
#include "Sky.h"
#include "JetShooter.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Constructor sets initial game state and initial jet
JetShooter::JetShooter()
:BaseEngine(11)
, gameState(stInitial)
, chosenJet(blue)
{
}


JetShooter::~JetShooter()
{
}


void JetShooter::SetupBackgroundBuffer()
{
	switch (gameState)
	{
	case stInitial:
		FillBackground(0x2c8cfd);
		chosenJet = blue;

		// Draws the background object
		m_ppDisplayableObjects[0]->Draw();

		// Draw 3 jets to choose
		playerJet->ChangeJet(200, 200, 0, true);
		playerJet->Draw();
		playerJet->ChangeJet(350, 200, 1, true);
		playerJet->Draw();
		playerJet->ChangeJet(500, 200, 2, true);
		playerJet->Draw();
		shield->ShieldUp(243, 255);
		return;
	case stPaused:
		break;
	case stFinished:
		StoreScore();
		DestroyOldObjects();
		Redraw(true);
		break;
	}
	
}


int JetShooter::InitialiseObjects()
{
	// Reset variables for the next game
	enemyHit = 0;
	score = 0;
	bShield = false;

	// Notifies that drawable array is changed, so it won't be used elsewhere
	DrawableObjectsChanged();

	// Destroy any existing objects 
	DestroyOldObjects();

	// Array of displayable objects
	m_ppDisplayableObjects = new DisplayableObject*[11];

	// Instances of objects
	enemyJet = new EnemyJet(this);
	enemyFast = new EnemyFast(this);
	enemyLarge = new LargeEnemyJet(this);
	bul = new Bullet(this);
	playerJet = new Jet(this);
	enBul = new EnemyBullet(this);
	enMissile = new missile(this);
	shield = new Shield(this);

	m_ppDisplayableObjects[0] = new Sky(this, 0);
	m_ppDisplayableObjects[1] = new Sky(this, -600);
	m_ppDisplayableObjects[2] = shield;
	m_ppDisplayableObjects[3] = enemyJet;
	m_ppDisplayableObjects[4] = enemyFast;
	m_ppDisplayableObjects[5] = enemyLarge;
	m_ppDisplayableObjects[6] = bul;
	m_ppDisplayableObjects[7] = enBul;
	m_ppDisplayableObjects[8] = enMissile;
	m_ppDisplayableObjects[9] = playerJet;
	m_ppDisplayableObjects[10] = NULL;
	return 0;
}



void JetShooter::GameAction()
{
	// If too early to act then do nothing
	if (!TimeToAct())
		return;

	SetTimeToAct(10);

	switch (gameState)
	{
	case stInitial:	
		// Uses shield to choose a jet in initial state
		shield->DoUpdate(GetTime());
	case stPaused:
		break;
	case stMain:
		// Make enemies to shoot on appearing
		if (enemyJet->GetYCentre() > 0 && enemyJet->IsVisible())
			enBul->Shoot(enemyJet->GetXCentre(), enemyJet->GetYCentre());
		else if (enemyLarge->GetYCentre() > 0 && enemyLarge->IsVisible())
			enMissile->Shoot(enemyLarge->GetXCentre(), enemyLarge->GetYCentre());
		else if (!enemyJet->IsVisible())
			enBul->SetVisible(false);

		// Puts a shield on
		if (bShield)
		{ 
			shield->ShieldUp(playerJet->GetXCentre(), playerJet->GetYCentre());
			shieldTime--;
			
			// Takes a shield off
			if (shieldTime < 0)
			{
				bShield = false;
				shield->SetVisible(false);
			}
		}

		// Calls a function to follow player
		enMissile->FindPlayer(playerJet->GetXCentre(), playerJet->GetYCentre());

		score++;
		sprintf(sScore, "Score: %d", score);
		Collisions();
		UpdateAllObjects(GetTime());
		break;
	case stFinished:
		break;
	}
}

void JetShooter::KeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // Exit
		SetExitWithCode(0);
		break;
	case SDLK_RETURN: // Start game, Play again
		if (gameState == stInitial)
		{
			// Go to state main
			gameState = stMain;
			playerJet->ChangeJet(400, 450, chosenJet, false);
			shield->SetVisible(false);

			// Redraw background
			SetupBackgroundBuffer();

			// Redraw the whole screen now
			Redraw(true);
		}
		else if (gameState == stFinished)
		{
			// Go to initial state
			gameState = stInitial;

			// Objects initialised to reset the game
			InitialiseObjects();

			// Redraw background
			SetupBackgroundBuffer();

			// Redraw the whole screen now
			Redraw(true);
		}
		break;
	case SDLK_p: // Pause
		switch (gameState)
		{
		case (stMain):
			gameState = stPaused;
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case (stPaused) :
			gameState = stMain;
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		}
		break;
	case SDLK_SPACE: // Shoot
		if (gameState == stMain)
			bul->Shoot(playerJet->GetXCentre(), playerJet->GetYCentre());
		break;
	case SDLK_LSHIFT: // Shield
		if (gameState == stMain)
		{
			if (!bShield)
			{
				// Sets shield to true and use it in main game loop
				bShield = true;
				shieldTime = 300;
			}
		}
		break;
	case SDLK_RIGHT: // Choosing jet
		if (gameState == stInitial)
		{
			switch (chosenJet)
			{
			case blue:
				chosenJet = red;
				shield->ShieldUp(393, 255);
				shield->RedrawBackground();
				DrawChangingObjects();
				playerJet->ChangeJet(200, 200, 0, true);
				playerJet->Draw();
				break;
			case red:
				chosenJet = black;
				shield->ShieldUp(540, 255);
				shield->RedrawBackground();
				DrawChangingObjects();
				playerJet->ChangeJet(350, 200, 1, true);
				playerJet->Draw();
				break;
			}
		}
		break;
	case SDLK_LEFT: // Choosing jet
		if (gameState == stInitial)
		{
			switch (chosenJet)
			{
			case red:
				chosenJet = blue;
				shield->ShieldUp(243, 255);
				shield->RedrawBackground();
				DrawChangingObjects();
				playerJet->ChangeJet(350, 200, 1, true);
				playerJet->Draw();
				break;
			case black:
				chosenJet = red;
				shield->ShieldUp(393, 255);
				shield->RedrawBackground();
				DrawChangingObjects();
				playerJet->ChangeJet(500, 200, 2, true);
				playerJet->Draw();
				break;
			}
		}
		break;
	}
}

void JetShooter::DrawStrings()
{
	// Draw strings depending on the state
	switch (gameState)
	{
	case stInitial:
		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(60, 100, "Choose a Jet using left/right arrows", 0x0, GetFont("Smart_Kid.otf", 50));
		DrawScreenString(250, 400, "Arrows - Controlling Jet", 0x0, GetFont("Smart_Kid.otf", 30));
		DrawScreenString(140, 430, "Left Shift - Shield protecting from a missile", 0x0, GetFont("Smart_Kid.otf", 30));
		DrawScreenString(300, 460, "Space - Shoot", 0x0, GetFont("Smart_Kid.otf", 30));
		DrawScreenString(330, 490, "P - Pause", 0x0, GetFont("Smart_Kid.otf", 30));
		DrawScreenString(100, 530, "Press ENTER to start the game", 0x0, GetFont("Smart_Kid.otf", 50));
		SetNextUpdateRect(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		break;
	case stMain:

		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(620, 550, sScore, 0x000000, GetFont("Make My Day.ttf", 30));
		SetNextUpdateRect(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		break;
	case stPaused:
		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(150, 300, "Paused. Press P to continue", 0x0, GetFont("Smart_Kid.otf", 50));
		SetNextUpdateRect(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		break;
	case stFinished:
		sprintf(cScore, "Current Score: %d", score);
		GetScore();
		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(270, 200, cScore, 0x000000, GetFont("Make My Day.ttf", 40));
		DrawScreenString(270, 300, hScore, 0x000000, GetFont("Make My Day.ttf", 40));
		DrawScreenString(150, 400, "Press ENTER to start again", 0x000000, GetFont("Smart_Kid.otf", 50));
		SetNextUpdateRect(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		break;
	}
}

void JetShooter::DrawChanges()
{
	// Do not draw objects if initialising
	if (gameState == stInitial)
		return;
	
	// Remove objects from their old positions
	UndrawChangingObjects();

	// Draw the text 
	DrawStrings();

	// Draw objects at their new positions
	DrawChangingObjects();
}

void JetShooter::DrawScreen()
{
	// First draw the background
	CopyAllBackgroundBuffer();

	DrawStrings();

	// Draw the changing objects
	DrawChangingObjects();
}

void JetShooter::Collisions()
{
	int bulX = bul->GetXCentre();
	int bulY = bul->GetYCentre();
	int enBulX = enBul->GetXCentre();
	int enBulY = enBul->GetYCentre();
	int enMissileX = enMissile->GetXCentre();
	int	enMissileY = enMissile->GetYCentre();
	unsigned int playerPix;
	unsigned int enemyLargePix;
	unsigned int enemyFastPix;
	unsigned int enemyJetPix;

	// Player's bullet collision
	if (bul->IsVisible()) {
		// Collision with enemyJet
		if (enemyJet->GetColourPixel(bulX, bulY) > 0xffffff && enemyJet->GetColourPixel(bulX, bulY) << 24 != 0xff && enemyJet->IsVisible())
		{
			enemyJet->SetVisible(false);
			bul->SetVisible(false);
			score += 500;
		}
		// Collision with enemyFast jet
		else if (enemyFast->GetColourPixel(bulX, bulY) > 0xffffff && enemyFast->GetColourPixel(bulX, bulY) << 24 != 0xff && enemyFast->IsVisible())
		{
			enemyFast->SetVisible(false);
			bul->SetVisible(false);
			score += 1500;
		}
		// Collision with enemyLarge jet
		else if (enemyLarge->GetColourPixel(bulX, bulY) > 0xffffff && enemyLarge->GetColourPixel(bulX, bulY) << 24 != 0xff && enemyLarge->IsVisible())
		{
			bul->SetVisible(false);
			enemyHit++;

			// Requires 2 hits to die
			if (enemyHit == 2)
			{
				enemyLarge->SetVisible(false);
				enemyHit = 0;
				score += 1000;
			}
		}
	}

	// Player's jet collision with enemy bullet
	if (playerJet->GetColourPixel(enBulX, enBulY) > 0xffffff && playerJet->GetColourPixel(enBulX, enBulY) << 24 != 0xff && enBul->IsVisible())
	{
		playerJet->SetVisible(false);
		gameState = stFinished;
		SetupBackgroundBuffer();
		return;
	}
	// Player's jet collision with enemy missile
	else if (playerJet->GetColourPixel(enMissileX, enMissileY) > 0xffffff && playerJet->GetColourPixel(enMissileX, enMissileY) << 24 != 0xff && enMissile->IsVisible())
	{
		// Remove shield if it's up
		if (bShield)
		{
			bShield = false;
			enMissile->SetVisible(false);
			shield->SetVisible(false);
		}
		// Game over
		else
		{
			playerJet->SetVisible(false);
			gameState = stFinished;
			SetupBackgroundBuffer();
			return;
		}
	}

	// Player's jet collision with all three enemy jets
	// Check each pixel of player's jet if it's not trasparent and there is an enemy's non trasparent pixel at the same place
	for (int playerX = (playerJet->GetXCentre() - 40); playerX < (playerJet->GetXCentre() + 40); playerX++)
	{
		for (int playerY = (playerJet->GetYCentre() - 60); playerY < (playerJet->GetYCentre() + 60); playerY++)
		{
			playerPix = playerJet->GetColourPixel(playerX, playerY);
			enemyLargePix = enemyLarge->GetColourPixel(playerX, playerY);
			enemyFastPix = enemyFast->GetColourPixel(playerX, playerY);
			enemyJetPix = enemyJet->GetColourPixel(playerX, playerY);

			if ((playerPix > 0xffffff && playerPix << 24 != 0xff) &&
				((enemyLargePix > 0xffffff && enemyLargePix << 24 != 0xff && enemyLarge->IsVisible()) ||
				(enemyFastPix > 0xffffff && enemyFastPix << 24 != 0xff && enemyFast->IsVisible()) ||
				(enemyJetPix > 0xffffff && enemyJetPix << 24 != 0xff && enemyJet->IsVisible())))
			{
				playerJet->SetVisible(false);
				gameState = stFinished;
				SetupBackgroundBuffer();
			}
		}
	}
}

void JetShooter::StoreScore()
{
	// Add a score to a file if it's higher than in the file
	int currentScore;
	GetScore();
	if (score > highScore)
	{
		ofstream scoresFile("highscores.txt");
		if (scoresFile.is_open())
		{
			scoresFile << score;
			scoresFile.close();
		}
		else cout << "Unable to open file";
	}
}

void JetShooter::GetScore()
{
	string highestScore;

	// Read all high scores into int array
	ifstream scoresFile("highscores.txt");
	if (scoresFile.is_open())
	{
		while (getline(scoresFile, highestScore))
		{
			stringstream(highestScore) >> highScore;
		}
		scoresFile.close();
	}
	else 
	{
		highScore = 0;
	}

	sprintf(hScore, "Highest Score: %d", highScore);
}