#include <stdlib.h>
#include <blocklist.pf/dyn_array.h>
#include <stdio.h>
#include <blocklist.pf/malloc.h>
#include <blocklist.pf/dyn_array.h>

dyn_array*
array_init(void) {
  dyn_array *ary = malloc(sizeof(dyn_array));
  ary->size = 0;
  ary->items = malloc(0);
  return ary;
}

dyn_array*
array_from_file(FILE *f, int maxcols) {
  char *str;
  dyn_array *ary;
  ary = array_init();
  str = safe_malloc(sizeof(char[maxcols]));
  while(fgets(str, maxcols, f) != NULL) {
    if (strchr(str, '\n') == NULL) {
      strncat(str, "\n", 1);
    }
    array_push(ary, str);
    str = safe_malloc(sizeof(char[maxcols]));
  }
  return ary;
}

int
array_push(dyn_array *arr, void *item) {
  arr->items = realloc(
    arr->items,
    (sizeof(void*) * arr->size) + sizeof(void*)
  );
  arr->items[arr->size++] = item;
  return arr->size;
}

dyn_array*
array_free_item(dyn_array *arr, int index) {
  free(arr->items[index]);
  for (int i = index; i < arr->size; i++) {
    arr->items[i] = arr->items[i+1];
  }
  arr->items = realloc(
    arr->items,
    (sizeof(void*) * arr->size) - sizeof(void*)
  );
  arr->size--;
  return arr;
}
