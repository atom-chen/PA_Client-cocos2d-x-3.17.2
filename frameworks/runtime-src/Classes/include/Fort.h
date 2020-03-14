#pragma once

#include <math.h>

#include <vector>
#include "Event.h"

#include "BaseData.h"

using namespace std;

class CBattle;

class CFort:public CBaseData
{
public:
	CFort();
	CFort(int fortSide, int nFortID, int nFortLv, CBattle *pBattle);
	~CFort();

	void init();
	void setBattlePoint(CBattle* pBattle);
	void update(double dTime);
	void setPosition(int nPosX, int nPosY);

	void justFly(double dTime);
	void flyToTarget(double dTime);
	void beHurtByShipBullet(double dInjury);
	void beHurtByFortBullet(double dInjuty, int nFirerID, int nFirerIndex, bool isTarget);// ����ˣ��Ƿ����������Ŀ�����
	void turnFortBody(double dTargetPosX, double dTargetPosY);   // ������ת�Ƕ�

	bool isStillLive();
	void fortInitState();
	void fortGoDie();
	void targetIsBroken();
	void attackerIsBroken(int nFort, int nFortIndex);

	void putFortInAttackVec(CFort* pFort);  //���빥���еĵл�����
	//void inRangeFortInVec(CFort* pFort);    //��������̷�Χ�ڵĵͼ�����
	void countShipDistance();               //�͵з�ս���ľ���

	void searchFort();

	void insertFortEvent(int nEvent, double dEventNumber);
	vector<SFortEvent> getFortEvent();
	void clearFortEvent();

	// ----------------------
	void countInRangeFort();                //ͳ�Ʒ�Χ�����ел�
	void judgeCloseTarget();                //�ж�����Ĺ����еĵл�
	// ----------------------

	SYNTHE_SIZE(int, m_nFortState, FortState);
	SYNTHE_SIZE(int, m_nBuffState, BuffState);
	SYNTHE_SIZE(int, m_nFortIndex, FortIndex);
	SYNTHE_SIZE(bool, m_isLockShip, LockShip);               // �Ƿ�����ս����Ϊ��������
	SYNTHE_SIZE(bool, m_isBeLockedByShip, IsBeLockedByShip); // ��ս����������
	SYNTHE_SIZE(double, m_dSpeed, speed);                    // �ƶ��ٶ�
	SYNTHE_SIZE(double, m_dInitSpeed, InitSpeed);
	SYNTHE_SIZE(CFort*, m_pAttackTarget, AttackTarget);   // ���������ĵл�
	SYNTHE_SIZE(int, m_nFortFireState, FortFireState);    // ս���Ĺ���״̬
	SYNTHE_SIZE(CFort*, m_pLockTarget, LockTarget);       // ������������
	SYNTHE_SIZE(double, m_dFireTimeCount, FireTimeCount); // ����ʱ��
	SYNTHE_SIZE(double, m_dSkillTimeCount, SkillTimeCount);//����ʱ�����
	SYNTHE_SIZE(double, m_dCountStepTime, CountStepTime); // ����ÿһ�������ʱ��
	
	SYNTHE_SIZE(int, m_nFortKind, FortKind);             //ս������
	SYNTHE_SIZE(int, m_nFortFireType, FortFireType);     //��������
	SYNTHE_SIZE(int, m_dInitBornTime, InitBornTime);     //��ʼ������ʱ��
	SYNTHE_SIZE(double, m_dFortBornTime, FortBornTime);  //����ս��ʱ��
	SYNTHE_SIZE(bool, m_isFortBorn, IsFortBorn);         //����״̬

	SYNTHE_SIZE(double, m_dFortVecX, FortVecX);          //ս��x����
	SYNTHE_SIZE(double, m_dFortVecY, FortVecY);          //ս��y����

	SYNTHE_SIZE(int, m_nEnergyCost, EnergyCost);         //����ʱ����������
	SYNTHE_SIZE(int, m_nArmPoint, ArmPoint);             //����ռ�õ�
	SYNTHE_SIZE(int, m_nBeDestroyEnergy, BeDestroyEnergy);//��׹������������

	
	SYNTHE_SIZE(double, m_dTurnRadian, TurnRadian);      // ת���Ļ��ȣ������ڿڣ�(������Ϊ����


	// ת���Ļ��ȣ����ڼ����ڿ�λ�ã�����ӵ�λ�ã�
	// ��Ӧʱ�䣨ת��ʱ��



private:
	CBattle* m_pFortBattle;
	vector<CFort*> m_vecInRangeForts;    // ����̷�Χ�ڵ�ս��
	vector<CFort*> m_vecAttackTarget;    // ���ڹ�����ս��
	vector<SFortEvent> m_vecFortEvent;   // ս�����¼�
};

