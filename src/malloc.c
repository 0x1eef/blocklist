#include <blockem/malloc.h>

void *
safe_malloc(size_t size)
{
  void *ptr;
  errno = 0;
  ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "(fatal): %s", strerror(errno));
    abort();
  }
  return (ptr);
}


void *
safe_realloc(void *ptr, size_t size)
{
  errno = 0;
  ptr = realloc(ptr, size);
  if (ptr == NULL) {
    fprintf(stderr, "(fatal): %s", strerror(errno));
    abort();
  }
  return (ptr);
}
