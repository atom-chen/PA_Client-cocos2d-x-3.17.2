#pragma once

#include "BulletBase.h"
#include "CommonData.h"
#include "Fort.h"
#include "Tool.h"
#include <vector>
#include <map>

using namespace std;

class CBattle;

class CBulletNormal:public CBulletBase
{
public:
	CBulletNormal(int nSide, int nID, int nType, CBattle* pBattle);
	~CBulletNormal();

	void update(double dTime);

	void setBeginPos(double dPosX, double dPosY);
	
	void bulletShellMove(double dTime);    // �����ƶ�
	void bulletShellMoveToShip(double dTime);// �ӵ�����ս��
	void pierceShellMove(double dTime);    // ���׵�
	void laserFire(double dTime);          // ����

	//void firerAndTarget(CFort* pFirerFort, CFort* pTargetFort);
	void setTargetFort(CFort* pFort);
	void setTheVecOfShip();
	void bulletFly(double dTime);
	
	int getTargetFortID();
	int getTargetFortIndex();
	// �㵽���������ľ���
	double countPointToLineDis(double dPointX, double dPointY);
	// ������ת�Ƕ�
	void turnBulletDirection(double dVecX, double dVecY);


	SYNTHE_SIZE(int, m_nBulletType, BulletType);
	SYNTHE_SIZE(bool, m_isShipBullet, IsShipBullet);            // �Ƿ�Ϊս���ӵ�
	SYNTHE_SIZE(bool, m_isBulletToShip, IsBulletToShip);        // �Ƿ�������ս�����ӵ�
	//SYNTHE_SIZE(CFort*, m_pTargetFort, TargetFort);             // Ŀ����̨
	//SYNTHE_SIZE(CFort*, m_pFirerFort, FirerFort);               // ������
	SYNTHE_SIZE(double, m_dTargetDirectionX, TargetDirectionX); // �����X��
	SYNTHE_SIZE(double, m_dTargetDirectionY, TargetDirectionY); // �����Y��
	SYNTHE_SIZE(double, m_dDirectionLength, DirectionLength);   // �����ĳ���
	SYNTHE_SIZE(double, m_dBulletDamage, BulletDamage);         // �ӵ����˺�
	SYNTHE_SIZE(int, m_nFirerID, FirerID);                      // �����ID
	SYNTHE_SIZE(int, m_nFirerIndex, FirerIndex);                // ��������
	SYNTHE_SIZE(double, m_dTurnRadian, TurnRadian);             // ��ת�Ƕȣ����ȣ�
	SYNTHE_SIZE(bool, m_isInShipUp, IsInShipUp);                // �ӵ��Ƿ���ս����
	SYNTHE_SIZE(bool, m_isDamageShip, IsDamageShip);            // �Ƿ񹥻���ս��	

private: 

	CBattle* m_pBulletBattle;
	vector<CFort*> m_vecRecordAttackFort;
	//CFort* m_pTargetFort;
};

