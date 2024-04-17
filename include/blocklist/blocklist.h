#pragma once
#include <stdbool.h>
#include <stdio.h>

struct blocklist {
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *www;
  const char *filename;
  const char *format;
  bool enabled;
  char* (*path)(const char*);
  int (*store)(const char*, const char*);
};

char* blocklist_path(const char*);
int blocklist_store(const char*, const char*);

#define BLOCKLIST_VERSION "v0.3.3"
#define NULL_BLOCKLIST                                     \
        (struct blocklist) { NULL, NULL, NULL, NULL, NULL, \
                             NULL, NULL, NULL, NULL, NULL, }
typedef struct blocklist block;
