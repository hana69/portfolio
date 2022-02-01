using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NextEnemyAppear : BattleSequence {
    public BattleClear battleClear;
    public SelectBehavior selectBehavior;
    protected override void GameStartInit()
    {

    }

    protected override void Init()
    {
        
    }

    public override void TextControllerInit()
    {
        textController.Init();
        Enemy enemy = battleClear.nowEnemy();
        enemy.gameObject.SetActive(true);
        textController.CurrentTxtUpdate( enemy.Name+"が現れた！" );
        textController.StartUpdating();
    }

    protected override BattleSequence NextSequence()
    {
        return selectBehavior;
    }

    void Update () {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            if (!textController.CharUpdatingFinished)
            {
                textController.SkipUpdate();
            }
            else
            {
                GoToNextSequences();
            }
        }
    }
}
