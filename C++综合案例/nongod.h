#pragma once

#include "Weapon.h"
using namespace std;
//#include "filemanager.h"
class nongod :	public Weapon
{
public:
	nongod();
	nongod(int id);
	//��ȡ�����˺�
	int getBaseDamage();
	//����Ч�� ����ֵ����0 ��������
	int getCrit(int a);
	//��ȡ��Ѫ ����ֵ����0 ������Ѫ
	int getSuckBlood(int a);
	//����Ч�� ����true �������
	bool getFrozen();
	//��������
	bool isTrigger(int rate);
	~nongod();
};

