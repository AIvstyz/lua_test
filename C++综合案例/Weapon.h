#pragma once
#include<iostream>
#include<string>
using namespace std;
class Weapon
{
public:
	int baseDamage; //��������
	string weaponName; //��������
	int critPlus;  //����ϵ��
	int critRate;  //������
	int suckPlus;  //��Ѫϵ��
	int suckRate;  //��Ѫ��
	int frozenRate;  //������
public:
	Weapon();
	//��ȡ�����˺�
	virtual int getBaseDamage() = 0;
	//����Ч�� ����ֵ����0 ��������
	virtual int getCrit(int a) = 0;
	//��ȡ��Ѫ ����ֵ����0 ������Ѫ
	virtual int getSuckBlood(int a) = 0;
	//����Ч�� ����true �������
	virtual bool getFrozen() = 0;
	//��������
	virtual bool isTrigger(int rate) = 0;
	virtual ~Weapon();


};

