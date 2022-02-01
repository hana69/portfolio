using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SystemTest : MonoBehaviour {
    public UnityEngine.UI.InputField inputField;
    public GameObject enemy_test;
	
	void Start () {
    //    Instantiate(enemy_test);
	}
	
	void Update () {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            inputField.ActivateInputField();
        }
	}
}
