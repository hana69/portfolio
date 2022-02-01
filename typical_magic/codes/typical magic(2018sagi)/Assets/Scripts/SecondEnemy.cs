using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SecondEnemy : Enemy
{
    public override void Init()
    {
        gameName = "Hi Wizard";
        usableSkills = new Skill[]
        {
    //      new Skill("a",10,"物理"),
            new Atack_Skill("fire",15,"炎",5),
            new Atack_Skill("elec",15,"雷",5),
            new Atack_Skill("BIG_BAN",30,"爆発",5),
            new Recovery_Skill("heal",30,10)
        };
        hpMax = 50;
        atackPara = 5;
        deffencePara = 6;
        recovered = false;
        Elementalrate = new Dictionary<string, float>
        {
            { "物理" ,1.3f},
            { "炎" ,0.7f},
            { "氷", 0.5f},
            { "水", 0.5f},
            { "雷", 0.5f},
            { "風", 0.7f},
            { "爆発", 1.0f},
            { "RANDOM", 1.0f}
        };
        base.Init();
    }
    bool recovered = false;
    int atackCount=0;
    public override void SetUseSkill()
    {
        if (hp >= hpMax / 2)//半分以上
        {
            if (atackCount <= 1)
            {
                nowTurnUseSkill = usableSkills[atackCount];
                atackCount++;
            }
            else
            {
                nowTurnUseSkill = usableSkills[Random.Range(0, 2)];
            }
        }
        else
        {
            if (!recovered)
            {
                nowTurnUseSkill = usableSkills[usableSkills.Length - 1];
                recovered = true;
            }
            else
            {
                nowTurnUseSkill = usableSkills[Random.Range(0, usableSkills.Length - 1)];
            }
        }
    }
}

