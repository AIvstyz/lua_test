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

//��ȡ�����˺�
int nongod::getBaseDamage()
{
	return this->baseDamage;
}
//����Ч�� ����ֵ����0 ��������
int nongod::getCrit(int a)
{
	if (isTrigger(this->critRate))
	{
		cout << "������" << endl;
		return this->critPlus*(this->baseDamage + a);
	}
	return 0;
}
//��ȡ��Ѫ ����ֵ����0 ������Ѫ
int nongod::getSuckBlood(int a)
{
	if (isTrigger(this->suckRate))
	{
		cout << "��Ѫ��" << endl;
		return (this->baseDamage + a)*this->suckPlus;
	}
	return 0;
}
//����Ч�� ����true �������
bool nongod::getFrozen()
{
	if (isTrigger(this->frozenRate))
	{
		cout << "��������" << endl;
		return true;
	}
	return false;
}
//��������
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
