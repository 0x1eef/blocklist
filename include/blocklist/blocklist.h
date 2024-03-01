#pragma once
#include <blocklist/dyn_array.h>
#include <stdlib.h>

typedef struct {
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *filename;
  const char *format;
} blocklist;


extern const char* TABLES[6];
extern int TABLES_LEN;
extern blocklist BLOCKLISTS[12];
extern int BLOCKLISTS_LEN;
dyn_array* group_blocklists(const char*);
