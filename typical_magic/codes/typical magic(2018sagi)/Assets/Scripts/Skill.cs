using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Skill
{
    readonly public int cost;
    readonly public string name;
    public Skill(string _name,int _cost)
    {
        name = _name;
        cost = _cost;
    }
    public abstract string EffectExplainTxt(string userName,string targetName);
    public abstract void ExecuteEffect(Unit user, Unit target);
}

public class Atack_Skill : Skill
{
    public Atack_Skill(string name, int _amount, string _type, int cost) : base(name, cost)
    {
        type = _type;
        amount = _amount;
    }
    public readonly int amount;
    readonly public string type;
    int realDamage;
    public int RealDamage{
        get{ return realDamage; }
    }
    public override string EffectExplainTxt(string userName, string targetName)
    {
        return targetName + "に" + realDamage + "の" + type + "属性ダメージ！";
    }
    public override void ExecuteEffect(Unit user, Unit target)
    {
        const float adjustRate = 0.5f;
        float rand = Random.Range(0.9f, 1.1f);
        int calucuratedDamage = (int)(amount * rand * (user.CorrectRate(true)+10)/target.CorrectRate(false)*adjustRate );
        if (amount < 30)
        {
            calucuratedDamage += Random.Range(-1, 1);
        }
        realDamage=target.GiveDamage(calucuratedDamage, type);
    }
}

public class Deffence_Skill:Skill
{
    public Deffence_Skill(string name,int cost):base(name,cost)
    { }
    public override string EffectExplainTxt(string userName, string targetName)
    {
        return userName + "は守りを固めた！";
    }
    public override void ExecuteEffect(Unit user, Unit target)
    {
        user.IsDeffending = true;
    }
}

public class Charge_Skill : Skill
{
    public Charge_Skill(string name,int cost):base(name,cost)
    { }
    public override string EffectExplainTxt(string userName, string targetName)
    {
        return userName + "は力を溜めている！";
    }
    public override void ExecuteEffect(Unit user, Unit target)
    {
        user.IsConcentrate = true;
    }
}

public class SelfBuff_Skill : Skill
{
    public SelfBuff_Skill(string name,int _atRank,int _dfRank,int cost) : base(name, cost)
    {
        atRank = _atRank;
        dfRank = _dfRank;
    }
    int atRank, dfRank;
    bool atBuffSuccess,dfBuffSuccess;
    public override string EffectExplainTxt(string userName, string targetName)
    {
        string s="";
        if (atRank > 0)
        {
            s=userName + "の攻撃力";
            if (atBuffSuccess)
            {
                s += "が上がった！";
            }
            else
            {
                s += "はもう上がりきっている！";
            }
        }
        else if(atRank < 0){
            s=targetName + "の攻撃力！";
            if (atBuffSuccess)
            {
                s += "が下がった！";
            }
            else
            {
                s += "はもう下がりきっている！";
            }
        }
        if (s!="")
        {
            s += "\n";
        }
        if (dfRank > 0)
        {
            s += userName + "の守備力";
            if (dfBuffSuccess)
            {
                s += "が上がった！";
            }
            else
            {
                s += "はもう上がりきっている！";
            }
        }
        else if (dfRank < 0)
        {
            s += targetName + "の守備力";
            if (dfBuffSuccess)
            {
                s += "が下がった！";
            }
            else
            {
                s += "はもう下がりきっている！";
            }
        }
        return s;
    }
    public override void ExecuteEffect(Unit user, Unit target)
    {
        user.AtackRank += atRank;
        atBuffSuccess = (atRank > 0 && user.AtackRank <= 3) || (atRank < 0 && user.AtackRank >= -3);

        user.DeffenceRank += dfRank;
        dfBuffSuccess = (dfRank > 0 && user.DeffenceRank <= 3) || (dfRank < 0 && user.DeffenceRank >= -3);
    }
}

public class EnemyDebuff_Skill : Skill
{
    public EnemyDebuff_Skill(string name, int _atRank, int _dfRank, int cost) : base(name, cost)
    {
        atRank = _atRank;
        dfRank = _dfRank;
    }
    int atRank, dfRank;
    public override string EffectExplainTxt(string userName, string targetName)
    {
        string s = "";
        if (atRank > 0)
        {
            s = targetName + "の攻撃力が上がった！";
        }
        else if (atRank < 0)
        {
            s = targetName + "の攻撃力が下がった！";
        }
        if (s != "")
        {
            s += "\n";
        }
        if (dfRank > 0)
        {
            s += targetName + "の守備力が上がった！";
        }
        else if (dfRank < 0)
        {
            s += targetName + "の守備力が下がった！";
        }
        return s;
    }
    public override void ExecuteEffect(Unit user, Unit target)
    {
        target.AtackRank += atRank;
        target.DeffenceRank += dfRank;
    }
}

public class Recovery_Skill : Skill
{
    public Recovery_Skill(string name, int _amount,int cost) : base(name,cost) {
        amount = _amount;
    }
    int amount;
    int realRecoverdAmount;
    public override string EffectExplainTxt(string userName, string targetName)
    {
        if (recoverSuccess) {
            return userName + "はHPを" + realRecoverdAmount + "回復した";
        }
        else
        {
            return userName + "はHPを回復しようとしたが、HPはこれ以上回復しない！";
        }
    }
    bool recoverSuccess=true;
    public override void ExecuteEffect(Unit user, Unit target)
    {
        const float adjustRate = 0.1f;
        float rand = Random.Range(0.9f, 1.1f);
        realRecoverdAmount = (int)((amount* user.CorrectRate(true)+50)*rand * adjustRate );
        if (amount < 30)
        {
            realRecoverdAmount += Random.Range(-1, 1);
        }

        recoverSuccess = (user.HP != user.HPMax);
        
        user.HP += realRecoverdAmount;
    }
}
public class Skill_Failed : Skill {
    public Skill_Failed() : base("失敗",0){
        
    }
    public override string EffectExplainTxt(string userName, string targetName)
    {
        return "しかし、なにも起こらなかった";
    }
    public override void ExecuteEffect(Unit user, Unit target)
    {

    }
}