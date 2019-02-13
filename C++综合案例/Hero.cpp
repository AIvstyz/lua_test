#include "Hero.h"
#include "monster.h"
#include "filemanager.h"
Hero::Hero()
{
}

Hero::Hero(int heroid)
{
	string myid = to_string(heroid);
	Mangerfile mf;
	map<string, map<string, string>>  m;
	mf.readline("Hero.csv", m);
	this->heroName = m[myid]["heroName"].c_str();
	this->heroHp = atoi(m[myid]["heroHp"].c_str());
	this->heroDef = atoi(m[myid]["heroDef"].c_str());
	this->heroAtk = atoi(m[myid]["heroAtk"].c_str());
	this->heroInfo = m[myid]["heroInfo"].c_str();
	this->pWeapon = NULL;
}
void Hero::Attack(monster *monster)
{
	int cirt = 0;
	int suck = 0;
	bool frozen = 0;
	int weapda = 0;
	if (pWeapon == NULL)
	{
		weapda = 0;
		cout << this->heroName << "赤手空拳冲了上去！" << endl;
	}
	else
	{
		weapda = this->heroAtk + this->pWeapon->baseDamage;
		cirt = pWeapon->getCrit(this->heroAtk);
		suck = pWeapon->getSuckBlood(this->heroAtk);
		frozen = pWeapon->getFrozen();
	}
	monster->isFrozen = frozen;
	int damage =weapda + cirt - monster->monsterDef;
	int truedamage = (damage > 0 ? damage : 1);
	this->heroHp += suck;
	monster->monsterHp -= truedamage;
	cout << this->heroName << "对怪物" << monster->monsterName << "造成了" << truedamage << "伤害！" << endl;

}
void Hero::EquipWeapon(Weapon *weapon)
{
	if (weapon == NULL)
		return;
	this->pWeapon = weapon;
	cout << this->heroName << "装备了" << this->pWeapon->weaponName << "!" << endl;
	
}
Hero::~Hero()
{
}
