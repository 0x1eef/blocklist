#pragma once
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void* safe_malloc(size_t size);
void* safe_realloc(void *ptr, size_t size);
