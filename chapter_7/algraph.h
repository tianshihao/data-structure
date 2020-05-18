#include "predefconst.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

typedef int InfoType;

typedef int VertexType;

typedef enum GraphType
{
    DG,
    DN,
    UDG,
    UDN
} GraphType;

typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    InfoType info;
} ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph
{
    AdjList vertices;
    int vexnum, arcnum;
    GraphType type;
} ALGraph;

Status CreateGraph(ALGraph *G);
Status CreateDG(ALGraph *G);
Status CreateDN(ALGraph *G);
Status CreateUDG(ALGraph *G);
Status CreateUDN(ALGraph *G);
Status InsertArcNode(ALGraph *G, int v1, int v2, int weight);
void PrintAdjacencyList(ALGraph G);
void DFSTraverse(ALGraph G, Status (*Visit)(int v));
void DFS(ALGraph G, int v, Status (*Visit)(int v), int visited[]);

Status CreateGraph(ALGraph *G)
{
    printf("enter graph's type: ");
    scanf("%u", &G->type);

    switch (G->type)
    {
    case DG:
        return CreateDG(G);
    case DN:
        return CreateDN(G);
    case UDG:
        return CreateUDG(G);
    case UDN:
        return CreateUDN(G);
    default:
        return ERROR;
    }

    return OK;
} // CreateGraph

Status CreateDG(ALGraph *G)
{
    printf("enter vertex and arc number of graph: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    printf("enter vertex vector of graph: ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }

    printf("enter vertex relation:\n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        InsertArcNode(G, v1, v2, weight);
    }

    return OK;
} // CreateDG

Status CreateDN(ALGraph *G)
{
    return CreateDG(G);
} // CreateDN

Status CreateUDG(ALGraph *G)
{
    printf("enter vertex and arc number of graph: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    printf("enter vertex vector of graph: ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
    }

    printf("enter vertex relation:\n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        InsertArcNode(G, v1, v2, weight);
        InsertArcNode(G, v2, v1, weight);
    }

    return OK;
} // CreateUDG

Status CreateUDN(ALGraph *G)
{
    return CreateUDG(G);
} // CreateUDN

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
} // PrintAdjacencyList

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
} // InsertArcNode

void DFSTraverse(ALGraph G, Status (*Visit)(int v))
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
} // DFSTraverse

void DFS(ALGraph G, int v, Status (*Visit)(int v), int visited[])
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
} // DFS