#pragma once

#include "Props.h"
#include "Event.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class CBattle;

class CPropsMgr
{
public:
	CPropsMgr(CBattle *pBattle, string propDataPath, string wrongDataPath);
	~CPropsMgr();
	void initData();
	void update(double delta);
	//nUser��ʹ�õ��߷��� 1��player����2��enemy����player(����Ŀ�귽) 1:player���� 2��enemy���� ȫ��Ŀ�꣬fortIDΪ0��
	int useProp(int nUser, int nPropID, int player, int fortID);

	void usePropForReconnect(int nPropCount, int nPropID, double dBurstTime, int nUser, int nTargetSide, int nFortID, double dEnergyNpcDamage);
	void putPropEventToVec(int nPropEventID, int nTarget);

	//����ID�� Ŀ�귽�� ��̨ID
	void insertUsePropEventInVec(int propID, int targetSide, int fortID);
	void insertPropBurstEventInVec();// ��ʱ�Ȳ���


	// �������ٻ�NPC 
	void energyBodyCallNpc(double damage, int nUser, int nTarget);

	int getPropsCount();
	void setPropsCount(int nCount);
	map<int, CProps*> getPropsMap();
	void cleanPropMap();
	vector<sPropEvent> getPropEventVec();
	void cleanPropEvent();
	bool isPlayerNpcSecond();
	void setPlayerNpcSecond(int nBool);
	bool isEnemyNpcSecond();
	void setEnemyNpcSecond(int nBool);
	int getPlayerPropNpc();
	void setPlayerPropNpc(int nKind);
	int getEnemyPropNpc();
	void setEnemyPropNpc(int nKind);
	double getPlayerDamage();
	void setPlayerDamage(double dDamage);
	double getEnemyDamage();
	void setEnemyDamage(double dDamage);

private:
	//bool m_isEnemy;
	CBattle *m_pPropMgrBattle;
	string m_strPropDataPath;
	string m_strWrongDataPath;

	int m_nPropsCount;
	map<int, CProps*> m_mapProps;

	vector<sPropEvent> m_vecPropEvent;

	// �Ŷ�NPC 
	bool m_isPlayerNpcSecond;  //�Ƿ��еڶ�ֻNPC
	bool m_isEnemyNpcSecond;   //�Ƿ��еڶ�ֻNPC
	int m_nPlayerPropNpc;    //������ҵĵ���NPCΪ1 ������ҵ�������NPCΪ2�� ��ʼΪ0.
	int m_nEnemyPropNpc;     //������ҵĵ���NPCΪ1 ������ҵ�������NPCΪ2�� ��ʼΪ0.
	double m_dPlayerDamage;  //����ҵ��������˺�
	double m_dEnemyDamage;   //����ҵ��������˺�
};

