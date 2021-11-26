/**
 * @file bitree.c
 * @author tianshihao
 * @brief implementation of binary tree function.
 * @version 0.2
 * @date 2020-08-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <bitree.h>
#include <sqqueue.h>
#include <sqstack.h>

Status InitTreeBinary(BiTree *t) {
  *t = NULL;  // 使得指针指向 NULL.

  return OK;
}

/**
 * 即使 BiTree 类型和 BiTNode * 等价, 表面上是指针, 但是在指针传递时, 仍要取
 * BiTree 的地址, 因为在子函数中需要改变是指针本身的内容 (改变了结点间的链接关
 * 系), 而不是指针指向的内容, 因此子函数参数列表中写 BiTree *t, 否则只能传递一份
 * 指向某二叉树的指针, 在子函数中修改了二叉树后, 主函数中的指针仍然指向 NULL.
 *
 * 简单的理解是, 在 C 语言中, 若想使得传递的参数实际被修改, 则在子函数中加上一层
 * 指针总是没有错的, 不论传递的参数是什么, 包括指针.
 */

Status CreateBinaryTreeFromFile(BiTree *t, const char *path) {
  // 打开存储二叉树先序序列的文件.
  FILE *fp = fopen(path, "r");

  // 如果文件打开失败, 返回 ERROR.
  if (fp == NULL) {
    printf("No such file %s\n", path);
    return ERROR;
  }
  printf("Load binay tree from file %s.\n", path);

  // 传递的还是二叉树指针的指针.
  CreateTreeBinary(t, fp);

  fclose(fp);

  return OK;
}

void CreateTreeBinary(BiTree *t, FILE *pre_seq) {
  char ch = 0;

  // 读取当前结点的值
  ch = fgetc(pre_seq);

  if ('^' != ch)  // 使用'^'表示空结点.
  {
    // 为根结点指针分配要指向要内存空间.
    *t = (BiTNode *)malloc(sizeof(BiTNode));
    if (!*t) {
      exit(OVERFLOW);
    }

    (*t)->data = ch;
    // 递归创建左右子树.
    CreateTreeBinary(&((*t)->lchild), pre_seq);
    CreateTreeBinary(&((*t)->rchild), pre_seq);
  } else {
    *t = NULL;
    return;
  }
}

Status PreOrderTraverseBinaryRecur(BiTree t, Status (*Visit)(BiTElemType e)) {
  if (NULL != t) {
    if (Visit(t->data)) {
      if (PreOrderTraverseBinaryRecur(t->lchild, Visit)) {
        if (PreOrderTraverseBinaryRecur(t->rchild, Visit)) {
          return OK;
        }
      }
    }
    return ERROR;
  } else {
    return OK;
  }
}

Status PreOrderTraverseBinaryNonRecur(BiTree t,
                                      Status (*Visit)(BiTElemType e)) {
  SqStack *s;
  InitStackSq(s);

  // 工作指针.
  BiTNode *p = t;

  while (NULL != p || !StackEmptySq(*s)) {
    /**
     * 1. 沿着根的左子, 一遍访问, 一遍入栈, 直至当前结点为空, 为空时说明该访
     * 问右子了.
     */
    if (NULL != p) {
      Visit(p->data);
      PushSq(s, *p);
      p = p->lchild;
    }
    /**
     * 2. 将结点从栈中弹出, 若其右子为空, 则继续执行 2, 否则右子树继续执行 1.
     */
    else {
      PopSq(s, &p);
      p = p->rchild;
    }
  }

  return OK;
}

Status InOrderTraverseBinaryRecur(BiTree t, Status (*Visit)(BiTElemType e)) {
  if (NULL != t) {
    if (InOrderTraverseBinaryRecur(t->lchild, Visit)) {
      if (Visit(t->data)) {
        if (InOrderTraverseBinaryRecur(t->rchild, Visit)) {
          return OK;
        }
      }
    }
    return ERROR;
  } else {
    return OK;
  }
}

Status InOrderTraverseBinaryNonRecur(BiTree t, Status (*Visit)(BiTElemType e)) {
  // 顺序栈.
  SqStack *s;
  InitStackSq(s);

  // 工作指针.
  BiTNode *p = t;

  while (NULL != p || !StackEmptySq(*s)) {
    /**
     * 沿着左子一路入栈, 不访问, 相当于把左子访问顺序滞后, 从而可以先访问根结点.
     */
    if (NULL != p) {
      PushSq(s, *p);
      p = p->lchild;
    }

    /**
     * 若左子为空, 按照中序遍历的规则, 应遍历根结点, 因此弹栈.  之后要遍历右子,
     * 所以工作指针指向右子.
     */
    if (!StackEmptySq(*s)) {
      PopSq(s, &p);
      Visit(p->data);
      p = p->rchild;
    }
  }

  return OK;
}

Status PostOrderTraverseBinaryRecur(BiTree t, Status (*Visit)(BiTElemType e)) {
  if (NULL != t) {
    if (PostOrderTraverseBinaryRecur(t->lchild, Visit)) {
      if (PostOrderTraverseBinaryRecur(t->rchild, Visit)) {
        if (Visit(t->data)) {
          return OK;
        }
      }
    }
    return ERROR;
  } else {
    return OK;
  }
}

Status PostOrderTraverseBinaryNonRecur(BiTree t,
                                       Status (*Visit)(BiTElemType e)) {
  SqStack s;
  InitStackSq(&s);

  // p 是工作指针.
  BiTNode *p = t;

  // r 记录最近访问过的结点.
  BiTNode *r = NULL;

  /**
   * 后续非递归遍历二叉树是先访问左子树, 再访问右子树, 最后访问根结点.
   */

  while (NULL != p || !StackEmptySq(s)) {
    /**
     * 1. 沿着根结点的左子, 依次入栈, 直至左子为空.
     */
    if (NULL != p) {
      PushSq(&s, *p);
      p = p->lchild;
    }
    /**
     * 左子为空之后再判断右子, 如果右子也为空, 则需要将栈顶元素出栈. 否则,
     * 右子树也要执行 1.
     */
    else {
      GetTopSq(s, &p);
      /**
       * 2. 若栈顶元素右子非空且未访问过, 则将右子执行 1.
       */
      /**
       * 注意, 原来 PushSq 只是将结点复制了一份存到了栈中, 所以 r 记录的上
       * 次访问过的结点和栈中相对应的结点并不相同, 不能直接使用
       * p->rchild != r 比较, 可以比较 data. 但是二叉树中可能会出现重复的
       * 元素, 比较 data 会出现误差, 所以修改 PushSq 为向栈中存放二叉树中
       * 结点本身, 而不是拷贝比较好.
       *
       * 刚才试了一下, 还是直接比较 data 方便.
       */
      if (NULL != p->rchild && p->rchild->data != r->data) {
        p = p->rchild;
        PushSq(&s, *p);  // 右子入栈.
        p = p->lchild;   // 检查右子左子.
      }
      /**
       * 否则栈顶元素出栈, 并访问.
       */
      /**
       * @see LevelOrderTraverseBinary(BiTree t, Status (*Visit)(ElemType e))
       *
       * 这里 PopSq 中第二个参数是类型是 BiTNode **, 即指向 BiTNode 指针的指
       * 针, 并不是我需要修改栈中的存储的元素本身, 而是只用当指针 p 为 NULL
       * 时, 才会使用 PopSq, 而 NULL 并没有指向的内容, 不能修改 p 指向的内
       * 容, 也就无法复制栈中的元素, 而在 PopSq 中为 p malloc 存储空间又改
       * 变了指针本身, 所以将参数改为 BiTNode **, 直接修改 *p, 即 BiTNode*.
       */
      else {
        PopSq(&s, &p);
        Visit(p->data);
        r = p;     // 更新最近访问结点.
        p = NULL;  // 结点访问之后置 p 为 NULL.
      }
    }
  }

  return OK;
}

Status LevelOrderTraverseBinary(BiTree t, Status (*Visit)(BiTElemType e)) {
  // 初始化辅助队列.
  SqQueue q;
  InitQueueSq(&q);

  // 二叉树根结点入队, 根结点为第一层.
  EnQueueSq(&q, *t);

  /**
   * @see PostOrderTraverseBinaryNonRecur(BiTree t, Status (*Visit)(ElemType e))
   *
   * 层序遍历 LevelOrderTraverseBinary 中队列出队操作没有像出栈操作一样修改
   * 为传递指针的指针, 原因是出队之前, 工作指针 p 未被初始化为 NULL, 算法也使得
   * p 不可能为 NULL, 所以在 DeQueueSq 中, 子函数修改了已经指向某块内存的
   * 指针 (不管这个指针指向什么, 即使是指向初始化时的随机内存单元) 所指向的内容,
   * 并没有修改指针本身, 所以原来的算法可以继续使用, 无需修改.
   * 这样做带来的副作用 是, 初始化指针 p 时, p 可能指向任何内存单元,
   * 向这个内存单元写入数据, 把原 来的数据覆盖掉, 可能会导致系统崩溃.
   * 我发现的副作用是多次执行这个函数, 输出 的结果可能不同.
   *
   * 但实际上, 编译器会将未初始化的指针指向固定的, 不用的地址. 可以试一试如下
   * 代码:
   *
   * int *p;
   *
   * printf(">>>>>>>>>>> *p = %d <<<<<<<<<<<\n", *p);
   *
   * system("pause");
   *
   * 相信每次的输出结果都是一样的, 例如:
   *
   * >>>>>>>>>>> *p = 17744 <<<<<<<<<<<
   * 请按任意键继续. . .
   *
   */

  // // 工作指针.

  // BiTNode *p = NULL;
  BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
  p->lchild = NULL;
  p->rchild = NULL;

  while (!QueueEmptySq(q)) {
    // 队头结点出队.
    DeQueueSq(&q, p);

    // 访问出队结点.
    Visit(p->data);

    // 左子树不为空, 则左子树根结点入队.
    if (p->lchild != NULL) {
      EnQueueSq(&q, *p->lchild);
    }

    // 右子树不为空, 则右子树根结点入队.
    if (p->rchild != NULL) {
      EnQueueSq(&q, *p->rchild);
    }
  }

  DestoryQueueSq(&q);

  return OK;
}

Status InvertLevelTraverseBinary(BiTree t, Status (*Visit)(BiTElemType e)) {
  if (t != NULL) {
    SqQueue q;
    InitQueueSq(&q);
    EnQueueSq(&q, *t);

    SqStack S;
    InitStackSq(&S);

    BiTNode *p = t;

    while (!QueueEmptySq(q)) {
      DeQueueSq(&q, p);

      PushSq(&S, *p);

      if (p->lchild != NULL) {
        EnQueueSq(&q, *p->lchild);
      }

      if (p->rchild != NULL) {
        EnQueueSq(&q, *p->rchild);
      }
    }

    while (!StackEmptySq(S)) {
      PopSq(&S, &p);
      Visit(p->data);
    }
    return OK;
  } else {
    return ERROR;
  }
}

int BiTreeHeight(BiTree t) {
  if (t != NULL) {
    /* 初始化队列. */
    SqQueue q;
    InitQueueSq(&q);

    /* 根节点入队. */
    EnQueueSq(&q, *t);

    /* 计数器, 记录二叉树的高度. */
    int height = 0;

    /* 工作指针 p. */
    /* BiTNode *p = t; */
    BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
    p->lchild = NULL;
    p->rchild = NULL;

    /* 指针指向每层最右边结点在队列中的位置. */
    int last = q.rear;

    while (!QueueEmptySq(q)) {
      /* 队头结点出队. */
      DeQueueSq(&q, p);

      if (p->lchild != NULL) {
        EnQueueSq(&q, *p->lchild);
      }

      if (p->rchild != NULL) {
        EnQueueSq(&q, *p->rchild);
      }

      /**
       * 在过程中出现队空的情况, 表示上一层元素都出栈了.
       */
      if (q.front == last) {
        /* 层数加 1. */
        ++height;

        /**
         * 更新标记.
         * 上一层的结点都出队完了, 也代表本层的结点全部入队了,
         * 此时队尾指针指向本层最后一个结点后面, 将其位置记录下来.
         *
         */
        last = q.rear;
      }
    }

    // 释放工作指针.
    free(p);
    p = NULL;

    DestoryQueueSq(&q);

    return height;
  } else {
    // 树空, 高度为 0.
    return 0;
  }
}

BiTree PreInCreate(BiTElemType *pre_order, int pre_l, int pre_r,
                   BiTElemType *in_order, int in_l, int in_r) {
  /* 创建根结点. */
  BiTree root = (BiTNode *)malloc(sizeof(BiTNode));

  /* 先序遍历序列第一个值是根结点的值. */
  root->data = pre_order[pre_l];

  /* 在中序遍历序列中找到根结点的位置. */
  int root_pos = in_l;
  while (in_order[root_pos] != root->data) {
    ++root_pos;
  }

  /* 左子树长度. */
  int lchild_len = root_pos - in_l;

  /* 右子树长度. */
  int rchild_len = in_r - root_pos;

  /* 左子树不为空. */
  if (lchild_len > 0) {
    /* 注意 +1, -1 边界条件. */
    // 构造左子树的参数中, 索引都和左边界有关.
    root->lchild = PreInCreate(pre_order, pre_l + 1, pre_l + lchild_len,
                               in_order, in_l, in_l + lchild_len - 1);
  } else {
    root->lchild = NULL;
  }

  /* 右子树不为空. */
  if (rchild_len > 0) {
    // 构造右子树的参数中, 索引都和右边界有关.
    root->rchild = PreInCreate(pre_order, pre_r - rchild_len + 1, pre_r,
                               in_order, in_r - rchild_len + 1, in_r);
  } else {
    root->rchild = NULL;
  }

  return root;
}

Status SwapSubTree(BiTree t) {
  /* 两种写法均可. */
  if (NULL != t) {
    SwapSubTree(t->lchild);
    SwapSubTree(t->rchild);

    BiTNode *tmp = t->lchild;
    t->lchild = t->rchild;
    t->rchild = tmp;
  }

#if 0
    BiTNode *tmp = t->lchild;
    t->lchild = t->rchild;
    t->rchild = tmp;

    if (t->lchild)
    {
        SwapSubTree(t->lchild);
    }

    if (t->rchild)
    {
        SwapSubTree(t->rchild);
    }
#endif

  return OK;
}

Status FindAncestor(BiTree t, BiTElemType x) {
  // 临时的栈.
  typedef struct TmpStack {
    BiTNode *node;
    int tag;  // 标志域, 结点 *node 右子被访问 tag = 1, 否则为 0.
  } TmpStack;

  // 算法本质是后序遍历过程, 所以栈的深度不会超过树的深度.
  TmpStack s[BiTreeHeight(t) + 1];
  // 栈顶指针. 从 1 开始, 0 表示空栈.
  int top = 0;

  // 工作指针 p.
  BiTNode *p = t;

  while (p != NULL || top > 0) {
    // 一路向左, 将结点入栈.
    while (p != NULL && p->data != x) {
      s[++top].node = p;
      s[top].tag = 0;
      p = p->lchild;  // 向左.
    }

    // 如果找到了 x. 注意上面的循环出来时 p 可以为空, 还要判空.
    if (p != NULL && p->data == x) {
      for (int i = 1; i <= top; ++i) {
        printf("%c%c", s[i].node->data, i == top ? '\n' : ',');
      }
      // exit(OK);
      return OK;
    }

    // 退栈.
    while (top > 0 && s[top].tag == 1) {
      top--;
    }

    // 沿着右分支向下遍历.
    if (top != 0) {
      s[top].tag = 1;           // 栈顶元素右子被访问了.
      p = s[top].node->rchild;  // 跳到右子.
    }
  }

  return ERROR;
}

BiTNode *FindCommonAncestor(BiTree t, BiTNode *p, BiTNode *q) {
  // 临时的栈.
  typedef struct stack {
    BiTNode *node;
    int tag;  // 标志域, 结点 *node 右子被访问 tag = 1, 否则为 0.
  } stack;

  // 算法本质是后序遍历过程, 所以栈的深度不会超过树的深度.
  stack s[BiTreeHeight(t) + 1];
  // 栈顶指针. 从 1 开始, 0 表示空栈.
  int top = 0;

  stack s1[BiTreeHeight(t) + 1];
  int top1 = 0;

  // 工作指针.
  BiTNode *ptr = t;

  while (ptr != NULL || top > 0) {
    // 沿着左子入栈.
    // ? 书中答案这个外面的 while 是不是是错了?
    // while (ptr != NULL && ptr != p && ptr != q)
    {
      while (ptr != NULL) {
        s[++top].node = ptr;
        s[top].tag = 0;
        ptr = ptr->lchild;
      }
    }

    /**
     * @see FindAncestor(BiTree t, ElemType x)
     * 退栈, FindAncestor 中退栈上面的操作也可以向下面这样写到退栈循环里面,
     * 先于 top-- 执行.
     */
    while (top > 0 && s[top].tag == 1) {
      // 找到了结点 p, 复制 s 即 p 的祖先到辅助栈 s1. 再继续寻找 q.
      if (s[top].node == p) {
        for (int i = 1; i <= top; ++i) {
          s1[i] = s[i];
        }
        top1 = top;
      }

      // 找到 q 时, 栈 s 中为 q 的祖先, 而 s1 中为 p 的祖先, 比较两个栈,
      // 将 q 的祖先到 p 的祖先中去匹配, 第一个匹配的元素就是 p 和 q 的
      // 最近公共祖先.
      if (s[top].node == q) {
        for (int i = top; i > 0; --i) {
          for (int j = top1; j > 0; --j) {
            if (s1[j].node == s[i].node) {
              return s[i].node;
            }
          }
        }
      }

      // 后序遍历中到了访问根结点时, 其左右子均已被访问, 访问完根结点, 根
      // 结点退栈.
      top--;
    }

    // 访问右子树.
    if (top != 0) {
      s[top].tag = 1;
      ptr = s[top].node->rchild;
    }
  }

  return NULL;
}

int BiTreeWidth(BiTree t) {
  if (t != NULL) {
    SqQueue q;
    InitQueueSq(&q);

    BiTNode *p = t;

    EnQueueSq(&q, *p);

    int last = q.rear;
    int cur_width = 0;
    int max_width = 0;

    while (!QueueEmptySq(q)) {
      DeQueueSq(&q, p);

      ++cur_width;

      if (p->lchild != NULL) {
        EnQueueSq(&q, *p->lchild);
      }

      if (p->lchild != NULL) {
        EnQueueSq(&q, *p->rchild);
      }

      if (last == q.front) {
        last = q.rear;
        if (cur_width > max_width) {
          max_width = cur_width;
        }
        cur_width = 0;
      }
    }

    return max_width;
  } else {
    return 0;
  }
}

void PreToPost(BiTElemType *pre_order, int preL, int preR,
               BiTElemType *post_order, int postL, int postR) {
  if (preR >= preL) {
    // 满二叉树左右子树在遍历序列中的长度相等.
    int half = (preR - preL) / 2;

    post_order[postR] = pre_order[preL];

    /**
     * 即先序遍历序列的非根结点部分的二分遍历. 每次二分都需要挖去先序序列中
     * 的最左边的元素 (即根结点), 且每次二分的长度都是上次的 1/2.
     */
    PreToPost(pre_order, preL + 1, preL + half, post_order, postL,
              postL + half - 1);

    PreToPost(pre_order, preL + half + 1, preR, post_order, postL + half,
              postR - 1);
  }
}

Status Similar(BiTree t1, BiTree t2) {
  if (t1 == NULL && t2 == NULL) {
    return TRUE;
  } else if (t1 == NULL || t2 == NULL) {
    return FALSE;
  } else {
    return Similar(t1->lchild, t2->lchild) && Similar(t1->rchild, t2->rchild);
  }
}

int WPL(BiTree t) { return WPLPreOrder(t, 1); }

int WPLPreOrder(BiTree p, int depth) {
  static int wpl = 0;

  // 若是叶结点, 累计 wpl.
  if (p->lchild == NULL && p->rchild == NULL) {
    wpl += depth * p->data;
  }

  // 若左子树不空, 则对左子树进行递归调用.
  if (p->lchild != NULL) {
    WPLPreOrder(p->lchild, depth + 1);
  }

  // 若右子树不空, 则对右子树进行递归调用.
  if (p->rchild != NULL) {
    WPLPreOrder(p->rchild, depth + 1);
  }

  return wpl;
}

int WPLLevelOrder(BiTree t) {
  // 顺序队列.
  SqQueue q;
  InitQueueSq(&q);

  // 工作指针 p.
  BiTNode *p = t;

  // 根结点入队.
  EnQueueSq(&q, *p);

  // 记录队尾指针, 用于判断一层是否遍历完毕.
  int last = q.rear;

  // wpl.
  int wpl = 0;

  // 当前访问的叶结点深度. 根结点以入队, 所以初始深度为 1.
  int depth = 1;

  while (!QueueEmptySq(q)) {
    DeQueueSq(&q, p);

    // 找到叶子结点, 更新 wpl.
    if (p->lchild == NULL && p->rchild == NULL) {
      wpl += depth * p->data;
    }

    if (p->lchild != NULL) {
      EnQueueSq(&q, *p->lchild);
    }

    if (p->rchild != NULL) {
      EnQueueSq(&q, *p->rchild);
    }

    if (last == q.front) {
      ++depth;
      last = q.rear;
    }
  }

  return wpl;
}

char predt = 0;

Status JudgeBST(BiTree t) {
  if (t == NULL) {
    return TRUE;
  } else {
    // 判断左子树.
    int left = JudgeBST(t->lchild);

    // 如果左子树不是二叉排序树或者前驱结点即左子的值大于当前结点,
    if (left == 0 || predt >= t->data) {
      // 则不是二叉排序树.
      return FALSE;
    }

    // 更新前驱结点值.
    predt = t->data;

    // 判断右子树.
    int right = JudgeBST(t->rchild);
    // 返回右子树的结果.
    return right;
  }
}

Status JudgeAVL(BiTree t, int *height, int *balance) {
  int lheight = 0, lbalance = 0, rheight = 0, rbalance = 0;

  // 1. 若 t 为空, 则height = 0, balance = 1.
  if (t == NULL) {
    *height = 0;
    *balance = 1;
  }
  // 2. 仅有根结点, 则height = 1, balance = 1.
  else if (t->lchild == NULL && t->rchild == NULL) {
    *height = 1;
    *balance = 1;
  }
  // 3. 否则,对 t 的左右子树执行后续遍历递归算法, 返回左右子树的高度和平衡标记.
  // t 的高度为最高子树的高度加 1. 若左右子树的高度差大于 1, 则 balance = 0;
  // 若左右子树的高度差小于等于 1, 且左右子树都平衡时, balance = 1, 否则,
  // balance = 0.
  else {
    JudgeAVL(t->lchild, &lheight, &lbalance);
    JudgeAVL(t->rchild, &rheight, &rbalance);

    *height = (lheight > rheight ? lheight : rheight) + 1;

    if (lheight - rheight < 2 || rheight - lheight < 2) {
      *balance = lbalance && rbalance;
    } else {
      *balance = 0;
    }
  }
}
