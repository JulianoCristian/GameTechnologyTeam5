#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "Character.h"
#include "BasicEnemy.h"

class Player : public Character
{
public:
	Player(Ogre::SceneNode*, Ogre::Entity*);
	~Player(){}

	void gainXP(int);
	void adjustKarma(int);
	int getKarma() { return _karmaPoints; }
	bool lightAttack() override;

	bool initialize() override;
	int _attackSpeed;
	int _AttackCD;

	BasicEnemy* _BasicEnemy;
	
	bool adjustHealth(float) override;
	bool adjustStaminaOverTime(Ogre::Real) override;
	bool adjustStamina(float) override;
	void update(const Ogre::FrameEvent&);

private:
	int _currentXP;
	int _xpTillNextLevel;
	int _karmaPoints;

	int calcXpTillLevel(int);
	void levelUp();
	bool _canAttack;
	Ogre::Real _attackCountDown;
	Ogre::Timer* _attackTimer;
};

#endif
