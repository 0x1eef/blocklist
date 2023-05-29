#pragma once
#include <blockem/dyn_array.h>
#include <blockem/set.h>
dyn_array* read_file(const char *path);
dyn_array* filter_file(dyn_array *file, struct Set *set);
char* format_file(dyn_array *file, int per_line);
int write_file(const char *path, dyn_array *ary);
