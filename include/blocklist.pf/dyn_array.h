#pragma once
typedef struct {
  int size;
  void **items;
} dyn_array;

dyn_array* array_init(void);
int array_push(dyn_array *ary, void *item);
