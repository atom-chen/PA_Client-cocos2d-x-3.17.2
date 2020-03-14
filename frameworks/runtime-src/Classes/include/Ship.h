#pragma once

#include "BaseData.h"
#include "CommonData.h"
#include "Tool.h"
#include <vector>
#include "Fort.h"
//#include <sstream>
#include <fstream>

using namespace std;

class CBattle;

class CShip :public CBaseData
{
public:
	CShip();
	CShip(int nPlayerSide, int nShipID, int nShipLv, CBattle *pBattle);
	~CShip();

	void init();
	void loadJsonData();
	void update(double dTime);
	void setShipBattle(CBattle* pBattle);

	void attackFort();
	void beDamageByFortBullet(int nInjury);
	void targetIsBroken(int nFortID = 1000, int nFortIndex = 1000);
	void turnBarrelDir(double dPosX, double dPosY);

	void shipDeath();
	
	SYNTHE_SIZE(double, m_dShipFireTime, ShipFireTime);
	SYNTHE_SIZE(double, m_dShipSkillTime, ShipSkillTime);// ս������ʱ��
	SYNTHE_SIZE(int, m_nShipState, ShipState);         // ս��״̬
	SYNTHE_SIZE(int, m_nShipFireKind, ShipFireKind);   // ս������ģʽ
	SYNTHE_SIZE(CFort*, m_pLockTarget, LockTarget);    // ������������
	SYNTHE_SIZE(double, m_dBarrelRadian, BarrelRadian);// ��Ͳ�ĽǶ�  

private:
	CBattle* m_pShipBattle;
	vector<CFort*> m_vecInRangeFort;
};

