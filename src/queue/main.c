/**
 * @file main.c
 * @author tianshihao4944@126.com
 * @brief Test sequence queue and link sequence.
 * @version 0.1
 * @date 2021-11-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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
        printf("Q length = %d.\n", QueueLengthSq(Q));

        QueueElemType e;

        GetHeadSq(Q, &e);

        DeQueueSq(&Q, &e);

        PrintQueueSq(Q);
        printf("Q length = %d.\n", QueueLengthSq(Q));
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
    InitQueueLink(&Q);
    QueueElemType e;

    printf("length = %d\n", QueueLengthLink(Q));

    EnQueueLink(&Q, 1);
    EnQueueLink(&Q, 2);
    EnQueueLink(&Q, 3);
    EnQueueLink(&Q, 4);

    printf("length = %d\n", QueueLengthLink(Q));

    DeQueueLink(&Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLengthLink(Q));

    PrintQueueLink(Q);

    GetHeadLink(Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLengthLink(Q));

    printf("length = %d\n", QueueLengthLink(Q));

    PrintQueueLink(Q);

    if (DeQueueLink(&Q, &e))
        printf("wrong\n");
    else
        printf("bingo\n");

    DestoryQueueLink(&Q);

    return;
}
