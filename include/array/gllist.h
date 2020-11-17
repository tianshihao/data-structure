/*******************************
 * @file  : glist.h
 * @brief : 广义表
 * @author: 田世豪
 * @date  : 2020-2-8
 * ****************************/

#ifndef GLLIST_H
#define GLLIST_H

#include <status.h>

typedef int AtomType;

typedef enum ElemTag
{
    ATOM,
    LIST
} ElemTag;

typedef struct GLNode
{
    // 公共部分, 用于区分原子结点和表结点
    ElemTag tag;

    // 联合中各变量互斥, 任何成员不会同时有效

    // 原子结点和表结点的联合部分
    // 叫它数据域好了
    union data {
        // atom 是原子的值域, AtomType 由用户定义
        AtomType atom;

        // ptr 是表结点的指针域, ptr.hp 和 ptr. tp 分别指向表头和表尾
        struct ptr
        {
            struct GLNode *hp, *tp;
        } ptr;
    };

    // 相当于线性链表的 next, 指向下一个元素结点
    struct GLNode *tp;
} * GList;

#endif // GLLIST_H
