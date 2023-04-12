#include <stdlib.h>
#include <stdio.h>
#include <blocklist.pf/malloc.h>
#include <blocklist.pf/dyn_array.h>

static char* read_line(FILE *f, int blocks);

dyn_array*
array_init(void) {
  dyn_array *ary;
  ary = safe_malloc(sizeof(dyn_array));
  ary->size = 0;
  ary->items = safe_malloc(0);
  return ary;
}

dyn_array*
array_from_file(FILE *f) {
  dyn_array *ary;
  ary = array_init();
  while(!feof(f)) {
    char *line;
    line = read_line(f, 16);
    if (line) {
      array_push(ary, line);
    }
  }
  return ary;
}

int
array_push(dyn_array *arr, void *item) {
  arr->items = safe_realloc(
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
  arr->items = safe_realloc(
    arr->items,
    (sizeof(void*) * arr->size) - sizeof(void*)
  );
  arr->size--;
  return arr;
}

char*
read_line(FILE *f, int blksize) {
  int i, buf;
  char c, *str, *ptr;
  i = 0;
  buf = blksize;
  ptr = str = safe_malloc(sizeof(char[blksize]));
  while((c = fgetc(f)) != EOF) {
    ptr = mempcpy(ptr, &c, sizeof(char));
    if (i+1 == buf-1) {
      ptr = str = safe_realloc(str, sizeof(char[buf + blksize]));
      ptr += i;
      buf += blksize;
    }
    if (c == '\n') {
      break;
    }
    i++;
  }
  if (i == 0) {
    free(str);
    return NULL;
  } else {
    memcpy(ptr, "\0", sizeof(char));
    return str;
  }
}
