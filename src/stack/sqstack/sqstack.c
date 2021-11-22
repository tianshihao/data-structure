/**
 * @file sqstack.c
 * @author tianshihao4944@126.com
 * @brief 顺序栈函数实现.
 * @version 0.1
 * @date 2020-01-27
 * @copyright Copyright (c) 2020
 */

#include <sqstack.h>
#include <string.h>

Status InitStackSq(SqStack *S) {
  /* 栈顶指针指向分配的内存空间的起始地址. */
  S->base = (StackElemType *)malloc(STACK_INIT_SIZE * sizeof(StackElemType));

  /* 存储分配失败. */
  if (!S->base) {
    exit(OVERFLOW);
  }

  /* 初始化栈顶指针. */
  S->top = S->base;

  /* 初始化已分配空间大小. */
  S->allocated_size = STACK_INIT_SIZE;

  return OK;
}

Status StackEmptySq(SqStack S) {
  if (S.top == S.base) {
    return TRUE;
  }

  return FALSE;
}

Status PushSq(SqStack *S, StackElemType e) {
  /* 栈满, 追加存储空间. */
  if ((S->top - S->base) >= S->allocated_size) {
    S->base = realloc(
        S->base, (S->allocated_size + STACK_INCREMENT) * sizeof(StackElemType));

    /* 内存分配失败. */
    if (!S->base) {
      exit(OVERFLOW);
    }

    /* 重置栈顶指针. */
    S->top = S->base + S->allocated_size;

    /* 更新栈大小. */
    S->allocated_size += STACK_INCREMENT;
  }

  /* 更新栈顶指针, top 始终指向栈顶元素的下一位. */
  *(S->top)++ = e;

  return OK;
}

Status PopSq(SqStack *S, StackElemType *e) {
  /* 若栈为空. */
  if (S->top == S->base) {
    return ERROR;
  }

  /* 弹出元素. */
  (*e) = *(--(S->top));

  return OK;
}

Status GetTopSq(SqStack S, StackElemType *e) {
  /* 空栈. */
  if (S.top == S.base) {
    return ERROR;
  }

  /* 获取栈顶元素. */
  *e = *(S.top - 1);

  return OK;
}

Status DestoryStack(SqStack *S) {
  /* 释放顺序栈内容空间. */
  free(S->base);

  /* 置栈顶栈顶指针为空. */
  S->base = NULL;
  S->top = NULL;

  return OK;
}

void Conversion() {
  SqStack S;
  InitStackSq(&S);

  printf("Enter a decimal number: ");

  int N = 0;
  scanf("%d", &N);

  while (N) {
    PushSq(&S, N % 8);
    N = N / 8;
  }

  printf("Octal of this number is: ");

  StackElemType e;
  while (!StackEmptySq(S)) {
    PopSq(&S, &e);
    printf("%d", e);
  }

  printf("\n");

  return;
}

Status MatchBracket() {
  fputs("Enter a bracket sequence, length does not exceed 20.\n", stdout);

  SqStack s;
  InitStackSq(&s);

  char buffer[20];
  fgets(buffer, 20, stdin);

  size_t len = strlen(buffer);

  for (int i = 0; (i < len) && (buffer[i] != '\0'); ++i) {
    // 左括号压栈.
    if ((buffer[i] == '(') || (buffer[i] == '[') || (buffer[i] == '{') ||
        (buffer[i] == '<')) {
      PushSq(&s, buffer[i]);
    } else {
      StackElemType left;

      // 栈中有左括号, 将其拿出来.
      if ((!StackEmptySq(s)) && (PopSq(&s, &left))) {
        // 匹配.  使用左括号和当前括号, 也即右括号, 进行匹配.
        // 每对括号的 ASCII 相差 2, 除了 () 相差 1.
        // 匹配成功就继续, 否据函数返回不匹配.
        if ((left == (buffer[i] - 1)) || left == (buffer[i] - 2)) {
          continue;
        }
        // 不匹配.
        else {
          return FALSE;
        }
      }
      // 栈中没有左括号了, 也不匹配.
      else {
        return FALSE;
      }
    }
  }

  // 若存在未消解的左括号, 则说明匹配失败.
  if (StackEmptySq(s)) {
    return TRUE;
  }

  return FALSE;
}
