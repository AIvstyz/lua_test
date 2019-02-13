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
		cout << this->monsterName << "�������ˣ�ֹͣ�˻غϣ�������һ�غϣ�" << endl;
		return;
	}
	int mdamage = this->monsterAtk;
	int truemdamage = mdamage > 0 ? mdamage : 1;
	hero->heroHp -= truemdamage;
	cout << "����<"<<this->monsterName << ">��Ӣ��" << hero->heroName << "�����" << truemdamage << "�˺���" << endl;
}
monster::~monster()
{
}
