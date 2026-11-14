using UnityEngine;

public class CreateBalls : MonoBehaviour
{
    [SerializeField] Vector3 startOffset;
    [SerializeField] Vector3Int ballArraySize;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Activate()
    {
        int size = ballArraySize.x * ballArraySize.y * ballArraySize.z;
        int x = 0, y = 0, z = 0;
        for (int i = 0; i < size; i++)
        {
            GameObject go = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            go.transform.position = transform.position + startOffset + new Vector3(x,y,z);
            go.AddComponent<Rigidbody>();

            if (++x > ballArraySize.x)
            {
                x = 0;
                if (++y > ballArraySize.y)
                {
                    y = 0;
                    ++z;
                }
            }
        }
    }
}
