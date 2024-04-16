#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <errno.h>
#include <sysexits.h>
#include <isinetaddr.h>
#include <string.h>

static const int MAXLEN = 128;
static char *tables[]   = {"attacks", "malware", "anonymizers", "adware", NULL};
static void table_head(FILE *, char *);
static void table_body(FILE *, struct blocklist[]);
static void table_tail(FILE *);
static void comment(FILE *, struct blocklist *);

int
emit_command(void)
{
  char **cursor;
  struct blocklist *enabled;
  cursor  = tables;
  enabled = blocklists_all("enabled");
  while (*cursor != NULL)
  {
    char *table;
    struct blocklist *blocks;
    table  = *cursor;
    blocks = blocklists_group(enabled, table);
    table_head(stdout, table);
    table_body(stdout, blocks);
    table_tail(stdout);
    cursor++;
    free(blocks);
  }
  free(enabled);
  return (EX_OK);
}

static void
table_head(FILE *fd, char *table)
{
  fprintf(fd, "table <%s> {\n", table);
}

static void
table_body(FILE *fd, struct blocklist blocks[])
{
  struct blocklist *block;
  char buf[MAXLEN];
  block = blocks;
  while (block->name != NULL)
  {
    char *path;
    FILE *file;
    path = block->path(block->filename);
    file = fopen(path, "r");
    if (file)
    {
      comment(fd, block);
      while (fgets(buf, MAXLEN, file))
      {
        buf[strcspn(buf, "\n")] = '\0';
        if (iscidraddr4(buf))
        {
          fprintf(fd, "  %s\n", buf);
        }
      }
      fclose(file);
    }
    free(path);
    block++;
  }
}

static void
table_tail(FILE *fd)
{
  fprintf(fd, "}\n");
}

static void
comment(FILE *fd, struct blocklist *block)
{
  fprintf(fd,
          "##\n"
          "# %s\n"
          "# %s\n"
          "# %s\n",
          block->name,
          block->desc,
          block->url);
}
