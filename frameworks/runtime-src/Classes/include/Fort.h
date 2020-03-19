#pragma once
#ifndef fort_h
#define fort_h

#include "Shape.h"
#include "InitialData.h"
#include "BuffMgr.h"
#include "Event.h"
#include "FortSkill.h"
#include <vector>

using namespace std;

class CBattle;

class CFort          // : public CShape
{
public:
	CFort(bool isEnemy, int fortIndex, string wrongCodePath);
	~CFort();

	enum FortType
	{
		ATTACK_TYPE = 0,
		DEFENSE_TYPE = 1,
		SKILL_TYPE = 2
	};

	void update(double dt);

	CFortSkill * getFortSkill();

	//void createFort(bool isEnemy, int fortIndex);
	void setFortID(int ID);
// �˺���̨
	double damageFort(double damage);   // damage �����ȿ����������ٴ�������
	// �ӵ��˺�
	void damageFortByBullet(double damage); 
	// �����˺�
	void damageFortBySkillBurst(double damage);
	// ���ܼ��ض����˺�
	void damageFortBySkillAddDamage(double damage);
	// NPC�˺�
	void damageFortByNPC(double damage);
	// ȼ���˺�
	void percentDamage(double percent);
	// �����ڵ��˺�
	void damageFortByPropBullet(double dDamage);
	// ��ʵ�˺�
	void trueDamageFort(double damage);
	// ս�����ܰٷֱ��˺�
	void damageFortByShipSkill(double dDamage);

	void fortDie();
// ����Ѫ��
	void addHp(double hp);
	// ���ܼ�Ѫ
	void addHpBySkill(double percent);
	// ս�����ܼ�Ѫ
	void addHpByShipSkill(double percent);

// ������̨������

			//long nFortID = lua_tointeger(FortData, 3); // ��̨ID
			//long nBulletID = lua_tointeger(FortData, 4);//ר��ID���ӵ���ͼ�꣩

			//long nFortType = lua_tointeger(FortData, 5); // ��̨����
			//long nFortLevel = lua_tointeger(FortData, 6); //��̨�ȼ�
			//long nFortStarDomainCoe = lua_tointeger(FortData, 7); //��̨����ϵ�� 
	void setFortData(int nFortID, int nBulletID, int nFortType, int nLevel, int nFortStarDomain, int nSkillLevel, string strPathJson);

	double getQualityCoeByLevel(int nLevel);
	
// ������̨��λ��
	void setFortPos(int posX, int posY);

	void setFortBulletID(int fortID);
// ������̨�ĳߴ磨��С��
	void fortSizeByID(int fortID);

// ����
	void addEnergy(double value);
	// ��������̨�ı���
	void addEnergySelf(); 
	// �������������
	void addEnergyByEnergy(double value);
	// �˺�������������(1)�뱻��(2)��
	void addEnergyByDamage(double dDamage, int nType);
	// ���߼�����
	void addEnergyByProp(double value);
	// ս�����ܼ�����
	void addEnergyByShipSkill(double percent);

	int fortSkillFireBegin(string strBuffPer); // ����
	void fortSkillFireEnd();
	const char * getIsAddBuff(); // ��ȡ�Ƿ����Buff��ֵ

	int getFortBulletID();

	int getFortIndex();
	double getFortAck();
	 
	// �ж���̨�Ƿ����
	bool isFortLive();
	int getFortID();
	double getFortHp();
	// ��ȡ��̨��ʼ�����Ѫ��
	double getFortMaxHp();
	double getFortEnergy();
	double getFortMaxEnergy();

	int getFortPosX();
	int getFortPosY();

	bool isFire();

	//��̨����(ս�����ܸ�����̨���Ӱٷ�20Ѫ�Ͱٷְ�����)
	void fortBeLiveByShipSkill(double dPercent);
	
	double getUnInjuryCoe();// ��ȡ�����ʼ����˺�������Ϊ������̨���ܻ���̨��Ҫ�������ظ���

	void cleanFortEventVec();
	vector<int> getFortEventVec();

	double getMomentAddHp();
	void recoverAddHp(double dHp);

	double getSkillAddHp();
	void recoverSkillAddHp(double dHp);

	double getPropAddHp();
	void recoverPropAddHp(double dHp);

	double getContinueAddHp();
	void recoverContinueAddHp(double dHp);

	double getSelfAddEnergy();
	void recoverSelfAddEnergy(double dEnergy);

	double getEnergyAddEnergy();
	void recoverEnergyAddEnergy(double dEnergy);

	double getPropAddEnergy();
	void recoverPropAddEnergy(double dEnergy);

	double getAttackAddEnergy();
	void recoverAttackAddEnergy(double dEnergy);

	double getBeDamageAddEnergy();
	void recoverBeDamageAddEnergy(double dEnergy);

	double getBulletDamage();
	void recoverBulletDamage(double dDamage);

	double getPropBulletDamage();
	void recoverPropBuleltDamage(double dDamage);

	double getBuffBurnDamage();
	void recoverBuffBurnDamage(double dDamage);

	double getNPCDamage();
	void recoverNPCDamage(double dDamage);

	double getSkillDamage();
	void recoverSkillDamage(double dDamage);

	double getReliveCountDown();

	double getShipSkillDamage();
	void recoverShipSkillDamage(double dDamage);

	double getShipSkillAddHp();
	void recoverShipSkillAddHp(double dHp);

	double getShipSkillAddEnergy();
	void recoverShipSkillAddEnergy(double dEnergy);

	void setFortBattle(CBattle *pBattle);
	void initFortSkill(int nSkillLevel, string strPath, double starDomainCoe);
	void setHaveSuitBuff(bool is, double suitBuffValue);

	void injuryAdditionInBossBattle(double dPercent);

public:
	void fortNormalState();
	void fortParalysisState();  // ̱��
	void fortBurningState();    // ȼ��
	void fortAckEnhanceState(double buffValue);
	void fortAckDisturbState(double buffValue);
	void fortRepaire(double percent);          // 
	void fortRepaireByEnergy(double percent);  // �����w�֏�
	void fortRepairing();
	void fortUnrepaire();
	void fortSupplyEnergy(double value);
	void fortUnEnergy();
	void fortShield(double percent);
	void fortRelive(double dPercent);
	//void fortDestroy();  // ����̨����İٷ�50���˺�
	void fortBreakArmorState(); // �Ƽ�״̬
	void fortPassiveSkillStrongerState();// ��ǿ��������

	void recoveryParalysis();
	void recoveryBurning();
	void recoveryAckUp();
	void recoveryAckDown();
	void recoveryEnergy();
	void recoveryRepairing();
	void recoveryUnrepaire();
	void recoveryUnEnergy();
	void recoveryShield();
	void recoveryFortBadBuff();
	void recoveryFortGoodBuff();
	void recoveryFortBreakArmorBuff();
	void recoveryFortPassiveSkillBuff();

	bool isParalysisState(); // ̱��
	bool isBurningState();   // ȼ��
	bool isAckUpState();     // ��������
	bool isAckDownState();   // ��������
	bool isRepairingState(); // ά��
	bool isUnrepaireState(); // ά�޸���
	bool isUnEnergyState();  // ��������
	bool isShieldState();    // ����
	bool isReliveState();    // ����״̬
	bool isSkillingState();  // ����״̬
	bool isBreakArmorState();// �Ƽ�״̬
	bool isPassiveSkillStrongerState();// ��ǿ��������״̬

private:
	vector<int> m_vecFortEvent;    // �¼���������ʱ����buff����̨������

	bool m_isEnemy;
	int m_nFortIndex;
	int m_nFortID;	
	int m_nFortBulletID;
	int m_nFortType;
	int m_nFortLevel;
	// ����ϵ��
	double m_dFortStarDomainCoe;
	// Ʒ��ϵ��
	double m_dFortQualityCoe;
	// �����ɳ�ϵ��
	double m_dFortAckGrowCoe;
	// �����ɳ�ϵ��
	double m_dFortHpGrowCoe;
	// ����ϵ��
	double m_dFortSpeedCoe;
	// ����ϵ��
	double m_dFortEnergyCoe;

	double m_dHp;
	double m_dEnergy;
	double m_dInterval;
	double m_dUnInjuryRate;
	double m_dFortDamage;

	int m_nPosX;
	int m_nPosY;
	bool m_isLive;
	double m_dFireTime;
	bool m_isFire; // û��

	CBattle *m_pFortBattle;
	CFortSkill *m_pFortSkill;

	string m_strWrongCodePath;
	bool m_isHaveSuitBuff;     //��һ��ʼ����ship���ݵ�ʱ��ֵ�ģ����ԣ��������踳ֵ��
	double m_dSuitBuffValue;

private:   // ��ʼ��ֵ
	double m_dInitAck;
	double m_dInitHp;
	double m_dInitEnergy;
	double m_dInitDefense;
	double m_dInitUnInjuryRate;
	double m_dInitDamage;
	
	bool m_isAddPassiveSkill;  // ��ⱻ������ֻ���һ�Σ����������_��

private:
	bool m_isFortParalysis;   // ̱��
	bool m_isFortBurning;    // ȼ��
	bool m_isFortAckUp;      // ��������

	bool m_isFortAckDown;    // ��������
	bool m_isFortRepairing;  // ����ά��
	bool m_isFortUnrepaire;  // ά�޸���
	bool m_isFortUnEnergy;     // ����
	bool m_isFortShield;
	bool m_isFortRelive;

	bool m_isFortSkillFire;
	bool m_isFortBreakArmor;    // �Ƽ�
	bool m_isFortPassiveSkillStronger; // ����������ǿ
	bool m_isHavePassiveSkillStronger;

	double m_dBurningCountTime;
	double m_dRepairingCountTime;
	double m_dReliveCountDown;
	double m_dReliveHp;
	double m_dAckDownValue;
	double m_dAckUpValue;

	double m_dAddPassiveEnergyTime;  // ��������̨����������ʱ��
	
	// ���@ʾ������׃��
private:
	double m_dMomentAddHp;      // ˲���Ѫ           ��
	double m_dSkillAddHp;       // ���ܻ�Ѫ
	double m_dPropAddHp;        // ���ߵ�˲�g��Ѫ     ��
	double m_dContinueAddHp;    // ���m��Ѫ           ��
	double m_dSelfAddEnergy;    // ������ӵ�����     ��
	double m_dEnergyAddEnergy;  // �����w��ӵ������w ��
	double m_dPropAddEnergy;    // �����������       ��
	double m_dAttackAddEnergy;  // ������ӵ�����     ��
	double m_dBeDamageAddEnergy;// ������ӵ�����     ��
	double m_dBulletDamage;     // �ӵ��˺�
	double m_dPropBulletDamage; // �����ڵ��˺�
	double m_dBuffBurnDamage;   // ȼ��buff�˺�
	double m_dNPC_Damage;       // NPC�˺�
	//double m_dSecondCountForRelive;// ����ʱ��һ�뷢һ��

	double m_dSkillDamage;      // ���܂���
	double m_dSkillTime;
	double m_dShipSkillDamage;  // ս�����ܿ�Ѫ
	double m_dShipSkillAddHp;   // ս�����ܼ�Ѫ
	double m_dShipSkillAddEnergy;//ս�����ܼ�����

	//////////////////////////////////
	        // ����������ͬ��//
	//////////////////////////////////
public:
	void resetFortEventVec(int nEvent);
	//getFortEventVec is up.
	//setIsEnemy ��ʵ���ã�һ��ʼ��ʼ�������ˣ���Ҫ��������ж����ıߵ��Ǹ���̨��
	bool isEnemy();
	//setFortIndex() Ҳ���ã���0����1�� ��2��һ��ʼ�趨�õı�ǡ������FortIndex��ȡ��̨����ĵڼ�����̨
	//getFortIndex() is up��
	//setFortID();���_ID
	//getFortID();
	//setFortBulletID();�ӏ�ID
	//getFortBulletID();
	void resetFortType(int nFortType);  //���_���
	int getFortType();
	void resetFortLevel(int nLevel);  // ���_�ȼ�
	int getFortLevel();
	void resetFortStarDomainCoe(double dStarDomainCoe); //����S��
	double getStarDomainCoe();
	void resetFortQualityCoe(double dQualityCoe); //Ʒ��ϵ��
	double getQualityCoe();
	void resetFortAckGrowCoe(double dAckGrowCoe); //�����ɳ�ϵ��
	double getAckGrowCoe();
	void resetFortHpGrowCoe(double dHpGrowCoe); //�����ɳ�ϵ��
	double getHpGrowCoe();
	void resetFortSpeedCoe(double dSpeedCoe); //����ϵ��
	double getSpeedCoe();
	void resetFortEnergyCoe(double dEnergyCoe); //����ϵ��
	double getEnergyCoe();
	void resetHp(double dHp); //Ѫ��
	//getFortHp()
	void resetEnergy(double dEnergy); //����
	//getFortEnergy();
	void resetFortInterval(double dInterval); //�����ӵ��ٶ�
	double getInterval();
	void resetUninjuryRate(double dUninjuryRate); //������
	//double getUnInjuryCoe();
	void resetFortAck(double dAck); //��̨�˺�
	//getFortAck()
	// setFortPos(x, y)   getFortPosX()   getFortPosY(); // ��̨����
	void resetFortLife(bool isLife); //��̨�Ƿ���״̬
	//isFortLive();
	void resetFireTime(double dFireTime); //��̨��ǰ���ͣ����ʱ��
	double getFireTime();
	void resetInitAck(double dAck); // ��ʼ����������Ӌ�㶼�Â����������������ã��䌍���Բ��á�
	double getInitAck();
	void resetInitHp(double dInitHp); //��ʼ��Ѫ�������Ѫ����
	//double geMaxtFortHp();
	//��ʼ��������100����ʼ���r�����ˣ���̎������
	void resetDefense(double dDefense); //���Ӌ������ʣ��䌍������ʣ��@���Ͳ����ˡ�
	double getDefense();
	void resetInitUnInjuryRate(double dRate); //��ʼ�������
	double getInitUnInjuryRate();
	void resetInitDamage(double dInitDamage); //��ʼ������ֵ
	double getInitDamage();
	void resetAddPassiveSkill(bool isAdd); //���������_�ı��Ӽ��ܙz�y
	bool isAddPassiveSkill();
	void resetFortParalysis(bool isParalysis); // �ɔ_��B
	void resetFortBurning(bool isBurning); // ȼ����B
	void resetAckUp(bool isAckUp); // ��������

	void resetAckDown(bool isAckDown);// ��������
	void resetRepairing(bool isRepairing);// ά��
	void resetUnrepaire(bool isUnrepaire);// ά�޸���
	void resetUnEnergy(bool isUnenergy);// ��������
	void resetShield(bool isShield);// ����
	void resetRelive(bool isRelive);// ��̨����
	void resetSkillFire(bool isSkillFire);//�ͷż���
	void resetBreakArmor(bool isBreakArmor);// �Ƽ�
	void resetPassiveSkillStronger(bool isPassiveSkillStronger);//��������
	bool isHavePassiveSkillStronger();          
	void resetHavePassiveSkillStronger(bool isHave);
	double getBurningCountTime();
	void setBurningCountTime(double dTime);
	double getRepairingCountTime();
	void setRepairingCountTime(double dTime);

	void setReliveCountDown(double dTime);
	double getReliveHp();
	void setReliveHp(double dHp);
	double getAckDownValue();
	void setAckDownValue(double dValue);
	double getAckUpValue();
	void setAckUpValue(double dValue);
	double getAddPassiveEnergyTime();
	void setAddPassiveEnergyTime(double dTime);
	double getSecondCountForRelive();
	void setSecondCountForRelive(double dTime);
	double getSkillTime();
	void setSkillTime(double dTime);
}; 

#endif /* fort_h */

