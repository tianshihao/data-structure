/**
 * @file mgraph.c
 * @author tianshihao
 * @brief 邻接矩阵
 * @version 0.1
 * @date 2020-09-12
 * @copyright Copyright (c) 2020
 */

#include <chapter7/mgraph/mgraph.h>

Status CreateGraph_M(MGraph *G)
{
    printf("Enter graph's type (1: DG, 2: DN, 3: UDG, 4: UDN): ");
    scanf("%u", &G->type);

    switch (G->type)
    {
    case DG:
        return CreateDG_M(G);
    case DN:
        return CreateDN_M(G);
    case UDG:
        return CreateUDG_M(G);
    case UDN:
        return CreateUDN_M(G);
    default:
        return ERROR;
    }

    return OK;
}

Status CreateDG_M(MGraph *G)
{
    printf("Enter vertex number of graph: ");
    scanf("%d", &G->vexnum);
    printf("Enter arc number of graph: ");
    scanf("%d", &G->arcnum);

    printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", (&G->vexs[i]));
    }

    /* 初始化有向图. */
    for (int i = 0; i < G->vexnum; ++i)
    {
        for (int j = 0; j < G->vexnum; ++j)
        {
            G->arcs[i][j].adj = INFINITY;
        }
    }

    printf("Enter vertex relation (e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.): \n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        int i = LocateVex(*G, v1);
        int j = LocateVex(*G, v2);

        G->arcs[i][j].adj = weight;
    }

    return OK;
}

Status CreateDN_M(MGraph *G)
{
    return CreateDG_M(G);
}

Status CreateUDG_M(MGraph *G)
{
    printf("Enter vertex number of graph: ");
    scanf("%d", &G->vexnum);
    printf("Enter arc number of graph: ");
    scanf("%d", &G->arcnum);

    printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", &G->vexs[i]);
    }

    for (int i = 0; i < G->vexnum; ++i)
    {
        for (int j = 0; j < G->vexnum; ++j)
        {
            G->arcs[i][j].adj = INFINITY;
        }
    }

    printf("Enter vertex relation (e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.): \n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        int i = LocateVex(*G, v1);
        int j = LocateVex(*G, v2);

        G->arcs[i][j].adj = weight;

        G->arcs[j][i].adj = G->arcs[i][j].adj;
    }

    return OK;
}

Status CreateUDN_M(MGraph *G)
{
    return CreateUDG_M(G);
}

VertexType LocateVex(MGraph G, VertexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vexs[i] == v)
        {
            return i;
        }
    }
    return 0;
}

VertexType FirstVex(MGraph G, VertexType v)
{
    /* 检查邻接矩阵的第 v 行. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        /* 若 v 和 i 之间既相连通, 权值也不为无穷. */
        if (G.arcs[v][i].adj != 0 && G.arcs[v][i].adj != INFINITY)
        {
            /* 则返回顶点 i. */
            return i;
        }
    }

    return -1;
}

VertexType NextVex(MGraph G, VertexType v, int w)
{
    /* 在顶点 v 的临接结点中找 w 之后的临接结点. */
    /* 搜索临接矩阵第 v 行. */
    for (int i = w + 1; i < G.vexnum; ++i)
    {
        /* 若 v 和 i 之间既相连通, 权值也不为无穷. */
        if (G.arcs[v][i].adj != 0 && G.arcs[v][i].adj != INFINITY)
        {
            /* 则返回顶点 i. */
            return i;
        }
    }

    return -1;
}

void PrintAdjMatrix(MGraph G)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
            if (G.arcs[i][j].adj == INFINITY)
            {
                printf("0\t");
            }
            else
            {
                printf("%d\t", G.arcs[i][j].adj);
            }
        }

        printf("\n");
    }
}

void BFSTraverse_M(MGraph G, Status (*Visit)(VertexType v))
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
    for (int v = 0; v < G.vexnum; ++v)
    {
        /* 对每个连通分量调用一次 BFS. */
        if (!visited[v])
        {
            /* vi 未访问过, 从 vi 开始 BFS. */
            BFS(G, v, Visit, visited, &Q);
        }
    }

    return;
}

void BFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited, SqQueue *Q)
{
    /* 访问初始顶点 v. */
    Visit(G.vexs[v]);

    /* 对 v 做已访问标记. */
    visited[v] = TRUE;

    /* 顶点 v 入队列.*/
    EnQueue_Sq(Q, v);

    while (!QueueEmpty_Sq(*Q))
    {
        /* 顶点 v 出队列.*/
        DeQueue_Sq(Q, &v);

        /* 检测 v 的所有邻接点. */
        for (VertexType w = FirstVex(G, v); w >= 0; w = NextVex(G, v, w))
        {
            /* w 为 v 的尚未访问的邻接点. */
            if (!visited[w])
            {
                /* 访问顶点 w. */
                Visit(G.vexs[w]);

                /* 对 w 做已访问标记. */
                visited[w] = TRUE;

                /* 顶点 w 入队列. */
                EnQueue_Sq(Q, w);
            }
        }
    }

    return;
}

void DFSTraverse_M(MGraph G, Status (*Visit)(VertexType v))
{
    /* 设置辅助数组, 标记顶点是否被访问. */
    int visited[G.vexnum];

    /* 初始化辅助数组. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    /* 从 0 号顶点开始遍历. */
    for (int v = 0; v < G.vexnum; ++v)
    {
        /* 对每个连通分量调用一次 DFS. */
        if (!visited[v])
        {
            /* vi 未访问过, 从 vi 开始 DFS. */
            DFS(G, v, Visit, visited);
        }
    }

    return;
}

void DFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited)
{
    /* 访问初始顶点 v. */
    Visit(G.vexs[v]);

    /* 对 v 做已访问标记. */
    visited[v] = TRUE;

    /* 检测 v 的所有邻接点. */
    for (int w = FirstVex(G, v); w >= 0; w = NextVex(G, v, w))
    {
        /* w 为 v 尚未访问过的邻接点. */
        if (!visited[w])
        {
            /* w 未访问过, 从 w 开始 DFS. */
            DFS(G, w, Visit, visited);
        }
    }

    return;
}
