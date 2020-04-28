/**
 * @file    huffmantree.h
 * @author  田世豪
 * @brief   赫夫曼树
 * @date    2020年4月28日
 * */

#pragma once

#include "stdio.h"
#include "stdlib.h"

typedef struct HTNode
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree; // 动态分配数组存储赫夫曼树.

typedef char **HuffmanCode; // 动态分配数组存储赫夫曼编码表.

// 从赫夫曼树的第 1 到 第 i - 1 个元素中找到最小的两个的索引.
void Select(HuffmanTree HT, int range, int &s1, int &s2)
{
    // 赫夫曼树的 0 号空间未用.
    for (int i = 1; i <= i - 1; ++i)
    {
        // 更新最小.
        if (HT[i].weight < HT[*s1].weight)
        {
            *s1 = i;
        }
        // 更新次小.
        else if ((HT[i].weight >= HT[*s1].weight) && (HT[i].weight < HT[*s2].weight))
        {
            *s2 = i;
        }
    }
} // Select

// 数组 *w 为 n 个结点的权重.
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
    if (n <= 1)
    {
        return;
    }

    // 叶结点有 n 个, 所有结点有 2 * n - 1 个
    int node_number = 2 * n - 1;

    // 为赫夫曼树分配内存, 0号空间未用.
    (*HT) = (HTNode *)malloc(sizeof(node_number + 1) * sizeof(HTNode));

    // 初始化前面的结点
    for (HuffmanTree p = *HT, i = 1; i <= n; ++i, ++p, ++w)
    {
        (*p).weight = w[i];
        (*p).lchild = 0;
        (*p).rchild = 0;
        (*p).parent = 0;
    }

    // 初始化后面的结点
    for (int i = n + 1; i < = m; ++i)
    {
        (*p).weight = 0;
        (*p).lchild = 0;
        (*p).rchild = 0;
        (*p).parent = 0;
    }
    // 建立赫夫曼树
    for (int i = n + 1; i <= node_number; ++i)
    {
        // 从 HT[1, i - 1]  中选择 parent 为 0, 且 weight 最小的两个结点,
        // 其序号分别为 s1, s2.
        int s1 = 1, s2 = 1;

        Select(*HT, i - 1, &s1, &s2);

        // 新建结点, 编号为 i, 为 s1 和 s2 的父结点
        *HT[s1].parent = i;
        *HT[s2].parent = i;
        *HT[i].lchild = s1;
        *HT[i].rchild = s2;
        *HT[i].weight = *HT[s1].weight + *HT[s2].weight;
    }

} // HuffmanCoding