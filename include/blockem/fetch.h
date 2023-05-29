#pragma once
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <fetch.h>
#include <stdlib.h>
#include <blockem/dyn_array.h>
#include <blockem/file.h>
#include <blockem/blocklist.h>
dyn_array* fetch_blocklist(blocklist *bl);
