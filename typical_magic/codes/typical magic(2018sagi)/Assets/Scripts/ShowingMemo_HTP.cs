using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShowingMemo_HTP : ShowingMemo {
    public ShowingMemo showingMemo;
	void Update () {
        if (Input.GetKeyDown(KeyCode.Return)) {
            if (textController.CurrentText== "※メモは敵を倒したあとに書き込むことが出来ます" && textController.CharUpdatingFinished) {
                GoToNextSequences();
            }
            else {
                textController.UpdateToNextTextORFinishNowUpdate();
            }
        }
    }

    protected override BattleSequence NextSequence()
    {
        return showingMemo;
    }
}
