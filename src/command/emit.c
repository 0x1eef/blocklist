#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <errno.h>
#include <sysexits.h>
#include <isinetaddr.h>
#include <string.h>

static const int MAXLEN = 128;
static const char *tablenames[]
    = {"attacks", "malware", "anonymizers", "adware", NULL};
static int write_table_head(FILE *, const char *);
static int write_table_body(FILE *, FILE *);
static int write_table_tail(FILE *);
static int write_table_comment(FILE *, block *);

int
emit_command(void)
{
  const char **name = tablenames;
  block *enabled    = blocklists_all("enabled");
  while (*name != NULL)
  {
    block *blocks = blocklists_group(enabled, *name);
    block *block  = blocks;
    write_table_head(stdout, *name);
    while (block->name != NULL)
    {
      char *path = block->path(block->filename);
      FILE *in   = fopen(path, "r");
      write_table_comment(stdout, block);
      if (in == NULL || write_table_body(stdout, in))
      {
        return (EX_IOERR);
      }
      free(path);
      block++;
    }
    write_table_tail(stdout);
    name++;
    free(blocks);
  }
  free(enabled);
  return (EX_OK);
}

static int
write_table_head(FILE *out, const char *name)
{
  fprintf(out, "table <%s> {\n", name);
  return 0;
}

static int
write_table_body(FILE *out, FILE *in)
{
  char buf[MAXLEN];
  int err = 0;
  errno   = 0;
  while (fgets(buf, MAXLEN, in))
  {
    buf[strcspn(buf, "\n")] = '\0';
    if (iscidraddr4(buf))
    {
      fprintf(out, "  %s\n", buf);
    }
    if (errno)
    {
      err = -1;
      break;
    }
  }
  return err;
}

static int
write_table_tail(FILE *out)
{
  fprintf(out, "}\n");
  return 0;
}

static int
write_table_comment(FILE *out, block *block)
{
  fprintf(out,
          "  ##\n"
          "  # %s\n"
          "  # %s\n"
          "  # www: %s\n"
          "  # raw: %s\n",
          block->name,
          block->desc,
          block->www,
          block->url);
  return 0;
}
