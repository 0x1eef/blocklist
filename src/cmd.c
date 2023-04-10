#include <blocklist.pf/fetch.h>
#include <blocklist.pf/file.h>
#include <blocklist.pf/cmd.h>
#include <blocklist.pf/set.h>
#include <blocklist.pf/dyn_array.h>
#include <blocklist.pf/hash.h>

#define MAXCOLS 200

void
fetch_cmd(void) {
  dyn_array *ary;
  for (int i = 0; i < (int)(sizeof(BLOCKLISTS) / sizeof(BLOCKLISTS[0])); i++) {
    blocklist bl = BLOCKLISTS[i];
    printf("Fetch: %s\n", bl.url);
    ary = fetch_blocklist(&bl, MAXCOLS);
    if (ary == NULL) {
      fprintf(stderr, "Network error: %s\n", fetchLastErrString);
      continue;
    }
    write_file(bl.path, ary);
    printf("Write: %s\n", bl.path);
  }
}

void
cat_cmd(void) {
  char *str;
  htable *table;
  dyn_array *blocklists, *file;
  hitem item, *fitem;
  struct Set set = RB_INITIALIZER(&set);

  table = group_blocklists_by_category(BLOCKLISTS);
  for (int i = 0; i < (int)(sizeof(TABLES) / sizeof(TABLES[0])); i++) {
    item.key = (char *)TABLES[i];
    hsearch_r(item, FIND, &fitem, table);
    printf("table <%s> {\n", fitem->key);
    blocklists = fitem->data;
    for (int j = 0; j < blocklists->size; j++) {
      blocklist *bl;
      bl = blocklists->items[j];
      printf("##\n# %s\n# %s\n# %s\n", bl->name, bl->desc, bl->url);
      file = read_file(bl->path, MAXCOLS);
      file = filter_file(file, &set);
      str = format_file(file, 3, MAXCOLS);
      printf("%s", str);
      free(str);
    }
    printf("}\n");
    free_set(&set);
  }
}

