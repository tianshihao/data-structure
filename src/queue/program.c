#include <queue/linkqueue/linkqueue.h>
#include <queue/sqqueue/sqqueue.h>

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
    InitQueue_Sq(&Q);

    EnQueue_Sq(&Q, 100);
    EnQueue_Sq(&Q, 2);
    EnQueue_Sq(&Q, 3);
    EnQueue_Sq(&Q, 4);
    EnQueue_Sq(&Q, 5);

    PrintQueue_Sq(Q);

    QueueElemType e;

    GetHead_Sq(Q, &e);

    DeQueue_Sq(&Q, &e);

    PrintQueue_Sq(Q);
    // GetHead_Sq(Q, &e);

    DestoryQueue_Sq(&Q);

    SqQueue P;
    InitQueue_Sq(&P);

    DestoryQueue_Sq(&Q);

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
