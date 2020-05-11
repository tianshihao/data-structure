#include "predefconst.h"
#include <stdio.h>

#define MAX_VERTEX_NUM 20

typedef int InfoType;

typedef int VertexType;

typedef enum GraphType
{
    DG,
    DN,
    UDG,
    UDN
} GraphType;

typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    InfoType *info;
} ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph
{
    AdjList vertices;
    int vexnum, arcnum;
    GraphType type;
} ALGraph;
