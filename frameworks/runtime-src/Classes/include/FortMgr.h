#pragma once
#ifndef CFortsMgr_h
#define CFortsMgr_h


#include <vector>
#include <map>

#include "InitialData.h"
#include <stdio.h>
#include "Fort.h"
#include <string>

using namespace std;

class CBattle;

class CFortsMgr
{
public:
	CFortsMgr(bool isEnemy, string wrongCodePath);
	~CFortsMgr();

	void update(double delta);

	//������̨
	void createForts();  //int fort1, int fort2, int fort3, bool isEnemy
	//�Ƴ�����̨
	void removeBrokenFort(int fortID);
	//�����𻵵���̨
	void createFortByID(int fortID);
	//������̨
	//void damageFort(int fortIndex, int nDamage);

	double getPlayerTotalHp();
	double getEnemyTotalHp();

	void cleanBetterBuff();
	void cleanBadBuff();

	int getFortAck(int fortIndex);
	bool isFortLive(int fortIndex);

	CFort* getFortByID(int ID, bool isEnemy);
	CFort* getFortByIndex(int index, bool isEnemy);
	//int* getFortsPos(int fortID, bool isEnemy);

	map<int, CFort*> getPlayerFort();
	map<int, CFort*> getEnemyFort();

	bool isPlayerCleanBetterBuff();
	bool isPlayerCleanBadBuff();
	bool isEnemyCleanBadBuff();
	bool isEnemyCleanBetterBuff();
	void recoveryCleanBetterBuff();
	void recoveryCleanBadBuff();

	void setFortMgrBattle(CBattle *pBattle);
	void setFortSuitBuff(double suitBuffValue);

	// for ��ȡ���������һ��̨
	void setPlayerDieFortID(int fortID);
	void setEnemyDieFortID(int fortID);
	int getDiePlayerFortID();
	int getDieEnemyFortID();

	// ����bossս���˺��ӳ�
	void addInjuryPercent(double dPercent);

private:
	map<int, CFort*> m_mapMyForts;
	map<int, CFort*> m_mapEnemyForts;
	bool m_isEnemy;
	int m_nMyTop_fortID;
	int m_nMyMid_fortID;
	int m_nMyBot_fortID;
	int m_nEnemyTop_fortID;
	int m_nEnemyMid_fortID;
	int m_nEnemyBot_fortID;
	// P:player �ҷ�
	bool m_isPCleanBetBuff;
	bool m_isPCleanBadBuff;
	// E:enemy �з�
	bool m_isECleanBetBuff;
	bool m_isECleanBadBuff;

	CBattle *m_pFortMgrBattle;
	string m_strWrongCodePath;

	int m_nRecentDiePlayerFort;
	int m_nRecentDieEnemyFort;
};


#endif /* CFortsMgr_h */


