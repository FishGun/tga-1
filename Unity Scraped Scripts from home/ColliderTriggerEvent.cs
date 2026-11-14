using UnityEngine;
using UnityEngine.Events;

public class ColliderTriggerEvent : MonoBehaviour
{
    [SerializeField] public string[] triggeringTagNames = {"Player"};

    public UnityEvent triggered;

    [Header("Trigger Conditions")]
    public bool triggerOnEnter = true;
    public bool triggerOnStay = false;
    public bool triggerOnExit = false;

    private void OnTriggerEnter(Collider other)
    {
        if (triggerOnEnter)
        {
            TriggerLogic(other);
        }
    }
    private void OnTriggerStay(Collider other)
    {
        if (triggerOnStay)
        {
            TriggerLogic(other);
        }
    }
    private void OnTriggerExit(Collider other)
    {
        if (triggerOnExit)
        {
            TriggerLogic(other);
        }
    }

    void TriggerLogic(Collider other)
    {
        foreach (string tagName in triggeringTagNames)
        {
            if (tagName == other.tag)
            {
                triggered.Invoke();
            }
        }
    }
}
