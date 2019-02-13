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

	cout << "请选择您的英雄:" << endl;
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
	cout << "您选择的英雄是:" << hero.heroName << endl;
	cout << "选择武器:" << endl;
	map<string, map<string, string>> weapondata;//武器容器
	mf.readline("Weapons.csv",weapondata);
	cout << "0、赤手空拳" << endl;
	sprintf(buf, "1、%s ", weapondata["1"]["weaponName"].c_str());
	cout << buf << endl;
	sprintf(buf, "2、%s ", weapondata["2"]["weaponName"].c_str());
	cout << buf << endl;
	sprintf(buf, "3、%s ", weapondata["3"]["weaponName"].c_str());
	cout << buf << endl;

	cin >> select;
	getchar();
	Weapon * weapon = NULL;
	switch (select)
	{
	case 1:
		cout << "武器在哪？";
		break;
	case 2:
		weapon = new nongod(select);
		break;
	}

	hero.EquipWeapon(weapon);//装备武器
	srand((unsigned int)time(NULL));
	int id = rand() % 5 + 1;//随机一个怪物

	monster monster(id);

	int round = 1;
	while (true)
	{
		getchar();
		cout << "当前第" << round << "回合开始---------" << endl;
		if (monster.monsterHp <= 0)
		{
			cout << "胜利！" << endl;
			break;
		}
		if (hero.heroHp <= 0)
		{
			cout << "失败！" << endl;
			break;
		}
		hero.Attack(&monster);
		cout << "怪物" << monster.monsterName << "剩余血量：" << monster.monsterHp << endl;
		monster.Attack(&hero);
		cout << "英雄" << hero.heroName << "剩余血量：" << hero.heroHp << endl;
		round++;
	}

}
int main(void)
{
	test01();
	system("pause");
	return 0;
}