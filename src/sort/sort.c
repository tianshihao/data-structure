/**
 * @file sort.c
 * @author tianshihao4944@126.com
 * @brief 排序算法实现
 * @version 0.3
 * @date 2020-11-25
 * @copyright Copyright (c) 2020
 */

#include <sort/sort.h>

void InsertionSort(ElemType arr[], int n)
{
    /**
     * [0]    [1]                       [2, 3, ..., n - 1]
     * pivot  sorted subsequence     unsorted subsequence
     *        j = i - 1                 i = 2
     */
    int i, j;
    // i 是无序子序列的第一个元素 2 开始, 默认将 arr[1] 作为有序子序列.
    // 无序子序列中元素的选取, 第 2 个, 是因为步长为 1, 从有序子序列最后一个元素开始,
    // 使用步长计算拿取哪一个元素, 1 + 1 = 2.
    for (i = 2; i < n; ++i)
    {
        // 无序子序列的第一个元素大于有序子序列的最后一个元素, 有比较的必要.
        if (arr[i] < arr[i - 1])
        {
            // 1. 设置哨兵.  记录这个需要插入的值.
            arr[0] = arr[i];

            // j 从有序子序列的最后一个元素开始.
            // [0, i - 1] 是有序子序列区间.
            for (j = i - 1; arr[j] > arr[0]; --j)
            {
                // 2. 将大于哨兵的元素向后挪动.  填补到被插入元素原来的位置.  j+1
                // 是腾出来的空位.
                arr[j + 1] = arr[j];
            }
            // 3. arr[j] 小于或等于哨兵, 应将哨兵复制插入位置 j + 1.
            arr[j + 1] = arr[0];
        }
    }

    return;
}

void BinaryInsertionSort(ElemType arr[], int n)
{
    int i, j, left, right, mid;

    // 开始在有序子序列中折半查找合适的插入位置. 有序子序列的起始
    // 索引为 1, i - 1.
    // 查找进行到最后一趟时, 不论区间长度奇偶, 一定出现 left == right == mid,
    // 此时有 2 种情况:
    // 1) 哨兵小于 mid 所指元素, 那么 right = mid - 1 == right - 1,
    // right < left, 循环结束;
    // 2) 哨兵大于 mid 所指元素, 那么 left = mid + 1 == left + 1,
    // right < left, 循环结束.
    // 这 2 种情况下, 都有 left == right + 1, 即 left 所指的元素大于哨兵,
    // right 所指的元素小于哨兵, 故插入位置在 left 和 right 之间, 应将
    // right 之前的元素后移, right + 1 插入哨兵.
    //
    // 初始
    // 0(pivot)  [1          left/mid/right       i - 1] [i    n]
    // 情況 1:
    // pivot < arr[mid] right = mid - 1 == right - 1
    // 0(pivot)  [1       right  left             i - 1] [i    n]
    //                         ⬆
    // 情況 2:
    // pivot > arr[mid] left = mid + 1 == left + 1
    // 0(pivot)  [1              right  left      i - 1] [i    n]
    //                                ⬆
    //
    // 由于 left, right 是指向有序子序列的, 因此, arr[left] > arr[right].

    // 从无序子序列的第一个元素 arr[2] 开始.
    for (i = 2; i < n; ++i)
    {
        if (arr[i] < arr[i - 1])
        {
            // 记录哨兵.
            arr[0] = arr[i];

            // 折半查找指针.
            left = 1, right = i - 1;
            // ! 注意, 这里一定是小于等于.
            while (left <= right)
            {
                mid = (left + right) / 2;
                // 合适的插入位置落在左半区间.  此处的 > 保证排序稳定.
                if (arr[mid] > arr[0])
                {
                    right = mid - 1;
                }
                // 合适的位置落在了右半区间.
                else
                {
                    left = mid + 1;
                }
            }
            // 折半查找之后, right + 1 即为要插入的位置. 统一将元素后移, 空出插入位置.
            // 从 i - 1 有序子序列的最后一个元素开始, 向后移动元素,
            // 移动区间为 [right + 1, i - 1].
            // 最后 arr[right + 1] 即为插入位置.
            for (j = i - 1; j >= right + 1; --j)
            {
                arr[j + 1] = arr[j];
            }
            // 将哨兵复制到插入位置.
            arr[right + 1] = arr[0];
        }
    }

    return;
}

void ShellSort(ElemType arr[], int n)
{
    /**
   * 在直接插入排序的基础上, 外面套一层步长 delta 循环, 里面将直接插入排序代码
   * 中所有的 1 替换成 delta. 包括 i = 2 = 1 + 1 => i = 1+delta, --j => j-=
   * delta.
   */
    int i, j, delta;
    for (delta = n / 2; delta >= 1; delta /= 2)
    {
        for (i = 1 + delta; i < n; ++i)
        {
            if (arr[i] < arr[i - delta])
            {
                arr[0] = arr[i];
                // 注意这里步长的取值可能导致数组越界, 因此条件加上 j > 0.
                for (j = i - delta; (j > 0) && (arr[j] > arr[0]); j -= delta)
                {
                    arr[j + delta] = arr[j];
                }
                arr[j + delta] = arr[0];
            }
        }
    }

    return;
}

void BubbleSort(ElemType arr[], int n)
{
    // [0, i] 是已排序的有序区间.
    for (int i = 0; i < n; ++i)
    {
        // 是否发生交换的标记.
        Status swapped = FALSE;

        for (int j = n - 1; j > i; --j)
        {
            // 若出现逆序.
            if (arr[j] < arr[j - 1])
            {
                // 交换元素.
                ElemType temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;

                // 更新标记.
                swapped = TRUE;
            }
        }
        // 若一趟排序下来没有发生交换, 则结束算法.
        if (swapped == FALSE)
        {
            return;
        }
    }

    return;
}

void QuickSort(ElemType arr[], int low, int high)
{
    if (low < high)
    {
        // 划分.
        int pivot_pos = Partition(arr, low, high);

        // 依次对两个子表进行排序.
        QuickSort(arr, low, pivot_pos - 1);
        QuickSort(arr, pivot_pos + 1, high);
    }

    return;
}

int Partition(ElemType arr[], int low, int high)
{
    // 将枢轴设置为当前表的第一个元素.
    ElemType pivot = arr[low];

    while (low < high)
    {
        // 将比枢轴小的元素移动到左端.
        while (low < high && arr[high] >= pivot)
        {
            --high;
        }
        arr[low] = arr[high];

        // 将比枢轴大的元素移动到右端.
        while (low < high && arr[low] <= pivot)
        {
            ++low;
        }
        arr[high] = arr[low];
    }

    // 将枢轴放到最终位置.
    arr[low] = pivot;

    // 返回存放枢轴的最终位置.
    return low;
}

void MergeSort(ElemType arr[], int low, int high, int n)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        MergeSort(arr, low, mid, n);
        MergeSort(arr, mid + 1, high, n);

        Merge(arr, low, mid, high, n);
    }

    return;
}

void Merge(ElemType arr[], int low, int mid, int high, int n)
{
    /**
     * 辅助数组 buffer, 用于存储本次归并之前的序列. 相当于将排序操作的对象变成 buffer,
     * 而原数组 arr 存储每次归并操作之后的结果, 即更新了数组 arr.
     */
    ElemType buffer[n];

    int i = 0, j = 0, write_ptr = 0;

    // 将 arr 中的元素复制到 buffer 中.
    for (write_ptr = low; write_ptr <= high; ++write_ptr)
    {
        buffer[write_ptr] = arr[write_ptr];
    }

    /**
     * 将待排序子序列 buffer[low, high] 分为两段, 设比较指针 i, j 和写入指针 write_ptr.
     * 指针 i = low 指向左半段的开始, 指针 j = mid + 1 指向右半段的开始,
     * 
     * 指针 write_ptr 指向原数组 arr 的待排序子序列开始.  然后每次从两个段中各取出一个元素
     * 进行比较, 讲较小者放入数组 arr, 即 arr[write_ptr] = min(buffer[i], buffer[j]).
     * 以最后一次归并为例, 比较数组 buffer 的左右两段, 每次各取出一个元素 buffer[i] == 38
     * 和 buffer[j] == 13, 比较 buffer[i] 和 buffer[j], 将较小的 buffer[j] == 13
     * 放入 arr[write_ptr].  指针 j++, write_ptr++.
     * 
     * 此时数组 arr 和空数组没有差别, 只是存储归并排序后的结果.
     *
     *            left == low              mid     right == mid + 1       high
     * buffer     [38      49      65      97]    [13      27      49     79]
     *             i(low)                          j(mid + 1)
     *
     * arr        [13                                                       ]
     *        write_ptr
     * 
     *                        ⬇  进行比较, 13 < 38  ⬇
     *
     * buffer     [38      49      65      97]    [13      27      49     79]
     *             i                               j  ->   j
     *
     * arr        [13      27      __      __      __      __      __     __]
     *      write_ptr  ->  write_ptr
     */

    // 比较 buffer 的左右两段中的元素.
    for (i = low, j = mid + 1, write_ptr = i; (i <= mid) && (j <= high); ++write_ptr)
    {
        /* 将较小的值复制到 arr. */
        if (buffer[i] <= buffer[j])
        {
            arr[write_ptr] = buffer[i++];
        }
        else
        {
            arr[write_ptr] = buffer[j++];
        }
    }

    // 说明右半段归并完了, 剩下左半段, 将左半段剩下内容复制到 arr.
    while (i <= mid)
    {
        arr[write_ptr++] = buffer[i++];
    }
    while (j <= high)
    {
        arr[write_ptr++] = buffer[j++];
    }

    return;
}

void BuildMaxHeap(ElemType A[], int len)
{
    // 从 i = n/2 到 1, 反复调整堆, 直至建成大根堆.
    for (int i = len / 2; i > 0; --i)
    {
        /* 以 i 为根将 A 调整为大根堆. */
        HeapAdjust(A, i, len);
    }

    return;
}

void HeapAdjust(ElemType arr[], int root, int len)
{
    /* arr[0] 暂存子树根结点. */
    arr[0] = arr[root];

    /* 从子树根结点开始, 一直沿着较大的子结点向下调整. */
    for (int child = 2 * root; child <= len; child *= 2)
    {
        /**
         * 使用线性表存储树, 若亲结点索引为 i, 则左右子结点索引分别为 2 * i 和
         * 2 * i + 1.
         */
        // 在合适范围内, 若左子小于右子.
        if (child < len && arr[child] < arr[child + 1])
        {
            // 则取较大的右子.
            ++child;
        }
        // 好, 选出了最大子结点. 若亲结点大于最大子结点, 则没有调整的必要, 跳出.
        if (arr[root] > arr[child])
        {
            break;
        }
        // 亲结点小于最大子结点.
        else
        {
            // 将子结点调整到亲结点上.
            arr[root] = arr[child];

            // 同时更新亲结点索引, 即将亲结点向下移动 Shift down.
            // 之后 for 循环更新子结点为新的亲结点的子结点.
            root = child;

            // 这里先不调整子结点的值, 当子结点作为新的根结点后, 新的子结点和新的根结点原来的值做比较.
        }
    }

    // 将被筛选的结点放入最终位置.
    arr[root] = arr[0];

    return;
}

void HeapSort(ElemType arr[], int len)
{
    // 建立大根堆.  此时根结点 arr[1] 是最大值.
    BuildMaxHeap(arr, len);

    // n - 1 趟交换和堆调整过程.
    for (int i = len; i > 1; --i)
    {
        // 通过交换堆顶和堆底元素来输出堆顶元素.
        Swap(&arr[i], &arr[1]);

        // 把剩下的 n - 1 个元素整理成堆.  相当于排序之后, 后面的结点从树中排除, 所以是 i - 1.
        HeapAdjust(arr, 1, i - 1);
    }

    return;
}

void SelectionSort(ElemType arr[], int len)
{
    // 一共进行 n-1 趟.
    for (int i = 0; i < len; ++i)
    {
        // 记录最小元素的位置.
        int min = i;

        // 在 [i,len-1] 中选择最小的元素.
        for (int j = i + 1; j < len; ++j)
        {
            // 更新最小元素的位置.
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            Swap(&arr[min], &arr[i]);
        }
    }

    return;
}

void Swap(ElemType *a, ElemType *b)
{
    ElemType temp = *a;
    *a = *b;
    *b = temp;

    return;
}

void BidirectionalBubbleSort(ElemType arr[], int n)
{
    int low = 0, high = n - 1;
    Status flag = TRUE;

    while (low < high && flag)
    {
        // 每趟初始设置 falg 为 FALSE.
        flag = FALSE;
        // 从前向后冒泡.
        for (int i = low; i < high; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                // 发生交换, 置 flag 为 TRUE
                Swap(&arr[i], &arr[i + 1]);
                flag = TRUE;
            }
        }
        // 更新上界.
        --high;
        // 从后向前冒泡.
        for (int i = high; i > low; --i)
        {
            if (arr[i] < arr[i - 1])
            {
                Swap(&arr[i], &arr[i - 1]);
                flag = TRUE;
            }
        }
        // 更新下界.
        ++low;
    }

    return;
}

void Move(ElemType A[], int n)
{
    int i = 0, j = n - 1;

    while (i < j)
    {
        // 从前往后找一个偶数元素.
        while (i < j && i % 2 != 0)
        {
            ++i;
        }
        // 从后往前找一个奇数元素.
        while (i < j && j % 2 != 1)
        {
            --j;
        }
        if (i < j)
        {
            Swap(&A[i], &A[j]);
        }
        ++i, --j;
    }

    return;
}

int KthElem(ElemType A[], int low, int high, int k)
{
    // 由于划分会修改 low 和 high 而递归时有需要它们, 故在这里暂存.
    int lowTemp = low, highTemp = high;

    // 快速排序的一趟划分.
    int pivot = A[low];
    while (low < high)
    {
        while (low < high && A[high] >= pivot)
        {
            --high;
        }
        A[low] = A[high];
        while (low < high && A[low] <= pivot)
        {
            ++low;
        }
        A[high] = A[low];
    }
    A[low] = pivot;

    // 若枢轴被放到了第 k 个位置, 即枢轴是第 k 小的元素, 直接返回 pivot.
    if (low == k)
    {
        return pivot;
    }
    // 在前一部分表中递归寻找. low 是枢轴索引, 以此划分.
    else if (low > k)
    {
        return KthElem(A, lowTemp, low - 1, k);
    }
    // 在后一部分表中递归寻找.
    else
    {
        return KthElem(A, low + 1, highTemp, k);
    }
}

void FlagArrange(Color A[], int n)
{
    /* 设置三个指针, i 之前的元素全为红色, k 之后的元素全为蓝色, j
   * 指向当前扫描元素. */
    int i = 0, j = 0, k = n - 1;

    while (i < k)
    {
        /* 判断条块的颜色. */
        switch (A[j])
        {
        case RED:
        {
            Swap(&A[i], &A[j]);
            ++i;
            ++j; /* 交换之前 i 指向的一定是白色, 所以交换后 j++. */
            break;
        }
        case WHITE:
        {
            j++;
            break;
        }
        case BLUE:
        {
            Swap(&A[j], &A[k]);
            --k;
        }
        }
    }

    return;
}
