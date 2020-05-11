#include "algraph.h"
#include <stdio.h>

int main()
{
    ALGraph G;

    CreateGraph(&G);

    PrintAdjacencyList(G);

    return 0;
}