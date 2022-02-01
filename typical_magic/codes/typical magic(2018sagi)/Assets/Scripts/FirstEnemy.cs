using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FirstEnemy : Enemy
{
    void Start()
    {
        Init();
    }
    public override void Init()
    {
        gameName = "Goblin";
        usableSkills = new Skill[]
        {
            new Atack_Skill("punch",10,"物理",5),
            new Skill_Failed()
        };
        atackPara = 3;
        deffencePara = 3;
        hpMax = 30;
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
}
