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
	int heroAtk;//Ӣ�ۻ�������
	int heroDef;//Ӣ�۷���
	string heroName;//Ӣ������
	string heroInfo;//Ӣ�۹�����Ϣ
	Weapon *pWeapon;//Ӣ��װ��
public:
	Hero();
	Hero(int heroId);
	void Attack(monster * monster);
	void EquipWeapon(Weapon *weapon);
	~Hero();

};

