#include <linkqueue.h>
#include <sqqueue.h>

void UseSqqueue();
void UseLinkqueue();

int main()
{
    UseSqqueue();

    system("pause");

    return 0;
}

void UseSqqueue()
{
    SqQueue Q;

    if (OK == InitQueueSq(&Q))
    {
        EnQueueSq(&Q, 100);
        EnQueueSq(&Q, 2);
        EnQueueSq(&Q, 3);
        EnQueueSq(&Q, 4);
        EnQueueSq(&Q, 5);

        PrintQueueSq(Q);

        QueueElemType e;

        GetHeadSq(Q, &e);

        DeQueueSq(&Q, &e);

        PrintQueueSq(Q);
        // GetHead_Sq(Q, &e);

        DestoryQueueSq(&Q);
    }

    SqQueue P;
    InitQueueSq(&P);

    DestoryQueueSq(&Q);

    return;
}

void UseLinkqueue()
{
    LinkQueue Q;
    InitQueue_Link(&Q);
    QueueElemType e;

    printf("length = %d\n", QueueLength_Link(Q));

    EnQueue_Link(&Q, 1);
    EnQueue_Link(&Q, 2);
    EnQueue_Link(&Q, 3);
    EnQueue_Link(&Q, 4);

    printf("length = %d\n", QueueLength_Link(Q));

    DeQueue_Link(&Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLength_Link(Q));

    PrintQueue_Link(Q);

    GetHead_Link(Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLength_Link(Q));

    printf("length = %d\n", QueueLength_Link(Q));

    PrintQueue_Link(Q);

    if (DeQueue_Link(&Q, &e))
        printf("wrong\n");
    else
        printf("bingo\n");

    DestoryQueue_Link(&Q);

    return;
}
