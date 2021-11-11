﻿/**
 * @file sort.h
 * @author tianshihao4944@126.com
 * @brief 排序算法.
 * @version 0.3
 * @date 2020-11-25
 * @copyright Copyright (c) 2020
 */

#ifndef SORT_H
#define SORT_H

#include <status.h>

/**
 * @brief Comparison between sort algorithm.
 * Algorithm               Time complexity        Space complexity
 * ---------------- Best      *Average  Worst                             Stable
 * Shell            O(n^1.3)  O(n^1.3)  O(n^2)    O(1)                    No
 * Insertion        O(n)      O(n^2)/4  O(n^2)    O(1)                    Yes 
 * Binary insertion \         O(n^2)    \         O(1)                    Yes
 * Selection        \         O(n^2)    \         O(1)                    NO
 * Bubble           O(n)      O(n^2)    O(n^2)    O(1)                    Yes 
 * Heap             \         O(nlogn)  \         O(1)                    No
 * Merge            \         O(nlogn)  \         O(n)                    Yes 
 * *Quick           O(nlogn)  O(nlogn)  O(n^2)    O(logn) best, O(n) avg. Usually not.
 */

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
 * 达到最大, 为 (2->n)Σi, 还要与 0 号元素哨兵比较, 故不是 i-1; 总的移动次数也
 * 达到最大, 为 (2->n)Σ(i+1), 即时间复杂度为 O(n^2).
 * @note 在平均情况下, 总的比较次数和移动次数约为 (n^2)/4.
 * @note 稳定性: 稳定.
 * @note 适用性: 顺序存储和链式存储的线性表.
 * @param arr 0 号索引为辅助空间的顺序存储结构, 数组. 
 * @param n 数组长度.
 */
void InsertionSort(ElemType arr[], int n);

/**
 * @brief 折半插入排序.
 * @note 就是插入排序插入的时候不一个一个和有序区间比较, 而是在有序区间折半.
 * @note 空间效率: 仅使用了常数个辅助单元, 因而空间复杂度为 O(1).
 * @note 时间效率: 时间复杂度仍为 O(n^2).
 * @note 相比于直接插入排序, 使用折半查找减少了比较元素的次数, 约为 O(nlogn),
 * 且该比较次数与待排序表的初始状况无关, 仅取决于表中元素个数 n; 而元素的
 * 移动次数未改变, 它依赖于待排序表的初始状况.
 * @note 适用性: 对于数据量不是很大的待排序表, 能表现出很好的性能.
 * @note 稳定性: 稳定.
 * @param arr 数组.
 * @param n 数组长度.
 */
void BinaryInsertionSort(ElemType arr[], int n);

/**
 * @brief 希尔排序, 又称缩小增量排序.
 * @note 空间效率: 仅使用了常数个辅助单元, 因而空间复杂度为 O(1).
 * @note 时间效率: 当 n 在某个特定范围时, 希尔排序的时间复杂度约为 O(n^1.3),
 * 最坏情况下希尔排序的时间复杂度为 O(n^2).
 * @note 适用性: 仅适用于线性表为顺序存储.
 * @note 稳定性: 不稳定.
 * @param arr 数组.
 * @param n 数组长度.
 */
void ShellSort(ElemType arr[], int n);

/**
 * @brief 冒泡排序.
 * @note 空间效率: 仅使用了常数个辅助单元, 因而空间复杂度为 O(1).
 * @note 时间效率: 平均时间复杂度为 O(n^2).
 * @note 在最好的情况下, 即初始比较序列有序时, 显然第 1 趟排序后直接跳出循环,
 * 比较次数仅为 n-1, 移动次数为 0, 从而此时时间复杂度为 O(n).
 * @note 在最坏的情况下, 即初始比较序列逆序时, 需要进行 n-1 趟排序. 第 i 趟排序
 * 要进行 n-i 次比较, 而且每次比较都必须移动元素 3 次来交换元素位置. 在这种情况
 * 下, 比较次数(1->n-1)Σ(n-i)=n(n-1)/2, 移动次数(i->n-1)Σ3(n-i)=3n(n-1)/2. 从而,
 * 此时的时间复杂度为 O(n^2).
 * @note 稳定性: 稳定.
 * @param arr 数组.
 * @param n 数组长度.
 */
void BubbleSort(ElemType arr[], int n);

/**
 * @brief 快速排序.
 * @note 空间效率: 由于快速排序是递归的, 因此需要借助一个递归工作栈来保存每一层
 * 调用时的必要信息, 其容量因与递归调用的最大深度一致. 最好的情况下为log2(n+1)取上底;
 * 最坏的情况下, 因为要进行 n-1 次递归调用, 所以栈的深度是 O(n); 平均情况下,
 * 栈的深度是 O(log2n). 因此,空间复杂度在最坏的情况下为 O(n), 平均情况下为 O(log2n).
 * @note 时间效率: 平均情况下, 时间复杂度为 O(nlog2n). 最坏的情况发生在两个区域
 * 分别包含 n-1 和 0 个元素时, 若这种情况发生在递归的每一层上, 就得到了最坏情况
 * 的时间复杂度 O(n^2). 当 Partition() 做到平衡的划分时, 效率大大提高, 此时的
 * 时间复杂度为 0(nlog2n). 平均情况下的的运行时间和最佳情况下的运行时间很接近,
 * 也是 O(nlog2n).
 * ! 快速排序是所有内部排序算法中平均性能最优的排序算法.
 * @note 稳定性: 不稳定.
 * @param arr 数组.
 * @param low 排序开始索引.
 * @param high 排序结束索引.
 */
void QuickSort(ElemType arr[], int low, int high);

/**
 * @brief 1 趟快速排序过程的划分算法.
 * @param A 数组.
 * @param low 划分开始索引.
 * @param high 划分结束索引.
 * @return int 存放枢轴的最终位置.
 */
int Partition(ElemType arr[], int low, int high);

/**
 * @brief 归并排序.
 * @note 空间效率: 操作 Merge() 中正好要占用 n 个单元, 所以归并排序的空间复杂度
 * 为 O(n).
 * @note 时间效率: 每一趟归并排序的时间复杂度为 O(n), 共需进行 log2n 取上底趟
 * 归并, 所以算法时间复杂度为 o(nlog2n).
 * @note 稳定性: 由于 Merge() 操作不会改变相同关键字记录的相对次序, 所以 2 路归并
 * 是一个稳定的算法.
 * @param arr 数组.
 * @param low 排序开始索引.
 * @param high 排序结束索引.
 * @param n 数组长度, 数组 arr 被当作参数传递之后, 在子函数中退化为指针, 无法计算
 * 数组长度, 导致算法出错, 故把数组长度也一并传递过去.
 */
void MergeSort(ElemType arr[], int low, int high, int n);

/**
 * @brief 归并操作. 将前后相邻的两个有序表归并为一个有序表的算法.
 * @note 为了操作方便, 数组索引为 0 的元素作为存放临时变量的地方, 只将索引从 1 到 n 的元素排序.
 * @param arr 数组.
 * @param low 归并开始索引.
 * @param mid mid = (low + high) / 2.
 * @param high 归并结束索引.
 * @param n 数组的长度.
 */
void Merge(ElemType arr[], int low, int mid, int high, int n);
/**
 * @brief 建立大根堆
 * @param arr 数组.
 * @param len 数组长度.
 */
void BuildMaxHeap(ElemType arr[], int len);

/**
 * @brief 堆调整. 将元素 parent 为根的子树进行调整. 即堆化, Heapify.
 * @note 时间效率: 调整的时间与树高有关, 为 O(h). 在建立含 n 个元素的堆时, 关键字
 * 的总比较次数不超过 4n, 时间复杂度为 O(n), 这说明可以在线性时间内将一个无序数组
 * 建成一个堆. 
 * @param arr 数组.
 * @param parent 以 parent 为根的某一子树.
 * @param len 数组长度.
 */
void HeapAdjust(ElemType arr[], int parent, int len);

/**
 * @brief 堆排序.
 * @note 空间效率: 仅使用了常数个辅助单元, 所以空间复杂度为 O(1).
 * @note 时间效率: 建堆时间为 O(n), 之后有 n-1 次向下调整的操作, 每次调整
 * 时间复杂度为 O(h), 故在最好, 最坏和平均情况下, 堆排序的时间复杂度为 O(nlog2n).
 * @note 稳定性: 不稳定.
 * @param arr 数组.
 * @param len 数组长度.
 */
void HeapSort(ElemType arr[], int len);

/**
 * @brief 简单选择排序.
 * @note 空间效率: 仅使用了常数个辅助单元, 故空间复杂度为 O(1).
 * @note 时间效率: 元素的比较次数与待排序序列初始状态无关, 始终为 n(n-1)/2 次,
 * 因此时间复杂度为 O(n^2). 此外, 元素的移动操作很少, 待排序序列逆序时, 最多,
 * 为 3n(n-1)/2 次; 有序时, 最少, 0 次.
 * @note 稳定性: 不稳定.
 * @param arr 数组.
 * @param len 数组长度.
 */
void SelectionSort(ElemType arr[], int len);

/**
 * @brief 交换元素 *A 和 *B 的值. 一共移动元素 3 次.
 * @param A 指向元素 A 的指针.
 * @param B 指向元素 B 的指针.
 */
void Swap(ElemType *A, ElemType *B);

/**
 * @brief 王道数据结构323/2, 双向冒泡排序, 又称筛动排序(Shaker Sort),
 * 鸡尾酒排序(Cocktail Sort).
 * @param A 待排序数组.
 * @param n 数组长度.
 */
void BidirectionalBubbleSort(ElemType A[], int n);

/**
 * @brief 王道数据结构323/3, 将所有奇数移动到所有偶数后面. 基于快速排序划分思想,
 * 时间复杂度为 O(n). 空间复杂度为 O(1);
 * @param A 数组.
 * @param n 数组长度.
 */
void Move(ElemType A[], int n);

/**
 * @brief 王道数据结构324/5, 找到数组中第 k 小的元素. 平均情况下时间复杂度为 O(n).
 * @param A 数组.
 * @param low 数组下界.
 * @param high 数组上界.
 * @param k 次序.
 */
int KthElem(ElemType A[], int low, int high, int k);

typedef enum Color
{
    RED,
    WHITE,
    BLUE
} Color;
/**
 * @brief 王道数据结构324/7, 荷兰国旗问题, 给定一个仅有红, 白, 蓝三种颜色的条块
 * 组成的条状序列, 是这些条块按红, 白, 蓝的顺序排好, 即荷兰国旗图案. 时间复杂度O(n).
 * @param A 颜色序列.
 * @param n 序列长度.
 */
void FlagArrange(Color A[], int n);

#endif /* SORT_H */
