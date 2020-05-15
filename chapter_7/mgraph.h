#include "predefconst.h"
#include <stdio.h>

#define INFINITY __INT_MAX__
#define MAX_VERTEX_NUM 20

typedef enum GraphType
{
    DG,  // Digraph
    DN,  // Dinet
    UDG, // Undigraph
    UDN  // Undinet
} GraphType;

typedef int VRType; // vertex relation type

typedef int VertexType;

typedef struct ArcCell
{
    VRType adj;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM]; // vertex vector
    AdjMatrix arcs;                  // adjacency matrix
    int vexnum, arcnum;
    GraphType type;
} MGraph;

Status CreateGraph(MGraph *G);
Status CreateDG(MGraph *G);
Status CreateDN(MGraph *G);
Status CreateUDG(MGraph *G);
Status CreateUDN(MGraph *G);
VertexType LocateVex(MGraph G, VertexType v);
int FirstVex(MGraph G, int v);
int NextVex(MGraph G, int v, int w);
void PrintAdjMatrix(MGraph G);
void DFSTraverse(MGraph G, void (*Visit)(int v));
void DFS(MGraph, int v, void (*Visit)(int v), int visited[]);

Status CreateGraph(MGraph *G)
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

Status CreateDG(MGraph *G)
{
    printf("enter vertex and arc number of graph: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    printf("enter vertex vector of graph: ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", (&G->vexs[i]));
    }

    for (int i = 0; i < G->vexnum; ++i)
    {
        for (int j = 0; j < G->vexnum; ++j)
        {
            G->arcs[i][j].adj = INFINITY;
        }
    }

    printf("enter vertex relation:\n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        int i = LocateVex(*G, v1);
        int j = LocateVex(*G, v2);

        G->arcs[i][j].adj = weight;
    }

    return OK;
} // CreateDG

Status CreateDN(MGraph *G)
{
    return CreateDG(G);
} // CreateDN

Status CreateUDG(MGraph *G)
{
    printf("enter vertex and arc number of graph: ");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    printf("enter vertex vector of graph: ");
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

    printf("enter vertex relation:\n");
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
} // CreateUDG

Status CreateUDN(MGraph *G)
{
    return CreateUDG(G);
} // CreateUDN

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
} // LocateVex

// 在图 G 中寻找顶点 v 的第一条弧
int FirstVex(MGraph G, int v)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.arcs[v][i].adj != INFINITY)
        {
            return i;
        }
    }

    return ERROR;
} // FirstVex

// 在图 G 中，寻找顶点 v 的弧 w 的下一条弧
int NextVex(MGraph G, int v, int w)
{
    for (int i = w + 1; i < G.vexnum; ++i)
    {
        if (G.arcs[v][i].adj != INFINITY)
        {
            return i;
        }
    }

    return ERROR;
} // NextVex

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
} // PrintAdjMatrix

void DFSTraverse(MGraph G, void (*Visit)(int v))
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

void DFS(MGraph G, int v, void (*Visit)(int v), int visited[])
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
} // DFS