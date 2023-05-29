#include <blockem/fetch.h>
#include <blockem/file.h>
#include <blockem/cmd.h>
#include <blockem/set.h>
#include <blockem/dyn_array.h>
#include <blockem/path.h>
#include <blockem/blocklist.h>

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
      fprintf(stderr, "Network error (%s): %s\n", bl.url, fetchLastErrString);
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
  struct Set set = RB_INITIALIZER(&set);
  dir = blocklistpf_dir();
  for (int i = 0; i < TABLES_LEN; i++)
  {
    dyn_array *bls;
    const char *tbl;
    tbl = TABLES[i];
    bls = group_blocklists(tbl);
    printf("table <%s> {\n", tbl);
    for (int j = 0; j < bls->size; j++)
    {
      blocklist *bl;
      dyn_array *file, *ipset;
      bl = bls->items[j];
      printf("##\n# %s\n# %s\n# %s\n", bl->name, bl->desc, bl->url);
      file = read_file(join_path(dir, bl->filename, NULL));
      ipset = filter_file(file, &set);
      str = format_file(ipset, 3);
      printf("%s", str);
      free(str);
    }
    printf("}\n");
    free_set(&set);
  }
}
