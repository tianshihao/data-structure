/**
 * @file algraph.h
 * @author tianshihao4944@126.com
 * @brief 邻接表.
 * @version 0.1
 * @date 2020-09-13
 * @copyright Copyright (c) 2020
 */

#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <chapter1/status.h>
#include <chapter7/algraph/sqqueue.h>
#include <stdio.h>
#include <stdlib.h>

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

/**
 * @brief 顶点存储的信息.
 */
typedef int InfoType;

/**
 * @brief 顶点类型.
 */
typedef int VertexType;

/**
 * @brief 弧/边.
 */
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    InfoType info;
} ArcNode;

/**
 * @brief 顶点表.
 */
typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

/**
 * @brief 邻接表.
 */
typedef struct ALGraph
{
    AdjList vertices;   /* 顶点表. */
    int vexnum, arcnum; /* 顶点数, 弧数. */
    GraphType type;     /* 图类型. */
} ALGraph;

/**
 * @brief 创建图.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR. 
 */
Status CreateGraph_AL(ALGraph *G);

/**
 * @brief 创建有向图.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateDG_AL(ALGraph *G);

/**
 * @brief 创建有向网.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateDN_AL(ALGraph *G);

/**
 * @brief 创建无向图.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateUDG_AL(ALGraph *G);

/**
 * @brief 创建无向网.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateUDN_AL(ALGraph *G);

Status InsertArcNode(ALGraph *G, VertexType v1, VertexType v2, int weight);
void PrintAdjacencyList(ALGraph G);
void BFSTraverse_AL(ALGraph G, Status (*Visit)(VertexType v));
void DFSTraverse_AL(ALGraph G, Status (*Visit)(VertexType v));
void DFS(ALGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited);

#endif // ALGRAPH_H
