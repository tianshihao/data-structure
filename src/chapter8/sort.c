/**
 * @file sort.c
 * @author tianshihao4944@126.com
 * @brief 排序算法实现
 * @version 0.1
 * @date 2020-11-01
 * @copyright Copyright (c) 2020
 */

#include <chapter8/sort.h>

void InsertionSort(ElemType A[], int n)
{
    int i, j;
    for (i = 2; i < n; ++i)
    {
        if (A[i] < A[i - 1])
        {
            A[0] = A[i]; /* 设置哨兵. */

            for (j = i - 1; A[j] > A[0]; --j)
            {
                A[j + 1] = A[j]; /* 将小于哨兵的元素向后挪动. */
            }
            A[j + 1] = A[0]; /* 将哨兵复制到插入位置. */
        }
    }
}

void BinaryInsertionSort(ElemType A[], int n)
{
    int i, j, left, right, mid;

    for (i = 2; i < n; ++i)
    {
        if (A[i] < A[i - 1])
        {
            A[0] = A[i]; /* 设置哨兵. */

            /**
             * @brief 开始在有序子序列中折半查找合适的插入位置. 有序子序列的起始
             * 索引为 1, i - 1.
             * 查找进行到最后一趟时, 不论区间长度奇偶, 一定出现 left == right == mid,
             * 此时有 2 种情况:
             * 1) 哨兵小于 left/right 所指元素, 那么 right = right - 1,
             * right < left, 循环结束;
             * 2) 哨兵大于 left/right 所指元素, 那么 left = left + 1,
             * right < left, 循环结束.
             * 这 2 种情况下, 都有 left = right + 1, 即 left 所指的元素大于哨兵,
             * right 所指的元素小于哨兵, 故插入位置在 left 和 right 之间, 应将
             * right 之前的元素后移, right + 1 插入哨兵.
             */
            left = 1, right = i - 1;
            while (left <= right)
            {
                mid = (left + right) / 2;
                /* 合适的插入位置落在左半区间. */
                if (A[mid] > A[0]) /* 此处的 > 保证排序稳定. */
                {
                    right = mid - 1;
                }
                /* 合适的位置落在了右半区间. */
                else
                {
                    left = mid + 1;
                }
            }
            /**
             * @brief 折半查找之后, right + 1 即为要插入的位置. 统一将元素后移,
             * 空出插入位置.
             */
            for (j = i - 1; j >= right + 1; --j)
            {
                A[j + 1] = A[j];
            }

            A[right + 1] = A[0]; /* 将哨兵复制到插入位置. */
        }
    }
}

void ShellSort(ElemType A[], int n)
{
    int i, j, delta;
    for (delta = n / 2; delta >= 1; delta = delta / 2)
    {
        for (i = 1 + delta; i < n; ++i)
        {
            if (A[i] < A[i - delta])
            {
                A[0] = A[i];
                for (j = i - delta; (j > 0) && (A[0] < A[j]); j -= delta)
                {
                    A[j + delta] = A[j];
                }
                A[j + delta] = A[0];
            }
        }
    }
}

void BubbleSort(ElemType A[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        Status flag = FALSE;
        for (int j = n - 1; j > i; --j)
        {
            /* 若出现逆序. */
            if (A[j] < A[j - 1])
            {
                /* 交换元素. */
                ElemType temp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = temp;

                /* 更新标记. */
                flag = TRUE;
            }
        }
        /* 若一趟排序下来没有发生交换, 则结束算法. */
        if (flag == FALSE)
        {
            return;
        }
    }
}

void QuickSort(ElemType A[], int low, int high)
{
    if (low < high)
    {
        /* 划分 */
        int pivotPos = Partition(A, low, high);

        /* 依次对两个子表进行排序. */
        QuickSort(A, low, pivotPos - 1);
        QuickSort(A, pivotPos + 1, high);
    }

    return;
}

int Partition(ElemType A[], int low, int high)
{
    /* 将枢轴设置为当前表的第一个元素. */
    ElemType pivot = A[low];

    while (low < high)
    {
        /* 将比枢轴小的元素移动到左端. */
        while (low < high && A[high] >= pivot)
        {
            --high;
        }
        A[low] = A[high];

        /* 将比枢轴大的元素移动到右端. */
        while (low < high && A[low] <= pivot)
        {
            ++low;
        }
        A[high] = A[low];
    }

    /* 将枢轴放到最终位置. */
    A[low] = pivot;

    /* 返回存放枢轴的最终位置. */
    return low;
}

void MergeSort(ElemType A[], int low, int high, int n)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        MergeSort(A, low, mid, n);
        MergeSort(A, mid + 1, high, n);

        Merge(A, low, mid, high, n);
    }

    return;
}

void Merge(ElemType A[], int low, int mid, int high, int n)
{
    ElemType B[n];

    int i = 0, j = 0, k = 0;

    /* 将 A 中的元素复制到 B 中. */
    for (k = low; k <= high; ++k)
    {
        B[k] = A[k];
    }

    /**
     * 指针 i 指向数组 B 的待排子序列开始, 指针 j 指向数组 B 的待排序子序列结束.
     * 指针 k 指向原数组 A 的待排序子序列开始. 以最后一次归并为例, 此时数组 B
     * 复制自数组 A, 比较数组 B 的左右两部分, 相当于将 A 腾空, 存储排序后的结果.
     * 
     * B      38      49      65      97      13      27      49     79
     *        i(low)                          j(high)
     * 
     * A      13
     *        k
     * 
     * B      38      49      65      97      13      27      49     79
     *        i(low)                                  j(high)
     * 
     * A      13      27
     *                k
     */
    for (i = low, j = mid + 1, k = i; (i <= mid) && (j <= high); ++k)
    {
        if (B[i] <= B[j])
        {
            A[k] = B[i++];
        }
        else
        {
            A[k] = B[j++];
        }
    }

    /* 说明右半段归并完了, 剩下左半段, 将左半段剩下内容复制到 A. */
    while (i <= mid)
    {
        A[k++] = B[i++];
    }
    while (j <= high)
    {
        A[k++] = B[j++];
    }

    return;
}

void BuildMaxHeap(ElemType A[], int len)
{
    /* 从 i = n/2 到 1, 反复调整堆, 直至建成大根堆. */
    for (int i = len / 2; i > 0; --i)
    {
        HeapAdjust(A, i, len);
    }

    return;
}

void HeapAdjust(ElemType A[], int parent, int len)
{
    /* A[0] 暂存子树根结点. */
    A[0] = A[parent];

    /* 从子树根结点开始, 一直沿着较大的子结点向下调整. */
    for (int child = 2 * parent; child <= len; child *= 2)
    {
        /**
         * 使用线性表存储树, 若亲结点索引为 i, 则左右子结点索引分别为 2*i 和
         * 2*i+1.
         */
        /* 在合适范围内, 若左子小于右子. */
        if (child < len && A[child] < A[child + 1])
        {
            /* 则取较大的右子. */
            ++child;
        }
        /* 好, 选出了最大子结点. 若亲结点大于最大子结点, 则没有调整的必要, 跳出. */
        if (A[0] > A[child])
        {
            break;
        }
        /* 亲结点小于最大子结点. */
        else
        {
            /* 将子结点调整到亲结点上. */
            A[parent] = A[child];

            /**
             * 同时更新亲结点索引, 即将亲结点向下移动. 之后 for 循环更新子结点为
             * 新的亲结点的子结点.
             */
            parent = child;
        }
    }

    /* 将被筛选的结点放入最终位置. */
    A[parent] = A[0];

    return;
}

void HeapSort(ElemType A[], int len)
{
    /* 建立大根堆. */
    BuildMaxHeap(A, len);

    /* n-1 趟交换和堆调整过程. */
    for (int i = len; i > 1; --i)
    {
        /* 通过交换堆顶和堆底元素来输出堆顶元素. */
        Swap(&A[i], &A[1]);

        /* 把剩下的 n-1 个元素整理成堆. */
        HeapAdjust(A, 1, i - 1);
    }

    return;
}

void SelectionSort(ElemType A[], int len)
{
    /* 一共进行 n-1 趟. */
    for (int i = 0; i < len; ++i)
    {
        /* 记录最小元素的位置. */
        int min = i;

        /* 在 [i,len-1] 中选择最小的元素. */
        for (int j = i + 1; j < len; ++j)
        {
            /* 更新最小元素的位置. */
            if (A[j] < A[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            Swap(&A[min], &A[i]);
        }
    }
}

void Swap(ElemType *A, ElemType *B)
{
    ElemType temp = *A;
    *A = *B;
    *B = temp;

    return;
}
