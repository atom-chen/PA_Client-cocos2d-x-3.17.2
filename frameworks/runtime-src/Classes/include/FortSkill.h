#pragma once
#include "json/json.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "InitialData.h"
#include <vector>
//#include <iostream>
using namespace std;

class CFort;
class CBattle;

class CFortSkill
{
public:
	CFortSkill(CFort *pFort, int nSkillLevel, string strPathJson, double starDomainCoe);
	~CFortSkill();
	void update(double delta);
	void loadDataByFile(string strFile, int nSkillLevel);
	void setSkillBattle(CBattle *pBattle);
	double getSkillTime();
	void lockTargetFort();   // ���似��ʱ��������Ŀ����̨
	const char* isAddBuff();  // ����buff�ĸ���ֵ�����buffΪ1������ӷ���0��
	void setAddBuff(string strBuffPer); // �ͻ��������Ƿ����buff�Ĳ���ֵ

	CFort* getTargetFort();
	void getOneLineFort();
	void chooseStateFort(int nState);
	void fireSkill();
	double countSkillDamagePercent(double dType, double dCorrectType, double dRange, double correctRange, int nSkillLevel);
	double countScorePercent(double dScore, double dScoreCoe, double dCorrectScore, double dScoreGrow, int nSkillLevel);
	double countContinueTime(double dBuffBeginTime, double dContinueCoe, double dCorrectContinue, double dTimeGrow, int nSkillLevel);
	double countEffectValue(double dEffectValue, double dBuffCoe, double dCorrectBuff, double dBuffGrow, double nSkillLevel);

	void damagePlayerFort(int nTypeFire, double dAddDamage);  // nTypeFire :1 Ϊ��ͨ�����˺�  2 Ϊ���˶����˺��ļ����˺�
	//void damageEnemyFort(int nTypeFire, double dAddDamage);
	void damageWholePlayerForts(); // ȫ���˺�
	void damageWholeEnemyForts();

	CFort* getMinHpFort(map<int, CFort*> map);  // ��ȡ�������ֵ��̨���
	void splitBuffAdd(string strBuffPer);

	// ----------------��·������--------------
	void firstSkill_DieCut();      // �����и�
	void secondSkill_SpreadPos();  // ��ɢ��λ��
	void thirdSkill_MaximalBurst(); // ���ޱ���
	void fourthSkill_CrazyBurst(); //�����
	void fifthSkill_SpiralWave(); //��������
	void sixthSkill_StormShoot(); //�籩����
	void seventhSkill_GodLight(); //��֮��
	void eighthSkill_LightningStrike(); //�����׻�
	void ninthSkill_SpiralHit(); //�������
	void tenthSkill_LightShoot(); // ��������
	void eleventhSkill_BirdAngry();//������֮ŭ
	void twelfthSkill_EnergyZone();//��������
	void thirteenthSkill_PulseWave();//���岨��
	void fourteenthSkill_LightSpread();//��â����
	void fifteenthSkill_DragonHowl(); //����֮��
	void sixteenthSkill_FightVoice(); //��־֮��
	void seventeenthSkill_DestroyLight();//����֮��
	void eighteenthSkill_UltimateBlow(); //����֮��
	void nineteenthSkill_DoubleWinding();//˫�Ӳ���
	void twentiethSkill_AbsoluteDomain();//��������
	void twentyFirst_SaveLight();   //����֮��
	void twentySecond_DestroyBurst();//������
	void twentyThird_ElectricStorm();//��ŷ籩
	void twentyFourth_FatalShoot(); //����ɨ��
	void twentyFifth_OlympicFlame();//ʥ��
	void twentySixth_PunishKnife(); //�Ʋ�֮��
	void twentySeventh_DoomsdayTrial();//ĩ������
	void twentyEighth_HolyDiscipline();//��ʥ�ͽ�
	void twenthNinth_LightningStorm();//����籩
	void thirtieth_EndKnife();//�ս�����

private:
	double m_dStarDomainCoe;
	int m_nSkillID;
	CBattle *m_pSkillBattle;
	CFort *m_pFort;
	CFort *m_pTargetFort;

	int m_nSkillLevel;
	double m_dSkillDamagePercent;
	double m_dScorePercent;
	double m_dContinueTime;
	double m_dSkillEffectValue;

	double m_dSkillTime;
	bool m_isAddBuff;

	int m_nSingleBuffAdd; // 1:�������buff��2:ȫ�����buff
	int m_nAddBuff[3];  // �����Ƿ�ͬ����
};

