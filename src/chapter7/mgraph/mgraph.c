/**
 * @file mgraph.c
 * @author tianshihao4944@126.com
 * @brief 邻接矩阵
 * @version 0.1
 * @date 2020-09-12
 * @copyright Copyright (c) 2020
 */

#include <chapter7/mgraph/mgraph.h>

Status CreateGraph_M(MGraph *G)
{
    printf("Enter graph's type (1: DG, 2: DN, 3: UDG, 4: UDN): ");
    scanf("%u", &G->type);

    switch (G->type)
    {
    case DG:
        return CreateDG_M(G);
    case DN:
        return CreateDN_M(G);
    case UDG:
        return CreateUDG_M(G);
    case UDN:
        return CreateUDN_M(G);
    default:
        return ERROR;
    }

    return OK;
}

Status CreateDG_M(MGraph *G)
{
    printf("Enter vertex number of graph: ");
    scanf("%d", &G->vexnum);
    printf("Enter arc number of graph: ");
    scanf("%d", &G->arcnum);

    printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", (&G->vertices[i]));
    }

    /* 初始化有向图. */
    for (int i = 0; i < G->vexnum; ++i)
    {
        for (int j = 0; j < G->vexnum; ++j)
        {
            /* 自己到自己的距离为 0. */
            if (i == j)
            {
                G->arcs[i][j].weight = 0;
            }
            else
            {
                G->arcs[i][j].weight = INFINITY;
            }
        }
    }

    printf("Enter vertex relation (e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.): \n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        int i = LocateVex_M(*G, v1);
        int j = LocateVex_M(*G, v2);

        G->arcs[i][j].weight = weight;
    }

    return OK;
}

Status CreateDN_M(MGraph *G)
{
    return CreateDG_M(G);
}

Status CreateUDG_M(MGraph *G)
{
    printf("Enter vertex number of graph: ");
    scanf("%d", &G->vexnum);
    printf("Enter arc number of graph: ");
    scanf("%d", &G->arcnum);

    printf("Enter vertex vector of graph (e.g. 1 2 3 4 or 0 1 2 3 4): ");
    for (int i = 0; i < G->vexnum; ++i)
    {
        scanf("%d", &G->vertices[i]);
    }

    for (int i = 0; i < G->vexnum; ++i)
    {
        for (int j = 0; j < G->vexnum; ++j)
        {
            /* 自己到自己的距离为 0. */
            if (i == j)
            {
                G->arcs[i][j].weight = 0;
            }
            else
            {
                G->arcs[i][j].weight = INFINITY;
            }
        }
    }

    printf("Enter vertex relation (e.g. 2 3 1, means vertex 2 relate to vertex 3 and arc's weight is 1.): \n");
    for (int k = 0; k < G->arcnum; ++k)
    {
        int v1, v2, weight;

        scanf("%d %d %d", &v1, &v2, &weight);

        int i = LocateVex_M(*G, v1);
        int j = LocateVex_M(*G, v2);

        /* 无向图/网是关于主对角线对称的. */
        G->arcs[i][j].weight = weight;
        G->arcs[j][i].weight = G->arcs[i][j].weight;
    }

    return OK;
}

Status CreateUDN_M(MGraph *G)
{
    return CreateUDG_M(G);
}

VertexType LocateVex_M(MGraph G, VertexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i] == v)
        {
            return i;
        }
    }
    return 0;
}

VertexType FirstVex_M(MGraph G, VertexType v)
{
    /* 检查邻接矩阵的第 v 行. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        /* 若 v 和 i 之间既相连通, 权值也不为无穷. */
        if (G.arcs[v][i].weight != 0 && G.arcs[v][i].weight != INFINITY)
        {
            /* 则返回顶点 i. */
            return i;
        }
    }

    return -1;
}

VertexType NextVex_M(MGraph G, VertexType v, int w)
{
    /* 在顶点 v 的临接结点中找 w 之后的临接结点. */
    /* 搜索临接矩阵第 v 行. */
    for (int i = w + 1; i < G.vexnum; ++i)
    {
        /* 若 v 和 i 之间既相连通, 权值也不为无穷. */
        if (G.arcs[v][i].weight != 0 && G.arcs[v][i].weight != INFINITY)
        {
            /* 则返回顶点 i. */
            return i;
        }
    }

    return -1;
}

void BFSTraverse_M(MGraph G, Status (*Visit)(VertexType v))
{
    /* 设置辅助数组, 标记顶点是否被访问. */
    int visited[G.vexnum];

    /* 初始化辅助数组. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    /* 顺序队列. */
    SqQueue Q;

    /* 队列中存放已经访问过但邻接结点未知的结点. */
    InitQueue_Sq(&Q);

    /* 从 0 号顶点开始遍历. */
    for (int v = 0; v < G.vexnum; ++v)
    {
        /* 对每个连通分量调用一次 BFS_M. */
        if (!visited[v])
        {
            /* vi 未访问过, 从 vi 开始 BFS_M. */
            BFS_M(G, v, Visit, visited, &Q);
        }
    }

    return;
}

void BFS_M(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited, SqQueue *Q)
{
    /* 访问初始顶点 v. */
    Visit(G.vertices[v]);

    /* 对 v 做已访问标记. */
    visited[v] = TRUE;

    /* 顶点 v 入队列.*/
    EnQueue_Sq(Q, v);

    while (!QueueEmpty_Sq(*Q))
    {
        /* 顶点 v 出队列.*/
        DeQueue_Sq(Q, &v);

        /* 检测 v 的所有邻接点. */
        for (VertexType w = FirstVex_M(G, v); w >= 0; w = NextVex_M(G, v, w))
        {
            /* 若 v 的邻接点 w 还没有被访问过. */
            if (!visited[w])
            {
                /* 访问顶点 w. */
                Visit(G.vertices[w]);

                /* 对 w 做已访问标记. */
                visited[w] = TRUE;

                /* 顶点 w 入队列. */
                EnQueue_Sq(Q, w);
            }
        }
    }

    return;
}

void DFSTraverse_M(MGraph G, Status (*Visit)(VertexType v))
{
    /* 设置辅助数组, 标记顶点是否被访问. */
    int visited[G.vexnum];

    /* 初始化辅助数组. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        visited[i] = FALSE;
    }

    /* 从 0 号顶点开始遍历. */
    for (int v = 0; v < G.vexnum; ++v)
    {
        /* 对每个连通分量调用一次 DFS_M. */
        if (!visited[v])
        {
            /* vi 还没有被访问过, 从 vi 开始 DFS_M. */
            DFS_M(G, v, Visit, visited);
        }
    }

    return;
}

void DFS_M(MGraph G, VertexType v, Status (*Visit)(VertexType v), int *visited)
{
    /* 访问初始顶点 v. */
    Visit(G.vertices[v]);

    /* 对 v 做已访问标记. */
    visited[v] = TRUE;

    /* 检测 v 的所有邻接点. */
    for (int w = FirstVex_M(G, v); w >= 0; w = NextVex_M(G, v, w))
    {
        /* w 为 v 尚未访问过的邻接点. */
        if (!visited[w])
        {
            /* w 未访问过, 从 w 开始 DFS_M. */
            DFS_M(G, w, Visit, visited);
        }
    }

    return;
}

void Dijkstra_M(MGraph G, VertexType source)
{
    /* 源点 source 在图的顶点表中对应的索引. */
    int sourceIndex = LocateVex_M(G, source);

    /**
     * ! 第一步, 初始化 S. 若 S[i] == TRUE, 说明顶点 vi 已在集合 S 中. 
     */

    /* 初始化 S. */
    VertexType S[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i)
    {
        S[i] = FALSE;
    }
    /* S 的初始元素为源点, 即 sourceIndex. */
    S[sourceIndex] = TRUE;

    /**
     * 辅助数组 dist, 记录源点 source 到其它各顶点当前的最短路径长度, 它的初态
     * 为: 若从 source 到 v 有弧, 则 dist[v] 为弧上的权值; 否则置 dist[v] = INFINITY.
     * dist[i] = G.arcs[sourceIndex][i].weight.
     */
    WeightType dist[G.vexnum];

    /**
     * 在创建图的时候已经考虑到了 INFINITY 的情况, 直接用 arcs[i][j].weight 赋值
     * 即可.
     */
    for (int i = 0; i < G.vexnum; ++i)
    {
        dist[i] = G.arcs[sourceIndex][i].weight;
    }

    /**
     * 辅助数组 path, 
     * 
     */
    VertexType path[G.vexnum][G.vexnum];

    /**
     * 第二, 三步各执行一次为一轮.
     */

    for (int i = 0; i < G.vexnum; ++i)
    {
        /**
         * ! 第二步. 从顶点集合 V - S 中选择 vj, 满足
         * dist[j] = Min{dist[i] | vi ∈ V - S},
         * vj 就是当前求得的一条从 source 出发的最短路径的终点, 令 S = S ∪ {vj}.
         */

        /* 集合 V - S 中 dist 最小的元素的索引. */
        VertexType vertexj;
        /* 最小值. */
        VertexType min = INFINITY;
        /* 循环找最小值. */
        for (int j = 0; j < G.vexnum; ++j)
        {
            /* 从集合 V - S 中选择一点*/
            if (S[j] == FALSE)
            {
                if (dist[j] < min)
                {
                    min = dist[j];
                    vertexj = j;
                }
            }
        }

        /* 将 vj 加入到 S中, S = S ∪ {vj}. */
        S[vertexj] = TRUE;

        /**
         * ! 第三步. 修改从 source 出发到集合 V - S 上任一顶点 vk 可到达的最短路径
         * 长度: 若 dist[j] + arcs[j][k] < dist[k], 则更新 dist[k] = dist[j] + arcs[j][k].
         * 
         * 这么理解, dist[j] 是源点 source 到顶点 j 的距离, 此距离再加上 arcs[j][k],
         * 即顶点 vj 到顶点 vk 的距离就是源点 source 到顶点 vk 的距离, 若新的距离
         * 小于原来的距离 dist[k], 则更新 dist[k].
         */

        for (int k = 0; k < G.vexnum; ++k)
        {
            /* 从集合 V - S 中选择一点*/
            if (S[k] == FALSE)
            {
                /**
                 * 1. 如果 arcs[vertexj][k].weight 为无穷, 再对其求和会溢出, 导
                 * 致比较出错; 
                 * 2. 无穷表示无法从顶点 vj 到达顶点 vk, 即无法通过路径
                 * source -> ... -> vj 再到达顶点 vk, 自然也没有比较的意义;
                 * 3. 无穷加任意正数, 仍可以看作无穷, 必不小于原来的 dist[k]. 
                 */
                if (G.arcs[vertexj][k].weight != INFINITY)
                {
                    if ((dist[vertexj] + G.arcs[vertexj][k].weight) < dist[k])
                    {
                        dist[k] = dist[vertexj] + G.arcs[vertexj][k].weight;
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

void Floyd_M(MGraph G)
{
    WeightType dist[G.vexnum][G.vexnum];

    /* 初始化: 方阵 dist = arcs. */
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
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

    for (int k = 0; k < G.vexnum; ++k)
    {
        for (int i = 0; i < G.vexnum; ++i)
        {
            for (int j = 0; j < G.vexnum; ++j)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return;
}

void PrintGraph_M(MGraph G)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
            printf("%d%c", G.arcs[i][j].weight, j == G.vexnum - 1 ? '\n' : '\t');
        }
    }

    return;
}
