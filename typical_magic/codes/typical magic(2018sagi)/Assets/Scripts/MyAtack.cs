using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
public class MyAtack : BattleSequence
{
    public BattleSequence enemyAtack;//次のシーン
    public BattleClear battleClear;//次のシーン
    
    UnityEngine.UI.InputField inputField;
    public UnityEngine.UI.InputField InputField
    {
        set { inputField = value; }
    }
    public GameObject meObj;
    
    Me me;
    Enemy enemy;
    
    protected override void GameStartInit()
    {
        me=meObj.GetComponent<Me>();
        
    }
    bool clear = false;
    protected override void Init()
    {
        me.InputedSpell = inputField.text;
        me.TurnInit();
        me.SetUseSkill();
        enemy = battleClear.nowEnemy().GetComponent<Enemy>();
        me.NowTurnUseSkill.ExecuteEffect(me,enemy);
        if (me.NowTurnUseSkill.GetType() != typeof(Charge_Skill))
        {
            me.ChargeInit();
        }
        clear = false;
    }
    public override void TextControllerInit()
    {
        textController.Init();
        textController.CurrentTxtUpdate(me.NowTurnUseSkill.EffectExplainTxt(me.Name,enemy.Name));
        textController.StartUpdating();
    }
    void Update()
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
                if (enemy.HP <= 0)
                {
                    clear = true;
                    inputField.text = "";
                    inputField.gameObject.SetActive(false);
                }
                GoToNextSequences();
            }
        }
       //Debug.Log( me.NowTurnUseSkill.EffectExplainTxt(enemy.Name) );
    }
    protected override BattleSequence NextSequence()
    {
        if (!clear)
        {
            return enemyAtack;
        }
        return battleClear;
    }
}
