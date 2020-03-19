#pragma once

#ifndef EVENT_H
#define EVENT_H

#include "stdafx.h"

enum EnergyEvent
{
	ENERGY_BORN = 0,    // ����������
	ENERGY_CHANGE = 1,  // ������ת��
	ENERGY_JUMP = 2,    // ������ԾǨ
	ENERGY_GO_DIE = 3   // �����屬ը
};

struct sEnergyBodyEvent
{
	sEnergyBodyEvent()
	{
		nEventType = 0;
		nBodyType = 0;
		dBodyHp = 0.0;
		dPlayerDamage = 0.0;
		dEnemyDamage = 0.0;
		nBodyPosX = 0.0;
		nBodyPosY = 0.0;
	}
	int nEventType;
	int nBodyType;
	double dBodyHp;
	double dPlayerDamage;
	double dEnemyDamage;
	int nBodyPosX;
	int nBodyPosY;
};

enum FortEvent
{
	FORT_FIRE = 1,				 // ��̨�����ӵ�            
	// ����
	FORT_SKILL = 2,				 // ��̨�ͷż���
	FORT_SKILL_END = 3,			 // ��̨�ͷż��ܽ���
	// ��Ѫ
	FORT_ENERGY_ADD_HP = 4,		 // ��̨(�����壩��Ѫ     ��ֵ��   
	FORT_PROP_ADD_HP = 5,        // ���߼�Ѫ              ��ֵ��
	FORT_CONTINUE_ADD_HP = 6,    // ������Ѫ              ��ֵ��
	FORT_SKILL_ADD_HP = 7,       // ���ܻ�Ѫ              ��ֵ��
	// ����
	FORT_SELF_ADD_ENERGY = 8,    // ��̨�����������      ��ֵ��
	FORT_ENERGY_ADD_ENERGY = 9,	 // ��̨������(������)    ��ֵ��
	FORT_PROP_ADD_ENERGY = 10,    // ��̨���߼���         ��ֵ��
	FORT_ATTACK_ADD_ENERGY = 11, // ��̨����������        ��ֵ��
	FORT_BE_DAMAGE_ADD_ENERGY = 12, // ��̨����������     ��ֵ��
	// ��Ѫ
	FORT_BULLET_DAMAGE = 13,     // �ӵ��˺���Ѫ          ��ֵ��
	FORT_PROP_BULLET_DAMAGE = 14,// �����ڵ��˺�          ��ֵ��
	FORT_BUFF_BURN_DAMAGE = 15,  // ȼ��buff�˺�          ��ֵ��
	FORT_NPC_DAMAGE = 16,        // NPC�˺�               ��ֵ��
	FORT_SKILL_DAMAGE = 17,      // ���܂���              ��ֵ��

	FORT_DEEP_DAMAGE = 18,       // �����ٷ�50�˺�
	FORT_BE_DEEP_DAMAGE = 19,    // ������ٷ�50�˺�         

	FORT_DIE = 20,				 // ��̨���� 
	FORT_RELIVE_COOLDOWN = 21,   // ��̨�����ʱ(0-10s) (ֵ��
//	//     FORT_RECOVER = 4,        //��̨����״̬��10�룩״̬Ϊ˲ʱ
	FORT_RELIVE = 22,            // ��̨����
	FORT_EVENT_CLEAN_GOOD_BUFF = 23,   // ��̨�������buff���з�ȫ�壬�����ҷ�ȫ�壩
	FORT_EVENT_CLEAN_BAD_BUFF = 24,   //��̨��ռ���buff

	// ս������
	FORT_SHIP_SKILL_ADD_HP = 25,    //��Ѫ
	FORT_SHIP_SKILL_ADD_ENERGY = 26,//������
	FORT_SHIP_SKILL_DAMAGE = 27     //�˺�����Ѫ��

};

enum BossEvent
{
	BOSS_FIRE = 1,                   // boss�չ�
	
	BOSS_SKILL_BEGIN = 2,            // boss���ܿ�ʼ
	BOSS_SKILL_FIRE = 3,             // boss���ܱ���
	//BOSS_SKILL_2_BEGIN = 4,          // ����1
	//BOSS_SKILL_2_FIRE = 5,           //
	//BOSS_SKILL_3_BEGIN = 6,          //

	BOSS_CALL_NPC_SKILL = 4,         // boss�ٻ�npc
	BOSS_CALL_NPC_BACK = 5,          // boss����npc��ȥ

	BOSS_BE_DAMAGE_BY_BULLET = 6,    // �ӵ��˺�
	BOSS_BE_DAMAGE_BY_FORT_SKILL = 7,// �����˺�
	BOSS_BE_DAMAGE_BY_NPC = 8,       // NPC �˺�
	BOSS_BE_DAMAGE_BY_PROP = 9,      // �����˺�
	BOSS_BE_DAMAGE_BY_SHIP_SKILL = 10,//ս�������˺�

	BOSS_CHANGE_STAGE_ONE = 11,      // �л�״̬1
	BOSS_CHANGE_STAGE_TWO = 12,      // �л�״̬2
	BOSS_CHANGE_STAGE_OVER = 13,     // �л�״̬���
    // ADD
    BOSS_BE_DEEP_DAMAGE_BY_FORT_SKILL = 14
};

struct sBuffEvent
{
	sBuffEvent()
	{
		nBuffID = 0;
		nBuffFort = 0;
	}
	int nBuffID;
	int nBuffFort;
};

enum buffEvent
{
	ACK_UP_BUFF_ADD = 1,          // ��ӻ�������
	REPAIRING_BUFF_ADD = 2,       // ��ӳ���ά��
	SHIELD_BUFF_ADD = 3,          // ��ӻ���
	PASSIVE_SKILL_STRONGER_BUFF_ADD = 4,// ��ӱ���������ǿ
	PARALYSIS_BUFF_ADD = 5,       // ���̱��
	BURNING_BUFF_ADD = 6,         // ���ȼ��
	ACK_DOWN_BUFF_ADD = 7,        // ��ӻ�������
	REPAIR_DISTURB_BUFF_ADD = 8,  // ���ά�޸���
	ENERGY_DISTURB_BUFF_ADD = 9,  // �����������
	BREAK_ARMOR_BUFF_ADD = 10,    // ����Ƽ�
	UNMISSILE_BUFF_ADD = 11,      // ��ӷ�����

	ACK_UP_BUFF_DELETE = 21,      // ɾ����������
	REPAIRING_BUFF_DELETE = 22,   // ɾ������ά��
	SHIELD_BUFF_DELETE = 23,      // ɾ������
	PASSIVE_SKILL_STRONGER_BUFF_DELETE = 24, // ɾ������������ǿ
	PARALYSIS_BUFF_DELETE = 25,   // ɾ��̱��
	BURNING_BUFF_DELETE = 26,     // ɾ��ȼ��
	ACK_DOWN_BUFF_DELETE = 27,    // ɾ����������
	REPAIR_DISTURB_BUFF_DELETE = 28, // ɾ��ά�޸���
	ENERGY_DISTURB_BUFF_DELETE = 29, // ɾ����������
	BREAK_ARMOR_BUFF_DELETE = 30, // ɾ���Ƽ�
	UNMISSILE_BUFF_DELETE = 31,   // ɾ��������
};

struct sPropEvent
{
	sPropEvent()
	{
		nPropEventID = 0;
		nTarget = 0;
	}
	int nPropEventID;
	int nTarget;
};

enum propEvent
{
	USE_ARMOR_PIERCING_SHELL = 1,    //���׵����˺����Ƽף�
	USE_BURN_SHELL = 2,               //ȼ�յ�
	USE_DISTURB_SHELL = 3,             //���ŵ���̱����
	USE_UNENERGY_SHELL = 4,             //���ܵ����������ţ�
	USE_DEEP_DAMAGE_SHELL = 5,           //ǿϮ�������˺���
	USE_DAMAGE_SHIP_SHELL = 6,            //�Խ�������ȫ���˺���
	USE_ACK_UP_PROP = 7,                   //��������
	USE_FORT_REPAIRING_PROP = 8,            //ս��ά�ޣ�����ά�ޣ�
	USE_SHIELD_PROP = 9,                     //�������ܣ����ܣ�
	USE_PASSIVE_SKILL_STRONG_PROP = 10,       //ս������ǿ��
	USE_ACK_DOWN_PROP = 11,                  //��������
	USE_UNREPAIRING_PROP = 12,              //ά�޸���
	USE_RELIVE_FORT_PROP = 13,             //ս���޸���������̨��
	USE_CHARGE_FORT_PROP = 14,            //��̨���ܣ��ָ�������
	USE_DESTORY_ENERGY_BODY_PROP = 15,   //�ݻ�������
	USE_LOCK_ENERGY_BODY_PROP = 16,     //����������
	USE_JUMP_ENERGY_BODY_PROP = 17,    //������ԾǨ
	USE_ALL_FIRE_PROP = 18,           //����ȫ����ȫ�����������
	USE_ABSOLUTE_ZONE_PROP = 19,     //�������򣨻��ܣ�
	USE_LIMIT_CHARGE_PROP = 20,       //���޳��ܣ���������
	USE_UNMISSILE_PROP = 21,           //��������Լ�����õ�����
	USE_CLEAN_BUFF_PROP = 22,           //������ʽ�����buff��
	USE_EMP_UNENERGY_PROP = 23,          //EMP�𵴲���ȫ���������ţ�
	USE_RADIATION_UNREPAIRING_PROP = 24,  //�����𵴲���ȫ��ά�޸��ţ�
	CALL_NPC_BY_PROP = 1408,                //����֧Ԯ������NPC�������ߣ�
	//CALL_NPC_BY_ENERGY = 26,                //����֧Ԯ������NPC���������壩

	BURST_ARMOR_PIERCING_SHELL = 51,          //���׵���ը
	BURST_BURN_SHELL = 52,                   //ȼ�յ���ը
	BURST_DISTURB_SHELL = 53,               //���ŵ���ը
	BURST_UNENERGY_SHELL = 54,             //���ܵ���ը
	BURST_DEEP_DAMAGE_SHELL = 55,         //ǿϮ����ը
	BURST_DAMAGE_SHIP_SHELL = 56,        //�Խ�����ը

	NPC_BACK = 75                      //NPC����
};

#endif // EVENT_H
