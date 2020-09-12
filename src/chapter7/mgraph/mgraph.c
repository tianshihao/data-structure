/**
 * @file mgraph.c
 * @author tianshihao
 * @brief 邻接矩阵
 * @version 0.1
 * @date 2020-09-12
 * @copyright Copyright (c) 2020
 */

#include <chapter7/mgraph/mgraph.h>
#include <chapter7/mgraph/sqqueue.h>

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

    // 初始化有向图.
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

    printf("Enter vertex vector of graph: ");
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

    printf("Enter vertex relation:\n");
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

// 在图 G 中寻找顶点 v 的第一个邻接点
int FirstVex(MGraph G, VertexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.arcs[v][i].adj != INFINITY)
        {
            return i;
        }
    }

    return ERROR;
}

// 在图 G 中，寻找顶点 v 的下一个邻接点
int NextVex(MGraph G, VertexType v, int w)
{
    for (int i = w + 1; i < G.vexnum; ++i)
    {
        if (G.arcs[v][i].adj != INFINITY)
        {
            return i;
        }
    }

    return ERROR;
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

void DFSTraverse(MGraph G, Status (*Visit)(VertexType v))
{
    int visited[G.vexnum];

    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    for (int v = 0; v < G.vexnum; ++v)
    {
        if (!visited[v])
        {
            DFS(G, v, Visit, visited);
        }
    }

    return;
}

void DFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int visited[])
{
    visited[v] = TRUE;

    Visit(G.vexs[v]);

    for (int w = FirstVex(G, v); w != 0; w = NextVex(G, v, w))
    {
        if (!visited[w])
        {
            DFS(G, w, Visit, visited);
        }
    }

    return;
}

void BFSTraverse(MGraph G, Status (*Visit)(VertexType v))
{
    // 设置辅助数组, 标记顶点是否被访问.
    int visited[G.vexnum];

    // 初始化辅助数组.
    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    // 顺序队列.
    SqQueue Q;

    // 队列中存放已经访问过但邻接结点未知的结点.
    InitQueue_Sq(&Q);

    for (int v = 0; v < G.vexnum; ++v)
    {
        if (!visited[v])
        {
            visited[v] = TRUE;
            Visit(G.vexs[v]);

            // 结点 v 已经访问，将其入队
            EnQueue_Sq(&Q, v);

            while (!QueueEmpty_Sq(Q))
            {
                int u;

                // 队头元素出队并置为u
                DeQueue_Sq(&Q, &u);

                // 访问已被访问过的结点 u 的邻接点
                for (int w = FirstVex(G, u); w != 0; w = NextVex(G, u, w))
                {
                    if (!visited[w])
                    {
                        visited[w] = TRUE;
                        Visit(G.vexs[w]);

                        EnQueue_Sq(&Q, w);
                    }
                }
            }
        } // if
    }

    return;
}

void BFS(MGraph M, VertexType v)
{
}
