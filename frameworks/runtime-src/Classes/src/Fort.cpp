#include "stdafx.h"
#include "Fort.h"
#include "Battle.h"

#include <stdio.h>

CFort::CFort(bool isEnemy, int fortIndex, string wrongCodePath)
	: m_dHp(0)
	, m_dEnergy(0.0)
	, m_dInterval(0.0)
	, m_dUnInjuryRate(0.0)
	, m_dFortDamage(0.0)

	, m_dFireTime(0.0)
	, m_isFire(false)
	, m_isLive(true)
	
	, m_isFortParalysis(false)
	, m_isFortBurning(false)
	, m_isFortAckUp(false)
	, m_isFortAckDown(false)
	, m_isFortUnEnergy(false)
	, m_isFortUnrepaire(false)
	, m_isFortRepairing(false)
	, m_isFortShield(false)
	, m_isFortRelive(false)
	, m_isFortSkillFire(false)
	, m_isFortBreakArmor(false)
	, m_isFortPassiveSkillStronger(false)
	, m_isHavePassiveSkillStronger(false)

	, m_dBurningCountTime(0.0)
	, m_dRepairingCountTime(0.0)
	, m_dReliveCountDown(FORT_RELIVE_TIME)
	, m_dReliveHp(0.0)
	, m_dAckDownValue(0.0)
	, m_dAckUpValue(0.0)

	, m_dAddPassiveEnergyTime(0.0)
	, m_dMomentAddHp(0.0)
	, m_dSkillAddHp(0.0)
	, m_dPropAddHp(0.0)
	, m_dContinueAddHp(0.0)    // ���m��Ѫ           ��
	, m_dSelfAddEnergy(0.0)    // ������ӵ�����     ��
	, m_dEnergyAddEnergy(0.0)  // �����w��ӵ������w ��
	, m_dPropAddEnergy(0.0)    // �����������       ��
	, m_dAttackAddEnergy(0.0)  // ������ӵ�����     ��
	, m_dBeDamageAddEnergy(0.0)// ������ӵ�����     ��
	, m_dBulletDamage(0.0)     // �ӵ��˺�
	, m_dPropBulletDamage(0.0) // �����ڵ��˺�
	, m_dBuffBurnDamage(0.0)   // ȼ��buff�˺�
	, m_dNPC_Damage(0.0)       // NPC�˺�
	, m_dShipSkillDamage(0.0)  // ս�������˺�
	, m_dShipSkillAddHp(0.0)   // ս�����ܼ�Ѫ
	, m_dShipSkillAddEnergy(0.0)// ս�����ܼ�����
	//, m_dSecondCountForRelive(0.1)// ����ʱ��һ�뷢һ��
{
	m_isEnemy = isEnemy;
	m_nFortIndex = fortIndex;

	m_nFortID = 0;
	m_nFortBulletID = 0;
	m_nFortType = 0;
	m_nFortLevel = 0;
	m_dFortStarDomainCoe = 0.0;
	m_dFortQualityCoe = 0.0;
	m_dFortAckGrowCoe = 0.0;
	m_dFortHpGrowCoe = 0.0;
	m_dFortSpeedCoe = 0.0;
	m_dFortEnergyCoe = 0.0;

	m_dInitAck = 0;
	m_dInitHp = 0;
	m_dInitEnergy = 100;
	m_dInitDefense = 0;
	m_dInitUnInjuryRate = 0.0;
	m_dInitDamage = 0.0;
	m_isAddPassiveSkill = false;

	m_dSkillDamage = 0.0;
	m_dSkillTime = 0;

	m_strWrongCodePath = wrongCodePath;
	m_isHaveSuitBuff = false;
	m_dSuitBuffValue = 0.0;
	//openFile.open(wrongCodePath, ios::binary);     //"data/libcode.json"
}

CFort::~CFort()
{
	if (m_pFortSkill)
	{
		delete(m_pFortSkill);
		m_pFortSkill = nullptr;
	}
	//openFile.close();
}

void CFort::update(double dt)
{
//	m_vecFortEvent.clear();    // ÿ֡ ����¼�����
	m_isFire = false;
	if (m_isLive)
	{
		if (!m_isFortSkillFire && !m_isFortParalysis)
		{
			m_dFireTime += dt;
			if (m_dFireTime >= m_dInterval)
			{
				//fire
				m_isFire = true;
				m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_FIRE);

				if (m_isEnemy)
				{
					m_pFortBattle->getEnemy()->createBullet(this);
				}
				else
				{
					m_pFortBattle->getPlayer()->createBullet(this);
				}

				if (m_dFireTime - m_dInterval <= 0.00001 && m_dFireTime - m_dInterval >= -0.00001)
				{
					m_dFireTime = m_dInterval;
				}
				m_dFireTime -= m_dInterval;
				//if (m_dFireTime <= 0.000001 && m_dFireTime >= -0.000001)
				//{
				//	m_dFireTime = 0;
				//}
			}
		}
		if (m_isFortSkillFire)
		{
			if ((m_dSkillTime - dt < 0.00001) && (m_dSkillTime - dt > -0.00001))
			{
				m_dSkillTime = dt;
			}
			m_dSkillTime -= dt;
			if (m_dSkillTime <= 0)
			{
				fortSkillFireEnd();
			}
		}

		if (m_isFortBurning)    // ��̨ȼ�� 
		{
			m_dBurningCountTime += dt;
			if (m_dBurningCountTime >= 0.5)
			{
				percentDamage(0.01);
				if (m_dBurningCountTime - 0.5 <= 0.00001 && m_dBurningCountTime - 0.5 >= -0.00001)
				{
					m_dBurningCountTime = 0.5;
				}
				m_dBurningCountTime -= 0.5;
			}
		}

		if (m_isFortRepairing)  //��̨�޸���Ѫ
		{
			m_dRepairingCountTime += dt;
			if (m_isFortUnrepaire)
			{
				recoveryRepairing();
				if (m_isEnemy)
				{
					m_pFortBattle->getEnemy()->getBuffMgr()->deleteBuffByFortID(m_nFortID, Buff::FORT_REPAIRING);
				}
				else
				{
					m_pFortBattle->getPlayer()->getBuffMgr()->deleteBuffByFortID(m_nFortID, Buff::FORT_REPAIRING);
				}
			}
			else if (m_dRepairingCountTime >= 0.5)
			{
				addHp(m_dInitHp * 0.01);
				if (m_dRepairingCountTime - 0.5 <= 0.00001 && m_dRepairingCountTime - 0.5 >= -0.00001)
				{
					m_dRepairingCountTime = 0.5;
				}
				m_dRepairingCountTime -= 0.5;
			}
		}

		if (m_nFortType == FortType::ATTACK_TYPE)
		{
			if (m_isAddPassiveSkill == false)
			{
				if (m_dHp / m_dInitHp < 0.5)
				{
					if (m_isFortPassiveSkillStronger)
					{
						m_dFortDamage = m_dFortDamage + m_dInitDamage * 0.30;
						m_isHavePassiveSkillStronger = true;
					}
					else
					{
						m_dFortDamage = m_dFortDamage + m_dInitDamage * 0.15;
					}
					m_isAddPassiveSkill = true;
				}
			}
			else
			{
				if (m_dHp / m_dInitHp >= 0.5)
				{
					if (m_isFortPassiveSkillStronger)
					{
						if (m_isHavePassiveSkillStronger)
						{
							m_dFortDamage = m_dFortDamage - m_dInitDamage * 0.30;
							m_isHavePassiveSkillStronger = false;
						}
						else
						{
							m_dFortDamage -= m_dInitDamage * 0.15;
						}
					}
					else
					{
						m_dFortDamage = m_dFortDamage - m_dInitDamage * 0.15;
					}
					m_isAddPassiveSkill = false;
				}
				else
				{
					if (m_isFortPassiveSkillStronger)
					{
						if (!m_isHavePassiveSkillStronger)
						{
							m_dFortDamage = m_dFortDamage + m_dInitDamage * 0.15;
							m_isHavePassiveSkillStronger = true;
						}
					}
				}
			}
		}
		else if (m_nFortType == FortType::SKILL_TYPE)
		{
			m_dAddPassiveEnergyTime += dt;
			if (m_dAddPassiveEnergyTime >= 1)
			{
				addEnergySelf();
				if (m_dAddPassiveEnergyTime - 1 <= 0.000001 && m_dAddPassiveEnergyTime - 1 >= -0.000001)
				{
					m_dAddPassiveEnergyTime = 1;
				}
				m_dAddPassiveEnergyTime -= 1.0;
			}
		}
	}
	else
	{
		if (m_isFortRelive)    // ��̨�����10��
		{
			if ((m_dReliveCountDown - dt < 0.00001) && (m_dReliveCountDown - dt > -0.00001))
			{
				m_dReliveCountDown = dt;
			}
			m_dReliveCountDown -= dt;
			// for fort relive send message per second
			//m_dSecondCountForRelive += dt;
			//if (m_dSecondCountForRelive >= 1)
			//{
				//m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_RELIVE_COOLDOWN);
				//m_dSecondCountForRelive -= 1;
			//}
			if (m_dReliveCountDown <= 0)
			{
				m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_RELIVE);
				m_isFortRelive = false;
				m_isLive = true;
				m_dHp = m_dReliveHp;
				m_dReliveHp = 0.0;
				//m_dSecondCountForRelive = 0.1;
				m_dReliveCountDown = FORT_RELIVE_TIME;
			}
		}
	}
}

CFortSkill * CFort::getFortSkill()
{
	return m_pFortSkill;
}

double CFort::damageFort(double damage)
{
	double dDamage = damage;
	//if (m_dHp < damage)
	//{
	//	dDamage = m_dHp;
	//}
	m_dHp -= dDamage;
	addEnergyByDamage(dDamage, 2);
	if (m_dHp <= 0)
	{
		m_dHp = 0.0;
		fortDie();
	}
	return dDamage;
}

// ������̨�ӵ�����ʱ, 
void CFort::damageFortByBullet(double damage)
{
	//double resultDamage = damage * (1 - m_dUnInjuryRate);
	if (m_dBulletDamage == 0)
	{
		m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_BULLET_DAMAGE);
		m_dBulletDamage = damageFort(damage);
	}
	else
	{
		m_dBulletDamage += damageFort(damage);
	}

}

// ���ܹ����˺�
void CFort::damageFortBySkillBurst(double damage)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SKILL_DAMAGE);
	m_dSkillDamage = damageFort(damage);
}
// ���أ�����ٷ�50�˺�
void CFort::damageFortBySkillAddDamage(double damage)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_BE_DEEP_DAMAGE);
	m_dSkillDamage = damageFort(damage);
}

// NPC ����
void CFort::damageFortByNPC(double damage)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_NPC_DAMAGE);
	m_dNPC_Damage = damageFort(damage);
}

// ȼ��buff�˺�
void CFort::percentDamage(double percent)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_BUFF_BURN_DAMAGE);
	double dDamage = m_dInitHp * percent;
	if (dDamage > 2000)
	{
		dDamage = 2000;
	}
	m_dBuffBurnDamage = damageFort(dDamage);
}

// ���ߵ����ڵ�����
void CFort::damageFortByPropBullet(double dDamage)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_PROP_BULLET_DAMAGE);
	//double damage = m_dInitHp * percent;
	m_dPropBulletDamage = damageFort(dDamage);
}

void CFort::trueDamageFort(double damage)
{
	m_dHp -= damage;
	if (m_dHp <= 0)
	{
		m_dHp = 0.0;
		fortDie();
	}
}

// ս�����ܹ���
void CFort::damageFortByShipSkill(double dDamage)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SHIP_SKILL_DAMAGE);
	if (dDamage > m_dHp)
	{
		m_dHp = 0;
		fortDie();
	}
	else
	{
		m_dHp -= dDamage;
	}
	m_dShipSkillDamage = dDamage;
}

void CFort::fortDie()
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_DIE);

	m_dEnergy = 0;
	m_isLive = false;
	m_dUnInjuryRate = m_dInitUnInjuryRate;
	m_dFortDamage = m_dInitDamage;
	m_dFireTime = 0;
	m_isAddPassiveSkill = false;
	m_isFortParalysis = false; 
	m_isFortBurning = false;   
	m_isFortAckUp = false;
	m_isFortAckDown = false;   
	m_isFortRepairing = false;
	m_isFortUnrepaire = false;
	m_isFortUnEnergy = false;
	m_isFortShield = false;
	m_isFortRelive = false;
	m_isFortSkillFire = false;
	m_dBurningCountTime = 0.0;
	m_dRepairingCountTime = 0.0;
	//m_dReliveCountDown = 0.0;
	m_dReliveHp = 0.0;
	m_dAddPassiveEnergyTime = 0.0;
	if (m_isEnemy)
	{
		m_pFortBattle->getEnemy()->getBuffMgr()->deleteAllBuffByFortID(m_nFortID);
		m_pFortBattle->getEnemy()->getShip()->getFortMgr()->setEnemyDieFortID(m_nFortID);
	}
	else
	{
		m_pFortBattle->getPlayer()->getBuffMgr()->deleteAllBuffByFortID(m_nFortID);
		m_pFortBattle->getPlayer()->getShip()->getFortMgr()->setPlayerDieFortID(m_nFortID);
	}
	
}

// for repairing
void CFort::addHp(double dHp)
{
	if (!m_isLive ) 
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_CONTINUE_ADD_HP);
	m_dHp += dHp;
	if (m_dHp > m_dInitHp)
	{
		m_dHp = m_dInitHp;
	}
	m_dContinueAddHp = dHp;
}

void CFort::addHpBySkill(double percent)
{
	if (!m_isLive || m_isFortUnrepaire)
	{
		return;
	}
	double spareHp = m_dInitHp - m_dHp;
	double addSkillHp = m_dInitHp * percent;
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SKILL_ADD_HP);
	if (spareHp < addSkillHp)
	{
		m_dHp = m_dInitHp;
	}
	else
	{
		m_dHp += addSkillHp;
	}
	m_dSkillAddHp = addSkillHp;
}

void CFort::addHpByShipSkill(double percent)
{
	if (!m_isLive || m_isFortUnrepaire)
	{
		return;
	}
	double addHp = m_dInitHp * percent;
	double spaceHp = m_dInitHp - m_dHp;  
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SHIP_SKILL_ADD_HP);
	if (addHp > spaceHp)
	{
		m_dHp = m_dInitHp;
	}
	else
	{
		m_dHp += addHp;
	}
	m_dShipSkillAddHp = addHp;
}
// ��ʱû��
void CFort::addEnergy(double value)
{
	if (!m_isLive) // �������
	{
		return;
	}
	if (m_isFortUnEnergy || m_dEnergy >= 100)
	{
		return;
	}
	m_dEnergy += value;
	if (m_dEnergy > 100)
	{
		m_dEnergy = 100.0;
	}
}

void CFort::addEnergySelf()
{
	if (!m_isLive)
	{
		return;
	}
	if (m_isFortUnEnergy)
	{
		return;
	}
	if (m_dEnergy >= 100)
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SELF_ADD_ENERGY);
	double dEnergy = m_dInitEnergy - m_dEnergy;
	if (m_isFortPassiveSkillStronger)
	{
		m_dEnergy += 2.0;
		m_dSelfAddEnergy = 2.0;
	}
	else
	{
		m_dEnergy += 1.0;
		m_dSelfAddEnergy = 1.0;
	}
	if (m_dEnergy >= 100)
	{
		m_dEnergy = 100;
		m_dSelfAddEnergy = dEnergy;
	}
}

void CFort::addEnergyByEnergy(double value)
{
	if (!m_isLive)
	{
		return;
	}
	if (m_isFortUnEnergy)
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_ENERGY_ADD_ENERGY);
	double dEnergy = m_dInitEnergy - m_dEnergy;
	m_dEnergy += value;
	if (m_dEnergy > 100)
	{
		m_dEnergy = 100;
	}
	m_dEnergyAddEnergy = value;
}

void CFort::addEnergyByDamage(double dDamage, int nType)
{
	if (m_isFortUnEnergy)
	{
		return;
	}
	if (m_dEnergy >= 100)
	{
		return;
	}
	if (nType == 1)     // ������̨�������
	{
		m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_ATTACK_ADD_ENERGY);
	}
	else if (nType == 2)   // �ܻ��������
	{
		m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_BE_DAMAGE_ADD_ENERGY);
	}
	double dEnergy = m_dInitEnergy - m_dEnergy;
	// �ܵ��˺� * 0.005% + ����ϵ�� + Ʒ��ϵ��
	double dAttackEnergy = dDamage * 0.00005 + m_dFortEnergyCoe + m_dFortQualityCoe;
	m_dEnergy += dAttackEnergy;
	if (m_dEnergy > 100)
	{
		m_dEnergy = 100.0;
		dAttackEnergy = dEnergy;
	}
	if (nType == 1)
	{
		m_dAttackAddEnergy = dAttackEnergy;
	}
	else if (nType == 2)
	{
		m_dBeDamageAddEnergy = dAttackEnergy;
	}
}
// ��ʱû��
void CFort::addEnergyByProp(double value)
{
	if (!m_isLive || m_isFortUnEnergy)
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_PROP_ADD_ENERGY);
	double dEnergy = m_dInitEnergy - m_dEnergy;
	m_dEnergy += value;
	if (m_dEnergy > 100)
	{
		m_dEnergy = 100;
	}
	m_dPropAddEnergy = value;
}

void CFort::addEnergyByShipSkill(double percent)
{
	if (!m_isLive || m_isFortUnEnergy)
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SHIP_SKILL_ADD_ENERGY);
	double addEnergy = m_dInitEnergy * percent;
	double spaceEnergy = m_dInitEnergy - m_dEnergy;
	if (addEnergy > spaceEnergy)
	{
		m_dEnergy = m_dInitEnergy;
	}
	else
	{
		m_dEnergy += addEnergy;
	}
	m_dShipSkillAddEnergy = addEnergy;
}



void CFort::setFortID(int ID)
{
	m_nFortID = ID;
}



int CFort::getFortID()
{
	return m_nFortID;
}

double CFort::getFortHp()
{
	return m_dHp;
}

double CFort::getFortMaxHp()
{
	return m_dInitHp;
}

double CFort::getFortEnergy()
{
	return m_dEnergy;
}

double CFort::getFortMaxEnergy()
{
	return m_dInitEnergy;
}


/*
void CFort::setFortInterval(double interval)
{
	m_dInitInterval = interval;
	m_dInterval = m_dInitInterval;
}
*/

void CFort::fortNormalState()
{
	// ��ʼ���ݣ��˺��� �����ٶȣ� ������ ��ֵ��
	m_dFortDamage = m_dInitDamage;
	m_dInterval = m_dFortSpeedCoe;
}

void CFort::fortParalysisState()
{
	// ̱�����޷����&ʹ�ü��ܣ��������Ի��ܣ�
	m_isFortParalysis = true;
	m_dFireTime = 0; 
}

void CFort::fortBurningState()
{
	// ȼ���˺�
	m_isFortBurning = true;
	m_dBurningCountTime = 0.0;
}

void CFort::fortAckEnhanceState(double buffValue)
{
	// �˺�����
	m_dFortDamage += m_dInitDamage * (buffValue - m_dAckUpValue);
	m_dAckUpValue = buffValue;
	m_isFortAckUp = true;
}

void CFort::fortAckDisturbState(double buffValue)
{
	// �˺�����
	m_dFortDamage -= m_dInitDamage * (buffValue - m_dAckDownValue);
	m_dAckDownValue = buffValue;
	m_isFortAckDown = true;
}

// ���߻�Ѫ
void CFort::fortRepaire(double percent)
{
	if (m_isFortUnrepaire)
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_PROP_ADD_HP);
	m_dHp += m_dInitHp * percent;
	if (m_dHp > m_dInitHp)
	{
		m_dHp = m_dInitHp;
	}
	m_dPropAddHp = m_dInitHp * percent;
}

// ˲���Ѫ
void CFort::fortRepaireByEnergy(double percent)
{
	if (!m_isLive) // �������
	{
		return;
	}
	if (m_isFortUnrepaire )//|| m_dHp >= m_dInitHp
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_ENERGY_ADD_HP);
	m_dHp += m_dInitHp * percent;
	if (m_dHp > m_dInitHp)
	{
		m_dHp = m_dInitHp;
	}

	m_dMomentAddHp = m_dInitHp * percent;
}

// ����ά�ޣ���Ѫ��
void CFort::fortRepairing()
{
	if (m_isFortUnrepaire)
	{
		m_isFortRepairing = false;
		return;
	}
	m_isFortRepairing = true;
}

// ��Ѫ����
void CFort::fortUnrepaire()
{
	m_isFortUnrepaire = true;
}

// �����ָ�
void CFort::fortSupplyEnergy(double value)
{
	if (m_isFortUnEnergy)
	{
		return;
	}
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_PROP_ADD_ENERGY);
	double dEnergy = m_dInitEnergy - m_dEnergy;
	m_dEnergy += value;
	if (m_dEnergy > 100)
	{
		m_dEnergy = 100;
	}
	m_dPropAddEnergy = value;
}

// �����ָ�����
void CFort::fortUnEnergy()
{
	m_isFortUnEnergy = true;
}

// ����
void CFort::fortShield(double percent)
{
	m_dUnInjuryRate = m_dInitUnInjuryRate + percent;
	if (m_dUnInjuryRate > 1)
	{
		m_dUnInjuryRate = 1;
	}
	m_isFortShield = true;
}

// ������̨
void CFort::fortRelive(double dPercent)
{
	if (m_isLive)
	{
		return;
	}
	m_isFortRelive = true;
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_RELIVE_COOLDOWN);
	m_dReliveHp = m_dInitHp * dPercent;
}

void CFort::fortBreakArmorState()
{
	if (m_isFortShield)
	{
		recoveryShield();
		if (m_isEnemy)
		{
			m_pFortBattle->getEnemy()->getBuffMgr()->deleteBuffByFortID(m_nFortID, Buff::FORT_SHIELD);
		}
		else
		{
			m_pFortBattle->getPlayer()->getBuffMgr()->deleteBuffByFortID(m_nFortID, Buff::FORT_SHIELD);
		}
	}
	m_dUnInjuryRate = 0;
	m_isFortBreakArmor = true;
}

void CFort::fortPassiveSkillStrongerState()
{
	m_isFortPassiveSkillStronger = true;
	if (m_nFortType == FortType::DEFENSE_TYPE)
	{
		m_dUnInjuryRate += 0.05;
	}
}

int CFort::fortSkillFireBegin(string strBuffPer)
{
	//vector<wrongCodeData> sWrongCodeData = m_pFortBattle->getWrongCodeData();
	//if (!m_isLive)// || m_dEnergy != 100|| m_isFortParalysis || m_isFortUnEnergy
	//{
	//	cout << "fort is die��������." << endl;
	//	return sWrongCodeData[0].nFortDie_skill;
	//}
	//if (m_isFortParalysis)
	//{
	//	cout << "fort is in paralysis��̱����" << endl;
	//	return sWrongCodeData[0].nFortParalysis_skill;
	//}
	//if (m_isFortUnEnergy)
	//{
	//	cout << "fort is in unenergy���������ţ�" << endl;
	//	return sWrongCodeData[0].nFortUnenergy;
	//}
	//if (m_dEnergy != 100)
	//{
	//	cout << "fort's energy no enough���������㣩" << endl;
	//	return sWrongCodeData[0].nFortEnergyNotEnough;
	//}
	//if (m_isFortSkillFire)
	//{
	//	cout << "fort is skilling now���ͷ������У�" << endl;
	//	return sWrongCodeData[0].nFortSkilling;
	//}
	//int success = sWrongCodeData[0].nSuccess;
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SKILL);
	m_isFortSkillFire = true;
	if (m_pFortBattle->getBattleType() == BattleType::BATTLE_NORMAL)
	{
		m_pFortSkill->lockTargetFort();
		m_pFortSkill->setAddBuff(strBuffPer);
	}
	else if (m_pFortBattle->getBattleType() == BattleType::BATTLE_BOSS)
	{
		// bossս����������̨
	}
	m_dSkillTime = m_pFortSkill->getSkillTime();
	m_dEnergy = 0;
	m_dFireTime = 0;
	return 1;
}

void CFort::fortSkillFireEnd()
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_SKILL_END);
	m_pFortSkill->fireSkill();
	m_dSkillTime = 0;
	m_isFortSkillFire = false;
}

const char * CFort::getIsAddBuff()
{
	return m_pFortSkill->isAddBuff();
}


void CFort::recoveryParalysis()
{
	m_isFortParalysis = false;
	m_dInterval = m_dFortSpeedCoe;
}

void CFort::recoveryBurning()
{
	m_isFortBurning = false;
	
}

void CFort::recoveryAckUp()
{
	m_dFortDamage -= m_dInitDamage * m_dAckUpValue;
	m_dAckUpValue = 0.0;
	m_isFortAckUp = false;
}

void CFort::recoveryAckDown()
{
	m_dFortDamage += m_dInitDamage * m_dAckDownValue;
	m_dAckDownValue = 0;
	m_isFortAckDown = false;
}

void CFort::recoveryEnergy()
{
}

void CFort::recoveryRepairing()
{
	m_dRepairingCountTime = 0;
	m_isFortRepairing = false;
}

void CFort::recoveryUnrepaire()
{
	m_isFortUnrepaire = false;
}

void CFort::recoveryUnEnergy()
{
	m_isFortUnEnergy = false;
}

void CFort::recoveryShield()
{
	m_dUnInjuryRate = m_dInitUnInjuryRate;
	m_isFortShield = false;
}

void CFort::recoveryFortBadBuff()
{
	if (m_isFortParalysis)
	{
		recoveryParalysis();
	}
	if (m_isFortBurning)
	{
		recoveryBurning();
	}
	if (m_isFortAckDown)
	{
		recoveryAckDown();
	}
	if (m_isFortUnrepaire)
	{
		recoveryUnrepaire();
	}
	if (m_isFortUnEnergy)
	{
		recoveryUnEnergy();
	}
	if (m_isFortBreakArmor)
	{
		recoveryFortBreakArmorBuff();
	}
}


void CFort::recoveryFortGoodBuff()
{
	if (m_isFortAckUp)
	{
		recoveryAckUp();
	}
	if (m_isFortRepairing)
	{
		recoveryRepairing();
	}
	if (m_isFortShield)
	{
		recoveryShield();
	}
	if (m_isFortPassiveSkillStronger)
	{
		recoveryFortPassiveSkillBuff();
	}
}

void CFort::recoveryFortBreakArmorBuff()
{
	m_dUnInjuryRate = m_dInitUnInjuryRate;
	m_isFortBreakArmor = false;
}

void CFort::recoveryFortPassiveSkillBuff()
{
	m_isFortPassiveSkillStronger = false;
	if (m_nFortType == FortType::DEFENSE_TYPE)
	{
		m_dUnInjuryRate -= 0.05;
	}
	else if (m_nFortType == FortType::ATTACK_TYPE)
	{
		if (m_isHavePassiveSkillStronger)
		{
			m_dFortDamage -= m_dInitDamage * 0.15;
		}
		m_isHavePassiveSkillStronger = false;
	}
}

bool CFort::isParalysisState()
{
	return m_isFortParalysis;
}

bool CFort::isBurningState()
{
	return m_isFortBurning;
}

bool CFort::isAckUpState()
{
	return m_isFortAckUp;
}

bool CFort::isAckDownState()
{
	return m_isFortAckDown;
}

bool CFort::isRepairingState()
{
	return m_isFortRepairing;
}

bool CFort::isUnrepaireState()
{
	return m_isFortUnrepaire;
}

bool CFort::isUnEnergyState()
{
	return m_isFortUnEnergy;
}

bool CFort::isShieldState()
{
	return m_isFortShield;
}

bool CFort::isReliveState()
{
	return m_isFortRelive;
}

bool CFort::isSkillingState()
{
	return m_isFortSkillFire;
}

bool CFort::isBreakArmorState()
{
	return m_isFortBreakArmor;
}

bool CFort::isPassiveSkillStrongerState()
{
	return m_isFortPassiveSkillStronger;
}

void CFort::setFortBulletID(int fortID)
{
	m_nFortBulletID = fortID;
}

int CFort::getFortBulletID()
{
	return m_nFortBulletID;
}

void CFort::setFortData(int nFortID, int nBulletID, int nFortType, int nLevel, int nFortStarDomainCoe, int nSkillLevel, string strPathJson)
{
	setFortID(nFortID);
	setFortBulletID(nBulletID);
	m_nFortType = nFortType;
	m_nFortLevel = nLevel;
	m_dFortStarDomainCoe = nFortStarDomainCoe * 0.01;

	// Ʒ��ϵ��
	m_dFortQualityCoe = getQualityCoeByLevel(nLevel);

	if (m_nFortType == FortType::ATTACK_TYPE)
	{
		m_dFortAckGrowCoe = AckFORT_AckCOE;
		m_dFortHpGrowCoe = AckFORT_HpCOE;
		m_dFortSpeedCoe = AckFORT_SpeCOE;
		m_dFortEnergyCoe = AckFORT_EneCOE;
	}
	else if (m_nFortType == FortType::DEFENSE_TYPE)
	{
		m_dFortAckGrowCoe = DefFORT_AckCOE;
		m_dFortHpGrowCoe = DefFORT_HpCOE;
		m_dFortSpeedCoe = DefFORT_SpeCOE;
		m_dFortEnergyCoe = DefFORT_EneCOE;
	}
	else if (m_nFortType == FortType::SKILL_TYPE)
	{
		m_dFortAckGrowCoe = SkiFORT_AckCOE;
		m_dFortHpGrowCoe = SkiFORT_HpCOE;
		m_dFortSpeedCoe = SkiFORT_SpeCOE;
		m_dFortEnergyCoe = SkiFORT_EneCOE;
	}
	// ����  ������
	double nOneLevelAck = 100.0 * 1 * m_dFortAckGrowCoe * m_dFortStarDomainCoe * m_dFortQualityCoe;
	if (m_nFortLevel == 1)
	{
		m_dInitAck = nOneLevelAck;
	}
	else
	{
		m_dInitAck = nOneLevelAck + 10.0 * m_nFortLevel * m_dFortAckGrowCoe * m_dFortStarDomainCoe * m_dFortQualityCoe;
	}

	// ��װ��ǿ��Ч����
	if (m_isHaveSuitBuff)
	{
		m_dInitAck *= (1 + m_dSuitBuffValue);
	}

	// ����  Ѫ��
	m_dInitHp = m_dInitAck * (120.0 - m_nFortLevel * 0.1) * m_dFortHpGrowCoe * m_dFortStarDomainCoe * m_dFortQualityCoe;
	m_dHp = m_dInitHp;

	// ����  ����ֵ
	m_dInitDefense = m_dInitHp * 0.05;
	// ��ֵ  �������
	m_dInterval = m_dFortSpeedCoe;
	// ����  �˺�
	m_dInitDamage = m_dInitAck * (2 - 100.0 / (m_nFortLevel * 10 + 100.0));
	m_dFortDamage = m_dInitDamage;
	// ������
	m_dInitUnInjuryRate = (m_dInitDefense / 500 + 1) * 0.01;
	if (m_nFortType == FortType::DEFENSE_TYPE)	// ��������̨���Ӱٷ�5
	{
		m_dInitUnInjuryRate += 0.05;
	}
	m_dUnInjuryRate = m_dInitUnInjuryRate;
	if (m_isEnemy)
	{
		m_pFortBattle->getEnemy()->countEnemyMaxHp(m_dInitHp);
	}
	else
	{
		m_pFortBattle->getPlayer()->countPlayerMaxHp(m_dInitHp);
	}

	initFortSkill(nSkillLevel, strPathJson, m_dFortStarDomainCoe);
}

// ����Ʒ��ϵ��
double CFort::getQualityCoeByLevel(int nLevel)
{
	if (m_nFortLevel <= 20)
	{
		return FORT_QUALITY_D;
	}
	else if (m_nFortLevel > 20 && m_nFortLevel <= 40)
	{
		return FORT_QUALITY_C;
	}
	else if (m_nFortLevel > 40 && m_nFortLevel <= 60)
	{
		return FORT_QUALITY_B;
	}
	else if (m_nFortLevel > 60 && m_nFortLevel <= 80)
	{
		return FORT_QUALITY_A;
	}
	else if (m_nFortLevel > 80 && m_nFortLevel < 100)
	{
		return FORT_QUALITY_S;
	}
	return 0;
}


void CFort::setFortPos(int posX, int posY)
{
	m_nPosX = posX; 
	m_nPosY = posY;
}


int CFort::getFortPosX()
{
	return m_nPosX;
}

int CFort::getFortPosY()
{
	return m_nPosY;
}

int CFort::getFortIndex()
{
	return m_nFortIndex;
}

double CFort::getFortAck()
{
	return m_dFortDamage;
}

void CFort::fortSizeByID(int fortID)
{
	int fortWidth = 0;
	int fortHeight = 0;

}


bool CFort::isFortLive()
{
	if (m_dHp <= 0)
	{
		m_isLive = false;
	}
	return m_isLive;
}

bool CFort::isFire()
{
	return m_isFire;
}

void CFort::fortBeLiveByShipSkill(double dPercent)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), FortEvent::FORT_RELIVE);
	m_isLive = true;
	m_dHp = m_dInitHp * dPercent;
	m_dEnergy = 100;
}

double CFort::getUnInjuryCoe()
{
	return m_dUnInjuryRate;
}

void CFort::cleanFortEventVec()
{
	m_vecFortEvent.clear();
}

vector<int> CFort::getFortEventVec()
{
	return m_vecFortEvent;
}

double CFort::getMomentAddHp() 
{
	return m_dMomentAddHp;
}

void CFort::recoverAddHp(double dHp)
{
	m_dMomentAddHp = dHp;
}

double CFort::getSkillAddHp()
{
	return m_dSkillAddHp;
}

void CFort::recoverSkillAddHp(double dHp)
{
	m_dSkillAddHp = dHp;
}

double CFort::getPropAddHp()
{
	return m_dPropAddHp;
}

void CFort::recoverPropAddHp(double dHp)
{
	m_dPropAddHp = dHp;
}

double CFort::getContinueAddHp()
{
	return m_dContinueAddHp;
}

void CFort::recoverContinueAddHp(double dHp)
{
	m_dContinueAddHp = dHp;
}

double CFort::getSelfAddEnergy()
{
	return m_dSelfAddEnergy;
}

void CFort::recoverSelfAddEnergy(double dEnergy)
{
	m_dSelfAddEnergy = dEnergy;
}

double CFort::getEnergyAddEnergy()
{
	return m_dEnergyAddEnergy;
}

void CFort::recoverEnergyAddEnergy(double dEnergy)
{
	m_dEnergyAddEnergy = dEnergy;
}

double CFort::getPropAddEnergy()
{
	return m_dPropAddEnergy;
}

void CFort::recoverPropAddEnergy(double dEnergy)
{
	m_dPropAddEnergy = dEnergy;
}

double CFort::getAttackAddEnergy()
{
	return m_dAttackAddEnergy;
}

void CFort::recoverAttackAddEnergy(double dEnergy)
{
	m_dAttackAddEnergy = dEnergy;
}

double CFort::getBeDamageAddEnergy()
{
	return m_dBeDamageAddEnergy;
}

void CFort::recoverBeDamageAddEnergy(double dEnergy)
{
	m_dBeDamageAddEnergy = dEnergy;
}

double CFort::getBulletDamage()
{
	return m_dBulletDamage;
}

void CFort::recoverBulletDamage(double dDamage)
{
	m_dBulletDamage = dDamage;
}

double CFort::getPropBulletDamage()
{
	return m_dPropBulletDamage;
}

void CFort::recoverPropBuleltDamage(double dDamage)
{
	m_dPropBulletDamage = dDamage;
}

double CFort::getBuffBurnDamage()
{
	return m_dBuffBurnDamage;
}

void CFort::recoverBuffBurnDamage(double dDamage)
{
	m_dBuffBurnDamage = dDamage;
}

double CFort::getNPCDamage()
{
	return m_dNPC_Damage;
}

void CFort::recoverNPCDamage(double dDamage)
{
	m_dNPC_Damage = dDamage;
}

double CFort::getSkillDamage()
{
	return m_dSkillDamage;
}

void CFort::recoverSkillDamage(double dDamage)
{
	m_dSkillDamage = dDamage;
}

double CFort::getReliveCountDown()
{
	return m_dReliveCountDown;
}

double CFort::getShipSkillDamage()
{
	return m_dShipSkillDamage;
}

void CFort::recoverShipSkillDamage(double dDamage)
{
	m_dShipSkillDamage = dDamage;
}

double CFort::getShipSkillAddHp()
{
	return m_dShipSkillAddHp;
}

void CFort::recoverShipSkillAddHp(double dHp)
{
	m_dShipSkillAddHp = dHp;
}

double CFort::getShipSkillAddEnergy()
{
	return m_dShipSkillAddEnergy;
}

void CFort::recoverShipSkillAddEnergy(double dEnergy)
{
	m_dShipSkillAddEnergy = dEnergy;
}

void CFort::setFortBattle(CBattle * pBattle)
{
	m_pFortBattle = pBattle;
}

// ��ʼ����̨����
void CFort::initFortSkill(int nLevel, string strPath, double starDomainCoe)
{
	m_pFortSkill = new CFortSkill(this, nLevel, strPath, starDomainCoe);
	m_pFortSkill->setSkillBattle(m_pFortBattle);
}

// ������������ ���������� suitBuffValue ֵ
void CFort::setHaveSuitBuff(bool is, double suitBuffValue)
{
	m_isHaveSuitBuff = is;
	m_dSuitBuffValue = suitBuffValue;
}

void CFort::injuryAdditionInBossBattle(double dPercent)
{
	m_dInitDamage *= (1 + dPercent);
	m_dFortDamage = m_dInitDamage;
}


////////////////////////////////
          //��������//
////////////////////////////////
void CFort::resetFortEventVec(int nEvent)
{
	m_vecFortEvent.insert(m_vecFortEvent.end(), nEvent);
}

bool CFort::isEnemy()
{
	return m_isEnemy;
}

void CFort::resetFortType(int nFortType)
{
	m_nFortType = nFortType;
}

int CFort::getFortType()
{
	return m_nFortType;
}

void CFort::resetFortLevel(int nLevel)
{
	m_nFortLevel = nLevel;
}

int CFort::getFortLevel()
{
	return m_nFortLevel;
}

void CFort::resetFortStarDomainCoe(double dStarDomainCoe)
{
	m_dFortStarDomainCoe = dStarDomainCoe * 0.01;
}

double CFort::getStarDomainCoe()
{
	return m_dFortStarDomainCoe * 100;
}

void CFort::resetFortQualityCoe(double dQualityCoe)
{
	m_dFortQualityCoe = dQualityCoe;
}

double CFort::getQualityCoe()
{
	return m_dFortQualityCoe;
}

void CFort::resetFortAckGrowCoe(double dAckGrowCoe)
{
	m_dFortAckGrowCoe = dAckGrowCoe;
}

double CFort::getAckGrowCoe()
{
	return m_dFortAckGrowCoe;
}

void CFort::resetFortHpGrowCoe(double dHpGrowCoe)
{
	m_dFortHpGrowCoe = dHpGrowCoe;
}

double CFort::getHpGrowCoe()
{
	return m_dFortHpGrowCoe;
}

void CFort::resetFortSpeedCoe(double dSpeedCoe)
{
	m_dFortSpeedCoe = dSpeedCoe;
}

double CFort::getSpeedCoe()
{
	return m_dFortSpeedCoe;
}

void CFort::resetFortEnergyCoe(double dEnergyCoe)
{
	m_dFortEnergyCoe = dEnergyCoe;
}

double CFort::getEnergyCoe()
{
	return m_dFortEnergyCoe;
}

void CFort::resetHp(double dHp)
{
	m_dHp = dHp;
}

void CFort::resetEnergy(double dEnergy)
{
	m_dEnergy = dEnergy;
}

void CFort::resetFortInterval(double dInterval)
{
	m_dInterval = dInterval;
}

double CFort::getInterval()
{
	return m_dInterval;
}

void CFort::resetUninjuryRate(double dUninjuryRate)
{
	m_dUnInjuryRate = dUninjuryRate;
}

void CFort::resetFortAck(double dAck)
{
	m_dFortDamage = dAck;
}

void CFort::resetFortLife(bool isLife)
{
	m_isLive = isLife;
}

void CFort::resetFireTime(double dFireTime)
{
	m_dFireTime = dFireTime;
}

double CFort::getFireTime()
{
	return m_dFireTime;
}

void CFort::resetInitAck(double dAck)
{
	m_dInitAck = dAck;
}

double CFort::getInitAck()
{
	return m_dInitAck;
}

void CFort::resetInitHp(double dInitHp)
{
	m_dInitHp = dInitHp;
}

void CFort::resetDefense(double dDefense)
{
	m_dInitDefense = dDefense;
}

double CFort::getDefense()
{
	return m_dInitDefense;
}

void CFort::resetInitUnInjuryRate(double dRate)
{
	m_dInitUnInjuryRate = dRate;
}

double CFort::getInitUnInjuryRate()
{
	return m_dInitUnInjuryRate;
}

void CFort::resetInitDamage(double dInitDamage)
{
	m_dInitDamage = dInitDamage;
}

double CFort::getInitDamage()
{
	return m_dInitDamage;
}

void CFort::resetAddPassiveSkill(bool isAdd)
{
	m_isAddPassiveSkill = isAdd;
}

bool CFort::isAddPassiveSkill()
{
	return m_isAddPassiveSkill;
}

void CFort::resetFortParalysis(bool isParalysis)
{
	m_isFortParalysis = isParalysis;
}

void CFort::resetFortBurning(bool isBurning)
{
	m_isFortBurning = isBurning;
}

void CFort::resetAckUp(bool isAckUp)
{
	m_isFortAckUp = isAckUp;
}

void CFort::resetAckDown(bool isAckDown)
{
	m_isFortAckDown = isAckDown;
}

void CFort::resetRepairing(bool isRepairing)
{
	m_isFortRepairing = isRepairing;
}

void CFort::resetUnrepaire(bool isUnrepaire)
{
	m_isFortUnrepaire = isUnrepaire;
}

void CFort::resetUnEnergy(bool isUnenergy)
{
	m_isFortUnEnergy = isUnenergy;
}

void CFort::resetShield(bool isShield)
{
	m_isFortShield = isShield;
}

void CFort::resetRelive(bool isRelive)
{
	m_isFortRelive = isRelive;
}

void CFort::resetSkillFire(bool isSkillFire)
{
	m_isFortSkillFire = isSkillFire;
}

void CFort::resetBreakArmor(bool isBreakArmor)
{
	m_isFortBreakArmor = isBreakArmor;
}

void CFort::resetPassiveSkillStronger(bool isPassiveSkillStronger)
{
	m_isFortPassiveSkillStronger = isPassiveSkillStronger;
}

bool CFort::isHavePassiveSkillStronger()
{
	return m_isHavePassiveSkillStronger;
}

void CFort::resetHavePassiveSkillStronger(bool isHave)
{
	m_isHavePassiveSkillStronger = isHave;
}

double CFort::getBurningCountTime()
{
	return m_dBurningCountTime;
}

void CFort::setBurningCountTime(double dTime)
{
	m_dBurningCountTime = dTime;
}

double CFort::getRepairingCountTime()
{
	return m_dRepairingCountTime;
}

void CFort::setRepairingCountTime(double dTime)
{
	m_dRepairingCountTime = dTime;
}

void CFort::setReliveCountDown(double dTime)
{
	m_dReliveCountDown = dTime;
}

double CFort::getReliveHp()
{
	return m_dReliveHp;
}

void CFort::setReliveHp(double dHp)
{
	m_dReliveHp = dHp;
}

double CFort::getAckDownValue()
{
	return m_dAckDownValue;
}

void CFort::setAckDownValue(double dValue)
{
	m_dAckDownValue = dValue;
}

double CFort::getAckUpValue()
{
	return m_dAckUpValue;
}

void CFort::setAckUpValue(double dValue)
{
	m_dAckUpValue = dValue;
}

double CFort::getAddPassiveEnergyTime()
{
	return m_dAddPassiveEnergyTime;
}

void CFort::setAddPassiveEnergyTime(double dTime)
{
	m_dAddPassiveEnergyTime = dTime;
}

//double CFort::getSecondCountForRelive()
//{
//	return m_dSecondCountForRelive;
//}
//
//void CFort::setSecondCountForRelive(double dTime)
//{
//	m_dSecondCountForRelive = dTime;
//}

double CFort::getSkillTime()
{
	return m_dSkillTime;
}

void CFort::setSkillTime(double dTime)
{
	m_dSkillTime = dTime;
}
