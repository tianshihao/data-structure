#include "bitree.h"

Status PrintElement(TElemType e)
{
    printf(" %c ", e);
    return OK;
} // PrintElement

int main()
{
    BiTree my_bitree = NULL;

    InitTree(&my_bitree);

    CreateBiTree(&my_bitree, ".\\input.txt");

    PostOrderTraverse(my_bitree, PrintElement);

    return 0;
}