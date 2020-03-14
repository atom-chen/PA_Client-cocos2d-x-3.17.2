#pragma once
#include "CommonData.h"

class CBaseData
{
public:
	CBaseData();
	~CBaseData();
	SYNTHE_SIZE(int, m_nSide, Side);
	SYNTHE_SIZE(int, m_nID, ID);
	SYNTHE_SIZE(int, m_nLv, Lv);
	SYNTHE_SIZE(double, m_dHp, Hp);
	SYNTHE_SIZE(double, m_dInitHp, InitHp);
	SYNTHE_SIZE(double, m_dEnergy, Energy);
	SYNTHE_SIZE(double, m_dAtk, Atk);
	SYNTHE_SIZE(double, m_dInitAtk, InitAtk);
	SYNTHE_SIZE(int, m_nRange, Range);//���
	
	SYNTHE_SIZE(double, m_dPosX, PosX);
	SYNTHE_SIZE(double, m_dPosY, PosY);
	SYNTHE_SIZE(int, m_nSizeRadius, SizeRadius);  // ��Χ��С
	SYNTHE_SIZE(int, m_nSizeLength, SizeLength);  // ��
	SYNTHE_SIZE(int, m_nSizeWidth, SizeWidth);    // �� 

	SYNTHE_SIZE(int, m_nBulletID, BulletID);             // �ӵ�ID
	SYNTHE_SIZE(int, m_nBulletType, BulletType);         // �ӵ�����
	SYNTHE_SIZE(int, m_nBulletSpeed, BulletSpeed);   // �ӵ������ٶ�

	SYNTHE_SIZE(double, m_dSkillTime, SkillTime);        // ����ʱ��
	
	SYNTHE_SIZE(double, m_dFireInterval, FireInterval); // �����ٶ�
	SYNTHE_SIZE(double, m_dInitFireInterval, InitFireInterval);//��ʼ������


	virtual bool isInRange(int ax, int ay, int bx, int by, int nRange);
};
