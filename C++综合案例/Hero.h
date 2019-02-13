#pragma once
#include<string>
#include "Weapon.h"
//#include "monster.h"
//#include "filemanager.h"
using namespace std;
class monster;
class Hero
{
public:
	int heroHp;
	int heroAtk;//Ó¢ÐÛ»ù´¡¹¥»÷
	int heroDef;//Ó¢ÐÛ·ÀÓù
	string heroName;//Ó¢ÐÛÃû×Ö
	string heroInfo;//Ó¢ÐÛ¹¥·ÀÐÅÏ¢
	Weapon *pWeapon;//Ó¢ÐÛ×°±¸
public:
	Hero();
	Hero(int heroId);
	void Attack(monster * monster);
	void EquipWeapon(Weapon *weapon);
	~Hero();

};

