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

#include <graph/algraph/sqqueue.h>
#include <graph/graphtype.h>
#include <status.h>

/**
 * 1------------------------2
 * |                      / |   \
 * |                    /   |       \
 * |                 /      |            \
 * |              /         |                 \
 * |            /           |                     3
 * |          /             |                 /
 * |       /                |            /
 * |    /                   |       /
 * | /                      |   /
 * 5------------------------4
 * 
 * 这张图使用邻接表存储的数据结构为
 * |1|----------------------->|2|->|5|
 * |2|----------------------->|1|->|3|->|4|->|5|
 * |3|----------------------->|2|->|4|
 * |4|----------------------->|2|->|5|->|3|
 * |5|----------------------->|4|->|1|->|2|
 * ⬆        ->                 ⬆
 * 顶点表     后面的边表       第一个元素相当于链表头结点
 * 顺序存储   链式存储         被称为firstarc
 * 类似数组   类似链表         存储在顶点表结点中
 * 一行就是一个顶点表结点      箭头上可以带权值 weight.
 *                             这个链表中每个结点代表边, 其中数字为该边指向某点.
 *                             例如第 4 行, 边表中有边结点 2, 5, 3, 代表从 4 号
 *                             结点射出了 3 条边/弧, 分别指向 2, 5, 3 号结点.
 */

/* 图中顶点数目的最大值. */
#define MAX_VERTEX_NUM 20

/**
 * @brief 顶点类型.
 */
typedef int VertexType;

/**
 * @brief 边权值.
 */
typedef int WeightType;

/**
 * @brief 弧/边结点.
 */
typedef struct ArcNode
{
    int adjvex;              /* 该弧所指向的顶点在顶点表中的位置. */
    struct ArcNode *nextarc; /* 指向下一条弧的位置. */
    WeightType weight;       /* 网络边权值. */
} ArcNode;

/**
 * @brief 顶点表结点.
 */
typedef struct VertexNode
{
    VertexType vex;    /* 顶点信息. */
    ArcNode *firstarc; /* 指向第一条依附在该顶点的弧的指针. */
} VertexNode, AdjList[MAX_VERTEX_NUM];

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

/**
 * @brief 计算顶点 v 在顶点表中对应的下标.
 * @param G 图.
 * @param v 要定位的顶点.
 * @return VertexType 顶点 v 在顶点表中的下标.
 */
VertexType LocateVex_AL(ALGraph G, VertexType v);

/**
 * @brief 向邻接表 G 中插入新的边 v1->v2, 边权值为 weight. 在顶点表中的 v1 的边表
 * 的表尾添加边/弧结点 ArcNode, 边结点的指向的顶点为 v2.
 * @param G 图.
 * @param v1 射出结点.
 * @param v2 射入结点.
 * @param weight 边权值.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作成功返回 ERROR. 
 */
Status InsertArcNode(ALGraph *G, VertexType v1, VertexType v2, WeightType weight);

/**
 * @brief 宽度优先搜索.
 * @param G 图.
 * @param Visit 访问函数.
 */
void BFSTraverse_AL(ALGraph G, Status (*Visit)(VertexType v));

/**
 * @brief 从顶点 v 出发, 广度优先遍历图 G.
 * @param G 图.
 * @param v 顶点.
 * @param Visit 访问函数.
 * @param visited 辅助数组.
 * @param Q 顺序队列.
 */
void BFS_AL(ALGraph G, int vindex, Status (*Visit)(VertexType v), int *visited, SqQueue *Q);

/**
 * @brief 深度优先搜索.
 * @param G 图.
 * @param Visit 访问函数.
 */
void DFSTraverse_AL(ALGraph G, Status (*Visit)(VertexType v));

/**
 * @brief 从顶点 v 出发, 深度优先遍历图 G.
 * @param G 图.
 * @param v 顶点.
 * @param Visit 访问函数.
 * @param visited 辅助数组.
 */
void DFS_AL(ALGraph G, int vindex, Status (*Visit)(VertexType v), int *visited);

/**
 * @brief 打印邻接表.
 * @param G 
 */
void PrintGraph_AL(ALGraph G);

#endif /* ALGRAPH_H */
