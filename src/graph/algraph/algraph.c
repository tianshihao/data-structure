/**
 * @file algraph.c
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 邻接表方法实现.
 * @version 0.2
 * @date 2020-12-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <algraph.h>

Status CreateGraphAL(ALGraph *pG) {
  printf("Enter graph's type (1: DG, 2: DN, 3: UDG, 4: UDN): ");
  scanf("%u", &pG->type);

  switch (pG->type) {
    case DG:
      return CreateDG_AL(pG);
    case DN:
      return CreateDN_AL(pG);
    case UDG:
      return CreateUDG_AL(pG);
    case UDN:
      return CreateUDN_AL(pG);
    default:
      return ERROR;
  }

  return OK;
}

Status CreateDG_AL(ALGraph *pG) {
  printf("Enter vertex number of graph: ");
  scanf("%d", &pG->vexNum);
  printf("Enter arc number of graph: ");
  scanf("%d", &pG->arcNum);

  printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
  for (int i = 0; i < pG->vexNum; ++i) {
    scanf("%d", &pG->vertices[i].vex);
    pG->vertices[i].firstArc = NULL;
  }

  printf(
      "Enter vertex relation\n",
      "e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.\n"
      ": \n");
  for (int k = 0; k < pG->arcNum; ++k) {
    int v1, v2, weight;

    scanf("%d %d %d", &v1, &v2, &weight);

    InsertArcNode(pG, v1, v2, weight);
  }

  return OK;
}

Status CreateDN_AL(ALGraph *pG) { return CreateDG_AL(pG); }

Status CreateUDG_AL(ALGraph *pG) {
  printf("Enter vertex number of graph: ");
  scanf("%d", &pG->vexNum);
  printf("Enter arc number of graph: ");
  scanf("%d", &pG->arcNum);

  printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
  for (int i = 0; i < pG->vexNum; ++i) {
    scanf("%d", &pG->vertices[i].vex);
    pG->vertices[i].firstArc = NULL;
  }

  printf(
      "Enter vertex relation\n",
      "e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.\n"
      ": \n");
  for (int k = 0; k < pG->arcNum; ++k) {
    int v1, v2, weight;

    scanf("%d %d %d", &v1, &v2, &weight);

    InsertArcNode(pG, v1, v2, weight);
    InsertArcNode(pG, v2, v1, weight);
  }

  return OK;
}

Status CreateUDN_AL(ALGraph *pG) { return CreateUDG_AL(pG); }

int LocateVex_AL(ALGraph G, VertexType v) {
  for (int i = 0; i < G.vexNum; ++i) {
    if (G.vertices[i].vex == v) {
      return i;
    }
  }

  return -1;
}

Status InsertArcNode(ALGraph *pG, VertexType v1, VertexType v2,
                     WeightType weight) {
  int v1Index = LocateVex_AL(*pG, v1);

  /* 如果没有依附于该顶点的边, 即边表为空, 创建新的头结点. */
  if (pG->vertices[v1Index].firstArc == NULL) {
    pG->vertices[v1Index].firstArc = malloc(sizeof(ArcNode));

    /* 在顶点表中寻找 v2 顶点对应的下标. */
    int v2Index = LocateVex_AL(*pG, v2);

    pG->vertices[v1Index].firstArc->adjVex = v2Index;
    pG->vertices[v1Index].firstArc->weight = weight;
    pG->vertices[v1Index].firstArc->nextArc = NULL;
  }
  /* 如果该顶点的边表不为空, 直接在边表尾新加结点. */
  else {
    /* 工作指针, 指向边表头结点. */
    ArcNode *p = pG->vertices[v1Index].firstArc;

    /* 找到表尾, 合适的插入位置. */
    while (p->nextArc != NULL) {
      p = p->nextArc;
    }

    /* 在顶点表中寻找 v2 顶点对应的下标. */
    int v2Index = LocateVex_AL(*pG, v2);

    /* 新边结点, 尾插法. */
    ArcNode *newArc = malloc(sizeof(ArcNode));
    newArc->adjVex = v2Index;
    newArc->weight = weight;
    newArc->nextArc = NULL;

    p->nextArc = newArc;
  }

  return OK;
}

void BFSTraverse_AL(ALGraph G, Status (*VisitFunc)(VertexType v)) {
  /* 设置辅助数组, 标记顶点是否被访问. */
  int visited[G.vexNum];

  /* 初始化辅助数组. */
  for (int i = 0; i < G.vexNum; ++i) {
    visited[i] = FALSE;
  }

  /* 顺序队列. */
  SqQueue Q;

  /* 队列中存放已经访问过但邻接结点未知的结点. */
  InitQueue_Sq(&Q);

  /* 从 0 号顶点开始遍历. */
  for (int vexIndex = 0; vexIndex < G.vexNum; ++vexIndex) {
    /* 对每个连通分量调用一次 BFS_AL. */
    if (!visited[vexIndex]) {
      /* vi 未访问过, 从 vi 开始 BFS_AL. */
      BFS_AL(G, vexIndex, VisitFunc, visited, &Q);
    }
  }

  return;
}

void BFS_AL(ALGraph G, int vexIndex, Status (*VisitFunc)(VertexType v),
            int *visited, SqQueue *Q) {
  /* 访问初始结点. */
  VisitFunc(G.vertices[vexIndex].vex);

  /* 对 vexIndex 做已访问标记. */
  visited[vexIndex] = TRUE;

  /* 顶点索引 vexIndex 入队列. */
  EnQueue_Sq(Q, vexIndex);

  while (!QueueEmpty_Sq(*Q)) {
    /* 顶点索引 vexIndex 出队列.*/
    DeQueue_Sq(Q, &vexIndex);

    /* 检测所有依附于顶点 vexIndex 的边. */
    for (ArcNode *pArc = G.vertices[vexIndex].firstArc; pArc != NULL;
         pArc = pArc->nextArc) {
      /* 若弧 pArc 指向的顶点还没有被访问过. */
      if (!visited[pArc->adjVex]) {
        /* 访问弧 pArc 指向的顶点. */
        VisitFunc(G.vertices[pArc->adjVex].vex);

        /* 对弧 pArc 指向的结点做访问标记. */
        visited[pArc->adjVex] = TRUE;

        /* 把弧 pArc 指向的顶点入队列. */
        EnQueue_Sq(Q, LocateVex_AL(G, pArc->adjVex));
      }
    }
  }

  return;
}

void DFSTraverse_AL(ALGraph G, Status (*VisitFunc)(VertexType v)) {
  /* 设置辅助数组, 标记顶点是否被访问. */
  int visited[G.vexNum];

  /* 初始化辅助数组. */
  for (int i = 0; i < G.vexNum; ++i) {
    visited[i] = FALSE;
  }

  /* 从 0 号元素开始遍历. */
  for (int vexIndex = 0; vexIndex < G.vexNum; ++vexIndex) {
    /* 对每个连通分量调用一次 DFS_AL. */
    if (!visited[vexIndex]) {
      /* vi 还没有被访问过, 从 vi 开始 DFS_AL. */
      DFS_AL(G, vexIndex, VisitFunc, visited);
    }
  }

  return;
}

void DFS_AL(ALGraph G, int vexIndex, Status (*VisitFunc)(VertexType v),
            int *visited) {
  /* 访问初始结点. */
  VisitFunc(G.vertices[vexIndex].vex);

  /* 对 vexIndex 做已访问标记. */
  visited[vexIndex] = TRUE;

  /* 对 vexIndex 的尚未访问的邻接顶点 arc->adjVex 递归调用 DFS_AL. */
  for (ArcNode *arc = G.vertices[vexIndex].firstArc; arc != NULL;
       arc = arc->nextArc) {
    if (!visited[vexIndex]) {
      DFS_AL(G, arc->adjVex, VisitFunc, visited);
    }
  }

  return;
}

void PrintGraph_AL(ALGraph G) {
  for (int i = 0; i < G.vexNum; ++i) {
    /* 打印顶点表顶点. */
    printf("V%d------>", G.vertices[i].vex);

    /* p 指向第 i 个顶点边表 (链表) 的第一个结点 (头结点). */
    ArcNode *p = G.vertices[i].firstArc;

    /* 循环输出边表结点指向的顶点的位置. */
    while (p) {
      /**
       * p->adjVex 是图中结点在数据结构 (顶点表) 存储的位置的下标, 要获得
       * 其对应的真正的图中的结点, 应该把 p->adjVex 作为下标去顶点表中寻找
       * 顶点表中存储的真正的结点.
       */
      printf("V%d", G.vertices[p->adjVex].vex);

      p = p->nextArc;

      if (p) {
        printf("-->");
      } else {
        printf("\n");
      }
    }

    printf("\n");
  }

  return;
}
