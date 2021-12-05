/**
 * @file graphtype.h
 * @author tianshihao4944@126.com
 * @brief 图类型. 重复声明枚举器报错, 故在一个头文件中声明图类型.
 * @version 0.1
 * @date 2020-09-16
 * @copyright Copyright (c) 2020
 */

#ifndef GRAPHTYPE_H
#define GRAPHTYPE_H

typedef enum GraphType {
  DG = 1,  /* Digraph, 有向图. */
  DN = 2,  /* Dinet, 有向网/有向带权图. */
  UDG = 3, /* Undigraph, 无向图. */
  UDN = 4  /* Undinet, 无向网/无向带权图. */
} GraphType;

#endif /* GRAPHTYPE_H */