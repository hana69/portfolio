using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShowingMemo : BattleSequence
{
    public SelectBehavior selectBehavior;
    Scrollbar bar;
    
    protected override void GameStartInit()
    {
        bar = transform.Find("Memo/Scrollbar").GetComponent<Scrollbar>();
    }
    protected override void Init()
    {
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(bar.gameObject);
        // throw new NotImplementedException();
    }

    protected override BattleSequence NextSequence()
    {
        return selectBehavior;
    }
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            if (textController.CharUpdatingFinished) {
                GoToNextSequences();
            }
            else
            {
                textController.SkipUpdate();
            }
        }
    }
}
