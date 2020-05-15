#include "mgraph.h"

void WriteGraph(MGraph *G);
void ReadGraph(MGraph *G);
void Visit(int i);

int main()
{
    MGraph G;

    // CreateGraph(&G);

    // PrintAdjMatrix(G);

    // WriteGraph(&G);

    ReadGraph(&G);

    PrintAdjMatrix(G);

    DFSTraverse(G, Visit);

    return 0;
}

void WriteGraph(MGraph *G)
{
    FILE *fp = fopen("./mgraph.bin", "wb");

    fwrite(G, sizeof(*G), 1, fp);

    fclose(fp);

    return;
} // WriteGraph

void ReadGraph(MGraph *G)
{
    FILE *fp = fopen("./mgraph.bin", "rb");

    fread(G, sizeof(*G), 1, fp);

    return;
} // ReadGraph

void Visit(int i)
{
    printf("%d ", i);

    return;
}