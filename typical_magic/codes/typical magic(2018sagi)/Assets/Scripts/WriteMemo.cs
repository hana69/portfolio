using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class WriteMemo : BattleSequence {
    //public Me me;
    public BattleClear battleClear;
    public NextEnemyAppear nextEnemyAppear;
    public Text memoText;//showingMemoが持ってる
    Text currentGotSkills;

    InputField field;
    Button okButton;
    Button rewriteButton;
    protected override void GameStartInit()
    {
        field = transform.Find("MemoPanel/InputField").GetComponent<InputField>();
        field.text = memoText.text;

        okButton = transform.Find("OKButton").GetComponent<Button>();
        okButton.onClick.AddListener(delegate
        {
            okButton.gameObject.SetActive(false);
            rewriteButton.gameObject.SetActive(false);
            memoText.text = field.text;
            textController.UpdateToNext();
            textController.StartUpdating();
        });
        
        rewriteButton = transform.Find("RewriteButton").GetComponent<Button>();
        rewriteButton.onClick.AddListener(delegate
        {
            okButton.gameObject.SetActive(false);
            rewriteButton.gameObject.SetActive(false);
            field.interactable = true;
            UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(field.gameObject);
            textController.CurrentTxtUpdate("入力が終わったら、Enterキーを押してください");
        }
        );
        field.onEndEdit.AddListener(delegate
        {
            field.interactable = false;
            textController.CurrentTxtUpdate("これでいいですか？");
            okButton.gameObject.SetActive(true);
            rewriteButton.gameObject.SetActive(true);
            UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(rewriteButton.gameObject);
        });
        currentGotSkills = transform.Find("SkillsText").GetComponent<Text>();
    }
    protected override void Init()
    {
        okButton.gameObject.SetActive(false);
        rewriteButton.gameObject.SetActive(false);
        
        field.interactable = true;
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(field.gameObject);
        Skill[] skills = battleClear.nowEnemy().UsableSkills;
        string s = "使えるようになったスキル\n";
        foreach (var skill in skills)
        {
            s += skill.name + "\n";
        }
        currentGotSkills.text = s;
    }
    
    void Update () {
        if (textController.NextTextNumber==2)
        {
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
    protected override BattleSequence NextSequence()
    {
        return nextEnemyAppear;
    }
}
