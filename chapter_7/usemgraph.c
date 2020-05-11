#include "mgraph.h"

int main()
{
    MGraph G;

    CreateGraph(&G);

    PrintAdjMatrix(G);

    return 0;
}