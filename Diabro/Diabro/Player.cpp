#include <vector>
#include "Player.h"

using namespace std;

Player::Player()
{	
	_dirVec = (0, 0, 0);
	_movespeed = 250;
	_runspeed = 450;

	_rotationspeed = 0.13;

	//_stats = new CharacterStats();
}

bool Player::Initialize()
{
	_dirVec = (0, 0, 0);
	_movespeed = 250;
	_runspeed = 750;

	_rotationspeed = 0.13;
	_isRunning = false;

	SetUpStats();

	_currentHealth = _stats->GetStat(MaxHealth);
	_currentStamina = _stats->GetStat(MaxStamina);

	return true;
}

bool Player::AdjustHealth(float adjust)
{
	if((_currentHealth -= adjust) <= 0)
	{
		//Die();
		return false;
	}

	return true;
}

bool Player::AdjustStaminaOverTime(Ogre::Real deltaTime)
{
	Ogre::Real adjust = _isRunning ? -_stats->GetStat(StaminaRegen)/2 : _stats->GetStat(MaxStamina);
	
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);

	printf("%f\n", adjust);
	printf("current health: %f\n", _currentStamina);

	fclose(fp);

	adjust *= deltaTime;

	if ((_currentStamina += adjust) <= 0)
	{
		ToggleRun(false);

		return false;
	}
	else if ((_currentStamina += adjust) >= _stats->GetStat(MaxStamina))
	{
		_currentStamina = _stats->GetStat(MaxStamina);
	}

	return true;
}

bool Player::AdjustStamina(float adjust)
{
	if ((_currentStamina += adjust) <= 0)
	{
		// attack should be canceled
		return false;
	}
	else if((_currentStamina += adjust) >= _stats->GetStat(MaxStamina))
	{
		_currentStamina = _stats->GetStat(MaxStamina);
	}

	return true;
}

bool Player::SetUpStats()
{
	vector<Stat> stats;

	int statNr = (int)StatType::AMOUNT_OF_TYPES;

	for(int i = 0; i < statNr; ++i)
	{
		Stat tempStat((StatType)i, 0);

		stats.push_back(tempStat);
	}

	// Set all key stats. 
	stats.at((int)Strength).value = 8;
	stats.at((int)Dexterity).value = 8;
	stats.at((int)Intelligence).value = 8;
	stats.at((int)Vitality).value = 8;

	// Add 2 to the prim stat of player class. 
	stats.at((int)Strength).value += 2;

	stats.at((int)Armor).value = 18;
	stats.at((int)Damage).value = 2;
	stats.at((int)Resistance).value = 1;
	stats.at((int)MaxHealth).value = 40;
	stats.at((int)MaxStamina).value = 125;
	stats.at((int)StaminaRegen).value = 4;
	stats.at((int)AttackSpeed).value = 0;

	_stats = new CharacterStats(stats);

	return true;
}

void Player::Move(Ogre::Vector3& moveVec)
{
	_dirVec = moveVec;
}