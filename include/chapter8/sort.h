﻿/**
 * @file sort.h
 * @author tianshihao4944@126.com
 * @brief 排序算法.
 * @version 0.1
 * @date 2020-10-27
 * @copyright Copyright (c) 2020
 */

#ifndef SORT_H
#define SORT_H

typedef int ElemType;

/**
 * @brief 直接插入排序, 排序结果为非递减序列.
 * @note 空间效率: 仅使用了常数个辅助单元, 因而空间复杂度为 O(1).
 * @note 时间效率: 在排序过程中, 向有序子表中逐个插入元素的操作进行了 n - 1 趟,
 * 都为比较关键字和移动元素, 因此比较次数和移动次数取决于待排序表的初始状态.
 * 时间复杂度为 O(n^2).
 * @note 在最好的情况下, 表中元素已经有序, 此时每插入一个, 都只需比较一次而不用
 * 移动元素, 因而时间复杂度为 O(n).
 * @note 在最坏的情况下, 表中元素刚好与排序结果中的元素顺序相反, 总的比较次数
 * 达到最大, 为 (2->n)Σi, 总的移动次数也达到最大, 为 (2->n)Σ(i+1), 即时间复杂度
 * 为 O(n^2).
 * @note 在平均情况下, 总的比较次数和移动次数约为 (n^2)/4.
 * @note 稳定性: 稳定.
 * @note 适用性: 顺序存储和链式存储的线性表.
 * @param Arr 0 号索引为辅助空间的顺序存储结构, 数组. 
 * @param n 数组长度.
 */
void InsertionSort(ElemType Arr[], int n);

#endif /* SORT_H */
