#include "algraph.h"
#include <stdio.h>

Status Visit(int v)
{
    printf("visited vertex v%d\n", v + 1);

    return OK;
}

int main()
{
    ALGraph G;

    CreateGraph(&G);

    PrintAdjacencyList(G);

    DFSTraverse(G, Visit);

    return 0;
}