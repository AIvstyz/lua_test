#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<time.h>
#include"Hero.h"
#include "filemanager.h"
#include "nongod.h"
#include "monster.h"
#include "Weapon.h"
using namespace std;

void test01()
{
	Mangerfile mf;
	map<string, map<string, string>> hm;
	mf.readline("Hero.csv", hm);

	cout << "��ѡ������Ӣ��:" << endl;
	char buf[1024];
	sprintf(buf, "1. %s<%s>", hm["1"]["heroName"].c_str(), hm["1"]["heroInfo"].c_str());
	cout << hm["1"]["heroinfo"].c_str()<<buf << endl;
	sprintf(buf, "2. %s<%s>", hm["2"]["heroName"].c_str(), hm["2"]["heroInfo"].c_str());
	cout << buf << endl;
	sprintf(buf, "3. %s<%s>", hm["3"]["heroName"].c_str(), hm["3"]["heroInfo"].c_str());
	cout << buf << endl;
	int select;
	cin >> select;
	getchar();

	Hero hero(select);
	cout << "��ѡ���Ӣ����:" << hero.heroName << endl;
	cout << "ѡ������:" << endl;
	map<string, map<string, string>> weapondata;//��������
	mf.readline("Weapons.csv",weapondata);
	cout << "0�����ֿ�ȭ" << endl;
	sprintf(buf, "1��%s ", weapondata["1"]["weaponName"].c_str());
	cout << buf << endl;
	sprintf(buf, "2��%s ", weapondata["2"]["weaponName"].c_str());
	cout << buf << endl;
	sprintf(buf, "3��%s ", weapondata["3"]["weaponName"].c_str());
	cout << buf << endl;

	cin >> select;
	getchar();
	Weapon * weapon = NULL;
	switch (select)
	{
	case 1:
		cout << "�������ģ�";
		break;
	case 2:
		weapon = new nongod(select);
		break;
	}

	hero.EquipWeapon(weapon);//װ������
	srand((unsigned int)time(NULL));
	int id = rand() % 5 + 1;//���һ������

	monster monster(id);

	int round = 1;
	while (true)
	{
		getchar();
		cout << "��ǰ��" << round << "�غϿ�ʼ---------" << endl;
		if (monster.monsterHp <= 0)
		{
			cout << "ʤ����" << endl;
			break;
		}
		if (hero.heroHp <= 0)
		{
			cout << "ʧ�ܣ�" << endl;
			break;
		}
		hero.Attack(&monster);
		cout << "����" << monster.monsterName << "ʣ��Ѫ����" << monster.monsterHp << endl;
		monster.Attack(&hero);
		cout << "Ӣ��" << hero.heroName << "ʣ��Ѫ����" << hero.heroHp << endl;
		round++;
	}

}
int main(void)
{
	test01();
	system("pause");
	return 0;
}