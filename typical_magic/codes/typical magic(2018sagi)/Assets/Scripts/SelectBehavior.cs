using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SelectBehavior : BattleSequence
{
    public BattleSequence InputSpell;
    public BattleSequence ShowingMemo;
    
    protected Button spellButton, memoButton;
    protected override void GameStartInit()
    {
        spellButton = transform.Find("SpellButton").GetComponentInChildren<Button>();
        memoButton = transform.Find("MemoButton").GetComponentInChildren<Button>();
        buttonsToNextSequences = new Dictionary<GameObject, BattleSequence>
        {
            {spellButton.gameObject , InputSpell },
            {memoButton.gameObject , ShowingMemo }
        };
        spellButton.GetComponent<Button>().onClick.AddListener( ()=>SetPushedButton(spellButton.gameObject) );
        spellButton.GetComponent<Button>().onClick.AddListener(() => GoToNextSequences());

        memoButton.GetComponent<Button>().onClick.AddListener(() => SetPushedButton(memoButton.gameObject));
        memoButton.GetComponent<Button>().onClick.AddListener( () => GoToNextSequences() );
    }
    protected override void Init()
    {
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(spellButton.gameObject);
    }
}
