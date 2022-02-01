using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameOver : BattleSequence {

    GameObject toTitleButton;
    //BattleSequence Title;
	
    protected override void GameStartInit()
    {
        toTitleButton = transform.Find("ToTitleButton").gameObject;toTitleButton.GetComponent<UnityEngine.UI.Button>().onClick.AddListener( () =>
            {
                UnityEngine.SceneManagement.SceneManager.LoadScene("Title");
            }
        );
    }
    protected override void Init()
    {
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(toTitleButton);

    }
    

    void Update () {
		
	}
    protected override BattleSequence NextSequence()
    {
        return base.NextSequence();
    }
    public override void TextControllerInit()
    {
        //textController.Init();
    }
}
