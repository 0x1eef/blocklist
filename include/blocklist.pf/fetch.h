#pragma once
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <fetch.h>
#include <stdlib.h>
#include <blocklist.pf/dyn_array.h>
#include <blocklist.pf/file.h>
#include <blocklist.pf/blocklist.h>
dyn_array* fetch_blocklist(blocklist *bl, int maxcols);
