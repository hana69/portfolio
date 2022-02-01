using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectBehavior_HTP : SelectBehavior {
    bool first = true;
    protected override void Init()
    {
        base.Init();
        if (first) {
            memoButton.interactable = false;
            spellButton.onClick.AddListener(() => { first = false; });
        }
        else
        {
            memoButton.interactable = true;
            spellButton.interactable = false;
            memoButton.gameObject.SetActive(false);
            spellButton.gameObject.SetActive(false);

            memoButton.onClick.AddListener(() =>
            {
                isExplaining = false;
            });
        }
    }
    public override void TextControllerInit()
    {
        if (first)
        {
            base.TextControllerInit();
        }
        else{
            base.TextControllerInit();
            textController.SkipScenarioTo("???:呪文を少しでも間違えれば魔法が発動することはない。気をつけよ");
        }
    }
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return) && !first) {
            if (textController.CurrentText == "???:もし呪文を忘れてしまいそうなら、その紙切れに書き込めばよい。" && textController.CharUpdatingFinished)
            {
                textController.UpdateToNextTextORFinishNowUpdate();
                memoButton.gameObject.SetActive(true);
                spellButton.gameObject.SetActive(true);
                UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(memoButton.gameObject);
            }
            else
            {
                textController.UpdateToNextTextORFinishNowUpdate();
            }
        }
    }
}
