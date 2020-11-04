/**
 * @file program8.c
 * @author tianshihao4944@126.com
 * @brief 测试排序算法
 * @version 0.1
 * @date 2020-11-01
 * @copyright Copyright (c) 2020
 */

#include <chapter8/sort.h>
#include <stdio.h>

int main()
{
    ElemType Arr[9] = {0, 49, 38, 65, 97, 76, 13, 27, 49};

    for (int i = 1; i < 9; ++i)
    {
        printf("%d%c", Arr[i], i == 8 ? '\n' : ',');
    }

    // InsertionSort(Arr, 9);
    // BinaryInsertionSort(Arr, 9);
    // ShellSort(Arr, 9);
    BubbleSort(Arr, 9);

    for (int i = 1; i < 9; ++i)
    {
        printf("%d%c", Arr[i], i == 8 ? '\n' : ',');
    }

    return 0;
}