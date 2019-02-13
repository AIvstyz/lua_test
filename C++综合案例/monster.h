#pragma once
#include"Hero.h"
#include <string>
using namespace std;
//class Hero;
class monster
{
public:
	string monsterName;
	int monsterHp;
	int monsterAtk;
	int monsterDef;
	bool isFrozen;

public:
	monster();
	monster(int mid);
	void Attack(Hero * hero);
	~monster();
};

