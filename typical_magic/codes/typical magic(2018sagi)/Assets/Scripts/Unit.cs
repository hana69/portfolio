using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class Unit : MonoBehaviour {
    protected string gameName;
    public string Name
    {
        get { return gameName; }
    }
    int atackRank;
    public int AtackRank{
        get { return atackRank; }
        set
        {
            atackRank = value;
            if (atackRank>3)
            {
                atackRank = 3;
            }
            if (atackRank<-3)
            {
                atackRank = -3;
            }
        }
    }
    int deffenceRank;
    public int DeffenceRank
    {
        get { return deffenceRank; }
        set
        {
            deffenceRank = value;
            if (deffenceRank > 3)
            {
                deffenceRank = 3;
            }
            if (deffenceRank < -3)
            {
                deffenceRank = -3;
            }
        }
    }

    protected int atackPara;
    protected int deffencePara;
    

    //public void ChangeRank(bool isAtack,int change)
    //{
    //    if (isAtack)
    //    {
    //        atackRank += change;
    //    }
    //    else
    //    {
    //        deffenceRank += change;
    //    }
    //}
    protected int hp;
    protected int hpMax;
    public int HPMax
    {
        get { return hpMax; }
    }

    bool isDeffending;
    public bool IsDeffending
    {
        get { return isDeffending; }
        set
        {
            if (value)
            {
                isDeffending = true;
            }
            else
            {
                throw new System.Exception();
            }
        }
    }

    bool isConcentrate;
    public bool IsConcentrate
    {
        get { return isConcentrate; }
        set
        {
            if (value)
            {
                isConcentrate = true;
            }
        }
    }
    public void TurnInit()
    {
        isDeffending = false;
    }
    public void ChargeInit()
    {
        isConcentrate = false;
    }

    public UnityEngine.UI.Slider slider;
    public int HP
    {
        get { return hp; }
        set
        {
            hp = value;
            if (hp <= 0)
            {
                hp = 0;
            }
            if (hp>hpMax)
            {
                hp = hpMax;
            }
            slider.value = (float)hp / hpMax;
        }
    }
    protected int mp = 0;
    protected int mpMax;
    public virtual int MP
    {
        get { return mp; }
        set
        {
            mp = value;
            if (mp <= 0)
            {
                mp = 0;
            }
            if (mp > mpMax)
            {
                mp = mpMax;
            }
            mpSlider.value = (float)mp / mpMax;
        }
    }
    public UnityEngine.UI.Slider mpSlider;

    protected Skill nowTurnUseSkill=null;
    public Skill NowTurnUseSkill
    {
        get { return nowTurnUseSkill; }
    }
    
    static public float EffectRate(int rank)
    {
        switch (rank)
        {
            case 3: return 1.7f;
            case 2: return 1.5f;
            case 1: return 1.3f;
            case 0: return 1.0f;
            case -1: return 0.8f;
            case -2: return 2.0f / 3.0f;
            case -3: return 0.6f;
        }
        throw new System.Exception();
    }

    protected Dictionary<string, float> Elementalrate;
    public int GiveDamage(int calucuratedDamage,string type) {
        int realDamage = (int)(calucuratedDamage * Elementalrate[type]);
        HP -= realDamage;
        return realDamage;
    }
    
    public float CorrectRate(bool isAtack)
    {
        if (isAtack)
        {
            if (isConcentrate)
            {
                return 3.0f*atackPara * EffectRate(atackRank);
            }
            return atackPara * EffectRate(atackRank);
        }
        else
        {
            if (isDeffending)
            {
                return deffencePara * EffectRate(deffenceRank) * 5;
            }
            return deffencePara * EffectRate(deffenceRank);
        }
    }
}
