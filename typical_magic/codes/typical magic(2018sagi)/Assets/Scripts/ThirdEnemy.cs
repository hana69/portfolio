using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThirdEnemy : Enemy {
    public Me me;
    public override void Init()
    {
        gameName = "Ice Maiden";
        usableSkills = new Skill[]
        {
            new Atack_Skill("IcicleDisaster",35,"氷",15),
            new Atack_Skill("Absolute_ZERO",100,"氷",100),
            new SelfBuff_Skill("IceCristal",1,1,20)
        };
        failed = new Skill_Failed();
        hpMax = 150;
        mpMax = 300;
        atackPara = 12;
        deffencePara = 10;
        buffUsedCount = 0;
        Elementalrate = new Dictionary<string, float>
        {
            { "物理" ,1.0f},
            { "炎" ,1.5f},
            { "氷", 0f},
            { "水", 0.5f},
            { "雷", 1.0f},
            { "風", 0.9f},
            { "爆発", 1.5f},
            { "RANDOM", 1.0f}
        };
        base.Init();
    }
    int buffUsedCount=0;
    Skill_Failed failed;
    public override void SetUseSkill()
    {
        if (buffUsedCount==0 && hp <= hpMax/2)
        {
            nowTurnUseSkill = usableSkills[2];//IceCrsital
            buffUsedCount = 1;
        }
        //else if (buffUsedCount == 1 && hp <= hpMax / 4)
        //{
        //    nowTurnUseSkill = usableSkills[2];//IceCrsital
        //    buffUsedCount = 2;
        //}
        else if ( me.HP < 100 && MP >= 100 )
        {
            nowTurnUseSkill = usableSkills[1];//absoluteZERO
        }
        else
        {
            int rand = Random.Range(0, 11);
             if (rand>=1)
            {
                nowTurnUseSkill = usableSkills[0];
            }
            else
            {
                nowTurnUseSkill = failed;
            }
        }
        if (nowTurnUseSkill.cost <= mp)
        {
            mp -= nowTurnUseSkill.cost;
        }
        else
        {
            nowTurnUseSkill = failed;
        }
    }
}
