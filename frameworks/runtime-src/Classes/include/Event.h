#pragma once

enum EFortEvent
{
	FORT_BORN = 1,                   // �������
	FORT_TURN_BODY = 2,              // ��ת���� ����ת������
	FORT_ATTACK_READY = 3,           // ����׼��
	FORT_FIRE_EVENT = 4,                   // ��������
	FORT_SKILL_ON = 5,               // ���ܿ�
	FORT_SKILL_OFF = 6,              // ������
	FORT_BE_DAMAGE = 7,              // ������  ���۳���Ѫ����
	FORT_ADD_ATK = 8,                // ������ǿ
	FORT_ADD_HP = 9,                 // Ѫ������ �����ӵ�Ѫ����
	FORT_ADD_ENERGY = 10,            // �������� �����ӵ�������
	FORT_DIE = 11,                   // ����
	FORT_CREATE = 12
};

struct SFortEvent
{
	SFortEvent()
	{
		nEventID = 0;
		dEventNumber = 0.0;
	}
	int nEventID;
	double dEventNumber;
};

enum EBulletEvent
{
	BULLET_BORN = 1,    // �ӵ�����
	BULLET_BOMB = 2,    // �ӵ���ը
	BULLET_REMOVE = 3   // �Ƴ��ӵ�
};

struct SBulletEventData
{
	SBulletEventData()
	{
		nBulletID = 0;
		nBulletIndex = 0;
		dPosX = 0.0;
		dPosY = 0.0;
		nEventID = 0;
	}
	int nBulletID;
	int nBulletIndex;
	double dPosX;
	double dPosY;
	int nEventID;
};

enum EShipEvent
{

};

struct SShipEventData
{

};