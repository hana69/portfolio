using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FourthEnemy : Enemy {

    public override void Init()
    {
        gameName = "The King of Giant";
        usableSkills = new Skill[]
        {
            new Atack_Skill("GiantSlash",70,"物理",25),
            new Deffence_Skill("GrandDeffence",2),
            new Charge_Skill("PowerSummarize",3),
            new SelfBuff_Skill("MalePurge",3,-1,10)
        };
        hpMax = 250;
        atackPara = 25;
        deffencePara = 28;
        Elementalrate = new Dictionary<string, float>
        {
            { "物理" ,0.5f},
            { "炎" ,1.5f},
            { "氷", 0.7f},
            { "水", 1.1f},
            { "雷", 1.5f},
            { "風", 0.7f},
            { "爆発", 1.0f},
            { "RANDOM", 1.0f}
        };
        base.Init();
    }
    public override void SetUseSkill()
    {
        if (IsConcentrate)
        {
            nowTurnUseSkill = usableSkills[0];
        }
        else
        {
            if (AtackRank <= 0 && hp<= hpMax*2/3)
            {
                nowTurnUseSkill = usableSkills[3];
            }
            else
            {
                int rand = Random.Range(0, 10);
                if (rand <= 3)
                {
                    nowTurnUseSkill = usableSkills[1];//まもる
                }
                else if(rand<=7)
                {
                    nowTurnUseSkill = usableSkills[2];//チャージ
                }
                else
                {
                    nowTurnUseSkill = usableSkills[0];
                }
            }
        }
    }
    // Update is called once per frame
    void Update () {
		
	}
}
