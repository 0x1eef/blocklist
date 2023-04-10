#pragma once
#include <blocklist.pf/dyn_array.h>
#include <blocklist.pf/set.h>
dyn_array* read_file(const char *path, int maxw);
dyn_array* filter_file(dyn_array *file, struct Set *set);
char* format_file(dyn_array *file, int per_line, int maxcols);
int write_file(const char *path, dyn_array *ary);
