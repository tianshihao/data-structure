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
        scanf("%d", &G->vertices[i].data);
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
        scanf("%d", &G->vertices[i].data);
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

void PrintAdjacencyList(ALGraph G)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        printf("V%d→", G.vertices[i].data);
        ArcNode *p = G.vertices[i].firstarc;

        while (p)
        {
            printf("%d→", p->adjvex);
            p = p->nextarc;
        }

        printf("\n");
    }

    return;
}

// 在顶点 v 的邻接表的表尾添加弧结点 ArcNode
Status InsertArcNode(ALGraph *G, int v1, int v2, int weight)
{
    // ArcNode *p = G->vertices[v1 - 1].firstarc;

    if (G->vertices[v1 - 1].firstarc == NULL)
    {
        G->vertices[v1 - 1].firstarc = malloc(sizeof(ArcNode));
        // adjvex 是邻接点的位置
        // v2 是结点编号
        // v2 - 1 是结点 v2 在邻接表中的索引
        G->vertices[v1 - 1].firstarc->adjvex = v2 - 1;
        G->vertices[v1 - 1].firstarc->info = weight;
        G->vertices[v1 - 1].firstarc->nextarc = NULL;
    }
    else
    {
        ArcNode *p = G->vertices[v1 - 1].firstarc;

        while (p->nextarc != NULL)
        {
            p = p->nextarc;
        }

        ArcNode *newarc = malloc(sizeof(ArcNode));
        newarc->adjvex = v2 - 1;
        newarc->info = weight;
        newarc->nextarc = NULL;

        p->nextarc = newarc;
    }

    return OK;
}

void DFSTraverse_AL(ALGraph G, Status (*Visit)(int v))
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

void DFS(ALGraph G, int v, Status (*Visit)(int v), int *visited)
{
    visited[v] = TRUE; // 标记顶点 v 已被访问

    Visit(v); // 访问顶点 v

    // 对 v 的尚未访问的邻接顶点 w 递归调用DFS
    for (ArcNode *w = G.vertices[v].firstarc; w != NULL; w = w->nextarc)
    {
        if (!visited[w->adjvex])
        {
            DFS(G, w->adjvex, Visit, visited);
        }
    }

    return;
}

void BFSTraverse_AL(ALGraph G, Status (*Visit)(int v))
{
    int visited[G.vexnum];

    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    SqQueue Q;
    InitSqQueue(&Q);

    for (int v = 0; v < G.vexnum; ++v)
    {
        if (!visited[v])
        {
            visited[v] = TRUE;
            Visit(v);

            EnSqQueue(&Q, v);

            while (!SqQueueEmpty(Q))
            {
                int w;
                DeSqQueue(&Q, &w);

                for (ArcNode *u = G.vertices[w].firstarc; u != NULL; u = u->nextarc)
                {
                    if (!visited[u->adjvex])
                    {
                        visited[u->adjvex] = TRUE;
                        Visit(u->adjvex);
                        EnSqQueue(&Q, u->adjvex);
                    }
                }
            }
        } // if
    }

    return;
}