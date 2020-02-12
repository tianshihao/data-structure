/*******************************************************************************
 * @file  : array.h
 * @brief : 数组
 * @author: 田世豪
 * @date  : 2020-1-30
 * ****************************************************************************/

#include "predefconst.h"

#include <stdarg.h>

typedef struct Array
{
    // 数组元素基址, 由 InitArray 分配
    ElemType *base;

    // 数组维数
    int dim;

    // 数组维界基址, 由 InitArray 分配
    // 存储每一维度的长度
    int *bounds;

    // 数组映像函数常量基址, 由 InitArray 分配
    // https://blog.csdn.net/panglinzhuo/article/details/79397277
    // 教材 92 页图 5.2 (b)
    // constants[i] = constants[i + 1] * bounds[i + 1]
    int *constants;
} Array;

// 若维数 dim 和随后的各维长度合法, 则构造相应的数组 A, 并返回 OK.
Status InitArray(Array *A, int dim, ...)
{
    if ((dim < 1) || (dim > MAX_ARRAY_DIM))
        return ERROR;

    A->dim = dim;

    A->bounds = (int *)malloc(dim * sizeof(int));

    if (!A->bounds)
        exit(OVERFLOW);

    // 若各维长度合法, 则存入 A->bounds, 并求出 A 的元素总数 elem_total
    int elem_total = 1;

    // ap 是 va_list 类型, 是存放变长参数表信息的数组
    va_list ap;

    // ! 若要使用 val_start 需要在其所在的函数参数列表后面加 ...
    va_start(ap, dim);

    for (int i = 0; i < dim; ++i)
    {
        A->bounds[i] = va_arg(ap, int);
        if (A->bounds[i] < 0)
            return UNDERFLOW;

        elem_total *= A->bounds[i];
    }

    va_end(ap);

    A->base = (ElemType *)malloc(elem_total * sizeof(ElemType));

    if (!A->base)
        exit(OVERFLOW);

    // 求映像函数的常数 ci, 并存入 A->constants[i - 1], i = 1, ..., dim
    A->constants = (int *)malloc(dim * sizeof(int));

    if (!A->constants)
        exit(OVERFLOW);

    // L = 1, 指针的增减以元素的大小为单位
    A->constants[dim - 1] = 1;

    for (int i = dim - 2; i >= 0; --i)
        A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];

    return OK;
} // InitArray

// 销毁数组 A.
Status DestoryArray(Array *A)
{
    if (!A->base)
        return ERROR;
    free(A->base);
    A->base = NULL;

    if (!A->bounds)
        return ERROR;
    free(A->bounds);
    A->bounds = NULL;

    if (!A->constants)
        return ERROR;
    free(A->constants);
    A->constants = NULL;

    return OK;
} // DestoryArray

// 若 ap 指示的各下标值合法, 则求出该元素在 A 中的相对地址 off.
Status Locate(Array *A, va_list ap, int *off)
{
    *off = 0;

    for (int i = 0; i < A->dim; ++i)
    {
        int ind = va_arg(ap, int);

        // 数组维度越界
        if ((ind < 0) || (ind >= A->bounds[i]))
            return OVERFLOW;

        (*off) += A->constants[i] * ind;
    }

    return OK;
} // Locate

/*******************************************************************************
 * ? stdarg.h 知多少 ? standard argument
 * 使用 stdarg.h 中定义的变量类型 va_list 和三个宏可以实现对函数未知参数(即参数个数可变时)的
 * 获取. 换句话说, 用于存取"变长参数表".
 * a.   可变参数的函数通过在参数列表的末尾使用省略号",..."来定义.
 * b.   获取可变参数的步骤: 
 *      i)      在函数列表末尾使用",..."定义该函数参数中含有可变参数;
 *      ii)     函数中定义 va_list 变量, 用于存储可变参数;
 *      iii)    使用 va_start(va_list ap, last_arg) 启用对可变参数实参的访问,
 *              其中 ap 是 va_list 类型的实例, last_arg 是首个可变参数前紧接的
 *              具名参数(最后一个具名参数), 不代表可变参数的数量!
 *      iv)     使用 va_arg(va_list ap, type) 遍历 ap 中存储的可变参数, 
 *              type 是要遍历的参数类型.
 *      v)      结束对可变函数参数实参的遍历.
 * c.   va_list 可以作为参数传递, 需要用 va_start() 将可变参数存储到 ap 中,
 *      之后便可以传递 ap, 在接受该参数的函数中, 无需再次 va_start(), 直接使用
 *      va_arg() 遍历 ap 即可. 在发送和接受 ap 的函数中好像都无需使用 va_end().
 * ****************************************************************************/

// A 是 n 维数组, e 是元素变量, 随后是 n 的下标值.
// 若个下标不超界, 则 e 赋值为所指定的 A 的元素值, 并返回 OK.
Status Value(Array A, ElemType *e, ...)
{
    va_list ap;
    va_start(ap, *e);

    int result = 0;
    int off = 0;
    if ((result = Locate(&A, ap, &off)) <= 0)
        return result;

    *e = *(A.base + off);

    return OK;
} // Value

// A 是 n 维数组, e 为元素变量, 随后是 n 个下标值.
// 若下标不超界, 则将 e 的值赋给所指定的 A 的元素, 并返回 OK.
Status Assign(Array *A, ElemType e, ...)
{
    va_list ap;
    va_start(ap, e);

    int result = 0;
    int off = 0;

    if ((result = Locate(A, ap, &off)) <= 0)
        return result;

    *(A->base + off) = e;

    return OK;
} // Assign

// 打印数组元素
void PrintArray(Array A)
{
    return;
} // PrintArray