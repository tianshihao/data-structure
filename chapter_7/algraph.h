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
    return OK;
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
    return OK;
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

Status InsertArcNode(ALGraph *G, int v1, int v2, int weight)
{
    ArcNode *arc = malloc(sizeof(ArcNode));

    arc->adjvex = v2 - 1;
    arc->info = weight;

    arc->nextarc = G->vertices[v1 - 1].firstarc;
    G->vertices[v1 - 1].firstarc = arc;

    return OK;
} // InsertArcNode