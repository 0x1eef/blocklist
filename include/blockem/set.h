#pragma once
#include <sys/tree.h>
#include <string.h>

typedef struct SetNode {
  char *str;
  RB_ENTRY(SetNode) node;
} SetNode;

extern int compare_nodes(SetNode *i1, SetNode *i2);
RB_HEAD(Set, SetNode);
RB_PROTOTYPE_STATIC(Set, SetNode, node, compare_nodes)
RB_GENERATE_STATIC(Set, SetNode, node, compare_nodes)
void free_set(struct Set *set);
