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
    UseBinaryTree();

    // int *p;

    // printf(">>>>>>>>>>> *p = %d <<<<<<<<<<<\n", *p);

    system("pause");

    // UseThreadTree();

    return 0;
}

void UseBinaryTree()
{
    BiTree T;
    InitTree_Binary(&T);

    CreateBinaryTree(&T, "input1.txt");

    // LevelOrderTraverse_Binary(T, MyVisit);
    printf("\n");

    printf("depth = %d\n", BiTreeDepth(T));

    // // printf("tree depth = %d\n", BiTreeDepth(T));
    // // printf("\n");

    // ElemType pre[5] = {'A', 'B', 'D', 'E', 'C'};
    // ElemType in[5] = {'D', 'B', 'E', 'A', 'C'};

    // BiTree T = PreInCreate(pre, in, 0, 4, 0, 4);

    // LevelOrderTraverse_Binary(T, MyVisit);

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
