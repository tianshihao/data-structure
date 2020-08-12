/**
 * @file program6.c
 * @author tianshihao
 * @brief 使用二叉树.
 * @version 0.1
 * @date 2020-08-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <chapter6/bitree.h>
#include <chapter6/threadtree.h>

void UseBinaryTree();
void UseThreadTree();
Status MyVisit(ElemType e);

int main()
{
    // UseBinaryTree();

    // int *p;

    // printf(">>>>>>>>>>> *p = %d <<<<<<<<<<<\n", *p);

    // system("pause");

    UseThreadTree();

    return 0;
}

void UseBinaryTree()
{
    BiTree T;
    InitTree_Binary(&T);

    CreateBinaryTree(&T, "input1.txt");

    LevelOrderTraverse_Binary(T, MyVisit);
    printf("\n");
    PreOrderTraverse_Binary(T, MyVisit);
    printf("\n");
    InOrderTraverse_Binary(T, MyVisit);
    printf("\n");
    PostOrderTraverse_Binary(T, MyVisit);

    return;
}

void UseThreadTree()
{
    ThreadTree T;
    InitTree_Thread(&T);

    CreateThreadTree(&T, "input1.txt");

    PreOrderTraverse_Thread(T, MyVisit);

    PreOrderThreading(&T);

    PreOrder(T, MyVisit);

    return;
}

Status MyVisit(ElemType e)
{
    printf("%c", e);

    return OK;
}
