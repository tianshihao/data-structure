﻿/**
 * @file bstree.c
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 二叉排序树方法实现
 * @version 0.2
 * @date 2020-12-21
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <bstree.h>

Status InitTreeBS(BSTree *T) {
  *T = NULL;
  return OK;
}

Status InsertBS(BSTree *T, BSTElem e) {
  /* 找到了合适的位置. */
  if (*T == NULL) {
    (*T) = malloc(sizeof(BSTNode));
    (*T)->data = e;
    (*T)->lchild = (*T)->rchild = NULL;
    return OK;
  }
  /* 树中存在相同关键字的结点, 插入失败. */
  else if (e == (*T)->data) {
    return ERROR;
  }
  /* 插入到左子树中. */
  else if (e < (*T)->data) {
    return InsertBS(&(*T)->lchild, e);
  }
  /* 插入到右子树中. */
  else {
    return InsertBS(&(*T)->rchild, e);
  }
}

Status CreateTreeBS(BSTree *T, BSTElem *str, int n) {
  *T = NULL;

  /* 计数器. */
  int i = 0;

  while (i < n) {
    InsertBS(T, str[i]);
    i++;
  }

  return OK;
}

Status SearchElem(BSTree T, BSTElem e) {
  if (T == NULL) {
    return ERROR;
  }
  if (e == T->data) {
    return OK;
  } else if (e < T->data) {
    return SearchElem(T->lchild, e);
  } else {
    return SearchElem(T->rchild, e);
  }
}

void Output(BSTree T, KeyType k) {
  if (T == NULL) {
    return;
  }
  if (T->rchild != NULL) {
    Output(T->rchild, k);
  }
  if (T->data >= k) {
    printf("%d", T->data);
  }
  if (T->lchild != NULL) {
    Output(T->lchild, k);
  }
}
