#pragma once

using namespace std;

class CBattle;

class CShipSkill
{
public:
	CShipSkill(bool isEnemy, int shipSkillID, CBattle *pBattle);
	~CShipSkill();
	void update(double dt);
	void setSkillData(double buffValue, double buffTime, double fireTime);
	void shipSkillFire();
	double getTotalAck(int nSide);
	void startUpdate();
	
	void ship1_fireSkill();  // ��עһ��
	void ship2_fireSkill();  // �����䱸
	void ship3_fireSkill();  // ��չ��
	void ship4_fireSkill();  // Զ����־
	void ship5_fireSkill();  // ����һ��
	void ship6_fireSkill();  // ���ȷ籩
	void ship7_fireSkill();  // ����֮��
	void ship8_fireSkill();  // ��ʤ֮��
	void ship9_fireSkill();  // ս���Ʋ�
	void ship10_fireSkill(); // ��֮���

private:
	bool m_isEnemy;
	int m_nShipSkillID;
	CBattle *m_pShipSkillBattle;
	double m_dBuffValue;
	double m_dBuffTime;
	double m_dFireTime;
	double m_dTime;
	bool m_isUpdate;
};

