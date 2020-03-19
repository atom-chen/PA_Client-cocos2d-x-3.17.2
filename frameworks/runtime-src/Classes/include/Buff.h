#pragma once

class CBattle;

class CBuff
{
public:
	enum buffObject
	{
		SHIP_BUFF,
		FORT_BUFF
	};
	CBuff(bool isEnemy, int fort = 0);
	~CBuff();
	int update(double dt);
	bool createBuff(int buffID, double buffValue, double buffTime);

	void resetBuffTime(double dTime);
	void resetBuffValue(double effectValue, double dTime);
	void setBuffIndex(int buffIndex);
	int getBuffIndex();

	int recoveryFortState();

	int getFortID();
	int getBuffID();

	void setBuffBattle(CBattle *pBattle);

	void addBuffTime(double dTime);

	//  ����
	double getBuffTime();
	double getBuffValue();

private:
	bool m_isEnemy;

	double m_dTime;
	int m_nBuffID;
	int m_nFortID;
	int m_nBuffIndex;
	double m_dBuffValue;  //buff �����滻��ͬһʱ��ֻ�����һ����ֻ��buff��ʱ���ڱ䡣����ÿ��buff��ʱ�䣬Ч��ֵ����һ����

	CBattle *m_pBuffBattle;
};

