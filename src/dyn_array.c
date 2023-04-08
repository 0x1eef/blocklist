#include <stdlib.h>
#include <blocklist.pf/dyn_array.h>

dyn_array*
array_init(void) {
  dyn_array *ary = malloc(sizeof(dyn_array));
  ary->size = 0;
  ary->items = malloc(0);
  return ary;
}

int
array_push(dyn_array *arr, void *item) {
  arr->items = realloc(
    arr->items,
    sizeof(arr->items) + sizeof(void*)
  );
  arr->items[arr->size++] = item;
  return arr->size;
}
