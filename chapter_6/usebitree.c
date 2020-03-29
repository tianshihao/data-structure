#include "bitree.h"

Status PrintElement(ElemType e)
{
    printf(" %c ", e);
    return OK;
} // PrintElement

int main()
{
    // my_bitree 是一个指向二叉树结点的指针.
    BiTree my_bitree = NULL;

    InitTree(&my_bitree);

    CreateBiTree(&my_bitree, ".\\input.txt");

    PostOrderTraverse(my_bitree, PrintElement);

    PreOrderTraverse(my_bitree, PrintElement);

    return 0;
}