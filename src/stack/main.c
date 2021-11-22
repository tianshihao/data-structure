/**
 * @file main.c
 * @author tianshihao4944@126.com
 * @brief 测试栈.
 * @version 0.2
 * @date 2020-01-27
 * @copyright Copyright (c) 2020
 */

#include <linkstack.h>
#include <sqstack.h>

void TestStackSq();

int main() {
  TestStackSq();

  system("pause");

  return 0;
}

void TestStackSq() {
  printf("Input 1 to ");
  printf("determine whether a bracket sequence is matched.\n");
  printf("Enter 2 to ");
  printf("convert a decimal to an octal number.\n");
  printf("Or input q to quit.\n");

  char request;

  while ((request = getchar()) != 'q') {
    getchar();
    if ('1' == request) {
      if (MatchBracket()) {
        printf("Input match.\n");
      } else {
        printf("Not match.\n");
      }
    } else if ('2' == request) {
      Conversion();
    } else {
      printf("Input is invalid!\n");
    }

    // SqStack S;
    // InitStackSq(&S);
    // PushSq(&S, 2);
    // PushSq(&S, 6);
    // PushSq(&S, 10);
    // PushSq(&S, 7);

    // StackElemType e;
    // printf("%d\n", e);

    // PopSq(&S, &e);
    // printf("%d\n", e);
  }

  printf("Bye!\n");

  return;
}
