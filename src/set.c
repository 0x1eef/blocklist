#include <blockem/set.h>
#include <stdlib.h>

int
compare_nodes(SetNode *n1, SetNode *n2)
{
  return (strcmp(n1->str, n2->str));
}


void
free_set(struct Set *set)
{
  SetNode *node, *tmp;
  RB_FOREACH_SAFE(node, Set, set, tmp)
  {
    RB_REMOVE(Set, set, node);
    free(node->str);
    free(node);
  }
  RB_INIT(set);
}
