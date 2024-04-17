#include <blocklist/alloc.h>
#include <blocklist/blocklists.h>
#include <errno.h>
#include <sysexits.h>
#include <isinetaddr.h>
#include <string.h>

static const int MAXLEN = 128;
static char *tablenames[]
    = {"attacks", "malware", "anonymizers", "adware", NULL};
static int write_table_head(FILE *, char *);
static int write_table_body(FILE *, FILE *);
static int write_table_tail(FILE *);
static int write_table_comment(FILE *, block *);

int
emit_command(void)
{
  char **tname   = tablenames;
  block *enabled = blocklists_all("enabled");
  while (*tname != NULL)
  {
    block *blocks = blocklists_group(enabled, *tname);
    block *block  = blocks;
    write_table_head(stdout, *tname);
    write_table_comment(stdout, block);
    while (block->name != NULL)
    {
      char *path = block->path(block->filename);
      FILE *in   = fopen(path, "r");
      if (in == NULL)
        return (EX_IOERR);
      else if (write_table_body(stdout, in))
        return (EX_IOERR);
      else
        free(path);
      block++;
    }
    write_table_tail(stdout);
    free(blocks);
    tname++;
  }
  free(enabled);
  return (EX_OK);
}

static int
write_table_head(FILE *out, char *tname)
{
  fprintf(out, "table <%s> {\n", tname);
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
          "##\n"
          "# %s\n"
          "# %s\n"
          "# %s\n",
          block->name,
          block->desc,
          block->url);
  return 0;
}
