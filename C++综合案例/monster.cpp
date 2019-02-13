#include "monster.h"
#include "filemanager.h"
monster::monster()
{
}

monster::monster(int mid)
{
	string mmid = to_string(mid);
	Mangerfile mf;
	map<string, map<string, string>> m;
	mf.readline("Monsters.csv", m);
	this->monsterName = m[mmid]["monsterName"];
	this->isFrozen = false;
	this->monsterAtk = atoi(m[mmid]["monsterAtk"].c_str());
	this->monsterDef = atoi(m[mmid]["monsterDef"].c_str());
	this->monsterHp = atoi(m[mmid]["monsterHp"].c_str());
}

void  monster::Attack(Hero * hero)
{
	if (this->isFrozen)
	{
		cout << this->monsterName << "被冰封了，停止此回合，进入下一回合！" << endl;
		return;
	}
	int mdamage = this->monsterAtk;
	int truemdamage = mdamage > 0 ? mdamage : 1;
	hero->heroHp -= truemdamage;
	cout << "怪物<"<<this->monsterName << ">对英雄" << hero->heroName << "造成了" << truemdamage << "伤害！" << endl;
}
monster::~monster()
{
}
