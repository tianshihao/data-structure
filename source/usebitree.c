#include "bitree.h"

int main()
{
    BiTree my_bitree = NULL;

    InitTree(&my_bitree);

    CreateBiTree(&my_bitree, ".\\input.txt");

    return 0;
}