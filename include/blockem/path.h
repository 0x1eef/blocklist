#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/stat.h>

char* blocklistpf_dir(void);
char* join_path(char *str, ...);
int mkdir_p(char *path);
