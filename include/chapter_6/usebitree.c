#include "bitree.h"

Status PrintElement(ElemType e)
{
    printf(" %c ", e);
    return OK;
} // PrintElement

int main()
{
    // myBiTree 是一个指向二叉树结点的指针.
    BiTree myBiTree = NULL;

    InitTree(&myBiTree);

    CreateBiTree(&myBiTree, ".\\input.txt");

    PostOrderTraverse(myBiTree, PrintElement);

    PreOrderTraverse(myBiTree, PrintElement);

    return 0;
}