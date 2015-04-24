#pragma once
#include "BaseEngine.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Jet.h"
#include "EnemyJet.h"
#include "EnemyFast.h"
#include "LargeEnemyJet.h"
#include "missile.h"
#include "Shield.h"

class JetShooter :
	public BaseEngine
{
public:
	JetShooter();
	~JetShooter();
	enum State { stInitial, stMain, stPaused, stFinished };
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void GameAction();
	void KeyDown(int iKeyCode);
	void DrawChanges();
	void DrawScreen();
	void DrawStrings();
	void Collisions();
	void StoreScore();
	void GetScore();

private:
	Bullet *bul;
	EnemyBullet *enBul;
	State gameState;
	Jet *playerJet;
	EnemyJet *enemyJet;
	EnemyFast *enemyFast;
	LargeEnemyJet *enemyLarge;
	missile *enMissile;
	Shield *shield;
	bool bShield;
	int shieldTime;
	int enemyHit;
	int score;
	char sScore[30];
	char cScore[30];
	char hScore[30];
	int highScore;
	enum JetModel {blue, red, black};
	JetModel chosenJet;
};

