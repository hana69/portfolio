using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Enemy : Unit
{
    protected Skill[] usableSkills;
    public Skill[] UsableSkills
    {
        get { return usableSkills; }
    }
    public virtual void Init()
    {
        hp = hpMax;
        mp = mpMax;
        AtackRank = 0;
        DeffenceRank = 0;
    }
    public override int MP
    {
        get
        {
            return mp;
        }

        set
        {

        }
    }
    void Update () {
        
    }

    public virtual void SetUseSkill()
    {
        nowTurnUseSkill = usableSkills[Random.Range(0, usableSkills.Length)];
    } 

    public string ChantedSpell()
    {
        if (nowTurnUseSkill.name=="失敗")
        {
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            int n = Random.Range(0, usableSkills.Length - 2);
            int wrongPos = Random.Range(0, usableSkills[n].name.Length);
            int m = Random.Range(0, 25);
            while (alphabet[m]== usableSkills[n].name[wrongPos]) {
                m = Random.Range(0, 26);
            }
            
            string spell = usableSkills[n].name.Substring(0,wrongPos);
            spell += alphabet[m].ToString();
            spell += usableSkills[n].name.Substring(wrongPos + 1); 
            return spell;
        }
        else
        {
            return nowTurnUseSkill.name;
        }
    }

    public void GotoNextEnemy(GameObject next)
    {
        this.gameObject.SetActive(false);
        next.SetActive(true);
    }
}