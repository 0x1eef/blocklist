#include <blocks/alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <errno.h>

void *
alloc(size_t size)
{
  void *mem;
  mem = malloc(size);
  if (mem == NULL)
  {
    fprintf(stderr, "error: malloc error\n");
    exit(EX_OSERR);
  }
  return (mem);
}
