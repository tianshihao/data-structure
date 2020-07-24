/*******************************
 * @file  : tsmatrix.h
 * @brief : 稀疏矩阵的三元组顺序表示
 * @author: 田世豪
 * @date  : 2020-2-6
 * ****************************/

#pragma once

#include "predefconst.h"

// 假设非零元个数的最大值为 12500
#define MAX_SIZE

typedef struct Triple
{
    int i, j;
    ElemType e;
} Triple;

typedef struct TSMatrix
{
    // 非零元三元组表, data[0] 未用
    // Triple data[MAX_SIZE + 1];
    Triple data[MAX_SIZE + 1];

    // 矩阵的行数, 列数和非零元个数
    int row_number, column_number, total_number;
} TSMatrix;

// 创建三元组表稀疏矩阵.
Status CreateTSMatrix(TSMatrix *M, int row_number, int column_number, int total_number)
{
    M->row_number = row_number;
    M->column_number = column_number;
    M->total_number = total_number;

    return OK;
}; // CreateTSMatrix

// 销毁稀疏矩阵 M.
Status DestoryTSMatrix(TSMatrix *M)
{
    free(M->data);
    M->row_number = 0;
    M->column_number = 0;
    M->total_number = 0;

    return OK;
} // DestoryTSMatrix

// 求稀疏矩阵 M 的转置矩阵 T
Status TransposeSMatrix(TSMatrix M, TSMatrix *T)
{
    /***************************************************************************
     * TransposeSMatrix() 的主要工作是在 col 和 M_index 的两重循环中完成的, 故时间复杂度
     * 为 O(column_number * total_number), 即与 M 的列数和非零元的个数的乘积成正比.
     * 与经典的矩阵转置算法
     * for(int col = 1; col <= column_number; ++col)
     *      for(int row = 1; row <= row_number; ++row)
     *          T[col][row] = M[row][col];
     * 时间复杂度为 O(row_number * column_number) 相比, 当非零元的个数 total_number 和
     * row_number * column_number 同数量级时, TransposeSMatrix 的时间复杂度就是
     * O(row_number * column_number^2), 虽然节省了空间, 但时间复杂度提高了, 因此仅适用于
     * total_number << row_number * column_number 的情况.
     * ************************************************************************/

    T->row_number = M.column_number;
    T->column_number = M.row_number;
    T->total_number = M.total_number;

    // 若存在非零元素
    if (T->total_number >= 0)
    {
        int T_index = 1;

        // 列序从 1 开始
        for (int col = 1; col <= M.column_number; ++col)

            // 扫描 M 中所有列序为 col 的元素
            for (int M_index = 1; M_index <= M.total_number; ++M_index)

                // 若找到, 则将其加至 T 中
                if (M.data[M_index].j == col)
                {
                    T->data[T_index].i = M.data[M_index].j;
                    T->data[T_index].j = M.data[M_index].i;
                    T->data[T_index].e = M.data[M_index].e;
                }
    }

    return OK;
} // TransposeSMatrix

// 快速稀疏矩阵转置.
Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T)
{
    /***************************************************************************
     * 该算法有四个并列单循环, 循环次数分别为 column_number 和 total_number, 因此总的
     * 时间复杂度为 O(column_number + total_number); 在 total_number 和
     * row_number * column_number 处于同一数量级时, 其时间复杂度为
     * O(row_number * column_number), 和上述经典算法的时间复杂度相同.
     * ************************************************************************/
    T->row_number = M.column_number;
    T->column_number = M.row_number;
    T->total_number = M.total_number;

    // 若存在非零元素
    if (T->total_number >= 0)
    {
        // num[col] 表示矩阵 M 中第 col 列中非零元的个数.
        int *num = (int *)malloc(sizeof(int) * M.column_number);
        for (int col = 1; col <= M.column_number; ++col)
            num[col] = 0;
        for (int col = 1; col <= M.total_number; ++col)
            ++num[M.data[col].j];

        // cpot[col] 指示 M 中第 col 列的第一个非零元在目标矩阵中的恰当位置.
        // 可以把 cpot 理解为一个指针数组, 里面存放了第 col 列在目标矩阵中的起始元素位置,
        // 相当于指针; 也可以把它理解为一个对照表, 可以查询第 col 列在目标矩阵中的位置.
        // 每次查询之后, 若更新目标矩阵, 则需要使指针指向下一位, 即 ++cpot[col].
        int *cpot = (int *)malloc(sizeof(int) * M.column_number);
        cpot[1] = 1;
        for (int i = 2; i <= M.column_number; ++i)
            cpot[i] = num[i - 1] + cpot[i - 1];

        for (int M_index = 1; M_index <= M.total_number; ++M_index)
        {
            // 获取第一个非零元素的列数
            int col = M.data[M_index].j;

            // 根据这个列数在 cpot 中找到其在矩阵 T 中的地址
            int addr = cpot[col];

            T->data[addr].i = M.data[col].j;
            T->data[addr].j = M.data[col].i;
            T->data[addr].e = M.data[col].e;

            // 更新
            ++cpot[col];
        } // for

        free(cpot);
        free(num);
    } // if

    return OK;
} // FastTransposeSMatrix
