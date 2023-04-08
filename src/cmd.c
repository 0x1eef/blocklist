#include <blocklist.pf/fetch.h>
#include <blocklist.pf/file.h>
#include <blocklist.pf/buffer.h>
#include <blocklist.pf/cmd.h>
#include <blocklist.pf/set.h>
#include <search.h>
#include <blocklist.pf/dyn_array.h>
#include <blocklist.pf/hash.h>

void
fetch_cmd(void) {
  int size;
  buffer *buf;
  size = sizeof(BLOCKLISTS) / sizeof(BLOCKLISTS[0]);
  for (int i = 0; i < size; i++) {
    blocklist bl = BLOCKLISTS[i];
    printf("Fetch: %s\n", bl.url);
    buf = fetch_blocklist(&bl, MAXROWS, MAXCOLS);
    if (buf == NULL) {
      fprintf(stderr, "Network error: %s\n", fetchLastErrString);
      continue;
    }
    write_file(bl.path, buf);
    printf("Write: %s\n", bl.path);
    free_buffer(buf);
  }
}

void
cat_cmd(void) {
  int size;
  char *str;
  buffer *buf;
  htable *table;
  struct Set set = RB_INITIALIZER(&set);
  hitem item, *fitem;
  table = group_blocklists_by_category(BLOCKLISTS);
  size = sizeof(TABLES) / sizeof(TABLES[0]);
  for (int i = 0; i < size; i++) {
    const char *tablen = TABLES[i];
    item.key = (char *)tablen;
    hsearch_r(item, FIND, &fitem, table);
    printf("table <%s> {\n", tablen);
    dyn_array *arr = fitem->data;
    for (int j = 0; j < arr->size; j++) {
      blocklist *bl = arr->items[j];
      printf("##\n# %s\n# %s\n# %s\n", bl->name, bl->desc, bl->url);
      buf = read_file(bl->path, MAXROWS, MAXCOLS);
      buf = filter_buffer(buf, &set);
      str = format_buffer(buf, 3);
      printf("%s", str);
      free_buffer(buf);
      free(str);
    }
    printf("}\n");
    free_set(&set);
  }
}

