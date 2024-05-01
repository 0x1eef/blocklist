#include "block.h"

struct block* blocks_all(const char*);
struct block* blocks_enabled(block blocks[]);
struct block* blocks_disabled(block blocks[]);
struct block* blocks_group(block blocks[], const char*);
size_t blocks_size(block blocks[]);
