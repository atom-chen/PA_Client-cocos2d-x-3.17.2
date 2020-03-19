#include "stdafx.h"
#include "Buff.h"
#include "Battle.h"

CBuff::CBuff(bool isEnemy, int fort)
	: m_dTime(0.0)
	, m_nBuffID(0)
	, m_nBuffIndex(0)
{	
	m_isEnemy = isEnemy;
	m_dBuffValue = 0.0;
	m_nFortID = fort; 

}


CBuff::~CBuff()
{

}

bool CBuff::createBuff(int buffID, double buffValue, double buffTime)
{
	m_nBuffID = buffID;
	m_dTime = buffTime;
	m_dBuffValue = buffValue;

	CFort* pFort = nullptr;
	if (m_nFortID != 0)
	{
		if (m_isEnemy)
		{
			pFort = m_pBuffBattle->getEnemy()->getShip()->getFortMgr()->getFortByID(m_nFortID, m_isEnemy);
		}
		else
		{
			pFort = m_pBuffBattle->getPlayer()->getShip()->getFortMgr()->getFortByID(m_nFortID, m_isEnemy);
		}
		if (!pFort->isFortLive())
		{
			return false;
		}
	}

	if (buffID == Buff::FORT_ATK_ENHANCE)          // ��������
	{
		pFort->fortAckEnhanceState(buffValue);
	}
	else if (buffID == Buff::FORT_REPAIRING)       // ����ά��
	{
		if (pFort->isUnrepaireState())
		{
			return false;
		}
		pFort->fortRepairing();
	}
	else if (buffID == Buff::FORT_SHIELD)          // ����
	{
		if (pFort->isBreakArmorState())
		{
			return false;
		}
		pFort->fortShield(buffValue);
	}
	else if (buffID == Buff::FORT_PASSIVE_SKILL_STRONGER) // ����������ǿ
	{
		pFort->fortPassiveSkillStrongerState();
	}
	else if (buffID == Debuff::FORT_PARALYSIS)     // ̱��
	{
		pFort->fortParalysisState();
	}
	else if (buffID == Debuff::FORT_BURNING)       // ȼ��
	{
		pFort->fortBurningState();
	}
	else if (buffID == Debuff::FORT_ATK_DISTURB)    // ��������
	{
		pFort->fortAckDisturbState(buffValue);
	}
	else if (buffID == Debuff::FORT_REPAIR_DISTURB) // ά�޸��� ���޷���Ѫ��Ҳ�޷�ʹ�õ��߻�Ѫ��
	{
		pFort->fortUnrepaire();	
	}
	else if (buffID == Debuff::FORT_ENERGY_DISTURB) // �������� �����ܳ���(ʹ�ü��ܣ�ʹ�������ָ�����)��
	{
		pFort->fortUnEnergy();
	}
	else if (buffID == Debuff::FORT_BREAK_ARMOR)   //�Ƽ�״̬���뻤�ܵ���ʱ����ʧЧ��
	{
		pFort->fortBreakArmorState();
	}
	else if (buffID == Debuff::PLAYER_UNMISSILE)  //������
	{
		if (m_isEnemy)
		{
			m_pBuffBattle->getEnemy()->unmissileState();
		}
		else
		{
			m_pBuffBattle->getPlayer()->unmissileState();
		}
	}
	return true;
}

// ����buff����ʱ��
void CBuff::resetBuffTime(double time)
{
	m_dTime = time;
}

void CBuff::resetBuffValue(double effectValue, double time)
{
	m_dBuffValue = effectValue;
	m_dTime = time;

	CFort* pFort = nullptr;
	if (m_nFortID != 0)
	{
		if (m_isEnemy)
		{
			pFort = m_pBuffBattle->getEnemy()->getShip()->getFortMgr()->getFortByID(m_nFortID, m_isEnemy);
		}
		else
		{
			pFort = m_pBuffBattle->getPlayer()->getShip()->getFortMgr()->getFortByID(m_nFortID, m_isEnemy);
		}
		if (!pFort->isFortLive())
		{
			return;
		}
	}

	if (m_nBuffID == Buff::FORT_ATK_ENHANCE)          // ��������
	{
		pFort->fortAckEnhanceState(effectValue);
	}
	else if (m_nBuffID == Buff::FORT_REPAIRING)       // ����ά��
	{
		if (pFort->isUnrepaireState())
		{
			return;
		}
		pFort->fortRepairing();
	}
	else if (m_nBuffID == Buff::FORT_SHIELD)          // ����
	{
		if (pFort->isBreakArmorState())
		{
			return;
		}
		pFort->fortShield(effectValue);
	}
	else if (m_nBuffID == Buff::FORT_PASSIVE_SKILL_STRONGER) //������ǿ
	{
		pFort->fortPassiveSkillStrongerState();
	}
	else if (m_nBuffID == Debuff::FORT_PARALYSIS)     // ̱��
	{
		pFort->fortParalysisState();
	}
	else if (m_nBuffID == Debuff::FORT_BURNING)       // ȼ��
	{
		pFort->fortBurningState();
	}
	else if (m_nBuffID == Debuff::FORT_ATK_DISTURB)    // ��������
	{
		pFort->fortAckDisturbState(effectValue);
	}
	else if (m_nBuffID == Debuff::FORT_REPAIR_DISTURB) // ά�޸��� ���޷���Ѫ��Ҳ�޷�ʹ�õ��߻�Ѫ��
	{
		pFort->fortUnrepaire();
	}
	else if (m_nBuffID == Debuff::FORT_ENERGY_DISTURB) // �������� �����ܳ���(ʹ�ü��ܣ�ʹ�������ָ�����)��
	{
		pFort->fortUnEnergy();
	}
	else if (m_nBuffID == Debuff::FORT_BREAK_ARMOR)   // �Ƽ�
	{
		pFort->fortBreakArmorState();
	}
	else if (m_nBuffID == Debuff::PLAYER_UNMISSILE)
	{

	}
	resetBuffTime(time);
}

int CBuff::update(double dt)
{
	if ((m_dTime - dt < 0.00001) && (m_dTime - dt > -0.00001))
	{
		m_dTime = dt;
	}
	m_dTime -= dt;
	if (m_dTime <= 0)
	{
		return recoveryFortState();
	}
	return 0;
}

void CBuff::setBuffIndex(int buffIndex)
{
	m_nBuffIndex = buffIndex;
}

int CBuff::getBuffIndex()
{
	return m_nBuffIndex;
}

int CBuff::recoveryFortState()
{
	// �Ƴ�buff
	CFort* pFort = nullptr;
	CBuffMgr* pBuffMgr = nullptr;

	if (m_isEnemy)
	{
		pFort = m_pBuffBattle->getEnemy()->getShip()->getFortMgr()->getFortByID(m_nFortID, m_isEnemy);
		pBuffMgr = m_pBuffBattle->getEnemy()->getBuffMgr();
	}
	else
	{
		pFort = m_pBuffBattle->getPlayer()->getShip()->getFortMgr()->getFortByID(m_nFortID, m_isEnemy);
		pBuffMgr = m_pBuffBattle->getPlayer()->getBuffMgr();
	}
	if (m_nBuffID == Buff::FORT_ATK_ENHANCE)          // ��������
	{
		pFort->recoveryAckUp();
		return 1;
	}
	else if (m_nBuffID == Buff::FORT_REPAIRING)       // ����ά��
	{
		pFort->recoveryRepairing();
		return 1;
	}
	else if (m_nBuffID == Buff::FORT_SHIELD)          // ����
	{
		pFort->recoveryShield();
		return 1;
	}
	else if (m_nBuffID == Buff::FORT_PASSIVE_SKILL_STRONGER) // ������ǿ
	{
		pFort->recoveryFortPassiveSkillBuff();
		return 1;
	}
	else if (m_nBuffID == Debuff::FORT_PARALYSIS)     // ̱��
	{
		pFort->recoveryParalysis();
		return 1;
	}
	else if (m_nBuffID == Debuff::FORT_BURNING)       // ȼ��
	{
		pFort->recoveryBurning();
		return 1;
	}
	else if (m_nBuffID == Debuff::FORT_ATK_DISTURB)    // ��������
	{
		pFort->recoveryAckDown();
		return 1;
	}
	else if (m_nBuffID == Debuff::FORT_REPAIR_DISTURB)      // ά�޸���
	{
		pFort->recoveryUnrepaire();
		return 1;
	}
	else if (m_nBuffID == Debuff::FORT_ENERGY_DISTURB)     // �������� �����ܳ��ܣ�ʹ�ü��ܣ�ʹ�������ָ����ߣ�
	{
		pFort->recoveryUnEnergy();
		return 1;
	}
	else if (m_nBuffID == Debuff::FORT_BREAK_ARMOR)     // �Ƽ�
	{
		pFort->recoveryFortBreakArmorBuff();
		return 1;
	}
	else if (m_nBuffID == Debuff::PLAYER_UNMISSILE)   //������
	{
		if (m_isEnemy)
		{
			m_pBuffBattle->getEnemy()->recoveryUnmissile();
            return 1;
		}
		else
		{
			m_pBuffBattle->getPlayer()->recoveryUnmisslie();
            return 1;
		}
	}
	return 0;
	//pBuffMgr->deleteBuff(m_nBuffIndex);
}

int CBuff::getFortID()
{
	return m_nFortID;
}

int CBuff::getBuffID()
{
	return m_nBuffID;
}

void CBuff::setBuffBattle(CBattle * pBattle)
{
	m_pBuffBattle = pBattle;
}

void CBuff::addBuffTime(double dTime)
{
	m_dTime += dTime;
}

double CBuff::getBuffTime()
{
	return m_dTime;
}

double CBuff::getBuffValue()
{
	return m_dBuffValue;
}
