#pragma once
#include "json/json.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class CBattle;
class CProps
{
public:
	CProps(CBattle *pBattle, string jsonStr, int propID);
	~CProps();

	int update(double delta);
	void initData();
	void burstProps();
	void loadDataByJson(string jsonStr, int propID);

	// nUser : (ʹ�õ�����) 1 player, 2 enemy;
	// return 1:��ʱ���ߣ��޲���ʱ�䡣 return 2:�ж������ߡ�return 3����ǰ��NPC�ڳ���return ������롣
	int isUseProp(int nUser, int nPlayer, int nFortID, string wrongCodePath);   // player Ϊ1������player  nplayerΪ2�� ����enemy
	int getPropID();
	int getUserNum();
	int getTargetNum();
	int getTargetFortID();

	void setEnergyNpcDamage(double damage);

	double getTotalAck(int nSide); // 1 : player    2 : enemy

	void armorPiercingShell();  //���׵�
	void burnShell();        // ȼ�յ�
	void disturbShell();     // ���ŵ�
	void unenergyShell();    //���ܵ�
	void deepDamageShell();  //ǿϮ����
	void damageShipShell();  //�Խ�����
	void ackUpProp();      //������������
	void fortRepairingProp();//ս��ά�޵���
	void shieldProp();          //���ܵ���
	void passiveSkillStrongProp();//ս��������ǿ����
	void ackDownProp();          //�������ŵ���
	void unrepairingProp();      //ά�޸��ŵ���
	void reliveFortProp();       //����޸�����
	void chargeFortProp();       //��̨���ܵ���
	void destoryEnergyBodyProp();//�����������ݻ������壩����
	void lockEnergyBodyProp();   //���������������岻�ٱ仯������
	void energyBodyJumpProp();   //����ԾǨ��������ת�Ƶ������������ϣ�����
	void allFireProp();          //����ȫ�����ߣ�����������
	void absoluteZoneProp();     //�������򣨻��ܣ�
	void limitChargeProp();   //���޳��ܣ��ٷְ�������
	void unmissileProp();       //���������ߣ���
	void cleanBuffProp();       //������ʽ���������buff or ����buff��
	void EMPunenergyProp();     //EMP�𵴲����޷����ܺ��ͷż��ܣ�
	void radiationUnrepairingProp();//�����𵴲����޷��ָ�Ѫ����
	void callNPCtoFight();       //����NPC 

	// -------------
	void setPropID(int nPropID);
	double getPropBurstTime();
	void setPropBurstTime(double dBurstTime);
	void setUser(int nUser);
	void setTargetSide(int nTarget);
	void setTargetFort(int nTargetFort);
	double getEnergyNpcDamage();

private:
	int m_nPropID;    //-
	CBattle *m_pPropBattle;
	int m_nMissileOrNot;
	double m_dPropDamagePercent;
	double m_dPropBuffTime;
	double m_dPropBurstTime;  //-
	double m_dPropBuffValue;

	int m_nUser;           //
	int m_nTargetSide;      //
	int m_nTargetFort;       //

	double m_dEnergyNpcDamage;  //

	int m_nPropBuffType;
};

