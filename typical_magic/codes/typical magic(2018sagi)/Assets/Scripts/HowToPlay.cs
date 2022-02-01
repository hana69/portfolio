using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class HowToPlay : BattleSequence {
    public NextEnemyAppear nextEnemyAppear;
    public SelectBehavior selectBehavior;
    public TextController textControllerObj;

    Button listenButton, noListenButton;
    GameObject HPexplain, MPexplain;
    // Use this for initialization
    void Start ()
    {
        BattleSequence.textController = textControllerObj;
        GameStartInitDone = true;

        //explainingPicNum = 0;
        //pics = Resources.LoadAll<Sprite>("HowToPlayImages/");

        TextAsset meScenarioAsset = Resources.Load("Aekashics_scenario") as TextAsset;
        meScenario = meScenarioAsset.text.Split('#');

        listenButton = transform.Find("ListenButton").GetComponent<Button>();
        listenButton.onClick.AddListener(() =>
        {
            isExplaining = true;
            textUpdateFlag = true;
            listenButton.gameObject.SetActive(false);
            noListenButton.gameObject.SetActive(false);
            textController.UpdateToNextTextORFinishNowUpdate();
        });
        
        noListenButton = transform.Find("NoListenButton").GetComponent<Button>();
        noListenButton.onClick.AddListener(() =>
        {
            textUpdateFlag = true;
            textController.Init();
            textController.SkipScenarioTo("???:では、その力を見せてみよ。幸運を祈る");
            textController.StartUpdating();
            listenButton.gameObject.SetActive(false);
            noListenButton.gameObject.SetActive(false);
        });

        HPexplain = transform.Find("HPexplain").gameObject;
        MPexplain = transform.Find("MPexplain").gameObject;

        textController.LoadNewScenairo(this);
        textController.Init();
        textController.StartUpdating();
    }
    protected override void Init()
    {
        throw new System.NotImplementedException();
    }
    protected override void GameStartInit()
    {
        throw new System.NotImplementedException();
    }
    
    //int explainingPicNum=0;
    //Sprite[] pics;

    string[] meScenario;
    int meScenarioNum=0;

    bool textUpdateFlag = true;
    void Update () {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            if (textUpdateFlag==true) {
                if (textController.FinishedFinalUpdating())
                {
                    GoToNextSequences();
                }
                else if (textController.CharUpdatingFinished)
                {
                    switch (textController.CurrentText) {
                        case "戦い方を……":
                            listenButton.gameObject.SetActive(true);
                            noListenButton.gameObject.SetActive(true);
                            UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(listenButton.gameObject);
                            textUpdateFlag = false;
                            break;
                        case "???:戦いで重要なのは、自らの、そして相手の生命力を知ることだ":
                            if (!HPexplain.activeSelf) {
                                HPexplain.SetActive(true);
                            }
                            else
                            {
                                HPexplain.SetActive(false);
                                textUpdateFlag = true;
                                textController.UpdateToNextTextORFinishNowUpdate();
                            }
                            break;
                        case "???:そして、魔法を扱うために必要な力が己に残っているかどうかも重要となる":
                            if (!MPexplain.activeSelf)
                            {
                                MPexplain.SetActive(true);
                            }
                            else
                            {
                                MPexplain.SetActive(false);
                                textUpdateFlag = true;
                                textController.UpdateToNextTextORFinishNowUpdate();
                            }
                            break;
                        case "???:「a」と唱えるのだ":
                            GoToNextSequences();
                            break;
                        default:
                            textController.UpdateToNextTextORFinishNowUpdate();
                            break;
                    }

                }
                else
                {
                    textController.UpdateToNextTextORFinishNowUpdate();
                }

                if (textController.CurrentText == "@")
                {
                    textController.CurrentTxtUpdate(meScenario[meScenarioNum]);
                    meScenarioNum++;
                    textController.StartUpdating();
                }
                
            }
        }
	}
    protected override BattleSequence NextSequence()
    {
        if (isExplaining)
        {
            return selectBehavior;
        }
        return nextEnemyAppear;
    }
}
