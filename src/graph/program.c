﻿/**
 * @file program.c
 * @author tianshihao4944@126.com
 * @brief 第七章代码测试.
 * @version 0.1
 * @date 2020-09-12
 * @copyright Copyright (c) 2020
 */

#include <graph/algraph/algraph.h>
#include <graph/mgraph/mgraph.h>

void WriteGraph(MGraph *G);
void ReadGraph(MGraph *G);
Status MyVisit(VertexType v);
void UseMgraph();
void UseAlgraph();

int main() {
  UseMgraph();
  // UseAlgraph();

  system("pause");

  return 0;
}

void UseMgraph() {
  MGraph G;

  CreateGraphM(&G);

  PrintGraphM(G);

  FloydM(G);

  return;
}

void UseAlgraph() {
  ALGraph G;

  CreateGraphAL(&G);

  DFSTraverse_AL(G, MyVisit);
  printf("\n");
  BFSTraverse_AL(G, MyVisit);
  printf("\n");

  PrintGraph_AL(G);

  return;
}

void WriteGraph(MGraph *G) {
  FILE *fp = fopen("./mgraph.bin", "wb");

  fwrite(G, sizeof(*G), 1, fp);

  fclose(fp);

  return;
}

void ReadGraph(MGraph *G) {
  FILE *fp = fopen("./mgraph.bin", "rb");

  fread(G, sizeof(*G), 1, fp);

  return;
}

Status MyVisit(VertexType v) {
  printf("%d ", v);

  return OK;
}
