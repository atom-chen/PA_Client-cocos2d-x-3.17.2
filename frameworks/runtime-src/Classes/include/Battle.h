#pragma once

#ifndef battle_h
#define battle_h

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <cstring>

#include "Player.h"
#include "Enemy.h"
#include "EnergyBody.h"
#include "InitialData.h"
#include "Event.h"
#include "KeyFrame.h"
#include "PropsMgr.h"
#include "Boss.h"

#include "json/json.h"
#include <fstream>

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;
using namespace rapidjson;

//#define _CRT_SECURE_NO_WARNINGS 1

using namespace std;

class CBattle
{
public:

	CBattle();
	~CBattle();
	void initData(int battleType);
	// ��ʼ��������̨���ݡ�     ������̨��λ��(0, 1, 2)����̨ID���ӵ�ID����̨����(0, 1, 2)���ȼ�����̨����ϵ��,  ���ܵȼ��� ��������json�ı�·��
	void setInitFortData(int nPlayer, int nFortPos, int nFortID, int nBulletID, int nFortType, int nFortLevel, int nFortStarDomainCoe, int nSkillLevel);
	// ��ʼ������ս������      �ҷ�ս��ID, ս�����ܵȼ��� ��̨1�� ��̨2�� ��̨3�� �з�ս��ID�� �з�ս�����ܵȼ��� ��̨1�� ��̨2�� ��̨3.�����Ҫ�ж��Ƿ�������װ���ԡ���
	void setInitShipData(int playerShipID, int playerShipSkillLevel, int p1, int p2, int p3, int enemyShipID, int enemyShipSkillLevel, int e1, int e2, int e3);
	// ��ʼ��bossս��ս������
	void setInitShipData(int playerShipID, int playerShipSkillLevel, int p1, int p2, int p3);

	void startFight();   // ս����ʼ
	void stopFight();    // ս��ֹͣ������
	void resumeFight();
	void update(double delta);
	void UpdateTime(double delta);
	void bossBattleUpdate(double delta); // boss ս��update

	// ���� ��-1����δ��������0����player win����1����enemy win����2����ƽ��
	int getBattleResult();
	int getBattleType();

	void playerWin();
	void playerLose();

	// ����¼�����
	void cleanEventVec(); // for ������
	void cleanEnergyEventVec();

	CPlayer* getPlayer();
	CEnemy* getEnemy();
	CBoss* getBoss();
	CEnergyBody* getEnergyBody();
	CPropsMgr* getPropMgr();
	bool isEnergyBodyLive();

	int getUpdataFrameCount();

	void countHitBulletToDelete(CBullet* pBullet);
	void cleanHitBulletMap();
	map<int, sHitBullet*> getHitBulletMap();

	// ���������¼���������
	void pushEnergyEventToVec(int eventType, bool isProp = false);
	vector<sEnergyBodyEvent*> getEnergyBodyEventVec();

	int getBattleTime();
	
	// ����������
	//�������ʼʱ��
	void initEnergyRefreshTimes();
	const char *getEnergyTimeString();
	// ���������·��
	void initEnergyBodyRoad();
	const char* getEnergyRoad();
	// buffRoad
	void initBossNpcBuffRoad();
	const char* getBossNpcBuffRoad();

	// �ͻ��˵���
	void setEnergyBodyRoad(string data);
	void setEnergyTimeString(string data);

	// json�ļ�·��
	void setJsonsPath(string skillDataPath, string propDataPath, string wrongCodePath, string shipSkillDataPath);
			// boss ��json�ļ�
	void setBossJsonPathAndID(string bossJsonPath, int bossID = 1);
	// ������̨����
	int fortSkillFire(int nSide, int nFortID, string strBuffPer);// �������ıߣ��ң�1���У�2������̨���� ��̨ID�� ���ܶ���ʱ�䣨s��, ��̨�������и���
	// ��ȡ�����Ƿ����buff
	const char * fortSkillIsAddBuff(int nSide, int nFortID);
	// ʹ�õ���
	int useProp(int nUser, int nPropID, int nTarget, int nFortID); // ʹ�÷���p:1, e:2;  ����ID;  Ӱ�췽��p:1, e:2; ��̨ID����ȫ�壬Ϊ0.
	// ʹ��ս������
	int useShipSkill(int nUser);//ʹ�÷��� p:1, e:2.

	// �ݻ�������
	void destroyEnergyBody(bool isProp = false);
	// �ֽ�������ˢ��ʱ��
	void splitEnergyRefreshTime(string data);
	void selectRefreshTime();

	//����֡���ݵ�keyframe
	void setKeyFrameData();
	// ��ȡconst char * ���͵�battle����
	const char* getCharBattleFrameData(int nPlayerIndex);//player�������ݣ�Ϊ0�� enemy�������ݣ�Ϊ1����Ҫ������������ǰ��
	const char* getCharOnlineSynchorFrameData(int nPlayerIndex);
	const char* getCharBossBattleFrameDataReconnect();
	const char* getCharBossBattleFrameData();// ͬ������
	// ��ȡstring���͵�battle����
	string getStringBattleFrameData();
	
	// �������ݽӿ�
	void setAllBattleData(char *data);
	void setAllNormalBattleData(char *allBattleData);
	void setAllBossBattleData(char *battleData);

	// ����ͬ�����ݽӿ�
	void synchronizationData(char *data);
	// ��ͨս��ͬ��
	void onlineSynchordata(char *partBattleData);
	// ͬ��bossս����
	void synchronizationBossData(char *bossBattleData);

	void setBattleData(char *data);     // ����
	int setBattleSynchordata(char* data);// ��ͨս��ͬ��
	void setBulletMgrData(char *data);

	void setPlayerData(char *data);
	void setEnemyData(char *data);

	void setPlayerFortData(char *data);
	void setEnemyFortData(char *data);
	void setHitBulletData(char *data);
	void setEnergyBodyEventData(char *data);
	void setPlayerBulletDataReconnect(char *data);
	void setEnemyBulletDataReconnect(char *data);
	void setEnergyBodyData(char *data);

	void setPlayerBuff(char *data);
	void setEnemyBuff(char *data);
	void setPlayerBuffEvent(char *data);
	void setEnemyBuffEvent(char *data);
	void setPlayerFortsEvent(char *data);
	void setEnemyFortsEvent(char *data);
	void setPropMgrData(char *data);
	void setPerPropMapData(char *data);
	void setPropEventData(char *data);
	
	void setBossBattleData(char *data);
	void setBossBulletMgrData(char *data);
	void setPlayerFortData_reconnect(char *data, int nFortIndex, int nPlayer);
	void setPlayerFortData_synchordata(char *data, int nFortIndex, int nPlayer);
	void setBattleData_BossReconnect(char *data);
	void setBattleData_BossSynchordata(char *data);
	void setBossBulletReconnect(char *data);
	void setBossEventReconnect(char *data);

	void decodeWrongCodeJsonFileData(); // �����������
	vector<wrongCodeData> getWrongCodeData();

	// ����ȫ������� (bossս)
	void setAllPlayerNumber(int nPlayerNumber);
	// bossս���ӵ��˺��ӳ�
	void addInjuryPercent(double dPercent);
	// bossս�����
	double getBossResultInjury();

	// ս�ܷ�ʣ����̨��
	int getFailerFortCount();
	void countSurrenderFort(int player);

private:
	int m_nBattleResult;
	int m_nBattleType;

	CPlayer *m_pPlayer;
	CEnemy *m_pEnemy;
	CBoss *m_pBoss;
	CPropsMgr *m_pPropsMgr;
	//CDataMgr *m_pDataMgr;
	int m_updateCount;

	CEnergyBody *m_pEnergyBody;
	double m_dEnergyRefreshTime;
	bool m_isEnergyLive;

	// �¼�
	int m_nCountUpdateFrame;
	//vector<CBattle*> m_vecBattleFrame;

	int m_nCountHitBullet;
	map<int, sHitBullet*> m_mapHitBullet;

	vector<sEnergyBodyEvent*> m_vecEnergyBodyEvent;

private:
	double m_dBattleTime;
	bool m_isBattleRuning;
	bool m_isBattleStop;
	CKeyFrame *m_pKeyFrame;
	string m_sEnergyBodyRoad;
	int m_nEnergyCreateCount;
	string m_stringEnergyTime;
	int m_nRefreshCount;
	int m_arrRefreshTime[12];

	string m_strSkillDataPath;
	string m_strPropDataPath;
	string m_strWrongCodePath;
	string m_strShipSkillDataPath;
	vector<wrongCodeData> m_vecWrongCodeData;

	string m_sBossNpcBuffRoad;
	string m_sBossDataPath;

	int m_nPlayerNumber;
	int m_nBossID;

	int m_nFailerFortNum; // ս��������ʧ�ܷ�ʣ����̨��

	// �����������õ����ݽӿڣ�ͬ����
public:
	void resetPlayer(CPlayer *pPlayer);
	void resetEnemy(CEnemy *pEnemy);
	void setEnergyRefreshTime(double dEnergyRefreshTime);
	double getEnergyRefreshTime();
	void resetEnergyLive(bool isLife);
	//isEnergyBodyLive();
	void resetCountHitBullet(int nCount);
	int getCountHitBullet();
	void resetHitBulletMap(map<int, sHitBullet*> map);
	//void resetEnergyBodyEventVec(vector<sEnergyBodyEvent*> vec);
	void resetBattleTime(double dTime);
	double getTime();
	void resetBattleRuning(bool isRuning);
	bool isBattleRuning();
	void resetBattleStop(bool isStop);
	bool isBattleStop();


};


#endif /* battle_h */
