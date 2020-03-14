#pragma once

#include <vector>
#include "BulletNormal.h"
#include "Event.h"

class CBattle;
class CBulletMgr
{
public:
	CBulletMgr(int nSide, CBattle* pBattle);
	~CBulletMgr();

	void update(double dTime);

	// �����̨
	void createBullet(int nID, int nType, double dPosX, double dPosY, int nFirerID, int nFirerIndex, double dAtk, CFort* pTargetFort = nullptr);
	// ���ս��
//	void createBulletToShip(int nID, int nType, double dPosX, double dPosY, int nFirerID, int nFirerIndex, double dShipPosX, double dShipPosY);
	// ս�����ӵ�
	void createShipBullet(int nID, int nType, double dPosX, double dPosY, CFort* pTargetFort);

	void removeBulletFromVec(int nID, int nIndex);
	// �Ƴ���������ս���ӵ�
	void removeBrokenTargetBullet(int nTargetID, int nTargetIndex);

	vector<CBulletNormal*> getBulletVec();

	vector<SBulletEventData> getBulletEvent();
	void insertBulletEvent(int nID, int nIndex, double dPosX, double dPosY, int nEvent);
	void clearBulletEventVec();

private:
	int m_nSide;
	CBattle* m_pBattle;
	vector<CBulletNormal*> m_vecBullet;
	int m_nBulletCount;
	vector<SBulletEventData> m_vecBulletEvent;
};

