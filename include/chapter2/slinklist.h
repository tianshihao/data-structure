/**
 * @file  : sqlist.h
 * @brief : 静态链表
 * @author: 田世豪
 * @date  : 2020-07-26
 * */

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef int ElemType;

typedef struct
{
    ElemType data;
    int next;
} SLinklist[MAX_SIZE];
