#pragma once
#include <blocklist.pf/dyn_array.h>
#include <stdlib.h>

typedef struct {
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *filename;
  const char *format;
} blocklist;


extern const char* TABLES[5];
extern blocklist BLOCKLISTS[11];
dyn_array* group_blocklists(const char*);
