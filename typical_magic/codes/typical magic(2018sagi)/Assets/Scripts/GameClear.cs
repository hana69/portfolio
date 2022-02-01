using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameClear : BattleSequence
{
    GameObject toTitleButton;
    protected override void GameStartInit()
    {
        toTitleButton = transform.Find("ToTitleButton").gameObject;
        toTitleButton.GetComponent<UnityEngine.UI.Button>().onClick.AddListener(() =>
        {
            UnityEngine.SceneManagement.SceneManager.LoadScene("Title");
        }
        );
    }

    protected override void Init()
    {
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(toTitleButton);
    }

    public override void TextControllerInit()
    {
        textController.CurrentTxtUpdate("");
    }

    // Update is called once per frame
    void Update () {
		
	}
}
