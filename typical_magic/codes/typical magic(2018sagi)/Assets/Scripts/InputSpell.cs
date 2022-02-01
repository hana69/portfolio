using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InputSpell : BattleSequence
{
    public MyAtack myAtack;
    public BattleSequence SelectBehavior;
    protected InputField inputField;
    //public UnityEngine.UI.Text limitTimeTxt;

    GameObject decideButton,resetButton;

    protected override void GameStartInit()
    {
        decideButton = transform.Find("DecideButton").gameObject;
        resetButton = transform.Find("ResetButton").gameObject;
        buttonsToNextSequences = new Dictionary<GameObject, BattleSequence>
            {
                {decideButton , myAtack },
                {transform.Find("ResetButton").gameObject , SelectBehavior  }
            };
        decideButton.GetComponent<UnityEngine.UI.Button>().onClick.AddListener(()=>SetPushedButton(decideButton));
        decideButton.GetComponent<UnityEngine.UI.Button>().onClick.AddListener(()=> {
            myAtack.InputField = inputField;
            GoToNextSequences();

        });
        resetButton.GetComponent<UnityEngine.UI.Button>().onClick.AddListener(()=>
        {
            inputField.interactable = true;
            inputField.ActivateInputField();

            decideButton.SetActive(false);
            resetButton.SetActive(false);
        });

        inputField = transform.Find("InputField").GetComponent<InputField>();
        inputField.onEndEdit.AddListener(delegate { FinishInputEvent(); });
    }

    protected override void Init()
    {
        inputField.gameObject.SetActive(true);
        inputField.interactable = true;
        inputField.ActivateInputField();
        
        decideButton.SetActive(false);
        resetButton.SetActive(false);
    }
    
    void Update()
    {
        //limitTime -= Time.deltaTime;
        //if (preTime-limitTime>1)
        //{
        //    preTime = limitTime;
        //    limitTimeTxt.text = Mathf.CeilToInt(limitTime).ToString();
        //}
        //if (limitTime <= 0)
        //{
        //    inputField.DeactivateInputField();
        //    GoToNextSequences();
        //}
    }
    public virtual void FinishInputEvent()
    {
        decideButton.SetActive(true);
        resetButton.SetActive(true);
        inputField.interactable = false;
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(decideButton);
    }   
    
}
