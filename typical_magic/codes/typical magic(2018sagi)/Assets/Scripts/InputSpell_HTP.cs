using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputSpell_HTP : InputSpell {

    public override void FinishInputEvent()
    {
        if (inputField.text=="a")
        {
            base.FinishInputEvent();
        }
        else
        {
            inputField.ActivateInputField();
            UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(inputField.gameObject);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
