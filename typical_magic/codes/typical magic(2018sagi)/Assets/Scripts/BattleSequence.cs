using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BattleSequence : MonoBehaviour
{
    protected Dictionary<GameObject, BattleSequence> buttonsToNextSequences;
    static protected TextController textController;
    static protected bool isExplaining = false;

    protected abstract void GameStartInit();
    protected abstract void Init();

    public class TwiceFlaggedException : System.Exception
    {
        public TwiceFlaggedException(){}
    }

    private bool gameStartInitDone = false;
    public bool GameStartInitDone {
        set
        {
            if (!gameStartInitDone && value)
            {
                gameStartInitDone = true;
            }
            else
            {
                throw new TwiceFlaggedException();
            }
        }
        get {
            return gameStartInitDone;
        }
    }

    protected GameObject pushedButton;
    public void GoToNextSequences()
    {
        this.gameObject.SetActive(false);
        BattleSequence nextSequence = NextSequence();
        nextSequence.gameObject.SetActive(true);
        if (!nextSequence.GameStartInitDone)
        {
            nextSequence.GameStartInit();
            nextSequence.GameStartInitDone = true;
        }
        nextSequence.Init();
        nextSequence.TextControllerInit();
    }
    protected virtual void SetPushedButton(GameObject button)
    {
        pushedButton = button;
    }
    protected virtual BattleSequence NextSequence()
    {
        return buttonsToNextSequences[pushedButton];
    }
    public virtual void TextControllerInit()
    {
        textController.LoadNewScenairo(this);
        textController.Init();
        textController.StartUpdating();
    }
}
