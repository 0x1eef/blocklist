#pragma once
#include <stdbool.h>
#include <stdio.h>

struct block {
  int id;
  const char *name;
  const char *desc;
  const char *table;
  const char *url;
  const char *www;
  const char *filename;
  const char *format;
  bool enabled;
  char* (*path)(struct block*);
  int (*write)(const char*, const char*);
};

char* block_path(struct block*);
int block_write(const char*, const char*);

#define BLOCKLIST_VERSION "v0.5.1"
#define NULL_BLOCKLIST                                     \
        (struct block) { 0, NULL, NULL, NULL, NULL, NULL, \
                             NULL, NULL, NULL, NULL, NULL, }
typedef struct block block;
