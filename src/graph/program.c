/**
 * @file program.c
 * @author tianshihao4944@126.com
 * @brief 第七章代码测试.
 * @version 0.1
 * @date 2020-09-12
 * @copyright Copyright (c) 2020
 */

#include <graph/algraph/algraph.h>
#include <graph/mgraph/mgraph.h>

void WriteGraph(MGraph *G);
void ReadGraph(MGraph *G);
Status MyVisit(int i);
void UseMgraph();
void UseAlgraph();

int main()
{
    UseMgraph();
    // UseAlgraph();

    return 0;
}

void UseMgraph()
{
    MGraph G;

    CreateGraph_M(&G);

    PrintGraph_M(G);

    Floyd_M(G);

    return;
}

void UseAlgraph()
{
    ALGraph G;

    CreateGraph_AL(&G);

    DFSTraverse_AL(G, MyVisit);
    printf("\n");
    BFSTraverse_AL(G, MyVisit);
    printf("\n");

    PrintGraph_AL(G);

    return;
}

void WriteGraph(MGraph *G)
{
    FILE *fp = fopen("./mgraph.bin", "wb");

    fwrite(G, sizeof(*G), 1, fp);

    fclose(fp);

    return;
}

void ReadGraph(MGraph *G)
{
    FILE *fp = fopen("./mgraph.bin", "rb");

    fread(G, sizeof(*G), 1, fp);

    return;
}

Status MyVisit(VertexType i)
{
    printf("%d ", i);

    return OK;
}
