#include <stdlib.h>
#include <stdio.h>
#include <blockem/malloc.h>
#include <blockem/dyn_array.h>

static char * read_line(FILE *f, int blocks);

dyn_array *
array_init(void)
{
  dyn_array *ary;
  ary = safe_malloc(sizeof(dyn_array));
  ary->size = 0;
  ary->items = safe_malloc(0);
  return (ary);
}


dyn_array *
array_from_file(FILE *f)
{
  dyn_array *ary;
  ary = array_init();
  while (!feof(f))
  {
    array_push(ary, read_line(f, 16));
  }
  return (ary);
}


int
array_push(dyn_array *arr, void *item)
{
  arr->items = safe_realloc(
    arr->items,
    (sizeof(void *) * arr->size) + sizeof(void *)
    );
  arr->items[arr->size++] = item;
  return (arr->size);
}


dyn_array *
array_free_item(dyn_array *arr, int index)
{
  free(arr->items[index]);
  for (int i = index; i < arr->size; i++)
  {
    arr->items[i] = arr->items[i+1];
  }
  arr->items = safe_realloc(
    arr->items,
    (sizeof(void *) * arr->size) - sizeof(void *)
    );
  arr->size--;
  return (arr);
}


char *
read_line(FILE *f, int blksize)
{
  int i, buf;
  char c, *str, *ptr;
  i = 0;
  buf = blksize;
  ptr = str = safe_malloc(sizeof(char[blksize]));
  while ((c = fgetc(f)) != '\n')
  {
    if (i == buf-3) {
      ptr = str = safe_realloc(str, sizeof(char[buf + blksize]));
      ptr += i;
      buf += blksize;
    }
    if (feof(f)) {
      break;
    }
    memcpy(ptr++, &c, sizeof(char));
    i++;
  }
  memcpy(ptr++, "\n", sizeof(char));
  memcpy(ptr, "\0", sizeof(char));
  return (str);
}
