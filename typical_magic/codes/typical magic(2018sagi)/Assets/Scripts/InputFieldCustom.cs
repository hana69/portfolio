using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputFieldCustom : UnityEngine.UI.InputField {

    protected override void LateUpdate()
    {
        base.LateUpdate();
        MoveTextEnd(false);
    }
}
