using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Me : Unit
{
    string inputedSpell;
    public string InputedSpell
    {
        set { inputedSpell = value; }
    }
    List<Skill> usableSkills;
    
    void Start() {
        gameName = "me";
        LoadSkill();
        failed = new Skill_Failed();
        BattleStartInit(100, 50, 3, 3);
        Elementalrate = new Dictionary<string, float>
        {
            { "物理" ,1.0f},
            { "炎" ,1.0f},
            { "氷", 1.0f},
            { "水", 1.0f},
            { "雷", 1.0f},
            { "風", 1.0f},
            { "爆発", 1.0f},
            { "RANDOM", 1.0f}
        };
    }

    public void BattleStartInit(int newHPMax,int newMPMax, int newAt,int newDf)
    {
        hpMax = newHPMax;
        HP = hpMax;
        mpMax = newMPMax;
        MP = mpMax;
        atackPara = newAt;
        deffencePara = newDf;
        AtackRank = 0;
        DeffenceRank = 0;
    }

    Skill_Failed failed;
    public void SetUseSkill()
    {
        nowTurnUseSkill = failed;
        foreach (var skill in usableSkills)
        {
            if (skill.name == inputedSpell)
            {
                nowTurnUseSkill = skill;
                if (skill.cost > mp)
                {
                    nowTurnUseSkill = failed;
                }
                else {
                    MP -= skill.cost;
                }
            }
        }
    }
    
    void LoadSkill()
    {
        usableSkills = new List<Skill>();
        TextAsset textSkillData = Resources.Load("spelldata") as TextAsset;
        string[] skillsData = textSkillData.text.Split(new string[] { "\r\n" },System.StringSplitOptions.None);
        //int nowSettingSkillsetNum=0;
        int nowLine = 0;
        while(nowLine < skillsData.Length){
            //int n = int.Parse(skillsData[nowLine]);
            //skills.Add(new List<Skill>(n));
            //for (int i= nowLine + 1;i<= nowLine + n;i++)
            //{
                string[] datas = skillsData[nowLine].Split(' ');
                switch (datas[0])
                {
                    case "at":
                        usableSkills.Add(new Atack_Skill(datas[1], int.Parse(datas[2]), datas[3], int.Parse(datas[4])));
                        break;
                    case "re":
                        usableSkills.Add(new Recovery_Skill(datas[1], int.Parse(datas[2]), int.Parse(datas[3])));
                        break;
                    case "sebf":
                        usableSkills.Add(new SelfBuff_Skill(datas[1], int.Parse(datas[2]), int.Parse(datas[3]) , int.Parse(datas[4]) ));
                        break;
                    case "enbf":
                        usableSkills.Add(new EnemyDebuff_Skill(datas[1], int.Parse(datas[2]), int.Parse(datas[3]), int.Parse(datas[4])));
                        break;
                    case "df":
                        usableSkills.Add( new Deffence_Skill( datas[1], int.Parse(datas[2]) ));
                        break;
                    case "ch":
                        usableSkills.Add(new Charge_Skill(datas[1], int.Parse(datas[2])));
                        break;
                    default:break;
                }
            //}
            //nowSettingSkillsetNum++;
            //nowLine += n + 1;
            nowLine ++ ;
        }

    }
}
