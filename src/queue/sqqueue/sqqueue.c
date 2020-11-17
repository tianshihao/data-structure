#include <queue/sqqueue/sqqueue.h>

Status InitQueue_Sq(SqQueue *Q)
{
    // 为顺序队列申请内存空间.
    Q->base = (QElemType *)malloc(MAX_SIZE * sizeof(QElemType));
    if (!Q->base)
    {
        exit(OVERFLOW);
    }

    // 初始化指针.
    Q->front = Q->rear = 0;

    printf("[debug] Initialize sequence queue.\n");

    return OK;
} // InitQueue_Sq

Status DestoryQueue_Sq(SqQueue *Q)
{
    if (Q->base)
    {
        free(Q->base);
        Q->base = NULL;
        Q->front = Q->rear = 0;
        printf("[debug] Destory sequence queue successfully.\n");
        return OK;
    }
    else
    {
        printf("[debug] Destory sequence queue failed.\n");
        exit(ERROR);
    }
} // DestoryQueue_Sq

Status QueueEmpty_Sq(SqQueue Q)
{
    return Q.front == Q.rear;
} // QueueEmpty_Sq

Status EnQueue_Sq(SqQueue *Q, QElemType e)
{
    // 队头指针在队尾指针的下一位是队满的标志,
    // 这样做会牺牲一位存储空间.
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        return ERROR;
    }

    // 新元素入队尾.
    // Q->base[Q->rear] = e;
    *(Q->base + Q->rear) = e;

    // 队尾指针进一.
    Q->rear = (Q->rear + 1) % MAX_SIZE;

    printf("[debug] %d enqueue.\n", e);

    return OK;
} // EnQueue_Sq

Status DeQueue_Sq(SqQueue *Q, QElemType *e)
{
    // 如果队列为空.
    if (Q->front == Q->rear)
    {
        return ERROR;
    }

    // 队头元素出队.
    *e = Q->base[Q->front];

    // 队头进一.
    Q->front = (Q->front + 1) % MAX_SIZE;

    printf("[debug] %d equeue.\n", *e);

    return OK;
} // DeQueue_Sq

Status GetHead_Sq(SqQueue Q, QElemType *e)
{
    if (Q.front == Q.rear)
    {
        return ERROR;
    }

    *e = Q.base[Q.front];

    printf("[debug] Get head of queue, it is %d.\n", *e);

    return OK;
} // GetHead_Sq

int QueueLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
} // QueueLength_Sq

Status PrintQueue_Sq(SqQueue Q)
{
    if (QueueEmpty_Sq(Q))
    {
        exit(ERROR);
    }

    printf("[debug] Print sequence queue:\n");
    printf("        <-front ");

    int p = Q.front;

    while (p != Q.rear)
    {
        printf(" %d ", Q.base[p]);

        // 队列指针进一.
        p = (p + 1) % MAX_SIZE;
    } // while

    printf(" rear->\n");

    return OK;
} // PrintQueue_Sq
