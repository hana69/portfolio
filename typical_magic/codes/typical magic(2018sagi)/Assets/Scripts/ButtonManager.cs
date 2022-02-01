using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonManager : MonoBehaviour {
    public Button[] buttons;
	// Use this for initialization
	void Start () {
        UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(buttons[0].gameObject);
        for (var i=1;i<buttons.Length;i++)
        {
            buttons[i].GetComponent<Button>().onClick.AddListener(
            ()=>{
                UnityEngine.SceneManagement.SceneManager.LoadScene("Battle");
            }
            );
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
