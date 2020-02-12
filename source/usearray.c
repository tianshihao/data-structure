/***************************
 * @file  : usearray.c
 * @brief : 测试数组
 * @author: 田世豪
 * @date  : 2020-1-30
 * ************************/

#include "array.h"

int main()
{
    Array A;

    // 构造一个三维数组, 其三维界限分别为2, 3, 4
    InitArray(&A, 3, 2, 3, 4);

    Assign(&A, 3, 0, 0, 0);
    Assign(&A, 99, 0, 0, 1);

    ElemType v = 0;

    Value(A, &v, 0, 0, 1);

    printf("%d\n", v);

    // DestoryArray(&A);

    return 0;
}