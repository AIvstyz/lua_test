#pragma once

#include "Weapon.h"
using namespace std;
//#include "filemanager.h"
class nongod :	public Weapon
{
public:
	nongod();
	nongod(int id);
	//获取基础伤害
	int getBaseDamage();
	//暴击效果 返回值大于0 触发暴击
	int getCrit(int a);
	//获取吸血 返回值大于0 触发吸血
	int getSuckBlood(int a);
	//冰冻效果 返回true 代表冰冻
	bool getFrozen();
	//触发概率
	bool isTrigger(int rate);
	~nongod();
};

