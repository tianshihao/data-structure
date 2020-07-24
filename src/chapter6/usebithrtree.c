#include "bithrtree.h"

Status PrintElement(ElemType e)
{
    printf(" %c ", e);
    return OK;
} // PrintElement

int main()
{
    BiThrTree myBiThrTre;

    InitTree_Thr(&myBiThrTre);

    CreateThrTree(&myBiThrTre, ".\\input2.txt");

    PreOrderTraverse(myBiThrTre->lchild, PrintElement);
    printf("\n");
    InOrderTraverse(myBiThrTre->lchild, PrintElement);
    printf("\n");

    InOrderThreading(&myBiThrTre, myBiThrTre->lchild);

    InOrderTraverse_Thr(myBiThrTre,PrintElement);

    return 0;
}