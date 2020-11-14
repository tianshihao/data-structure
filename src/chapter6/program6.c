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

#include <chapter6/bitree/bitree.h>
#include <chapter6/bstree/bstree.h>
#include <chapter6/threadtree/threadtree.h>

void UseBinaryTree();
void UseThreadTree();
void UseBinarySearchTree();
Status MyVisit(ElemType e);

int main()
{
    UseBinaryTree();

    // int *p;

    // printf(">>>>>>>>>>> *p = %d <<<<<<<<<<<\n", *p);

    // system("pause");

    // UseThreadTree();

    // UseBinarySearchTree();

    system("pause");

    return 0;
}

void UseBinaryTree()
{
    BiTree T;
    InitTree_Binary(&T);

    CreateBinaryTree(&T, "../input/input1.txt");

    printf("Tree's height or depth is ");
    printf("%d\n", BiTreeHeight(T));

    printf("Traverse tree with level-order.\n");
    LevelOrderTraverse_Binary(T, MyVisit);
    printf("\n");

    int height = 0;
    int balance = 0;

    JudgeAVL(T, &height, &balance);

    if (balance == 1)
    {
        printf("This tree is a AVL tree.\n");
    }
    else
    {
        printf("This tree is not a AVL tree.\n");
    }

    printf("Tree's height or depth is ");
    printf("%d\n", BiTreeHeight(T));

    printf("Taverse tree with inverted level-order (from bottom to top, from right to left)\n");
    InvertLevelTraverse_Binary(T, MyVisit);
    printf("\n");

    // {
    //     ElemType ch = 'D';
    //     printf("Find %c's all ancestors.\n", ch);
    //     FindAncestor(T, 'D');

    //     BiTNode *q = T->rchild;
    //     BiTNode *p = T->lchild->rchild;
    //     printf("Node %c and node %c's closest common ancestor is ", q->data, p->data);
    //     printf("%c\n", FindCommonAncestor(T, p, q)->data);
    // }

    printf("The width of binary tree is ");
    printf("%d\n", BiTreeWidth(T));

    printf("Construct tree from preorder and inorder sequence.\n");
    ElemType pre[5] = {'A', 'B', 'D', 'E', 'C'};
    ElemType in[5] = {'D', 'B', 'E', 'A', 'C'};
    BiTree N = PreInCreate(pre, 0, 4, in, 0, 4);

    printf("Binary tree N's level order traverse sequence is ");
    LevelOrderTraverse_Binary(N, MyVisit);
    printf("\n");

    if (Similar(T, N))
    {
        printf("Tree T and N is similar.\n");
    }
    else
    {
        printf("Tree T and N is not similar.\n");
    }

    printf("wpl = %d\n", WPL(N));
    printf("wpl = %d\n", WPLLevelOrder(N));

    // // printf("tree depth = %d\n", BiTreeHeight(T));
    // // printf("\n");

    // // printf("depth = %d\n", BiTreeHeight(T));
    // LevelOrderTraverse_Binary(T, MyVisit);
    // printf("\n");
    // SwapSubTree(T);
    // LevelOrderTraverse_Binary(T, MyVisit);
    // printf("\n");

    return;
}

void UseThreadTree()
{
    ThreadTree T;
    InitTree_Thread(&T);

    CreateThreadTree(&T, "../input/input1.txt");

    PreOrderTraverse_Thread(T, MyVisit);

    PreOrderThreading(&T);

    PreOrder(T, MyVisit);

    return;
}

void UseBinarySearchTree()
{
    BSTree T;
    InitTree_BS(&T);

    BSTElem arr[8] = {53, 17, 78, 45, 9, 23, 87, 65};

    CreateTree_BST(&T, arr, 8);

    if (SearchElem(T, 87))
    {
        printf("found\n");
    }
    else
    {
        printf("not found\n");
    }

    // 从大到小输出值大于 k 的结点.
    Output(T, 60);

    return;
}

Status MyVisit(ElemType e)
{
    printf("%c", e);

    return OK;
}
