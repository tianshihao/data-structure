﻿/**
 * @file mgraph.c
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 邻接矩阵方法实现.
 * @version 0.2
 * @date 2020-12-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <mgraph.h>

Status CreateGraphM(MGraph *p_graph) {
  printf("Enter graph's type (1: DG, 2: DN, 3: UDG, 4: UDN): ");
  /* 输入枚举类型时, 使用 %u 作为占位符. */
  scanf("%u", &p_graph->type);

  switch (p_graph->type) {
    case DG:
      return CreateDGM(p_graph);
    case DN:
      return CreateDNM(p_graph);
    case UDG:
      return CreateUDGM(p_graph);
    case UDN:
      return CreateUDNM(p_graph);
    default:
      return ERROR;
  }

  return OK;
}

Status CreateDGM(MGraph *p_graph) {
  printf("Enter vertex number of graph: ");
  scanf("%d", &p_graph->vex_num);
  printf("Enter arc number of graph: ");
  scanf("%d", &p_graph->arc_num);

  printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
  for (int i = 0; i < p_graph->vex_num; ++i) {
    scanf("%d", (&p_graph->vertices[i]));
  }

  /* 初始化有向图. */
  for (int i = 0; i < p_graph->vex_num; ++i) {
    for (int j = 0; j < p_graph->vex_num; ++j) {
      /* 自己到自己的距离为 0. */
      if (i == j) {
        p_graph->arcs[i][j].weight = 0;
      } else {
        p_graph->arcs[i][j].weight = INFINITY;
      }
    }
  }

  printf(
      "Enter vertex relation\n",
      "e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.\n"
      ": \n");
  for (int k = 0; k < p_graph->arc_num; ++k) {
    int v1, v2, weight;

    scanf("%d %d %d", &v1, &v2, &weight);

    int i = LocateVexM(*p_graph, v1);
    int j = LocateVexM(*p_graph, v2);

    p_graph->arcs[i][j].weight = weight;
  }

  return OK;
}

Status CreateDNM(MGraph *p_graph) { return CreateDGM(p_graph); }

Status CreateUDGM(MGraph *p_graph) {
  printf("Enter vertex number of graph: ");
  scanf("%d", &p_graph->vex_num);
  printf("Enter arc number of graph: ");
  scanf("%d", &p_graph->arc_num);

  printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
  for (int i = 0; i < p_graph->vex_num; ++i) {
    scanf("%d", &p_graph->vertices[i]);
  }

  for (int i = 0; i < p_graph->vex_num; ++i) {
    for (int j = 0; j < p_graph->vex_num; ++j) {
      /* 自己到自己的距离为 0. */
      if (i == j) {
        p_graph->arcs[i][j].weight = 0;
      } else {
        p_graph->arcs[i][j].weight = INFINITY;
      }
    }
  }

  printf(
      "Enter vertex relation\n",
      "e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.\n"
      ": \n");
  for (int k = 0; k < p_graph->arc_num; ++k) {
    int v1, v2, weight;

    scanf("%d %d %d", &v1, &v2, &weight);

    int i = LocateVexM(*p_graph, v1);
    int j = LocateVexM(*p_graph, v2);

    /* 无向图/网是关于主对角线对称的. */
    p_graph->arcs[i][j].weight = weight;
    p_graph->arcs[j][i].weight = p_graph->arcs[i][j].weight;
  }

  return OK;
}

Status CreateUDNM(MGraph *p_graph) { return CreateUDGM(p_graph); }

int LocateVexM(MGraph G, VertexType vex) {
  for (int i = 0; i < G.vex_num; ++i) {
    /* 在顶点表中搜索顶点 vex. */
    if (G.vertices[i] == vex) {
      return i;
    }
  }

  return -1;
}

int FirstVexM(MGraph G, int vexIndex) {
  /* 检查邻接矩阵的第 vexIndex 行. */
  for (int i = 0; i < G.vex_num; ++i) {
    /* 若 vexIndex 和 i 之间既相连通, 权值也不为无穷. */
    if (G.arcs[vexIndex][i].weight != 0 &&
        G.arcs[vexIndex][i].weight != INFINITY) {
      /* 则返回索引 i. */
      return i;
    }
  }

  return -1;
}

int NextVexM(MGraph G, int vexIndex, int nextIndex) {
  /* 在顶点 G.vertices[vexIndex] 的临接结点中找 G.vertices[nextIndex]
   * 之后的临接结点. */
  /* 搜索临接矩阵第 vexIndex 行. */
  for (int i = nextIndex + 1; i < G.vex_num; ++i) {
    /* 若 vexIndex 和 i 之间既相连通, 权值也不为无穷. */
    if (G.arcs[vexIndex][i].weight != 0 &&
        G.arcs[vexIndex][i].weight != INFINITY) {
      /* 则返回索引 i. */
      return i;
    }
  }

  return -1;
}

void BFSTraverseM(MGraph G, Status (*VisitFunc)(VertexType vex)) {
  /* 设置辅助数组, 标记顶点是否被访问. */
  int visited[G.vex_num];

  /* 初始化辅助数组. */
  for (int i = 0; i < G.vex_num; ++i) {
    visited[i] = FALSE;
  }

  /* 顺序队列. */
  SqQueue Q;

  /* 队列中存放已经访问过但邻接结点未知的结点. */
  InitQueue_Sq(&Q);

  /* 从 0 号顶点开始遍历. */
  for (int vexIndex = 0; vexIndex < G.vex_num; ++vexIndex) {
    /* 对每个连通分量调用一次 BFSM. */
    if (!visited[vexIndex]) {
      /* vexIndex 未访问过, 从 vexIndex 开始 BFSM. */
      BFSM(G, vexIndex, VisitFunc, visited, &Q);
    }
  }

  return;
}

void BFSM(MGraph G, int vexIndex, Status (*VisitFunc)(VertexType vex),
          int *visited, SqQueue *pQ) {
  /* 访问初始顶点 vexIndex. */
  VisitFunc(G.vertices[vexIndex]);

  /* 对 vexIndex 做已访问标记. */
  visited[vexIndex] = TRUE;

  /* 顶点 vexIndex 入队列.*/
  EnQueue_Sq(pQ, vexIndex);

  while (!QueueEmpty_Sq(*pQ)) {
    /* 顶点 vexIndex 出队列.*/
    DeQueue_Sq(pQ, &vexIndex);

    /* 检测 vexIndex 的所有邻接点. */
    for (int nextIndex = FirstVexM(G, vexIndex); nextIndex >= 0;
         nextIndex = NextVexM(G, vexIndex, nextIndex)) {
      /* 若 vexIndex 的邻接点 nextIndex 还没有被访问过. */
      if (!visited[nextIndex]) {
        /* 访问顶点 nextIndex. */
        VisitFunc(G.vertices[nextIndex]);

        /* 对 nextIndex 做已访问标记. */
        visited[nextIndex] = TRUE;

        /* 顶点 nextIndex 入队列. */
        EnQueue_Sq(pQ, nextIndex);
      }
    }
  }

  return;
}

void DFSTraverseM(MGraph G, Status (*VisitFunc)(VertexType vex)) {
  /* 设置辅助数组, 标记顶点是否被访问. */
  int visited[G.vex_num];

  /* 初始化辅助数组. */
  for (int i = 0; i < G.vex_num; ++i) {
    visited[i] = FALSE;
  }

  /* 从 0 号顶点开始遍历. */
  for (int vexIndex = 0; vexIndex < G.vex_num; ++vexIndex) {
    /* 对每个连通分量调用一次 DFSM. */
    if (!visited[vexIndex]) {
      /* vexIndex 还没有被访问过, 从 vexIndex 开始 DFSM. */
      DFSM(G, vexIndex, VisitFunc, visited);
    }
  }

  return;
}

void DFSM(MGraph G, int vexIndex, Status (*VisitFunc)(VertexType vex),
          int *visited) {
  /* 访问初始顶点 vexIndex. */
  VisitFunc(G.vertices[vexIndex]);

  /* 对 vexIndex 做已访问标记. */
  visited[vexIndex] = TRUE;

  /* 检测 vexIndex 的所有邻接点. */
  for (int nextIndex = FirstVexM(G, vexIndex); nextIndex >= 0;
       nextIndex = NextVexM(G, vexIndex, nextIndex)) {
    /* nextIndex 为 vexIndex 尚未访问过的邻接点. */
    if (!visited[nextIndex]) {
      /* nextIndex 未访问过, 从 nextIndex 开始 DFSM. */
      DFSM(G, nextIndex, VisitFunc, visited);
    }
  }

  return;
}

// void DFSMNoRec(MGraph G, int v, Status (*VisitFunc)(VertexType v), int
// *visited)
// {
//     /**/
//     SqStack S;
//     InitStack_Sq(&S);
//     Push_Sq(&S, v);
//     while (!StackEmptySq(S))
//     {
//         int k = Pop_Sq(&S, k);
//         VisitFunc(G.vertices[k]);
//         for (int w = FirstVexM(G, k); k >= 0; w = NextVexM(G, k, w))
//         {
//             if (!visited[w])
//             {
//                 Push_Sq(&S, w);
//                 visited[w];
//             }
//         }
//     }
// }

void DijkstraM(MGraph G, VertexType source) {
  /* 源点 source 在图的顶点表中对应的索引. */
  int sourceIndex = LocateVexM(G, source);

  /**
   * ! 第一步, 初始化 S. 若 S[i] == TRUE, 说明顶点 vi 已在集合 S 中.
   */

  /* 初始化 S. 集合 S 为已经包括进来的点. */
  VertexType S[G.vex_num];
  for (int i = 0; i < G.vex_num; ++i) {
    S[i] = FALSE;
  }
  /* S 的初始元素为源点, 即 G.vertices[sourceIndex]. */
  S[sourceIndex] = TRUE;

  /**
   * 辅助数组 dist, 记录源点 source 到其它各顶点当前的最短路径长度, 它的初态
   * 为: 若从 source 到 v 有弧, 则 dist[v] 为弧上的权值; 否则置 dist[v] =
   * INFINITY. dist[i] = G.arcs[sourceIndex][i].weight.
   */
  WeightType dist[G.vex_num];

  /**
   * 在创建图的时候已经考虑到了 INFINITY 的情况, 直接用 arcs[i][j].weight 赋值
   * 即可.
   */
  for (int i = 0; i < G.vex_num; ++i) {
    dist[i] = G.arcs[sourceIndex][i].weight;
  }

  /**
   * todo 辅助数组 path, 记录最短路径, 不会.
   */
  VertexType path[G.vex_num][G.vex_num];

  /**
   * 第二, 三步各执行一次为一轮.
   */

  /* 一共循环 n 次. */
  for (int i = 0; i < G.vex_num; ++i) {
    /**
     * ! 第二步. 从顶点集合 V - S 中选择 vj, 满足
     * dist[j] = Min{dist[i] | vi ∈ V - S},
     * vj 就是当前求得的一条从 source 出发的最短路径的终点, 令 S = S ∪ {vj}.
     */

    /* 集合 V - S 中 dist 最小的元素的索引. */
    int minVexIndex;
    /* 最小值. */
    int min = INFINITY;
    /* 循环找最小值. */
    for (int j = 0; j < G.vex_num; ++j) {
      /* 从集合 V - S 中选择一点*/
      if (S[j] == FALSE) {
        /* 寻找 dist 中的最小值. */
        if (dist[j] < min) {
          /* 更新. */
          min = dist[j];
          minVexIndex = j;
        }
      }
    }

    /* 将 vj 加入到 S中, S = S ∪ {vj}. */
    S[minVexIndex] = TRUE;

    /**
     * ! 第三步. 修改从 source 出发到集合 V - S 上任一顶点 vk 可到达的最短路径
     * 长度: 若 dist[j] + arcs[j][k] < dist[k], 则更新 dist[k] = dist[j] +
     * arcs[j][k].
     *
     * 这么理解, dist[j] 是源点 source 到顶点 j 的距离, 此距离再加上 arcs[j][k],
     * 即源点 source 经顶点 vj 到顶点 vk 的距离. dist[k] 是源点 source 到顶点 vk
     * 的距离, 若新的距离小于原来的距离 dist[k], 则更新 dist[k].
     */

    for (int k = 0; k < G.vex_num; ++k) {
      /* 从集合 V - S 中选择一点*/
      if (S[k] == FALSE) {
        /**
         * 1. 如果 arcs[minVexIndex][k].weight 为无穷, 再对其求和会溢出, 导
         * 致比较出错;
         * 2. 无穷表示无法从顶点 vj 到达顶点 vk, 即无法通过路径
         * source -> ... -> vj 再到达顶点 vk, 自然也没有比较的意义;
         * 3. 无穷加任意正数, 仍可以看作无穷, 必不小于原来的 dist[k].
         */
        if (G.arcs[minVexIndex][k].weight != INFINITY) {
          /**
           * 前面第二个 if 没有排除 k != minVexIndex 的情况,
           * 因为自己到自己的距离为 0, 不会更新最小值.
           */
          if ((dist[minVexIndex] + G.arcs[minVexIndex][k].weight) < dist[k]) {
            dist[k] = dist[minVexIndex] + G.arcs[minVexIndex][k].weight;
          }
        }
      }
    }

    /**
     * 第四步, 重复第二步到第三步操作共 n - 1 次, 直到所有的顶点都包含在 S 中.
     */
  }

  return;
}

void FloydM(MGraph G) {
  WeightType dist[G.vex_num][G.vex_num];

  /* 初始化: 方阵 dist = arcs. */
  for (int i = 0; i < G.vex_num; ++i) {
    for (int j = 0; j < G.vex_num; ++j) {
      dist[i][j] = G.arcs[i][j].weight;
    }
  }

  /**
   * 第一轮: 将 v0 作为中间顶点, 对于所有顶点对 {i, j}, 如果有
   * dist[i][j] > dist[i][0] + dist[0][j],
   * 则将 dist[i][j] 更新为 dist[i][0] + dist[0][j].
   * 标记更新之后的方阵为 dist^0.
   *
   * 第 k 轮: 将 vk 作为中间结点, 继续检测全部顶点对 {i, j}, 如果有
   * dist[i][j] > dist[i][k] + dist[k][j],
   * 则将 dist[i][j] 更新为 dist[i][k] + dist[k][j].
   * 标记更新之后的方阵为 dist^k.
   */

  for (int k = 0; k < G.vex_num; ++k) {
    for (int i = 0; i < G.vex_num; ++i) {
      for (int j = 0; j < G.vex_num; ++j) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  return;
}

void PrintGraphM(MGraph G) {
  for (int i = 0; i < G.vex_num; ++i) {
    for (int j = 0; j < G.vex_num; ++j) {
      printf("%d%c", G.arcs[i][j].weight, j == G.vex_num - 1 ? '\n' : '\t');
    }
  }

  return;
}
