/**
 * @file mgraph.h
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 邻接矩阵头文件.
 * @version 0.2
 * @date 2020-12-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef MGRAPH_H
#define MGRAPH_H

#include <graphtype.h>
#include <sqqueue.h>
#include <sqstack.h>
#include <status.h>

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
typedef struct ArcCell {
  // 边权值.
  WeightType weight;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/**
 * @brief 临接矩阵存储的图.
 */
typedef struct MGraph {
  /* vertex vector, 顶点向量, 顶点表 */
  VertexType vertices[MAX_VERTEX_NUM];
  /* adjacency matrix, 临接矩阵. */
  AdjMatrix arcs;
  /* 顶点数, 弧数. */
  int vex_num, arc_num;
  /* 图类型. */
  GraphType type;
} MGraph;

/**
 * @brief 创建图.
 * @param pG 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.
 */
Status CreateGraphM(MGraph *pG);

/**
 * @brief 创建有向图.
 * @param pG 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.
 */
Status CreateDGM(MGraph *pG);

/**
 * @brief 创建有向网.
 * @param pG 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.
 */
Status CreateDNM(MGraph *pG);

/**
 * @brief 创建无向图.
 * @param pG 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.
 */
Status CreateUDGM(MGraph *pG);

/**
 * @brief 创建无向网.
 * @param pG 指向空图的指针.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR.
 */
Status CreateUDNM(MGraph *pG);

/**
 * @brief 定位顶点 vex 在图中的位置.
 * @param G 图.
 * @param vex 要定位的顶点.
 * @return int 返回顶点 vex 在图的顶点表中的索引, 顶点表中不存在则返回 -1.
 */
int LocateVexM(MGraph G, VertexType vex);

/**
 * @brief 在图 G 中寻找顶点 G.vertices[vexIndex] 的第一个邻接点, 没有则返回 -1.
 * @param G 图.
 * @param vexIndex 顶点在顶点表中的索引.
 * @return int 返回顶点 G.vertices[vexIndex] 的第一个邻接点的在顶点表中的索引.
 */
int FirstVexM(MGraph G, int vexIndex);

/**
 * @brief 在图 G 中，寻找位于顶点 G.vertices[vexIndex] 之邻接点
 * G.vertices[nextIndex] 后的又一邻接点. 若 G.vertices[nextIndex] 是
 * G.vertices[vexIndex] 的最后一个临接结点, 则返回 -1.
 * @param G 图.
 * @param vexIndex 当前顶点在顶点表中的索引.
 * @param nextIndex 下一个顶点的在顶点表中的索引.
 * @return int 所求顶点在顶点表中的索引.
 */
int NextVexM(MGraph G, int vexIndex, int nextIndex);

/**
 * @brief 宽度优先搜索.
 * @param G 图.
 * @param VisitFunc 访问函数.
 */
void BFSTraverseM(MGraph G, Status (*VisitFunc)(VertexType vex));

/**
 * @brief 从顶点 G.vertices[vexIndex] 出发, 广度优先遍历图 G.
 * @param G 图.
 * @param vexIndex 顶点在顶点表中的索引.
 * @param VisitFunc 访问函数.
 * @param visited 辅助数组.
 * @param Q 顺序队列.
 */
void BFSM(MGraph G, int vexIndex, Status (*VisitFunc)(VertexType vex),
          int *visited, SqQueue *pQ);

/**
 * @brief 深度优先搜索.
 * @param G 图.
 * @param VisitFunc 访问函数.
 */
void DFSTraverseM(MGraph G, Status (*VisitFunc)(VertexType vex));

/**
 * @brief 从顶点 G.vertices[vexIndex] 出发, 深度优先遍历图 G.
 * @param G 图.
 * @param vexIndex 顶点在顶点表中的索引.
 * @param VisitFunc 访问函数.
 * @param visited 辅助数组.
 */
void DFSM(MGraph G, int vexIndex, Status (*VisitFunc)(VertexType vex),
          int *visited);

/**
 * @brief 从顶点 G.vertices[vexIndex] 出发, 以非递归的方式深度优先遍历图 G.
 * @param G 图.
 * @param vexIndex 顶点在顶点表中的索引.
 * @param VisitFunc 访问函数.
 * @param visited 辅助数组.
 */
void DFSMNoRec(MGraph G, int v, Status (*VisitFunc)(VertexType vex),
               int *visited);

/**
 * @brief 迪杰斯特拉算法, 计算源点 source 到其余各点的最短距离.
 * @param G 图.
 * @param source 源点.
 */
void DijkstraM(MGraph G, VertexType source);

/**
 * @brief 弗洛伊德算法，计算各点之间的最短路径.
 * @param G 图.
 */
void FloydM(MGraph G);

/**
 * @brief 打印邻接矩阵.
 * @param G 图.
 */
void PrintGraphM(MGraph G);

#endif /* MGRAPH_H */
