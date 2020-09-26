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
#include <chapter7/graphtype.h>
#include <chapter7/mgraph/sqqueue.h>
#include <stdio.h>
#include <stdlib.h>

/* 定义最大值. */
#define INFINITY __INT_MAX__

/* 图中顶点数目的最大值. */
#define MAX_VERTEX_NUM 20

/**
 * @brief 顶点关系类型/权值数据类型.
 */
typedef int WeightType;

/**
 * @brief 顶点类型.
 */
typedef int VertexType;

/**
 * @brief 弧/边结点, 临接矩阵存储单元. 不存在权值为负的边.
 */
typedef struct ArcCell
{
    WeightType weight; /* 边权值. */
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/**
 * @brief 临接矩阵.
 */
typedef struct MGraph
{
    VertexType vertices[MAX_VERTEX_NUM]; /* vertex vector, 顶点向量, 顶点表 */
    AdjMatrix arcs;                      /* adjacency matrix, 临接矩阵. */
    int vexnum, arcnum;                  /* 顶点数, 弧数. */
    GraphType type;                      /* 图类型. */
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
VertexType LocateVex_M(MGraph G, VertexType v);

/**
 * @brief 在图 G 中寻找顶点 v 的第一个邻接点, 没有则返回 -1.
 * @param G 图.
 * @param v 顶点.
 * @return VertexType 顶点 v 的第一个邻接点.
 */
VertexType FirstVex_M(MGraph G, VertexType v);

/**
 * @brief 在图 G 中，寻找顶点 v 相对于 w 的下一个邻接点. 若 w 是 v 的最后一个
 * 临接结点, 则返回 -1.
 * @param G 图.
 * @param v 当前顶点.
 * @param w 下一个顶点.
 * @return VertexType 当前顶点 v 的下一个顶点 w.
 */
VertexType NextVex_M(MGraph G, VertexType v, int w);

/**
 * @brief 宽度优先搜索.
 * @param G 图.
 * @param Visit 访问函数.
 */
void BFSTraverse_M(MGraph G, Status (*Visit)(VertexType v));

/**
 * @brief 从顶点 v 出发, 广度优先遍历图 G.
 * @param G 图.
 * @param v 顶点.
 * @param Visit 访问函数.
 * @param visited 辅助数组.
 * @param Q 顺序队列.
 */
void BFS_M(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited, SqQueue *Q);

/**
 * @brief 深度优先搜索.
 * @param G 图.
 * @param Visit 访问函数.
 */
void DFSTraverse_M(MGraph G, Status (*Visit)(VertexType v));

/**
 * @brief 从顶点 v 出发, 深度优先遍历图 G.
 * @param G 图.
 * @param v 顶点.
 * @param Visit 访问函数.
 * @param visited 辅助数组.
 */
void DFS_M(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited);

/**
 * @brief 迪杰斯特拉算法, 计算源点 source 到其余各点的最短距离.
 * @param G 图.
 * @param source 源点. 
 */
void Dijkstra_M(MGraph G, VertexType source);

/**
 * @brief 弗洛伊德算法，计算各点之间的最短路径.
 * @param G 图.
 */
void Floyd_M(MGraph G);

/**
 * @brief 打印邻接矩阵.
 * @param G 图.
 */
void PrintGraph_M(MGraph G);

#endif /* MGRAPH_H */
