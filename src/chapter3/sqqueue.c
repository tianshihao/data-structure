#include <chapter3/sqqueue.h>

// 构造一个空队列.
Status InitQueue_Sq(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(sizeof(MAXQSIZE * sizeof(QElemType)));

    if (!Q->base)
        exit(OVERFLOW);

    Q->front = Q->rear = 0;

    return OK;
} // InitQueue_Sq

// 返回 Q 的元素个数, 即队列的长度.
int QueueLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
} // QueueLength_Sq

// 插入元素 e 为 Q 的新的队尾元素
Status EnQueue_Sq(SqQueue *Q, QElemType e)
{
    // 队列满
    if ((Q->rear + 1) % MAXQSIZE == Q->front)
        return ERROR;

    Q->base[Q->rear] = e;

    Q->rear = (Q->rear + 1) % MAXQSIZE;

    return OK;
} // EnQueue_Sq

// 若队列不空, 则删除 Q 的队头元素, 用 e 返回其值, 并返回 OK;
// 否则返回 ERROR.
Status DeQueue_Sq(SqQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)
        return ERROR;

    *e = Q->base[Q->front];

    Q->front = (Q->front + 1) % MAXQSIZE;

    return OK;
} // DeQueue_Sq

Status QueueEmpty_Sq(SqQueue Q)
{
    return Q.front == Q.rear;
} // QueueEmpty_Sq

// 打印循环队列元素.
void PrintQueue_Sq(SqQueue Q)
{
    if (Q.front == Q.rear)
    {
        printf("queue is empty\n");
        return;
    }

    QElemType ptr = Q.front;

    while (ptr != Q.rear)
    {
        printf(" %d ", Q.base[ptr]);

        ptr = (ptr + 1) % MAXQSIZE;
    } // while
    printf("\n");

    return;
} // PrintQueue_Sq