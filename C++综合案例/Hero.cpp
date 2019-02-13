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
		cout << this->heroName << "���ֿ�ȭ������ȥ��" << endl;
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
	cout << this->heroName << "�Թ���" << monster->monsterName << "�����" << truedamage << "�˺���" << endl;

}
void Hero::EquipWeapon(Weapon *weapon)
{
	if (weapon == NULL)
		return;
	this->pWeapon = weapon;
	cout << this->heroName << "װ����" << this->pWeapon->weaponName << "!" << endl;
	
}
Hero::~Hero()
{
}
