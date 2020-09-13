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

/**
 * @brief 顶点关系类型/权值数据类型.
 */
typedef int ArcType;

/**
 * @brief 顶点类型.
 */
typedef int VertexType;

/**
 * @brief 弧/边, 临接矩阵存储单元.
 */
typedef struct ArcCell
{
    ArcType adj;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/**
 * @brief 临接矩阵.
 */
typedef struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM]; /* vertex vector, 顶点向量, 顶点表 */
    AdjMatrix arcs;                  /* adjacency matrix, 临接矩阵. */
    int vexnum, arcnum;              /* 顶点数, 弧数. */
    GraphType type;                  /* 图类型. */
} MGraph;

/**
 * @brief 创建图.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR. 
 */
Status CreateGraph_M(MGraph *G);

/**
 * @brief 创建有向图.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateDG_M(MGraph *G);

/**
 * @brief 创建有向网.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateDN_M(MGraph *G);

/**
 * @brief 创建无向图.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateUDG_M(MGraph *G);

/**
 * @brief 创建无向网.
 * @param G 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.  
 */
Status CreateUDN_M(MGraph *G);

/**
 * @brief 定位顶点 v 在图中的位置.
 * @param G 图.
 * @param v 要定位的顶点.
 * @return VertexType 顶点在图中的位置.
 */
VertexType LocateVex(MGraph G, VertexType v);

/**
 * @brief 在图 G 中寻找顶点 v 的第一个邻接点, 没有则返回 -1.
 * @param G 图.
 * @param v 顶点.
 * @return VertexType 顶点 v 的第一个邻接点.
 */
VertexType FirstVex(MGraph G, VertexType v);

/**
 * @brief 在图 G 中，寻找顶点 v 相对于 w 的下一个邻接点. 若 w 是 v 的最后一个
 * 临接结点, 则返回 -1.
 * @param G 图.
 * @param v 当前顶点.
 * @param w 下一个顶点.
 * @return VertexType 当前顶点 v 的下一个顶点 w.
 */
VertexType NextVex(MGraph G, VertexType v, int w);

/**
 * @brief 打印邻接矩阵.
 * @param G 图.
 */
void PrintAdjMatrix(MGraph G);

/**
 * @brief 宽度优先搜索.
 * @param G 图.
 * @param Visit 访问函数.
 */
void BFSTraverse(MGraph G, Status (*Visit)(VertexType v));

/**
 * @brief 从顶点 v 出发, 广度优先遍历图 G.
 * @param G 图.
 * @param v 顶点.
 * @param Visit 访问函数.
 * @param visited 辅助数组.
 * @param Q 顺序队列.
 */
void BFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited, SqQueue *Q);

/**
 * @brief 深度优先搜索.
 * @param G 图.
 * @param Visit 访问函数.
 */
void DFSTraverse(MGraph G, Status (*Visit)(VertexType v));

/**
 * @brief 从顶点 v 出发, 深度优先遍历图 G.
 * @param G 图.
 * @param v 顶点.
 * @param Visit 访问函数.
 * @param visited 辅助数组.
 */
void DFS(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited);

#endif /* MGRAPH_H */
