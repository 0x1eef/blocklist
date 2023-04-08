#pragma once
#include <blocklist.pf/hash.h>
#include <blocklist.pf/dyn_array.h>
#include <stdlib.h>

typedef struct {
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *path;
  const char *format;
} blocklist;

extern blocklist BLOCKLISTS[10];
extern const char* TABLES[5];

htable* group_blocklists_by_category(blocklist blocklist[]);
