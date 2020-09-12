/**
 * @file mgraph.h
 * @author tianshihao4944@126.com
 * @brief 邻接矩阵
 * @version 0.1
 * @date 2020-09-12
 * @copyright Copyright (c) 2020
 */

#ifndef MGRAPH_H
#define MGRAPH_H

#include <chapter1/status.h>
#include <chapter7/mgraph/sqqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define INFINITY __INT_MAX__
#define MAX_VERTEX_NUM 20

/**
 * @brief 图的类型.
 */
typedef enum GraphType
{
    DG,  /* Digraph, 有向图. */
    DN,  /* Dinet, 有向网/有向带权图. */
    UDG, /* Undigraph, 无向图. */
    UDN  /* Undinet, 无向网/无向带权图. */
} GraphType;

typedef int VRType; // vertex relation type

typedef int VertexType;

/**
 * @brief 弧.
 */
typedef struct ArcCell
{
    VRType adj;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM]; /* vertex vector */
    AdjMatrix arcs;                  /* adjacency matrix */
    int vexnum, arcnum;
    GraphType type;
} MGraph;

Status CreateGraph_M(MGraph *G);
Status CreateDG_M(MGraph *G);
Status CreateDN_M(MGraph *G);
Status CreateUDG_M(MGraph *G);
Status CreateUDN_M(MGraph *G);
VertexType LocateVex(MGraph G, VertexType v);
int FirstVex(MGraph G, VertexType v);
int NextVex(MGraph G, VertexType v, int w);
void PrintAdjMatrix(MGraph G);
void DFSTraverse(MGraph G, Status (*Visit)(VertexType v));
void DFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited);
void BFSTraverse(MGraph G, Status (*Visit)(VertexType v));
void BFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited, SqQueue *Q);

#endif /* MGRAPH_H */
