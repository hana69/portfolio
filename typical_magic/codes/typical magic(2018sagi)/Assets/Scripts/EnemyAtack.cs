using UnityEngine;
using System.Collections;
using System;

public class EnemyAtack : BattleSequence
{
    public BattleSequence SelectBehavior;
    public SelectBehavior_HTP selectBehavior_HTP;
    public BattleSequence GameOver;

    public BattleClear battleClear;

    public UnityEngine.UI.InputField inputField;

    public GameObject meObj;

    Me me;
    Enemy enemy;

    protected override void GameStartInit()
    {
        me = meObj.GetComponent<Me>();
        gameOver = false;
    }
    protected override void Init()
    {
        enemy = battleClear.nowEnemy().GetComponent<Enemy>();
        enemy.TurnInit();
        enemy.SetUseSkill();
        damageGiven = false;
        inputField.text = "";
        inputField.gameObject.SetActive(false);
    }
    public override void TextControllerInit()
    {
        textController.Init();
        textController.CurrentTxtUpdate(enemy.Name+"は"+enemy.ChantedSpell()+"を使った！\n");
        textController.StartUpdating();
    }
    bool damageGiven=false;
    bool gameOver = false;
    void Update()
    {
        if (!damageGiven)//ダメージ与える前
        {
            if (!textController.CharUpdatingFinished)
            {
                if (Input.GetKeyDown(KeyCode.Return))
                {
                    textController.SkipUpdate();
                }
            }
            else
            {
                if (Input.GetKeyDown(KeyCode.Return))
                {
                    Skill skill = enemy.NowTurnUseSkill;
                    //me.HP -= skill.strength;
                    skill.ExecuteEffect(enemy, me);
                    if ( skill.GetType()!=typeof(Charge_Skill)){
                        enemy.ChargeInit();
                    }
                    damageGiven = true;

                    if (skill.name == "失敗")
                    {
                        textController.CurrentTxtUpdate("しかし何も起こらなかった");
                    }
                    else
                    {
                        textController.CurrentTxtUpdate(skill.EffectExplainTxt(enemy.Name,me.Name));
                    }
                    textController.Init();
                    textController.StartUpdating();
                }
            }
        }//ダメージ与える前
        else//ダメージ与えた後
        {
            if (!textController.CharUpdatingFinished)
            {
                if (Input.GetKeyDown(KeyCode.Return))
                {
                    textController.SkipUpdate();
                }
            }
            else
            {
                if (me.HP==0)
                {
                    gameOver = true;
                }
                if (Input.GetKeyDown(KeyCode.Return))
                {
                    GoToNextSequences();
                }
            }
        }//ダメージ与えた後
    }

    protected override BattleSequence NextSequence()
    {
        if (gameOver)
        {
            return GameOver;
        }
        if (isExplaining)
        {
            return selectBehavior_HTP;
        }
        return SelectBehavior;
    }
}
