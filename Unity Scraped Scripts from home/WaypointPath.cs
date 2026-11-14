using UnityEngine;
using System.Collections;

// Note: this is not an editor script.
public class WaypointPath : MonoBehaviour
{

    [System.Serializable]
    public class TravelingObject
    {
        public Transform transform;
        public float speed = 5;
        public int currentWaypoint = 0;
        public bool shouldMove = true;
        public bool movingBackwards = false;
    }

    public TravelingObject[] travelingObjects;

    public Transform[] waypointArray;

    public bool connectLastToFirst = true;

    public void Update()
    {
        for (int i = 0; i < travelingObjects.Length; i++)
        {
            TravelingObject tObject = travelingObjects[i];

            if (tObject.shouldMove == false)
            {
                continue;
            }

            if (tObject.transform.position == waypointArray[tObject.currentWaypoint].position)
            {
                tObject.currentWaypoint += tObject.movingBackwards ? -1 : 1;

                if (tObject.currentWaypoint >= waypointArray.Length)
                {
                    if (connectLastToFirst)
                    {
                        tObject.currentWaypoint = 0;
                    }
                    else
                    {
                        tObject.movingBackwards = true;
                        tObject.currentWaypoint--;
                    }
                }
                else if (tObject.currentWaypoint < 0)
                {
                    if (connectLastToFirst)
                    {
                        tObject.currentWaypoint = waypointArray.Length - 1;
                    }
                    else
                    {
                        tObject.movingBackwards = false;
                        tObject.currentWaypoint = 0;
                    }
                }
            }
            Vector3 difference = waypointArray[tObject.currentWaypoint].position - tObject.transform.position;
            Vector3 expectedShift = difference.normalized * tObject.speed * Time.deltaTime;

            tObject.transform.position = difference.magnitude < expectedShift.magnitude ? waypointArray[tObject.currentWaypoint].position : tObject.transform.position + expectedShift;
        }
    }

    private void OnDrawGizmos()
    {
        if (waypointArray == null) return;

        for (int i = 0; i < waypointArray.Length; i++)
        {
            if ((!connectLastToFirst && i + 1 >= waypointArray.Length) || waypointArray[i] == null || (i + 1 < waypointArray.Length && waypointArray[i + 1] == null))
            {
                return;
            }
            Gizmos.color = new Color(1f, 1f, 0f, 0.75f); // Yellow with custom alpha
            Vector3 thisWaypointPos = waypointArray[i].position;
            Vector3 nextWaypointPos = (i + 1) >= waypointArray.Length ? waypointArray[0].position : waypointArray[i + 1].position;

            // Draw the line
            Gizmos.DrawLine(thisWaypointPos, nextWaypointPos);

            // Draw spheres at start and end points
            Gizmos.color = Color.red;
            Gizmos.DrawSphere(nextWaypointPos, 0.1f);

            // Calculate and display the midpoint
            Vector3 midpoint = (thisWaypointPos + nextWaypointPos) / 2f;

            // Display the distance
            float distance = Vector3.Distance(thisWaypointPos, nextWaypointPos);
            UnityEditor.Handles.Label(midpoint, $"Distance: {distance:F2}");
        }
    }
}