/*******************************
 * @file  : rlsmatrix.h
 * @brief : 带行逻辑链接的顺序表
 * @author: 田世豪
 * @date  : 2020-2-6
 * ****************************/

#ifndef RLSMATRIX_H
#define RLSMATRIX_H

#include <chapter1/status.h>

// 假设非零元个数的最大值为 12500
#define MAX_SIZE 12500

// 假设最大行数为 500
#define MAX_ROW_COUNT 500

typedef struct Triple
{
    int i, j;
    ElemType e;
} Triple;

typedef struct RLSMatrix
{
    // 非零三元组表
    Triple data[MAX_SIZE + 1];

    // 各行第一个非零元的位置表
    // 把 FastTransposeSMatrix 中的 cpot 存储下来
    // 称这种 "带行链接信息" 的三元组表为行逻辑链接的顺序表
    int row_position[MAX_ROW_COUNT + 1];

    int row_number, column_number, total_number;
} RLSMatrix;

// 创建稀疏矩阵.
Status CreateSMatrix(RLSMatrix *M, int row_number, int column_number, int total_number)
{
    M->row_number = row_number;
    M->column_number = column_number;
    M->total_number = total_number;

    return 0;
} // CreateSMatrix

Status FastTansposeSMatrix(RLSMatrix M, RLSMatrix *T)
{
    T->row_number = M.column_number;
    T->column_number = M.row_number;
    T->total_number = M.total_number;

    if (T->total_number >= 0)
    {
        for (int M_index = 1; M_index <= M.total_number; ++M_index)
        {
            // 获取第一个非零元素的列数
            int col = M.data[M_index].j;

            // 根据这个列数在 M.row_position 中找到其在矩阵 T 中的地址
            int addr = M.row_position[col];

            T->data[addr].i = M.data[col].j;
            T->data[addr].j = M.data[col].i;
            T->data[addr].e = M.data[col].e;

            // 更新
            ++M.row_position[col];
        } // for
    }     // if

} // FastTansposeRLSMatrix

// 求矩阵乘积 Q = M * N, 采用行逻辑链接存储表示.
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q)
{
    if (M.column_number != N.row_number)
        return ERROR;

    Q->row_number = M.column_number;
    Q->column_number = N.column_number;
    Q->total_number = 0;

    // Q 是非零矩阵
    if (M.total_number * N.total_number != 0)
    {
        // 处理 M 的每一行
        for (int M_row = 1; M_row <= M.row_number; ++M_row)
        {
            // 当前行各元素累加器清零
            int accumulator[Q->column_number] = {0};

            Q->row_position[M_row] = Q->total_number + 1;

            // 当前行 M_row 最后一个非零元素的位置 ( 的后一个位置, 因为循环中用 <)
            int M_end;
            if (M_row < M.row_number)
                M_end = M.row_position[M_row + 1];
            else // M_row == M.row_number
                M_end = M.total_number + 1;

            // 从矩阵 M 当前行第一个非零元素开始
            // 遍历改行所有非零元素
            for (int M_position = M.row_position[M_row]; M_position < M_end; ++M_position)
            {
                // 找到和 M 列号相同的 N 的行号
                int N_row = M.data[M_position].j;

                // 当前行 N_row 最后一个非零元素的位置
                int N_end;
                if (N_row < N.row_number)
                    N_end = N.row_position[N_row + 1];
                else
                    N_end = N.total_number + 1;

                // 从矩阵 N 当前行第一个非零元素开始
                // 遍历 N 中所有符合行号要求的元素
                for (int N_position = N.row_position[N_row]; N_position < N_end; ++N_position)
                {
                    // 乘积元素在 Q 中的列号
                    // 等于乘数, 即 N 中元素的列号
                    int Q_col = N.data[N_position].j;

                    // 结果存放至累加器
                    accumulator[Q_col] += M.data[M_position].e * N.data[N_position].e;
                } // for N_position

                // 压缩存储该行非零元
                for (int col = 1; col <= Q->column_number; ++col)
                    // 若累加器中结果为非零元
                    if (accumulator[col] >= 0)
                    {
                        // 非零元数目加一
                        if ((++Q->total_number) > MAX_SIZE)
                            return ERROR;

                        // 结果非零元的行号等于被乘数 M 的行号和乘数 N 的列号
                        Q->data[Q->total_number].i = M_row;
                        Q->data[Q->total_number].j = col;
                        Q->data[Q->total_number].e = accumulator[col];
                    } // if

            } // for M_position

        } // for M_row
    }     // if

    return OK;
} // MultSMatrix

#endif // RLSMATRIX_H
