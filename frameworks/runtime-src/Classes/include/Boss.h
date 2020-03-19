#pragma once
#include <vector>
#include <string>
#include "Bullet.h"
#include "Event.h"
#include "BulletMgr.h"

using namespace std;

class CBattle;

class CBoss
{
public:
	enum bossStage
	{
		ONE_STAGE,
		TWO_STAGE,
		THREE_STAGE
	};
	CBoss(string strDataPath, CBattle *pBattle, int nPlayer, int bossID);
	~CBoss();
	void init();
	void update(double delta);
	void loadBossData(string strBossDataPath);// distinguish client and server
	void splitNpcBuffRoad(string strData);

	void createBossBullet(int nBulletIndex, double dTime);// ����
	void addBossEvent(int nEvent); // ����

	CBulletMgr* getBossBulletMgr();

	vector<int> getBossEvent();
	vector<CBullet*> getBossBullet();

	// ����ȫ�������
	//void setAllPlayerNumber(int nPlayer);

	void cleanBossEventVec();
	void cleanBossBulletVec();
	// ��ͨ�ӵ����������̨
	void bulletDamagePlayer();
	// ����
	void bossSkillBurst();
	void oneStageSkill();
	void twoStageSkill();
	void finalSkill();

	// boss�л�״̬ʱ������ת��
	void changeDataToNextStage();
	// boss��ʼ�л�״̬
	void bossChangeBegin();
	// ���ö�ս��̨̱��
	void setFortParalysis();
	// ��̨�ָ�״̬
	void recoverFortState();
	// �л�״̬����
	void bossChangeOver();
	// �ٻ�NPC�������
	void NpcFight();
	// ����npcЯ����buff
	int chooseNpcBuff(int nKind);

	// boss �ܻ�
	void bossBeDamageByBullet(double dDamage);
	void bossBeDamageByFortSkill(double dDamage);
	void bossBeDamageByNPC(double dDamage);
	void bossBeDamageByProp(double dDamage);
	void bossBeDamageByShipSkill(double dDamage);
    void bossBeDeepDamageByFortSkill(double dDamage);

	// boss��������
	double getBossUninjuryRate();
	// ����boss������Ѫ��
	double getBossTotalDamage();

	// ����ʾ�¼����õ����ݽӿ�
	double getBulletDamageNumber();
	double getFortSkillDamageNumber();
	double getNpcDamageNumber();
	double getPropDamageNumber();
	double getShipSkillDamageNumber();
	int getNpcType();

	// �ָ����ݣ���ȡ��ʾ������֮��
	void recoveryNumber();

	void setNumberData(double dBullet, double dFortSkill, double dNpc, double dProp, double dShipSkill, int nNpcType);

//------------------------------------------
	       // ����
//------------------------------------------
	double getBossAck();
	int getBossStage();
	double getTotalDamage();
	bool isInChange();
	bool isFire();
	double getBossTotalTime();
	double getFireTime();
	double getStageTime();
	double getStageTiming();
	int getCountBullet();
	// ������
	double getChangeTime();
	double getNpcTime();
	bool isNpcFlying();
	double getNpcFlyTime();
	int getCountNpc();
	double getFireInterval();
	bool isBossSkill();
	double getBossSkilling();
	double getSkillBurstTime();
	// speed
	double getFireSkillCondition();
	double getBulletBurstTime();

	void cntSetBossAck(double dBossAck);
	void cntSetBossStage(int nBossStage);
	void cntSetTotalDamage(double dTotalDamage);
	void cntIsInChange(int nIs);
	void cntIsFire(int nIs);
	void cntSetBossTotalTime(double dTotalTime);
	void cntSetFireTime(double dTime);
	void cntSetStageTime(double dTime);
	void cntSetStageTiming(double dTime);
	void cntSetCountBullet(int nBulletCount);
	void cntSetChangeTime(double dTime);
	void cntSetNpcTime(double dTime);
	void cntIsNpcFlying(int nIs);
	void cntSetNpcFlyTime(double dTime);
	void cntSetCountNpc(int nCount);
	void cntSetFireInterval(double dInterval);
	void cntIsBossSkill(int nIs);
	void cntSetBossSkilling(double dTime);
	void cntSetSkillBurstTime(double dTime);
	void cntSetFireSkillCondition(double dNumber);
	void cntSetBulletBurstTime(double dTime);

private:
	CBattle *m_pBossBattle;
	CBulletMgr *m_pBossBulletMgr;

	int m_nBossID;
	int nBuffRoad[10];

	int m_nAllPlayer;       // ȫ�������

	double m_dBossAck;		// boss�Ĺ�����
	int m_nBossStage;		// boss�Ľ׶�
	double m_dTotalDamage;	// boss�ܵ������˺�
	bool m_isInChange;		// �Ƿ��л�״̬
	bool m_isFire;			// �����ӵ�
	double m_dBossTotalTime;// ��ʱ��
	double m_dFireTime;		// ������ͨ�����ķ���ʱ��
	double m_dStageTime;    // �ֽ׶ε�״̬��ʱ��
	double m_dStageTiming;	// ״̬ʱ��
	int m_nCountBullet;		// ͳ���ӵ�
	double m_dInjuryRate;	// ������
	double m_dChangeTime;	// ����ʱ��
	double m_dNpcTime;		// �ٻ�NPCʱ��
	bool m_isNpcFlying;     // NPC�ڳ�
	double m_dNpcFlyTime;	// NPC����ʱ���¼
	int m_nCountNpc;        // ͳ��NPC��������
	double m_dFireInterval;	//��ͨ�ӵ�������
	bool m_isBossSkill;     // boss�Ƿ����ͷż���
	double m_dBossSkilling; // ����boss����ʱ��
	double m_dSkillBurstTime;	 // �����ͷŵ����ܲ����˺���ʱ��
	double m_dBossBulletSpeed;   // boss �ӵ��ٶ�
	double m_dFireSkillCondition;// ���ܷ�������
	double m_dDataBulletBurstTime;// ��ͨ�ӵ�,���𵽼����˺���ʱ��

	double m_dBossHp;
	double m_dDataOneAckConst;    //����
	double m_dDataOneAckBase;	  //����
	double m_dDataOneAckTime;	  //����
	double m_dDataOneAckMax;	  //����
	double m_dDataOneFireInterval;//�������
	double m_dDataOneFireTime;    //����ʱ��
	double m_dDataTwoAckConst;	  //����
	double m_dDataTwoAckBase;	  //����
	double m_dDataTwoAckTime;	  //����
	double m_dDataTwoAckMax;	  //����
	double m_dDataTwoFireInterval;//�������
	double m_dDataTwoFireTime;    //����ʱ��
	double m_dDataStageOneTime;   //״̬1��ʱ��
	double m_dDataStageTwoTime;	  // ״̬2��ʱ��
	double m_dDataChangeOneTime;  // ״̬1�ı任ʱ��
	double m_dDataChangeTwoTime;  // ״̬2�ı任ʱ��

	double m_dDataFireSkillCondition1; // �׶�1���似���������չ�������
	double m_dDataFireSkillCondition2; // �׶�2���似���������չ�������

	double m_dDataSkillBurstTime1;	// ����1�ͷŵ����ܲ����˺���ʱ��
	double m_dDataSkillBurstTime2;	// ����2�ͷŵ����ܲ����˺���ʱ��
	double m_dDataSkillBurstTime3;	// ����3�ͷŵ����ܲ����˺���ʱ��
	double m_dDataSkillDamageMultiple1; // ����1 ���˺�����
	double m_dDataSkillDamageMultiple2; // ����2 ���˺�����
	double m_dDataSkillDamageMultiple3; // ����3 ���˺�����
	double m_dDataSkillBuffTime1;   // ����1 ��buff����ʱ��
	double m_dDataSkillBuffTime2;   // ����2 ��buff����ʱ��


	double m_dDataCallNpcTime;   // �ٻ�NPC��ʱ�� (25��)
	double m_dDataNpcFireTime;   // NPC�ٻ������󵽿����ʱ��
	int m_nDataNpcBuff1_kind;    // buff1 ������
	double m_dDataNpcBuff1_value;// buff1 ��Ч��ֵ
	double m_dDataNpcBuff1_time; // buff1 ��ʱ��
	int m_nDataNpcBuff2_kind;    // buff2 ������
	double m_dDataNpcBuff2_value;// buff2 ��buffֵ
	double m_dDataNpcBuff2_time; // buff2 ��ʱ��
	int m_nDataNpcBuff3_kind;    // buff3 ������
	double m_dDataNpcBuff3_value;// buff3 ��buffֵ
	double m_dDataNpcBuff3_time; // buff3 ��ʱ��
	double m_dDataNpcDamageMultiple; // npc�˺�����

	double m_dDataBulletSpeed1;  // boss״̬1���ӵ��ٶ�   ��Ĭ��1000)
	double m_dDataBulletSpeed2;  // boss״̬2���ӵ��ٶ�

	vector<int> m_vecBossEvent;
	vector<CBullet*> m_vecBossBullet;

	double m_dDamageByBullet;
	double m_dDamageByFortSkill;
	double m_dDamageByNpc;
	double m_dDamageByProp;
	double m_dDamageByShipSkill;
	int m_nNpcType;
};

