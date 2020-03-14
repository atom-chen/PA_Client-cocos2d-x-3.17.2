#pragma once

#include "Fort.h"
#include <map>
#include <time.h>

using namespace std;

class CBattle;

class CFortMgr
{
public:
	CFortMgr();
	CFortMgr(int nSide, CBattle* pBattle);
	~CFortMgr();

	void init();
	void update(double dTime);
	// ����������
	int createFort(int nFortID, int nFortLv, int nFortPosY, int nArmyPoint);
	// �ͻ��˵���
	void createFortInClient(int nFortID, int nFortLv, int nFortPosY, int nFortPosX);
	int getRandFortX();// ����ʱ��X�����ֵ

	CFort* getFortByID(int nFortID, int nFortIndex);
	double getFortAtkByID(int nFortID, int nFortIndex);

	void removeBrokenFort(int nFortID, int nFortIndex);

	SYNTHE_SIZE(int, m_nFortMgrSide, FortMgrSide);
	SYNTHE_SIZE(int, m_nCountFort, CountFort);
	//SYNTHE_SIZE(map<int, CFort*>, m_mapFortMgr, FortMap);
	map<int, CFort*> getFortsMap();

private:
	map<int, CFort*> m_mapForts;
	CBattle* m_pFortMgrBattle;
};

