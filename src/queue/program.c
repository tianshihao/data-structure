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

    QElemType e;

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
    InitQueue_L(&Q);
    QElemType e;

    printf("length = %d\n", QueueLength(Q));

    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);
    EnQueue(&Q, 4);

    printf("length = %d\n", QueueLength(Q));

    DeQueue(&Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLength(Q));

    PrintQueue_L(Q);

    GetHead(Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLength(Q));

    printf("length = %d\n", QueueLength(Q));

    ClearQueue(&Q);

    PrintQueue_L(Q);

    if (DeQueue(&Q, &e))
        printf("wrong\n");
    else
        printf("bingo\n");

    DestoryQueue_L(&Q);

    return;
}
