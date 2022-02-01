using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FifthEnemy : Enemy
{
    
    public override void Init()
    {
        gameName = "Hades";
        usableSkills = new Skill[]
        {
            new Atack_Skill("Allow Rain" , 55 ,"物理", 11 ),
            new Atack_Skill("BIG_BAN",30,"爆発",5),
            new Atack_Skill("CaosBlade_Chain",20,"物理",3),
            new Atack_Skill("Absolute_ZERO",100,"氷",100),
            new Atack_Skill("SunCrarion",200,"炎",250),
            new SelfBuff_Skill("LunaCrarion",2,2,100),
            //new Atack_Skill("Sun")
            new Recovery_Skill("heal",30,5),
            new Charge_Skill("PowerSummarize",3),
            new EnemyDebuff_Skill("CurseDulling",-1,-1,40)
        };
        hpMax = 999;
        mpMax = 999;
        atackPara = 50;
        deffencePara = 50;
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
        base.Init();
    }
    public Me me;
    int meAtackMax = -1;
    public override void SetUseSkill()
    {
        //if (meAtackMax >= hp)
        //{
        //    nowTurnUseSkill = usableSkills[3];//回復
        //}
        //else
        //{
        //    Skill[] atackSkills=usableSkills.CopyTo(,)
        //}
        nowTurnUseSkill = usableSkills[Random.Range(0, usableSkills.Length)];
    }
}
