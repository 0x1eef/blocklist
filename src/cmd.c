#include <blocklist.pf/fetch.h>
#include <blocklist.pf/file.h>
#include <blocklist.pf/cmd.h>
#include <blocklist.pf/set.h>
#include <blocklist.pf/dyn_array.h>
#include <blocklist.pf/hash.h>
#include <blocklist.pf/path.h>

void
fetch_cmd(void)
{
  dyn_array *ary;
  char *dir, *pth;
  dir = blocklistpf_dir();
  for (int i = 0; i < (int)(sizeof(BLOCKLISTS) / sizeof(BLOCKLISTS[0])); i++)
  {
    blocklist bl = BLOCKLISTS[i];
    pth = join_path(dir, bl.filename, NULL);
    ary = fetch_blocklist(&bl);
    if (ary == NULL) {
      fprintf(stderr, "Network error: %s\n", fetchLastErrString);
      continue;
    }
    mkdir_p(dir);
    write_file(pth, ary);
    printf("Write: %s\n", pth);
  }
}


void
cat_cmd(void)
{
  char *str, *dir;
  htable *table;
  dyn_array *blocklists;
  hitem item, *fitem;
  size_t bl_size;
  struct Set set = RB_INITIALIZER(&set);
  bl_size = sizeof(BLOCKLISTS) / sizeof(BLOCKLISTS[0]);
  table = group_blocklists(BLOCKLISTS, bl_size);
  dir = blocklistpf_dir();
  for (int i = 0; i < (int)(sizeof(TABLES) / sizeof(TABLES[0])); i++)
  {
    item.key = (char *)TABLES[i];
    hsearch_r(item, FIND, &fitem, table);
    printf("table <%s> {\n", fitem->key);
    blocklists = fitem->data;
    for (int j = 0; j < blocklists->size; j++)
    {
      blocklist *bl;
      dyn_array *file;
      bl = blocklists->items[j];
      printf("##\n# %s\n# %s\n# %s\n", bl->name, bl->desc, bl->url);
      file = read_file(join_path(dir, bl->filename, NULL));
      file = filter_file(file, &set);
      str = format_file(file, 3);
      printf("%s", str);
      free(str);
    }
    printf("}\n");
    free_set(&set);
  }
}
