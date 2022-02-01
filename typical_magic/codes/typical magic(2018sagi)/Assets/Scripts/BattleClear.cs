using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BattleClear : BattleSequence {
    public Me me;
    public GameObject[] enemies;
    public WriteMemo writeMemo;
    public NextEnemyAppear nextEnemyAppear;


    public BattleSequence gameCleared;

    int nowEnemyNum;
    protected override void GameStartInit()
    {
        nowEnemyNum = 0;
        decideWritingMemo = transform.Find("DecideWritingMemo").GetComponent<Button>();
        decideWritingMemo.onClick.AddListener(() =>
        {
            gotoWriteMemo = true;
            textController.UpdateToNext();
            textController.StartUpdating();
            decideWritingMemo.gameObject.SetActive(false);
            decideSkipWriting.gameObject.SetActive(false);
        }
        );
        decideSkipWriting = transform.Find("DecideSkipWriting").GetComponent<Button>();
        decideSkipWriting.onClick.AddListener(() => {
            gotoWriteMemo = false;
            textController.UpdateToNext();
            textController.StartUpdating();
            decideWritingMemo.gameObject.SetActive(false);
            decideSkipWriting.gameObject.SetActive(false);
        });
    }
    readonly int[] hpRate = {
        50,100,250,300,999
    };
    readonly int[] mpRate = {
        30,80,200,400,999
    };
    readonly int[]  atParameterRate =
    {
        3,5,11,20,50
    },
                    dfParameterRate = {
        3,5,11,20,50
    };
    protected override void Init()
    {
        enemies[nowEnemyNum].SetActive(false);
        nowEnemyNum++;
        if (nowEnemyNum != enemies.Length)//さいごのてきいがいを倒したとき
        { 
            me.BattleStartInit(hpRate[nowEnemyNum], mpRate[nowEnemyNum], atParameterRate[nowEnemyNum], dfParameterRate[nowEnemyNum]);
        }
    }

    public Enemy nowEnemy()
    {
        return enemies[nowEnemyNum].GetComponent<Enemy>();
    }

    private Button decideWritingMemo;
    private Button decideSkipWriting;

    void Update()
    {
        if (textController.FinishedFinalUpdating() && !decideWritingMemo.IsActive())
        {
            if (Input.GetKeyDown(KeyCode.Return))
            {
                GoToNextSequences();
            }
        }
        
        if (Input.GetKeyDown(KeyCode.Return))
        {
            if (nowEnemyNum == enemies.Length)//さいごのてきを倒した後
            {
                if (textController.CharUpdatingFinished)
                {
                    GoToNextSequences();
                }
                else
                {
                    textController.SkipUpdate();
                }
            }
            //else if(textController.NextTextNumber==1)
            //{
            //    textController.UpdateToNextTextORFinishNowUpdate();
            //    if (textController.NextTextNumber == 2)
            //    {
            //        textController.CurrentTxtUpdate(SkillGetString());
            //    }
            //}
            else if (textController.CurrentText == "メモを書きますか？" && textController.CharUpdatingFinished)
            {
                decideWritingMemo.gameObject.SetActive(true);
                decideSkipWriting.gameObject.SetActive(true);
                UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(decideWritingMemo.gameObject);
            }
            else
            {
                textController.UpdateToNextTextORFinishNowUpdate();
            }
        }
    }
    public override void TextControllerInit()
    {
        decideWritingMemo.gameObject.SetActive(false);
        decideSkipWriting.gameObject.SetActive(false);
        textController.Init();
        textController.LoadNewScenairo(this);
        textController.CurrentTxtUpdate(enemies[nowEnemyNum - 1].GetComponent<Enemy>().Name + "をたおした！");
        textController.StartUpdating();
    }
    bool gotoWriteMemo;
    protected override BattleSequence NextSequence()
    {
        if (nowEnemyNum < enemies.Length)
        {
            Enemy enemy = enemies[nowEnemyNum].GetComponent<Enemy>();
            enemy.Init();
            if (gotoWriteMemo) {
                return writeMemo;
            }
            else
            {
                return nextEnemyAppear;
            }
        }
        else
        {
            return gameCleared;
        }
    }
}
