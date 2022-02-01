using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class TextController : MonoBehaviour
{
    public UnityEngine.UI.Text uiText;//UI操作用
    public GameObject arrowEnter;

    private int nextTextNumber = 1;
    public int NextTextNumber
    {
        get { return nextTextNumber; }
    }
    private string currentText = string.Empty;
    public string CurrentText{
        get { return currentText; }
    }
    // Use this for initialization
    void Start()
    {
        scenarios = new Dictionary<BattleSequence, string[]> { };
        coroutine = UpdateChar();
        Init(); 
    }

    private bool charUpdatingFinished = false;
    public bool CharUpdatingFinished
    {
        get { return charUpdatingFinished; }
    }
    
    public void UpdateToNextTextORFinishNowUpdate()
    {
        if (charUpdatingFinished)
        {
            if (nextTextNumber < nowScenario.Length)
            {
                UpdateToNext();
                charUpdatingFinished = false;
                StartCoroutine(UpdateChar());
                arrowEnter.SetActive(false);
            }
        }
        else
        {
            charUpdatingFinished = true;
        }
    }
    public bool FinishedFinalUpdating()
    {
        return nextTextNumber == nowScenario.Length && charUpdatingFinished;
    }
    TextAsset scenarioAsset;
    Dictionary<BattleSequence, string[]> scenarios;
    string[] nowScenario;
    
    public void CurrentTxtUpdate(string txt)
    {
        currentText = txt;
    }
    public void AddCurrentTxt(string txt)
    {
        currentText += txt;
    }

    public void InsertScenario(string _scenario,int insertNum)
    {
        nowScenario[insertNum] = _scenario;
    }

    public void SkipScenarioTo(string target)
    {
        while (currentText != target && nextTextNumber < nowScenario.Length)
        {
            UpdateToNext();
        }
        if (currentText != target) {
            throw new System.Exception();
        }
    }

    IEnumerator coroutine;
    public void Init()
    {
        StopCoroutine(coroutine);
        charUpdatingFinished = false;
        nextTextNumber = 1;
    }
    
    public void LoadNewScenairo(BattleSequence sequence)
    {
        if (!scenarios.ContainsKey(sequence))
        {
            scenarioAsset = Resources.Load("BattleTexts/" + sequence.name) as TextAsset;
            scenarios[sequence] = scenarioAsset.text.Split(char.Parse("#"));
        }
        nowScenario = scenarios[sequence];
        currentText = nowScenario[0];
    }

    public void StartUpdating()
    {
        coroutine = null;
        coroutine = UpdateChar();
        StartCoroutine(coroutine);
    }
    public void SkipUpdate()
    {
        charUpdatingFinished = true;
    }

    IEnumerator UpdateChar()
    {
        for (int i = 0; i < currentText.Length; i++)
        {
            uiText.text = currentText.Substring(0, i);
            if (i == currentText.Length - 1)//文字更新が文章の最後まで達した時
            {
                charUpdatingFinished = true;
            }
            if (charUpdatingFinished)
            {
                uiText.text = currentText;//キー操作でcharUpdatingFinishedがtrueになる場合があるので、textを最後まで進める
                arrowEnter.SetActive(true);
                yield break;
            }
            yield return new WaitForSeconds(0.1f);
        }
    }
    public void UpdateToNext()
    {
        currentText = nowScenario[nextTextNumber];
        nextTextNumber++;
    }

}
