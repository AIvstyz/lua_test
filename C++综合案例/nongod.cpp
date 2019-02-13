#include "nongod.h"
#include"filemanager.h"
#include <ctime>
nongod::nongod()
{

}

nongod::nongod(int id)
{
	cout << "nongod()" << endl;
	Mangerfile mf;
	map<string, map<string, string>>  m;
	mf.readline("Weapons.csv", m);
	string myid = to_string(id);
	this->weaponName = m[myid]["weaponName"].c_str();
	this->baseDamage = atoi(m[myid]["weaponAtk"].c_str());
	this->critPlus = atoi(m[myid]["weaponCritPlus"].c_str());
	this->critRate = atoi(m[myid]["weaponCritRate"].c_str());
	this->suckPlus = atoi(m[myid]["weaponSuckPlus"].c_str());
	this->suckRate = atoi(m[myid]["weaponSuckPlus"].c_str());
	this->suckRate = atoi(m[myid]["weaponFrozenRate"].c_str());
}

//获取基础伤害
int nongod::getBaseDamage()
{
	return this->baseDamage;
}
//暴击效果 返回值大于0 触发暴击
int nongod::getCrit(int a)
{
	if (isTrigger(this->critRate))
	{
		cout << "暴击！" << endl;
		return this->critPlus*(this->baseDamage + a);
	}
	return 0;
}
//获取吸血 返回值大于0 触发吸血
int nongod::getSuckBlood(int a)
{
	if (isTrigger(this->suckRate))
	{
		cout << "吸血！" << endl;
		return (this->baseDamage + a)*this->suckPlus;
	}
	return 0;
}
//冰冻效果 返回true 代表冰冻
bool nongod::getFrozen()
{
	if (isTrigger(this->frozenRate))
	{
		cout << "冰封术！" << endl;
		return true;
	}
	return false;
}
//触发概率
bool nongod::isTrigger(int rate)
{
	srand((unsigned int)time(NULL));
	int num = rand() % 101;
	return num > rate;
}

nongod::~nongod()
{
	cout << "~nongod" << endl;
}
