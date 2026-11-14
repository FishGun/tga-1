using UnityEngine;
using UnityEngine.Events;

public class Timer : MonoBehaviour
{
    public float duration;

    bool isActive = false;
    float expirationTime = float.PositiveInfinity;

    public UnityEvent timerExpiredEvent;


    /// <summary>
    /// Expected usage is:
    /// if ([A trigger that cares if the timer hasn't expired] && IsActiveElseActivate())
    /// {
    ///     UnexpiredReTriggerFunctionality();
    /// }
    /// </summary>
    /// <returns></returns>
    /// 
    public bool IsActiveElseRestart()
    {
        bool toReturn = isActive;
        RestartIfInactive();
        return toReturn;
    }

    public void RestartIfInactive()
    {
        if (isActive == false)
        {
            Restart();
        }
    }

    public void Deactivate()
    {
        isActive = false;
    }

    public bool IsActive()
    {
        return isActive;
    }
    public void Restart()
    {
        isActive = true;
        expirationTime = Time.time + duration;
    }

    void Update()
    {
        if (isActive && expirationTime <= Time.time)
        {
            timerExpiredEvent.Invoke();
            isActive = false;
        }
    }
}
