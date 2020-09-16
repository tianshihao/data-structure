/**
 * @file algraph.c
 * @author tianshihao4944@126.com
 * @brief 邻接表.
 * @version 0.1
 * @date 2020-09-13
 * @copyright Copyright (c) 2020
 */

#include <chapter7/algraph/algraph.h>

Status CreateGraph_AL(ALGraph *G)
{
    printf("Enter graph's type (1: DG, 2: DN, 3: UDG, 4: UDN): ");
    scanf("%u", &G->type);

    switch (G->type)
    {
    case DG:
        return CreateDG_AL(G);
    case DN:
        return CreateDN_AL(G);
    case UDG:
        return CreateUDG_AL(G);
    case UDN:
        return CreateUDN_AL(G);
    default:
        return ERROR;
    }

    return OK;
}

Status CreateDG_AL(ALGraph *G)
{
    printf("Enter vertex number of graph: ");
    scanf("%d", &G->vexnum);
    printf("Enter arc number of graph: ");
    scanf("%d", &G->arcnum);

    printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", &G->vertices[i].vex);
        G->vertices[i].firstarc = NULL;
    }

    printf("Enter vertex relation (e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.): \n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        InsertArcNode(G, v1, v2, weight);
    }

    return OK;
}

Status CreateDN_AL(ALGraph *G)
{
    return CreateDG_AL(G);
}

Status CreateUDG_AL(ALGraph *G)
{
    printf("Enter vertex number of graph: ");
    scanf("%d", &G->vexnum);
    printf("Enter arc number of graph: ");
    scanf("%d", &G->arcnum);

    printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", &G->vertices[i].vex);
        G->vertices[i].firstarc = NULL;
    }

    printf("Enter vertex relation (e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.): \n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        InsertArcNode(G, v1, v2, weight);
        InsertArcNode(G, v2, v1, weight);
    }

    return OK;
}

Status CreateUDN_AL(ALGraph *G)
{
    return CreateUDG_AL(G);
}

VertexType LocateVex_AL(ALGraph G, VertexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i].vex == v)
        {
            return i;
        }
    }
}

Status InsertArcNode(ALGraph *G, VertexType v1, VertexType v2, WeightType weight)
{
    int v1index = LocateVex_AL(*G, v1);

    /* 如果没有依附于该顶点的边, 即边表为空, 创建新的头结点. */
    if (G->vertices[v1index].firstarc == NULL)
    {
        G->vertices[v1index].firstarc = malloc(sizeof(ArcNode));

        /* 在顶点表中寻找 v2 顶点对应的下标. */
        int v2index = LocateVex_AL(*G, v2);

        G->vertices[v1index].firstarc->adjvex = v2index;
        G->vertices[v1index].firstarc->weight = weight;
        G->vertices[v1index].firstarc->nextarc = NULL;
    }
    /* 如果该顶点的边表不为空, 直接在边表尾新加结点. */
    else
    {
        /* 工作指针, 指向边表头结点. */
        ArcNode *p = G->vertices[v1index].firstarc;

        /* 找到表尾, 合适的插入位置. */
        while (p->nextarc != NULL)
        {
            p = p->nextarc;
        }

        /* 在顶点表中寻找 v2 顶点对应的下标. */
        int v2index = LocateVex_AL(*G, v2);

        /* 新边结点, 尾插法. */
        ArcNode *newarc = malloc(sizeof(ArcNode));
        newarc->adjvex = v2index;
        newarc->weight = weight;
        newarc->nextarc = NULL;

        p->nextarc = newarc;
    }

    return OK;
}

void BFSTraverse_AL(ALGraph G, Status (*Visit)(int v))
{
    /* 设置辅助数组, 标记顶点是否被访问. */
    int visited[G.vexnum];

    /* 初始化辅助数组. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    /* 顺序队列. */
    SqQueue Q;

    /* 队列中存放已经访问过但邻接结点未知的结点. */
    InitQueue_Sq(&Q);

    /* 从 0 号顶点开始遍历. */
    for (int vindex = 0; vindex < G.vexnum; ++vindex)
    {
        /* 对每个连通分量调用一次 BFS_AL. */
        if (!visited[vindex])
        {
            /* vi 未访问过, 从 vi 开始 BFS_AL. */
            BFS_AL(G, vindex, Visit, visited, &Q);
        }
    }

    return;
}

void BFS_AL(ALGraph G, int vindex, Status (*Visit)(VertexType v), int *visited, SqQueue *Q)
{
    /* 访问初始结点. */
    Visit(G.vertices[vindex].vex);

    /* 对 vindex 做已访问标记. */
    visited[vindex] = TRUE;

    /* 顶点索引 vindex 入队列. */
    EnQueue_Sq(Q, vindex);

    while (!QueueEmpty_Sq(*Q))
    {
        /* 顶点索引 vindex 出队列.*/
        DeQueue_Sq(Q, &vindex);

        /* 检测所有依附于顶点 vindex 的边. */
        for (ArcNode *arc = G.vertices[vindex].firstarc; arc != NULL; arc = arc->nextarc)
        {
            /* 若弧 arc 指向的顶点还没有被访问过. */
            if (!visited[arc->adjvex])
            {
                /* 访问弧 arc 指向的顶点. */
                Visit(G.vertices[arc->adjvex].vex);

                /* 对弧 arc 指向的结点做访问标记. */
                visited[arc->adjvex] = TRUE;

                /* 把弧 arc 指向的顶点入队列. */
                EnQueue_Sq(Q, LocateVex_AL(G, arc->adjvex));
            }
        }
    }

    return;
}

void DFSTraverse_AL(ALGraph G, Status (*Visit)(VertexType v))
{
    /* 设置辅助数组, 标记顶点是否被访问. */
    int visited[G.vexnum];

    /* 初始化辅助数组. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    /* 从 0 号元素开始遍历. */
    for (int vindex = 0; vindex < G.vexnum; ++vindex)
    {
        /* 对每个连通分量调用一次 DFS_AL. */
        if (!visited[vindex])
        {
            /* vi 还没有被访问过, 从 vi 开始 DFS_AL. */
            DFS_AL(G, vindex, Visit, visited);
        }
    }

    return;
}

void DFS_AL(ALGraph G, int vindex, Status (*Visit)(VertexType v), int *visited)
{
    /* 访问初始结点. */
    Visit(G.vertices[vindex].vex);

    /* 对 vindex 做已访问标记. */
    visited[vindex] = TRUE;

    /* 对 vindex 的尚未访问的邻接顶点 arc->adjvex 递归调用 DFS_AL. */
    for (ArcNode *arc = G.vertices[vindex].firstarc; arc != NULL; arc = arc->nextarc)
    {
        if (!visited[vindex])
        {
            DFS_AL(G, arc->adjvex, Visit, visited);
        }
    }

    return;
}

void PrintGraph_AL(ALGraph G)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        /* 打印顶点表顶点. */
        printf("V%d------>", G.vertices[i].vex);

        /* p 指向第 i 个顶点边表 (链表) 的第一个结点 (头结点). */
        ArcNode *p = G.vertices[i].firstarc;

        /* 循环输出边表结点指向的顶点的位置. */
        while (p)
        {
            /**
             * p->adjvex 是图中结点在数据结构 (顶点表) 存储的位置的下标, 要获得
             * 其对应的真正的图中的结点, 应该把 p->adjvex 作为下标去顶点表中寻找
             * 顶点表中存储的真正的结点.
             */
            printf("V%d->", G.vertices[p->adjvex].vex);

            p = p->nextarc;
        }

        printf("\n");
    }

    return;
}
