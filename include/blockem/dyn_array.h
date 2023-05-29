#pragma once
#include <stdio.h>

typedef struct {
  int size;
  void **items;
} dyn_array;

dyn_array* array_init(void);
int array_push(dyn_array *ary, void *item);
dyn_array* array_from_file(FILE *f);
dyn_array* array_free_item(dyn_array *arr, int index);
