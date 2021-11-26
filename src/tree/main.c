/**
 * @file program.c
 * @author tianshihao
 * @brief 使用二叉树.
 * @version 0.1
 * @date 2020-08-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <bitree.h>
#include <tree/bstree/bstree.h>
#include <tree/threadtree/threadtree.h>

void TestBinaryTree();
void UseThreadTree();
void UseBinarySearchTree();
Status MyVisit(BiTElemType e);

int main() {
  TestBinaryTree();

  // int *p;

  // printf(">>>>>>>>>>> *p = %d <<<<<<<<<<<\n", *p);

  // system("pause");

  // UseThreadTree();

  // UseBinarySearchTree();

  system("pause");

  return 0;
}

void TestBinaryTree() {
  BiTree t;
  InitTreeBinary(&t);

  const char *file_path = "../../../data/bitree.txt";

  if (ERROR == CreateBinaryTreeFromFile(&t, file_path)) {
    exit(ERROR);
  }

  printf("Tree's height or depth is ");
  printf("%d\n", BiTreeHeight(t));

  printf("Traverse tree with level-order.\n");
  LevelOrderTraverseBinary(t, MyVisit);
  printf("\n");

  int height = 0;
  int balance = 0;

  JudgeAVL(t, &height, &balance);

  if (balance == 1) {
    printf("This tree is a AVL tree.\n");
  } else {
    printf("This tree is not a AVL tree.\n");
  }

  printf("Tree's height or depth is ");
  printf("%d\n", BiTreeHeight(t));

  printf(
      "Taverse tree with inverted level-order (from bottom to top, from right "
      "to left)\n");
  InvertLevelTraverseBinary(t, MyVisit);
  printf("\n");

  // {
  //     ElemType ch = 'D';
  //     printf("Find %c's all ancestors.\n", ch);
  //     FindAncestor(T, 'D');

  //     BiTNode *q = T->rchild;
  //     BiTNode *p = T->lchild->rchild;
  //     printf("Node %c and node %c's closest common ancestor is ", q->data,
  //     p->data); printf("%c\n", FindCommonAncestor(T, p, q)->data);
  // }

  printf("The width of binary tree is ");
  printf("%d\n", BiTreeWidth(t));

  printf("Construct tree from preorder and inorder sequence.\n");
  BiTElemType pre[5] = {'A', 'B', 'D', 'E', 'C'};
  BiTElemType in[5] = {'D', 'B', 'E', 'A', 'C'};
  BiTree N = PreInCreate(pre, 0, 4, in, 0, 4);

  printf("Binary tree N's level order traverse sequence is ");
  LevelOrderTraverseBinary(N, MyVisit);
  printf("\n");

  if (Similar(t, N)) {
    printf("Tree T and N is similar.\n");
  } else {
    printf("Tree T and N is not similar.\n");
  }

  printf("wpl = %d\n", WPL(N));
  printf("wpl = %d\n", WPLLevelOrder(N));

  // // printf("tree depth = %d\n", BiTreeHeight(T));
  // // printf("\n");

  // // printf("depth = %d\n", BiTreeHeight(T));
  // LevelOrderTraverseBinary(T, MyVisit);
  // printf("\n");
  // SwapSubTree(T);
  // LevelOrderTraverseBinary(T, MyVisit);
  // printf("\n");

  return;
}

void UseThreadTree() {
  ThreadTree T;
  InitTree_Thread(&T);

  CreateThreadTree(&T, "../input/input1.txt");

  PreOrderTraverse_Thread(T, MyVisit);

  PreOrderThreading(&T);

  PreOrder(T, MyVisit);

  return;
}

void UseBinarySearchTree() {
  BSTree T;
  InitTree_BS(&T);

  BSTElem arr[8] = {53, 17, 78, 45, 9, 23, 87, 65};

  CreateTree_BST(&T, arr, 8);

  if (SearchElem(T, 87)) {
    printf("found\n");
  } else {
    printf("not found\n");
  }

  // 从大到小输出值大于 k 的结点.
  Output(T, 60);

  return;
}

Status MyVisit(BiTElemType e) {
  printf("%c", e);

  return OK;
}
